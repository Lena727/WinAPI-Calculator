#ifndef TOKEN_H
#define TOKEN_H

#include<stdint.h>

typedef double Number;
typedef wchar_t Operator;
typedef enum __TokenType {
	NUMBER = 1,
	OPERATOR
} __TokenType;

typedef union __TokenData {
	Number num;
	Operator op;
} __TokenData;

typedef struct Token {
	__TokenData data;
	__TokenType type;

	struct Token* next;
} Token;

Token* AllocToken();
void FreeToken(Token* head);
Token* TokenizeA(const char* const expression);
Token* TokenizeW(const wchar_t* const expression);

#endif // !TOKEN_H
