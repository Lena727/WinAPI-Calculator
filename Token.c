#include"Token.h"
#include<string.h>
#include<ctype.h>
#include<Windows.h>

Token* AllocToken() {
	Token* newToken = (Token*)malloc(sizeof(Token));
	if (newToken == NULL) {
		MessageBoxA(0, "Memory allocation failed in AllocToken()", "Error", MB_ICONERROR);
		return NULL;
	}
	return newToken;
}

void FreeToken(Token* head) {
	Token* current = head;
	while (current) {
		Token* next = current->next;
		free(current);
		current = next;
	}
	head = 0;
}

Token* TokenizeA(const char* const expression) {
    Token* head = NULL;
    Token* current = NULL;
    const char* cursor = expression;

    while (*cursor) {
        char lexem = *cursor;

        if (isdigit(lexem) || lexem == '.') {
            Number num = 0;
            double divisor = 1.0;
            int is_fraction = 0;

            while (isdigit(*cursor) || *cursor == '.') {
                if (*cursor == '.') {
                    if (is_fraction) break;
                    is_fraction = 1;
                }
                else {
                    if (is_fraction) {
                        divisor *= 10.0;
                        num += (*cursor - '0') / divisor;
                    }
                    else {
                        num = num * 10 + (*cursor - '0');
                    }
                }
                cursor++;
            }

            Token* newToken = AllocToken();
            if (!newToken) return NULL;
            newToken->type = NUMBER;
            newToken->data.num = num;
            newToken->next = NULL;

            if (!head) head = current = newToken;
            else current = current->next = newToken;
        }
        else if (strchr("+-*/%", lexem)) {
            Token* newToken = AllocToken();
            if (!newToken) return NULL;
            newToken->type = OPERATOR;
            newToken->data.op = lexem;
            newToken->next = NULL;

            if (!head) head = current = newToken;
            else current = current->next = newToken;
            cursor++;
        }
        else {
            cursor++;
        }
    }
    return head;
}

Token* TokenizeW(const wchar_t* const expression) {
    Token* head = NULL;
    Token* current = NULL;
    const wchar_t* cursor = expression;

    while (*cursor) {
        wchar_t lexem = *cursor;

        if (iswdigit(lexem) || lexem == L'.') {
            Number num = 0;
            double divisor = 1.0;
            int is_fraction = 0;

            while (iswdigit(*cursor) || *cursor == L'.') {
                if (*cursor == L'.') {
                    if (is_fraction) break;
                    is_fraction = 1;
                }
                else {
                    if (is_fraction) {
                        divisor *= 10.0;
                        num += (*cursor - L'0') / divisor;
                    }
                    else {
                        num = num * 10 + (*cursor - L'0');
                    }
                }
                cursor++;
            }

            Token* newToken = AllocToken();
            if (!newToken) return NULL;
            newToken->type = NUMBER;
            newToken->data.num = num;
            newToken->next = NULL;

            if (!head) head = current = newToken;
            else current = current->next = newToken;
        }
        else if (wcschr(L"+-*/%", lexem)) {
            Token* newToken = AllocToken();
            if (!newToken) return NULL;
            newToken->type = OPERATOR;
            newToken->data.op = lexem;
            newToken->next = NULL;

            if (!head) head = current = newToken;
            else current = current->next = newToken;
            cursor++;
        }
        else {
            cursor++;
        }
    }
    return head;
}
