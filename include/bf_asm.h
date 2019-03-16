/**
 * @file bf_asm.h
 * @author Gnik Droy
 * @brief File containing various assembly instructions for the commands.
 *
 */
#pragma once

/*
    Some general techniques used.
    1) edi always contains the address in memory of the first cell
    2) esi always contains the index of the current cell
*/


/** The assembly instructions for allocating 30,000 bytes of memory.
    Uses the brk() system call without any library wrappers. 
    NOTE: brk() zeros out memory during first call. No need to initialize to 0.*/
char ALLOCATE_MEMORY[] = ".intel_syntax noprefix\n"
                         "_start:\n"
                         "mov eax,0x2d\n"
                         "xor ebx,ebx\n"
                         "int 0x80\n"
                         "add eax,30000\n"
                         "mov ebx,eax\n"
                         "mov eax,0x2d\n"
                         "int 0x80\n"
                         "mov edi,eax\n"
                         "sub edi,30000\n";

/** The assembly instructions for increasing the current cell pointer. */
char INCREMENT_POINTER[] = "add esi,0x04\n";

/** The assembly instructions for decreasing the current cell pointer. */
char DECREMENT_POINTER[] = "sub esi,0x04\n";

/** The assembly instructions for increasing the value at current cell. */
char INCREMENT[] = "mov eax,edi\n"
                   "add eax,esi\n"
                   "inc byte ptr [eax]\n";

/** The assembly instructions for decreasing the value at current cell. */
char DECREMENT[] = "mov eax,edi\n"
                   "add eax,esi\n"
                   "dec byte ptr [eax]\n";

/** The assembly instructions for starting a loop in bf. LABEL references are not present and are calculated at compile time. */
char LOOP_START[] =
    //"_LABEL_XXXX:\n"
    "mov eax,edi\n"
    "add eax,esi\n"
    "cmp byte ptr [eax],0x00\n"
    //"je _LABEL_XXXX\n";
    "je ";

/** The assembly instructions for ending a loop in bf. LABEL references are not present and are calculated at compile time. */
char LOOP_END[] =
    //"_LABELXXXX:\n"
    "mov eax,edi\n"
    "add eax,esi\n"
    "cmp byte ptr [eax],0x00\n"
    //"jne _LABEL_XXXX\n";
    "jne ";

/** The assembly instructions for the write syscall. Executes the raw syscall. The value is printed to stdout. */
char WRITE_CHAR[] = "mov eax,0x04\n"
                    "xor ebx,ebx\n"
                    "inc ebx\n"
                    "mov ecx,edi\n"
                    "add ecx,esi\n"
                    "xor edx,edx\n"
                    "inc edx\n"
                    "int 0x80\n";

/** The assembly instructions for the read syscall. Executes the raw syscall. The value is stored in the current cell. */
char READ_CHAR[] = "mov eax,0x03\n"
                   "xor ebx,ebx\n"
                   "mov ecx,edi\n"
                   "add ecx,esi\n"
                   "xor edx,edx\n"
                   "inc edx\n"
                   "int 0x80\n";

/** The assembly instructions for the exit syscall. Executes the raw syscall.*/
char SYS_EXIT_CALL[] = "mov eax,0x01\n"
                       "xor ebx,ebx\n"
                       "int 0x80\n";
