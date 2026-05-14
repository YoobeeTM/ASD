//FILE DA MODIFICARE
#include <iostream>
#include "ASD-token.h"

using namespace std;

/**************************************************/
/*      funzioni da implementare                  */
/**************************************************/

//funzione che estrae il prossimo token della string st
//lo mette in tok e modifica st,
//ritorna true se c'era un token da estrarre,
//ritorna false se non c'era niente da estrarre e si e arrivato alla fine di st,
//solleva una eccezione di tipo string se legge un token di tipo sconosciuto
bool nextToken(string &st, token &tok) {
    tok.val = 0;

    while (!st.empty() && st[0] == ' ') {
        st.erase(0, 1);
    }

    if (st.empty()) return false;

    if (isdigit(st[0]) || (st[0] == '-' && st.size() > 1 && isdigit(st[1]))) {
        int i = 0;
        int segno = 1;

        if (st[0] == '-') {
            segno = -1;
            i = 1;
        }

        long long valore_accumulato = 0;
        while (i < (int)st.size() && isdigit(st[i])) {
            valore_accumulato = valore_accumulato * 10 + (st[i] - '0');
            i++;
        }

        if (i < (int)st.size() && st[i] != ' ' && st[i] != ')') {
            throw string("Lexical error");
        }

        tok.val = (int)(valore_accumulato * segno);
        tok.k = NUMERO;
        st.erase(0, i);
        return true;
    }

    char c = st[0];
    if (c == '(') tok.k = PARENTESI_APERTA;
    else if (c == ')') tok.k = PARENTESI_CHIUSA;
    else if (c == '+') tok.k = OP_SOMMA;
    else if (c == '*') tok.k = OP_MOLTIPLICAZIONE;
    else if (c == '-') tok.k = OP_SOTTRAZIONE;
    else throw string("Lexical error");

    st.erase(0, 1);
    return true;
}