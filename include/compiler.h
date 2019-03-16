/**
 * @file compiler.h
 * @author Gnik Droy
 * @brief Function definitions of the main compiler source
 *
 */
#pragma once
#include <stdio.h>

/** The structure which represents the parsed global args.*/
struct globalArgs_t
{
    /** The path to the source brainfuck code.*/
    char *input_file;
    /** The path to the output executable file.*/
    char *output_file;
} globalArgs; ///< The variable which is populated by the parse_args() function.

/**
 * @brief Print the help text
 */
void print_help();

/**
 * @brief Parse the args provided from the command line
 *
 * The globalArgs struct is populated from this function.
 * 
 * @param argc Number of arguments.
 * @param argv The list of arguments.
 */
void parse_args(int argc, char **argv);

/**
 * @brief Verifies if the brainfuck source file is valid
 *
 *  The file seek is set to 0 after the verfication of the source is complete.
 * 
 * @param input_fp The brainfuck input source file.
 */
void verify_syntax(FILE *input_fp);

/**
 * @brief Creates the .s assembly source file that contains the list of assembly instructions for the brainfuck program.
 * 
 * Calls assemble() after checking if the output file could be created.
 * 
 * @param input_fp The brainfuck input source file.
 * @param output_file The .s assembly file.
 */
void create_assembly_source(FILE *input_fp, const char *output_file);

/**
 * @brief Creates the .s assembly source file that contains the list of assembly instructions for the brainfuck program.
 *
 * Writes the assembly instructions by parsing the source and refering to the bf_asm.h constants.
 * 
 * @param input_fp The brainfuck input source file.
 * @param output_fp The .s assembly file.
 */
void assemble(FILE *input_fp, FILE *output_fp);

/**
 * @brief Creates the .o elf file from the .s assembly file.
 * 
 * Calls the GNU assembler 'as'.
 * 
 * @param input_file The file path to the .s assembly file.
 */
void execute_assembler(char *input_file);

/**
 * @brief Creates the executable file from the .o elf file.
 * 
 * Calls the GNU linker 'ld'.
 * 
 * @param input_file The file path to the .o elf file.
 */
void execute_linker(const char *input_file);

/**
 * @brief Creates the executable file from the .o elf file.
 * 
 * Compiles the source.
 * This function calls create_assembly_source(),execute_assembler() and execute_linker() with proper arguments.
 * 
 * @param input_fp The brainfuck source file.
 */
void compile(FILE *input_fp);

/**
 * @brief The main start point of the compiler.
 * 
 * @param argc The number of arguments.
 * @param argv Pointer to the argument list.
 */
int main(int argc, char **argv);