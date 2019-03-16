/**
 * @file stack.c
 * @author Gnik Droy
 * @brief File containing the custom stack implementation.
 *
 */
#include "stack.h"
#include "stddef.h"

struct StackNode *newNode(int jmp_addr, int second_jmp_addr)
{
    struct StackNode *stackNode =
        (struct StackNode *)malloc(sizeof(struct StackNode));
    stackNode->jmp_address = jmp_addr;
    stackNode->second_jmp_address = second_jmp_addr;
    stackNode->next = NULL;
    return stackNode;
}

bool isEmpty(struct StackNode *root)
{
    return !root;
}

void push(struct StackNode **root, int jmp_addr, int second_jmp_addr)
{
    struct StackNode *stackNode = newNode(jmp_addr, second_jmp_addr);
    stackNode->next = *root;
    *root = stackNode;
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