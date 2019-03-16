/**
 * @file stack.c
 * @author Gnik Droy
 * @brief File containing the custom stack implementation.
 *
 */
#include "stack.h"
#include <stddef.h>
#include <stdio.h>

struct StackNode *newNode(int jmp_addr, int second_jmp_addr)
{
    struct StackNode *stack_node =
        (struct StackNode *)malloc(sizeof(struct StackNode));
    if (stack_node == NULL)
    {
        fputs("FATAL: Memory allocation failed.", stderr);
        exit(EXIT_FAILURE);
    }
    stack_node->jmp_address = jmp_addr;
    stack_node->second_jmp_address = second_jmp_addr;
    stack_node->next = NULL;
    return stack_node;
}

bool isEmpty(struct StackNode *root)
{
    return !root;
}

void push(struct StackNode **root, int jmp_addr, int second_jmp_addr)
{
    struct StackNode *stack_node = newNode(jmp_addr, second_jmp_addr);
    stack_node->next = *root;
    *root = stack_node;
}

bool pop(struct StackNode **root)
{
    if (isEmpty(*root))
        return false;
    struct StackNode *temp = *root;
    *root = (*root)->next;
    free(temp);
    return true;
}