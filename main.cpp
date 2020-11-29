#include "assembler.h"

int main(void) {

    // Create the assembler object
    unsigned int num_registers = 6;
    Assembler assembler(num_registers);

    // Program
    assembler.read_program();

    // Print the program
    assembler.print_full_program();

    // Execute the program
    assembler.run();

    // Print the final register configuration
    assembler.print_registers();

    return 0;
}