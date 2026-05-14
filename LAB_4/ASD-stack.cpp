// FILE DA MODIFICARE
#include "ASD-stack.h"

using namespace my_stack;

/**************************************************/
/*      funzioni da implementare                  */
/**************************************************/
/* restituisce lo stack vuoto */
Stack my_stack::createEmpty(){
   Stack sret;
   sret.li = nullptr;
	return sret;
}

/* restituisce true se lo stack e' vuoto */
bool my_stack::isEmpty(const Stack& st){
    return st.li == nullptr;
}

/* aggiunge elem in cima (operazione safe, si può sempre fare) */
/* NB: se stack implementato con array dinamico, 
   quando necessario implementare ridimensionamento in espansione*/
void my_stack::push(const Elem el, Stack& st){
   Node* aux = new Node;
   aux->data = el;
   aux->next = st.li;
   st.li = aux;
}

/* toglie dallo stack l'ultimo elemento e lo restituisce */
/* se lo stack è vuoto solleva una eccezione di tipo string */
/* NB: se stack implementato con array dinamico, 
   quando necessario implementare ridimensionamento in contrazione*/
Elem my_stack::pop(Stack& st){
   if (isEmpty(st)) throw std::string("ERRORE, LO STACK NON CONTIENE ELEMENTI DA ELIMINARE");

   Node* aux = st.li;
   Elem el = aux->data;
   st.li = aux->next;
   delete aux;

   return el;
}
