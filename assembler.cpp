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

std::vector<int> reg = {0, 0, 0, 0, 0, 0};
// void (*FUNCS[4]) (int a, int b, int c) = 
//     {addr, addi, mulr, muli, banr, bani, borr, bori, setr, seti, gtir, gtri, gtrr, eqir, eqri, eqrr};

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

// std::vector<int> instructions;
int instrptrval = 0;



void addr(int a, int b, int c) {
    reg[c] = reg[a] + reg[b];
}

void addi(int a, int b, int c) {

    reg[c] = reg[a] + b;
}

void mulr(int a, int b, int c) {
    reg[c] = reg[a] * reg[b];
}

void muli(int a, int b, int c) {
    reg[c] = reg[a] * b;
}

void banr(int a, int b, int c) {
    reg[c] = reg[a] & reg[b]; 
}

void bani(int a, int b, int c) {
    reg[c] = reg[a] & b;
}

void borr(int a, int b, int c) {
    reg[c] = reg[a] | reg[b]; 
}

void bori(int a, int b, int c) {
    reg[c] = reg[a] | b; 
}

void setr(int a, int b, int c) {
    reg[c] = reg[a]; 
}

void seti(int a, int b, int c) {
    reg[c] = a; 
}

void gtir(int a, int b, int c) {
    if (a > reg[b]) {
        reg[c] = 1;
    }
    else {
        reg[c] = 0;
    }
}

void gtri(int a, int b, int c) {
    if (reg[a] > b) {
        reg[c] = 1;
    }
    else {
        reg[c] = 0;
    }
}
 
void gtrr(int a, int b, int c) {
    if (reg[a] > reg[b]) {
        reg[c] = 1;
    }
    else {
        reg[c] = 0;
    }
}

void eqir(int a, int b, int c) {
    if (a == reg[b]) {
        reg[c] = 1;
    }
    else {
        reg[c] = 0;
    }
}

void eqri(int a, int b, int c) {
    if (reg[a] == b) {
        reg[c] = 1;
    }
    else {
        reg[c] = 0;
    }
}

void eqrr(int a, int b, int c) {
    if (reg[a] == reg[b]) {
        reg[c] = 1;
    }
    else {
        reg[c] = 0;
    }
}


void call(std::string op, int a, int b, int c) {

    // Call the function
    str_to_fp[op](a,b,c);
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
        // Print registers
        // std::cout << "[";
        // for (auto i = reg.begin(); i != reg.end(); ++i)
        //     std::cout << *i << ", ";
        // std::cout << "]"<< std::endl;

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

    // print full program
    std::cout << "\n\n\nPRINTING FULL PROGRAM\n" << std::endl;
    for (int i = 0; i < program.size(); i++) {
        op = program[i][0];
        a = std::stoi(program[i][1]);
        b = std::stoi(program[i][2]);
        c = std::stoi(program[i][3]);
        std::cout << op << " " << a << " " << b << " " << c << std::endl;
    }

    // Read instruction and arguments
    // op = cmds[0];
    // a = std::stoi(cmds[1]);
    // b = std::stoi(cmds[2]);
    // c = std::stoi(cmds[3]);
    // std::cout << op << " " << a << " " << b << " " << c << std::endl;

    // Increment instruction pointer
    // reg[instrptr] += 1
    // instrptrval = reg[instrptr]

    // Index and value of instruction pointer
    int ipval = reg[ip];
    int i, it = 0;

     // Run the program
    while (ipval < program.size()) {
        i = reg[ip]; 

        op = program[i][0];
        a = std::stoi(program[i][1]);
        b = std::stoi(program[i][2]);
        c = std::stoi(program[i][3]);

        call(op, a, b, c);

        // Increment the instruction pointer
        reg[ip]++;
        ipval = reg[ip];
        // std::cout << op << " " << a << " " << b << " " << c << std::endl;
        it++; 

        if (it % 1000000 == 0) {
            std::cout << "Iteration: " << it << std::endl;
                for (auto i = reg.begin(); i != reg.end(); ++i)
                    std::cout << *i << ' ';
                std::cout << std::endl;

        }

        if (it == 9000000)
            break;
    }



    // Print registers
    for (auto i = reg.begin(); i != reg.end(); ++i)
        std::cout << *i << ' ';
    std::cout << std::endl;

    std::cout << "Answer: " << reg[0] << std::endl;





    return 0;
}