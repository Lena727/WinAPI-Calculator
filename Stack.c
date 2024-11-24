#include"Stack.h"
#include<stdlib.h>

Stack* AllocStack() {
	return (Stack*)calloc(1, sizeof(Stack));
}

bool isEmpty(Stack* stack) {
	return stack->top == NULL;
}

void push(Stack* stack, Number value) {
	StackNode* newNode = (StackNode*)calloc(1, sizeof(StackNode));
	if (!newNode) {
		return;
	}
	newNode->data = value;
	newNode->next = stack->top;
	stack->top = newNode;
}

Number pop(Stack* stack) {
	if (isEmpty(stack)) {
		return;
	}
	StackNode* temp = stack->top;
	Number value = temp->data;
	stack->top = temp->next;
	free(temp);
	return value;
}

void FreeStack(Stack** stack) {
	StackNode* current = (*stack)->top;
	StackNode* next;
	while (current) {
		next = current->next;
		free(current);
		current = next;
	}
	free(*stack);
	*stack = NULL;
}