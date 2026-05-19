#include <iostream>

#include "graph.h"

using namespace graph;

struct edgeNode;

struct graph::vertexNode {
  Label city;
  Graph next;
  edgeNode* adjList;
  bool visited ;
};
struct edgeNode {
  Weight distance;
  Graph target;
  edgeNode* next;
};


/**********************************************************************/
/*               Funzione da implementare                             */
/**********************************************************************/
// Restituisce il grafo vuoto
Graph graph::createEmptyGraph(){
  return emptyGraph;
}

// Restituisce il puntatore al vertice data una label l, se non la trova restituisce emptyGraph
Graph findVertex(Label l, Graph g){
  if (isEmpty(g)) return emptyGraph;

  if(g->city == l) return g;

  return findVertex(l, g->next);
}

// Aggiunge nuovo vertice con etichetta la stringa.
// Se non è gia presente, ritorna true, altrimenti fallisce e ritorna false 
bool graph::addVertex(Label l, Graph& g){
  vertexNode* vert = findVertex(l, g);
  if(vert != nullptr) return false;

  Graph vertex = new vertexNode;
  vertex->city = l;
  vertex->next = g;
  vertex->adjList = nullptr;
  vertex->visited = false;

  g = vertex;

  return true;
}

// Aggiunge nuovo arco tra i due vertici con etichette le due stringe e peso
// l'intero. Fallisce se non sono presenti tutti e due i nodi o se l'arco
// tra i due e' gia' presente. Se fallisce ritorna false,
// altrimenti ritorna true
bool graph::addEdge(Label from, Label to, Weight w, Graph& g){
  // Grafo vuoto
  if(isEmpty(g)) return false;

  vertexNode* fromV = nullptr;
  vertexNode* toV = nullptr;

  vertexNode* currV = g; 
  while(fromV == nullptr || toV == nullptr) {
    if(currV == emptyGraph) return false;
    if(currV->city == from) fromV = currV;
    if(currV->city == to) toV= currV;
    currV = currV->next;
  }

  edgeNode* currE = fromV->adjList;
  while(currE != nullptr) {
    if(currE->target->city == to) return false;
    currE = currE->next;
  }

  // Creo gli archi
  edgeNode* fromE = new edgeNode;
  edgeNode* toE = new edgeNode;

  // Imposto peso
  fromE->distance = w;
  toE->distance = w;

  // gli archi puntano al loro corrispondente
  fromE->target = toV;
  toE->target = fromV;

  // Il prossimo elemento e il primo della lista di adiacenza
  fromE->next = fromV->adjList;
  toE->next = toV->adjList;

  // aggiungo in cima alla lista
  fromV->adjList = fromE;
  toV->adjList = toE;

  return true;
}

// Restituisce true se il grafo e' vuoto, false altrimenti
bool graph::isEmpty(const Graph& g){
  return g == emptyGraph;
  
}

// Ritorna il numero di vertici del grafo
unsigned int graph::numVertices(const Graph& g){
  if(isEmpty(g)) return 0;

  return numVertices(g->next) + 1;
}

// Ritorna il numero di archi del grafo
unsigned int graph::numEdges(const Graph& g){
  if(isEmpty(g)) return 0;

  g->visited = true;
  edgeNode* currV = g->adjList;
  while(currV != nullptr) {
    if (!currV->target->visited){
      return numEdges(g);
    }
    currV = currV->next;
  }

  return 1;
}

// Calcola e ritorna (nel secondo parametro) il grado del vertice.
// Restituisce un valore falso se il vertice non esiste,
// altrimenti ritorna true
bool graph::nodeDegree(Label l, unsigned int& degree, const Graph& g) {
  vertexNode* vertex = findVertex(l, g);
  if (isEmpty(vertex)) return false;
  degree = 0;
  edgeNode* currV = vertex->adjList;
  while(currV != nullptr) {
    degree++;
    currV = currV->next;
  }
  return true;
}

// Verifica se due vertici sono adiacenti (ovvero se esiste un arco)
bool graph::areAdjacent(Label v1, Label v2, const Graph& g) {
  vertexNode* vertex = findVertex(v1, g); 
  if(isEmpty(vertex)) return false;
  
  edgeNode* currV = vertex->adjList;
  while(currV != nullptr) {
    if(currV->target->city == v2) return true;
    currV = currV->next;
  }

  return false;
}

// Ritorna la lista di adiacenza di un vertice
// corrispondente alla lista dei label dei vertici adiacenti
list::List graph::adjacentList(Label v1, const Graph& g) {
  // Creo lista vuota
  list::List list = list::createEmpty();

  // Trovo il vertice 
  vertexNode* vertex = findVertex(v1, g); 
  if(isEmpty(vertex)) return list;
  
  // Scorro la lista di adiacenza e aggiungo gli elementi
  edgeNode* currV = vertex->adjList;
  while(currV != nullptr) {
    list::addFront(v1, list);
    currV = currV->next;
  }

  // return lista
  return list;
}

// Calcola, se esiste, un cammino tra due vertici
// Il primo argomento e il vertice di partenza
// Il secondo argomento e il vertice di arrivo
// Il terzo argomento sara la lista delle etichette degli
// vertici visitati sul cammino (senza il vertice di partenza,
// ma con il vertice di arrivo)
// Si assume che il chiamante fornisca inizialmente una lista vuota.
// Il quarto argomento e il peso del cammino
// La funzione ritorna false se non c'e un cammino tra i due vertici
// Se il vertice di partenza e uguale al vertice di arrivo, la funzione
// ritorna true, e il peso e' 0 e la lista e' vuota
bool graph::findPath(Label v1, Label v2, list::List& path, Weight& weight, const Graph& g) {
  return true;
}

// Svuota un grafo
void graph::clear(graph::Graph& g){
 //TODO
}

// Stampa il grafo
// Per ogni vertice stampa su una riga l'etichetta del vertice seguito di ':'
// poi le etichette dei vertici adiacenti con fra parentesi il peso associato,
// separate da virgole
void graph::printGraph(const graph::Graph& g) {
  if(isEmpty(g)) {
    cout << endl;
    return;
  }

  cout << g->city << ":";
  edgeNode* currV = g->adjList;
  while(currV != nullptr) {
    cout << currV->target->city << ",";
    currV = currV->next;
  }

  return printGraph(g->next);
}
