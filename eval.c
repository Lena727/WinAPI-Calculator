#include<math.h>
#include"eval.h"

int priority(Operator op) {
	if (op == L'+' || op == L'-')
		return 1;
	if (op == L'*' || op == L'/' || op == L'%')
		return 2;
	return 0;
}

Number ApplyOp(Number lhs, Number rhs, Operator op) {
	switch (op)
	{
	case L'+':
		return lhs + rhs;
	case L'-':
		return lhs - rhs;
	case L'*':
		return lhs * rhs;
	case L'/':
		if (rhs == 0) {
			return INFINITY;
		}
		return lhs / rhs;
	case L'%':
		return (int)lhs % (int)rhs;
	}
	return 0;
}

Number eval(Token* head) {
	Stack* numStack = AllocStack();
	Stack* opStack = AllocStack();

	Token* current = head;
	while (current) {
		if (current->type == NUMBER) {
			push(numStack, current->data.num);
		} else {
			Operator op = current->data.op;
			while (!isEmpty(opStack) && priority(op) <= priority(opStack->top->data)) {
				Number val2 = pop(numStack);
				Number val1 = pop(numStack);
				Operator topOp = pop(opStack);
				push(numStack, ApplyOp(val1, val2, topOp));
			}
			push(opStack, op);
		}
		current = current->next;
	}

	while (!isEmpty(opStack)) {
		Number val2 = pop(numStack);
		Number val1 = pop(numStack);
		Operator topOp = pop(opStack);
		push(numStack, ApplyOp(val1, val2, topOp));
	}

	Number result = pop(numStack);
	FreeStack(&numStack);
	FreeStack(&opStack);
	return result;
}