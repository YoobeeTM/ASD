// FILE DA MODIFICARE
#include <iostream>
#include <fstream>
#include <string>

#include "ASD-queue-list.h"

using namespace queue;
using namespace std;

//implementazione di una doubly linked list
struct queue::cell{
   Elem el;
   cell *next;
   cell *prev;
};

/**************************************************/
/*      funzioni da implementare                  */
/**************************************************/

/* restituisce la coda vuota */
Queue queue::createEmpty(){
   Queue qret;
   qret.li = nullptr;
   qret.end = nullptr;
   return qret;
}

/* restituisce true se la queue e' vuota */
bool queue::isEmpty(const Queue& q){
   return (q.li == nullptr);
}

/* inserisce l'elemento "da una parte" della coda */
void queue::enqueue(Elem e, Queue& q){
   cell* aux = new cell;
   aux->el = e;
   aux->prev = nullptr; // Essendo in testa, non c'è nulla prima
   aux->next = q.li;    // Punta alla vecchia testa

   if (isEmpty(q)) {
      // Se la coda era vuota, il nuovo nodo è sia inizio che fine
      q.end = aux;
   } else {
      // Se c'erano elementi, la vecchia testa deve puntare indietro al nuovo nodo
      q.li->prev = aux;
   }
   
   // In ogni caso, la testa della coda ora è il nuovo nodo
   q.li = aux;
}

/* cancella l'elemento (se esiste) "dall'altra parte */
/*della coda" e lo restituisce; se la coda è vuota solleva */
/*una eccezione di tipo string*/
Elem queue::dequeue(Queue& q){
   if (isEmpty(q)) throw string("ERRORE, LA LISTA è VUOTA!");

   cell* daEliminare = q.end;
   Elem ret = daEliminare->el;

   // Spostiamo il puntatore end all'indietro
   q.end = q.end->prev;

   if (q.end == nullptr) {
      // Se la coda è diventata vuota, anche li deve diventare nullptr
      q.li = nullptr;
   } else {
      // Altrimenti, il nuovo "ultimo" non deve avere un "next"
      q.end->next = nullptr;
   }

   delete daEliminare;
   return ret;
}

/* restituisce l'elemento in prima posizione (se esiste) senza cancellarlo*/ 
/*se la coda è vuota solleva una eccezione di tipo string*/
Elem queue::first(Queue& q){
   if (isEmpty(q)) throw string("ERRORE, LA LISTA è VUOTA!");
   return q.end->el;
}

/**************************************************/
/*      funzioni implementate                    */
/**************************************************/
/* riempie una coda da file */
Queue queue::readFromFile(std::string name_file){
   ifstream infile;
   string read_data;
   infile.open(name_file);
   Queue qret=createEmpty();
   while (getline (infile,read_data)){
      if(read_data.length()>0){
         enqueue(stoi(read_data),qret);
      } 
   }
   return qret;
}

/* legge il contenuto di una coda da standard input */
Queue queue::readFromStdin(){
   cout << "Inserire una sequenza di numeri separati da spazi seguiti da END per terminare\n";
   Queue qret=createEmpty();
   string read_data;
   cin>>read_data;
   while(read_data!="END"){
      enqueue(stoi(read_data),qret);
      cin>>read_data;
   }
   return qret;
}

/* stampa la coda*/
void queue::print(const Queue& q){
   cout<<tostring(q)<<endl;
}

/* produce una string contenente la coda*/
std::string queue::tostring(const Queue& q){
   string out="";
   out+="{";
   list l=q.li;
   while(l!=EMPTYLIST){
      out+=to_string(l->el);
      if(l!=q.end){
         out+=",";
      }
      l=l->next;
   }
   out+="}";
   return out;
}

