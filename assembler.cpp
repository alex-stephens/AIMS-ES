#include <iostream>
#include <cmath>
#include <map>
#include <vector>
#include <sstream>

void addr(int, int, int);
void addi(int, int, int);
void mulr(int, int, int);
void muli(int, int, int);
void banr(int, int, int);
void bani(int, int, int);
void borr(int, int, int);
void bori(int, int, int);
void setr(int, int, int);
void seti(int, int, int);
void gtir(int, int, int);
void gtri(int, int, int);
void gtrr(int, int, int);
void eqir(int, int, int);
void eqri(int, int, int);
void eqrr(int, int, int);

// Six registers
unsigned int NUM_REGISTERS = 6;
std::vector<int> reg(NUM_REGISTERS, 0);

// Map strings onto operations
std::map<std::string, void (*)(int,int,int)> str_to_fp = {
    {"addi", addi},
    {"addr", addr},
    {"mulr", mulr},
    {"muli", muli},
    {"banr", banr},
    {"bani", bani},
    {"borr", borr},
    {"bori", bori},
    {"setr", setr},
    {"seti", seti},
    {"gtir", gtir},
    {"gtri", gtri},
    {"gtrr", gtrr},
    {"eqir", eqir},
    {"eqri", eqri},
    {"eqrr", eqrr}
};

/*
Add the values from registers a and b. 
*/ 
void addr(int a, int b, int c) {
    reg[c] = reg[a] + reg[b];
}

/*
Add the value from register a with the value b. 
*/ 
void addi(int a, int b, int c) {

    reg[c] = reg[a] + b;
}

/*
Multiply the values from registers a and b. 
*/ 
void mulr(int a, int b, int c) {
    reg[c] = reg[a] * reg[b];
}

/*
Multiply the value from register a with the value b. 
*/ 
void muli(int a, int b, int c) {
    reg[c] = reg[a] * b;
}

/*
Bitwise AND of the values from registers a and b. 
*/ 
void banr(int a, int b, int c) {
    reg[c] = reg[a] & reg[b]; 
}

/*
Bitwise AND of the value from register a with the value b. 
*/ 
void bani(int a, int b, int c) {
    reg[c] = reg[a] & b;
}

/*
Bitwise OR of the values from registers a and b. 
*/ 
void borr(int a, int b, int c) {
    reg[c] = reg[a] | reg[b]; 
}

/*
Bitwise OR of the value from register a with the value b. 
*/ 
void bori(int a, int b, int c) {
    reg[c] = reg[a] | b; 
}

/*
Set the value of register c to the value of register a.
*/
void setr(int a, int b, int c) {
    reg[c] = reg[a]; 
}

/*
Set the value of register c to the value a.
*/
void seti(int a, int b, int c) {
    reg[c] = a; 
}

/*
Set value in register c to 0 or 1 depending if 
the value a is greater than the value in register b.
*/
void gtir(int a, int b, int c) {
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
void gtri(int a, int b, int c) {
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
void gtrr(int a, int b, int c) {
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
void eqir(int a, int b, int c) {
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
void eqri(int a, int b, int c) {
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
void eqrr(int a, int b, int c) {
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
void call(std::string op, int a, int b, int c) {

    // Call the function
    str_to_fp[op](a,b,c);
}

/*
Print the values of all registers.
*/
void print_registers(void) {
    std::cout << "Registers: ";
    for (auto i = reg.begin(); i != reg.end(); ++i)
        std::cout << *i << ", ";
}

/*
Print the full program read from the input file.
*/
void print_full_program(std::vector< std::vector <std::string> > program) {

    std::cout << "\n\n\nPRINTING FULL PROGRAM\n" << std::endl;
    std::string op;
    int a, b, c;
    for (int i = 0; i < program.size(); i++) {
        op = program[i][0];
        a = std::stoi(program[i][1]);
        b = std::stoi(program[i][2]);
        c = std::stoi(program[i][3]);
        std::cout << op << " " << a << " " << b << " " << c << std::endl;
    }
}

int main(void) {

    std::string line, op;
    int a, b, c;
    int ip;

    // Program
    std::vector< std::vector <std::string> > program; 

    // Read program into memory from text file
    while (std::getline(std::cin, line))
    {

        // Instruction pointer initialisation
        if (line.rfind("#ip", 0) != std::string::npos) {
            std::cout << line << std::endl;
            ip = (int) line[4] - '0';
            std::cout << ip << std::endl;
            continue;
        }

        // Split line into separate strings
        std::istringstream iss(line);
        std::vector<std::string> cmds((std::istream_iterator<std::string>(iss)),
                                        std::istream_iterator<std::string>());

        // Add commands to the program
        program.push_back(cmds);
    }

    print_full_program(program);

    // Temporary value of instruction pointer
    int i;

    // Iteration number
    int it = 0;

     // Run the program
    while (reg[ip] < program.size()) {
        i = reg[ip]; 

        op = program[i][0];
        a = std::stoi(program[i][1]);
        b = std::stoi(program[i][2]);
        c = std::stoi(program[i][3]);

        call(op, a, b, c);

        // Increment the instruction pointer
        reg[ip]++;

        // Progress printing
        it++; 
        if (it % 1000000 == 0) {
            std::cout << "Iteration: " << it << std::endl;
                for (auto i = reg.begin(); i != reg.end(); ++i)
                    std::cout << *i << ' ';
                std::cout << std::endl;

        }
    }

    print_registers();
    std::cout << "Answer: " << reg[0] << std::endl;

    return 0;
}