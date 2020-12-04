#include "assembler.h"

int main(void) {

    // Create the assembler object
    unsigned int num_registers = 6;
    Assembler assembler(num_registers);

    // Set max iterations (optional)
    assembler.set_max_iterations(10000000);

    // Read the program from cin into memory
    assembler.read_program();

    // Print the program
    assembler.print_registers();
    assembler.print_full_program();

    // Execute the program
    assembler.run();

    // Print the final register configuration
    assembler.print_registers();

    return 0;
}