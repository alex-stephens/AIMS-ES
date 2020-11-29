#include "assembler.h"


/*
Constructor.
*/ 
Assembler::Assembler(unsigned int nreg) {
    num_registers = nreg;
    for (int i = 0; i < nreg; i++) {
        reg.push_back(0);
    }
}


/*
Set a maximum number of iterations for the program.
*/ 
void Assembler::set_max_iterations(int max_it) {
    if (max_it <= 0) {
        max_iterations = UNLIMITED;
    }
    else {
        max_iterations = max_it;
    }
}


/*
Return true if the maximum number of iterations has been reached.
*/ 
bool Assembler::max_iterations_reached(int it) {
    return (max_iterations != UNLIMITED && it >= max_iterations);
}


/*
Add the values from registers a and b. 
*/ 
void Assembler::addr(int a, int b, int c) {
    reg[c] = reg[a] + reg[b];
}


/*
Add the value from register a with the value b. 
*/ 
void Assembler::addi(int a, int b, int c) {
    reg[c] = reg[a] + b;
}


/*
Multiply the values from registers a and b. 
*/ 
void Assembler::mulr(int a, int b, int c) {
    reg[c] = reg[a] * reg[b];
}


/*
Multiply the value from register a with the value b. 
*/ 
void Assembler::muli(int a, int b, int c) {
    reg[c] = reg[a] * b;
}


/*
Bitwise AND of the values from registers a and b. 
*/ 
void Assembler::banr(int a, int b, int c) {
    reg[c] = reg[a] & reg[b]; 
}


/*
Bitwise AND of the value from register a with the value b. 
*/ 
void Assembler::bani(int a, int b, int c) {
    reg[c] = reg[a] & b;
}


/*
Bitwise OR of the values from registers a and b. 
*/ 
void Assembler::borr(int a, int b, int c) {
    reg[c] = reg[a] | reg[b]; 
}


/*
Bitwise OR of the value from register a with the value b. 
*/ 
void Assembler::bori(int a, int b, int c) {
    reg[c] = reg[a] | b; 
}


/*
Set the value of register c to the value of register a.
*/
void Assembler::setr(int a, int b, int c) {
    reg[c] = reg[a]; 
}


/*
Set the value of register c to the value a.
*/
void Assembler::seti(int a, int b, int c) {
    reg[c] = a; 
}


/*
Set value in register c to 0 or 1 depending if 
the value a is greater than the value in register b.
*/
void Assembler::gtir(int a, int b, int c) {
    if (a > reg[b]) {
        reg[c] = 1;
    }
    else {
        reg[c] = 0;
    }
}


/*
Set value in register c to 0 or 1 depending if 
the value in register a is greater than the value b.
*/
void Assembler::gtri(int a, int b, int c) {
    if (reg[a] > b) {
        reg[c] = 1;
    }
    else {
        reg[c] = 0;
    }
}
 

/*
Set value in register c to 0 or 1 depending if 
the value in register a is greater than the value in register b.
*/
void Assembler::gtrr(int a, int b, int c) {
    if (reg[a] > reg[b]) {
        reg[c] = 1;
    }
    else {
        reg[c] = 0;
    }
}


/*
Set value in register c to 0 or 1 depending if 
the value a is equal to the value in register b.
*/
void Assembler::eqir(int a, int b, int c) {
    if (a == reg[b]) {
        reg[c] = 1;
    }
    else {
        reg[c] = 0;
    }
}


/*
Set value in register c to 0 or 1 depending if 
the value in register a is equal to the value b.
*/
void Assembler::eqri(int a, int b, int c) {
    if (reg[a] == b) {
        reg[c] = 1;
    }
    else {
        reg[c] = 0;
    }
}


/*
Set value in register c to 0 or 1 depending if 
the value in register a is equal to the value in register b.
*/
void Assembler::eqrr(int a, int b, int c) {
    if (reg[a] == reg[b]) {
        reg[c] = 1;
    }
    else {
        reg[c] = 0;
    }
}


/*
Call the function corresponding to opcode op, with arguments
a, b, and c.
*/
void Assembler::call(std::string op, int a, int b, int c) {

    // Call the function
    (this->*STR_TO_FP[op])(a,b,c);
}


/*
Print the values of all registers.
*/
void Assembler::print_registers(void) {
    std::cout << "Register values: [";
    for (auto i = reg.begin(); i != reg.end(); ++i) {
        std::cout << *i;
        if (i != reg.end() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;;
}


/*
Print the full program read from the input file.
*/
void Assembler::print_full_program() {

    std::cout << "\n------------------------------------------------" << std::endl;
    std::cout << "FULL PROGRAM\n" << std::endl;
    std::string op;
    int a, b, c;
    for (int i = 0; i < program.size(); i++) {
        op = program[i][0];
        a = std::stoi(program[i][1]);
        b = std::stoi(program[i][2]);
        c = std::stoi(program[i][3]);
        std::cout << "\t" << op << " " << a << " " << b << " " << c << std::endl;
    }
    std::cout << "------------------------------------------------\n" << std::endl;
}


/*
Read the program from cin into memory.
*/
void Assembler::read_program() {

    std::string line, op;
    int a, b, c;

    // Read program into memory from text file
    while (std::getline(std::cin, line))
    {

        // Instruction pointer initialisation
        if (line.rfind("#ip", 0) != std::string::npos) {
            ip = (int) line[4] - '0';
            std::cout << "\nInstruction pointer initialised to value " << ip << "." << std::endl;
            continue;
        }

        // Split line into separate strings
        std::istringstream iss(line);
        std::vector<std::string> cmds((std::istream_iterator<std::string>(iss)),
                                        std::istream_iterator<std::string>());

        // Add commands to the program
        program.push_back(cmds);
    }
}


/*
Execute the stored program.
*/
void Assembler::run() {

    // Temporary variables
    std::string line, op;
    int i, a, b, c;

    // Iteration number
    int it = 0;

     // Run the program
    while (reg[ip] < program.size()) {
        
        // Current instruction
        i = reg[ip]; 

        // Retrieve opcode and parameters
        op = program[i][0];
        a = std::stoi(program[i][1]);
        b = std::stoi(program[i][2]);
        c = std::stoi(program[i][3]);

        // Execute the instruction
        call(op, a, b, c);

        // Increment the instruction pointer
        reg[ip]++;

        // Progress printing
        it++; 
        if (it % 1000000 == 0) {
            std::cout << "Iteration: " << it << std::endl;
        }

        if (max_iterations_reached(it)) {
            std::cout << "Program terminated after " << it << " iterations." << std::endl;
            break;
        }
    }
}