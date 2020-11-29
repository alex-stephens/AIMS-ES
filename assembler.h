#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <iostream>
#include <cmath>
#include <map>
#include <vector>
#include <sstream>

class Assembler {
public:

    // Constructor
    Assembler(unsigned int nreg = 6);

    // Opcode functions
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

    // Call opcode functions
    void call(std::string op, int a, int b, int c);

    // Program
    void read_program();
    void run();

    // Getters and setters
    void set_max_iterations(int max_it);

    // Printing
    void print_registers();
    void print_full_program();


protected: 

    // Instruction pointer and registers
    unsigned int num_registers;
    int ip;

    // Optional maximum iterations
    int max_iterations = -1;

    // Program (line by line strings)
    std::vector< std::vector <std::string> > program; 

    // Unlimited iterations special value
    int UNLIMITED = -1;

    // Registers
    std::vector<int> reg;

    // Map strings onto operations
    std::map<std::string, void (Assembler::*)(int,int,int)> STR_TO_FP = {
        {"addi", &Assembler::addi},
        {"addr", &Assembler::addr},
        {"mulr", &Assembler::mulr},
        {"muli", &Assembler::muli},
        {"banr", &Assembler::banr},
        {"bani", &Assembler::bani},
        {"borr", &Assembler::borr},
        {"bori", &Assembler::bori},
        {"setr", &Assembler::setr},
        {"seti", &Assembler::seti},
        {"gtir", &Assembler::gtir},
        {"gtri", &Assembler::gtri},
        {"gtrr", &Assembler::gtrr},
        {"eqir", &Assembler::eqir},
        {"eqri", &Assembler::eqri},
        {"eqrr", &Assembler::eqrr}
    };

    // Other helper functions
    bool max_iterations_reached(int it) ;


private:
};

#endif // ASSEMBLER_H
