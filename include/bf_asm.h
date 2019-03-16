/**
 * @file bf_asm.h
 * @author Gnik Droy
 * @brief File containing various assembly instructions for the commands.
 *
 */
#pragma once

/*
    Some general techniques used.
    1) edi always contains the address in memory of the current cell
    2) edx is always 1 (for read and write syscalls).
*/

/** The assembly instructions for allocating 30,000 bytes of memory.
    Uses the brk() system call without any library wrappers. 
    NOTE: brk() zeros out memory during first call. No need to initialize to 0.*/
const char ALLOCATE_MEMORY[] = ".intel_syntax noprefix\n"
                         ".global _start\n"
                         "_start:\n"
                         "mov eax,0x2d\n"
                         "xor ebx,ebx\n"
                         "int 0x80\n"
                         "add eax,30000\n"
                         "mov ebx,eax\n"
                         "mov eax,0x2d\n"
                         "int 0x80\n"
                         "mov edi,eax\n"
                         "sub edi,30000\n"
                         //Sets edx=1 for future read and write calls. This is never modified.
                         "xor edx,edx\n"
                         "inc edx\n";

/** The assembly instructions for increasing the current cell pointer. */
const char INCREMENT_POINTER[] = "add edi,0x%02x\n";

/** The assembly instructions for decreasing the current cell pointer. */
const char DECREMENT_POINTER[] = "sub edi,0x%02x\n";

/** The assembly instruction to increase the value at current cell */
const char INCREMENT[] = "add byte ptr [edi],0x%02x\n";

/** The assembly instruction to decrease the value at current cell */
const char DECREMENT[] = "sub byte ptr [edi],0x%02x\n";

/** The assembly instructions for starting a loop in bf. LABEL references are not present and are calculated at compile time. */
const char LOOP_START[] =
    //"_LABEL_XXXX:\n"
    "cmp byte ptr [edi],0x00\n"
    //"je _LABEL_XXXX\n";
    "je ";

/** The assembly instructions for ending a loop in bf. LABEL references are not present and are calculated at compile time. */
const char LOOP_END[] =
    //"_LABELXXXX:\n"
    "cmp byte ptr [edi],0x00\n"
    //"jne _LABEL_XXXX\n";
    "jne ";

/** The assembly instructions for the write syscall. Executes the raw syscall. The value is printed to stdout. */
const char WRITE_CHAR[] = "mov eax,0x04\n"
                    "xor ebx,ebx\n"
                    "inc ebx\n"
                    "mov ecx,edi\n"
                    "int 0x80\n";

/** The assembly instructions for the read syscall. Executes the raw syscall. The value is stored in the current cell. */
const char READ_CHAR[] = "mov eax,0x03\n"
                   "xor ebx,ebx\n"
                   "mov ecx,edi\n"
                   "int 0x80\n";

/** The assembly instructions for the exit syscall. Executes the raw syscall.*/
const char SYS_EXIT_CALL[] = "mov eax,0x01\n"
                       "xor ebx,ebx\n"
                       "int 0x80\n";
