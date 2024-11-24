#ifndef STACK_H
#define STACK_H

#include"Token.h"
#include<stdbool.h>

typedef struct StackNode {
	Number data;
	struct StackNode* next;
} StackNode;

typedef struct Stack {
	StackNode* top;
} Stack;

Stack* AllocStack();
bool isEmpty(Stack* stack);
void push(Stack* stack, Number value);
Number pop(Stack* stack);
void FreeStack(Stack** stack);

#endif // !STACK_H
