#ifndef EVAL_H
#define EVAL_H

#include"Token.h"
#include"Stack.h"

int priority(Operator op);
Number ApplyOp(Number lhs, Number rhs, Operator op);

Number eval(Token* tokens);

#endif // !EVAL_H
