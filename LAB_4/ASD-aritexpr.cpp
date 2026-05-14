// FILE DA MODIFICARE
#include <string>
#include <iostream>
#include "ASD-aritexpr.h"
#include "ASD-token.h"
#include "ASD-stack.h"

using namespace my_stack;
using namespace std;

/*Calcola il valore intero dell'espressione aritmetica st*/
/*se st non corrisponde ad un expression aritmetica*/
/*solleva un'eccezione di tipo string*/
/*con valore: "Lexical error" se st non è composta da tokens validi*/
/*e valore: "Syntactical error" se st non è ben formata*/
int compute_arithmetic_expr(const string& st) {
    for (char c : st) {
        if (c != '(' && c != ')' && c != ' ' && c != '-' && 
            c != '*' && c != '+' && !isdigit(c)) {
            throw string("Lexical error");
        }
    }

    string stringa = st;
    token tok;
    Stack stack = createEmpty();

    while (nextToken(stringa, tok)) {
        if (tok.k != PARENTESI_CHIUSA) 
		{
            push(tok, stack);
        } 
		else 
		{
            if (isEmpty(stack)) throw string("Syntactical error");
            token n2 = pop(stack);
            
            if (isEmpty(stack)) throw string("Syntactical error");
            token op = pop(stack);
            
            if (isEmpty(stack)) throw string("Syntactical error");
            token n1 = pop(stack);
            
            if (isEmpty(stack)) throw string("Syntactical error");
            token open = pop(stack);

            if (n1.k != NUMERO || n2.k != NUMERO || open.k != PARENTESI_APERTA || 
               (op.k != OP_SOMMA && op.k != OP_SOTTRAZIONE && op.k != OP_MOLTIPLICAZIONE)) {
                throw string("Syntactical error");
            }

            int res;
            if (op.k == OP_SOMMA) res = n1.val + n2.val;
            else if (op.k == OP_SOTTRAZIONE) res = n1.val - n2.val;
            else res = n1.val * n2.val;

            token resTok;
            resTok.k = NUMERO;
            resTok.val = res;
            push(resTok, stack);
        }
    }

    if (isEmpty(stack)) throw string("Syntactical error");
    token finale = pop(stack);

    if (!isEmpty(stack)) throw string("Syntactical error");

    return finale.val;
}
