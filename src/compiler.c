/**
 * @file compiler.c
 * @author Gnik Droy
 * @brief File containing implementation of the compiler.
 *
 */
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include "bf_asm.h"
#include "stack.h"
#include "compiler.h"


void verify_syntax(FILE *inputfp)
{
    char c;
    unsigned int stack_count = 0;
    unsigned int line = 0;
    while ((c = fgetc(inputfp)) != EOF)
    {
        switch (c)
        {
        case ']':
            stack_count--;
            break;
        case '[':
            stack_count++;
            break;
        case '\n':
            line++;
        default:;
        }
        
        if (stack_count < 0)
        {
            fprintf(stderr, "SYNTAX ERROR: Unexpected instruction '%c' in line %u. A corresponding bracket couldn't be found.\n", c, line);
            exit(EXIT_FAILURE);
        }
    }
    if (stack_count > 0)
    {
        fprintf(stderr, "SYNTAX ERROR: Brackets are not balanced. Found %u stray brackets.\n", stack_count);
        exit(EXIT_FAILURE);
    }
    
    fseek(inputfp, 0, SEEK_SET);
}

void assemble(FILE *inputfp, FILE *outputfp)
{

    char c;
    fputs(ALLOCATE_MEMORY, outputfp);
    unsigned int jmp_label = 0;
    struct StackNode *stack = NULL;
    while ((c = fgetc(inputfp)) != EOF)
    {
        switch (c)
        {
        case '+':
            fputs(INCREMENT, outputfp);
            break;
        case '-':
            fputs(DECREMENT, outputfp);
            break;
        case '>':
            fputs(INCREMENT_POINTER, outputfp);
            break;
        case '<':
            fputs(DECREMENT_POINTER, outputfp);
            break;
        case '.':
            fputs(WRITE_CHAR, outputfp);
            break;
        case ',':
            fputs(READ_CHAR, outputfp);
            break;
        case '[':
        {
            push(&stack, jmp_label, jmp_label + 1);
            fprintf(outputfp, "_LABEL_%u:\n", jmp_label);
            fputs(LOOP_START, outputfp);
            fprintf(outputfp, "_LABEL_%u\n", jmp_label + 1);
            jmp_label += 2;
            break;
        }
        case ']':
        {
            fprintf(outputfp, "_LABEL_%u:\n", stack->second_jmp_address);
            fputs(LOOP_END, outputfp);
            fprintf(outputfp, "_LABEL_%u\n", stack->jmp_address);
            pop(&stack);
            break;
        }
        default:;
        }
    }
    fputs(SYS_EXIT_CALL, outputfp);
}

void print_help()
{
    puts("Usage: bf [OPTION] -f [INPUT FILE]\n"
         "Compiles brainfuck code to 32-bit executable file.\n"
         "\nThe cell size is set to 30,000 and one byte is allocated to each cell.\n"
         "\nThe default output file is 'a.out'.\n"
         "This compiler also uses the GNU linker 'ld' and the GNU assembler 'as'.\n"
         "Make sure both of these are installed and in your path before running this program.\n"
         "\nOptions:\n"
         " -f <INPUT FILE>  \t\tSpecifies the input file.\n"
         " -o <OUTPUT FILE> \t\tSpecifies the output file.\n"
         " -h               \t\tDisplay the help message.\n");
}

void parse_args(int argc, char **argv)
{
    globalArgs.output_file = "a.out";
    globalArgs.input_file = NULL;
    int opt;
    while ((opt = getopt(argc, argv, "ho:f:")) != -1)
    {
        switch (opt)
        {
        case 'h':
            print_help();
            exit(EXIT_SUCCESS);
            break;
        case 'o':
            globalArgs.output_file = optarg;
            break;
        case 'f':
            globalArgs.input_file = optarg;
        default:;
        }
    }
    if (globalArgs.input_file == NULL)
    {
        fputs("ERROR: No input file was specified.\n\n", stderr);
        print_help();
        exit(EXIT_FAILURE);
    }
}
void create_assembly_source(FILE *inputfp, const char *assembler_output_file)
{
    FILE *assembler_output_fp = fopen(assembler_output_file, "w");
    if (assembler_output_fp == NULL)
    {
        fprintf(stderr, "The file %s couldn't be opened while assembling code.", assembler_output_file);
        exit(EXIT_FAILURE);
    }
    assemble(inputfp, assembler_output_fp);
    fclose(assembler_output_fp);
}

void execute_assembler(char *assembler_input_file)
{
    const char *start_command = "as --32 ";
    char *command = (char *)malloc(sizeof(char) * (strlen(start_command) + strlen(assembler_input_file) * 2 + 5));
    strcpy(command, start_command);
    strcat(command, assembler_input_file);
    strcat(command, " -o ");
    assembler_input_file[strlen(assembler_input_file) - 1] = 'o';
    strcat(command, assembler_input_file);
    assembler_input_file[strlen(assembler_input_file) - 1] = 's';
    system(command);
    remove(assembler_input_file);
    free(command);
}

void execute_linker(const char *linker_input_file)
{
    const char *start_command = "ld -m elf_i386 ";
    char *command = (char *)malloc(sizeof(char) * (strlen(start_command) + strlen(linker_input_file) * 2 + 4));
    strcpy(command, start_command);
    strcat(command, linker_input_file);
    strcat(command, " -o ");
    strcat(command, globalArgs.output_file);
    system(command);
    remove(linker_input_file);
    free(command);
}

void compile(FILE *inputfp)
{
    int str_size = strlen(globalArgs.output_file) + 3;
    char *input_file = (char *)malloc(str_size * sizeof(char));
    strcpy(input_file, globalArgs.output_file);
    strcat(input_file, ".s");
    create_assembly_source(inputfp, input_file);
    execute_assembler(input_file);
    input_file[strlen(input_file) - 1] = 'o'; //Converting input_file to .o which was created by the assembler.
    execute_linker(input_file);
    free(input_file);
}


int main(int argc, char **argv)
{
    parse_args(argc, argv);
    
    FILE *inputfp = fopen(globalArgs.input_file, "r");

    if (inputfp == NULL)
    {
        fputs("ERROR: The input file couldn't be opened.", stderr);
        exit(EXIT_FAILURE);
    }

    verify_syntax(inputfp);
    compile(inputfp);

    fclose(inputfp);
    return EXIT_SUCCESS;
}