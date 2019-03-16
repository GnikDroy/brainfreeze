/**
 * @file stack.h
 * @author Gnik Droy
 * @brief Custom stack implementation.
 *
 */
#pragma once
#include <stdbool.h>
#include <stdlib.h>

/** A Node on the stack */
struct StackNode
{
    /** The address of loop start */
    unsigned int jmp_address;

    /** The address of loop end */
    unsigned int second_jmp_address;

    /** The address of the next node in stack */
    struct StackNode *next;
};

/**
 * @brief Creates a new node
 *
 * Creates a new node in the stack.
 * Memory is allocated on the heap. 
 * The next stackNode is automatically set to NULL.
 * 
 * @param jmp_addr The jump label index for the start of loop.
 * @param second_jmp_addr The jump label index for the end of loop.
 * @return The new node created.
 */
struct StackNode *newNode(int jmp_addr, int second_jmp_addr);

/**
 * @brief Checks if the stack is empty.
 *
 * @param root The current stack top.
 * @return If stack is empty
 */
bool isEmpty(struct StackNode *root);

/**
 * @brief Push a new node to top of stack
 *
 * @param root The current stack top.
 * @param jmp_addr The jump label index for the start of loop.
 * @param second_jmp_addr The jump label index for the end of loop.
 */
void push(struct StackNode **root, int jmp_addr, int second_jmp_addr);

/**
 * @brief Pop the top of stack and free memory allocated on the heap.
 * The next node becomes the top of the stack.
 *
 * @param root The current stack top.
 */
bool pop(struct StackNode **root);
