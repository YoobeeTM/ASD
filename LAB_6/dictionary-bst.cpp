#include "dictionary.h"

using namespace dict;

//STRUCT TO BE COMPLETED
// *** NON AGGIUNGETE IL PUNTATORE AL PADRE ALLA STRUCT!!!! *** 
struct dict::bstNode {
  Elem e;
  bstNode* rightchild;
  bstNode* leftchild;
};

//Funzione da implementare
bool dict::isEmpty(const Dictionary& d){
  return (d==emptyDictionary);
}
   
//Funzione da implementare
Dictionary dict::createEmptyDict(){
  Dictionary d = emptyDictionary;
  return d;
}
//Funzione da implementare
Error dict::insertElem(const Key k, const Value v, Dictionary& d){
  if (isEmpty(d))
  {
    d = new bstNode;
    d->e.key = k;
    d->e.value = v;
    d->leftchild = emptyNode;
    d->rightchild = emptyNode;

    return OK;
  }
  else
  {
    if (k == d->e.key) return FAIL;
    else if (k < d->e.key)
    {
      return insertElem(k, v, d->leftchild);
    }

    else
    {
      return insertElem(k, v, d->rightchild);
    }
  }
  return FAIL;
}

//Funzione da imple1mentare
Value dict::search(const Key k, const Dictionary& d){
  if (isEmpty(d)) return emptyValue;

  else if (k == d->e.key) return d->e.value;

  else if (k < d->e.key)
  {
    return search(k, d->leftchild);
  }

  else
  {
    return search(k, d->rightchild);
  }
  
  return emptyValue;
}

//Funzione ausiliaria per deleteElem
Elem deleteMin(Dictionary &d){
if (d->leftchild == emptyNode)
{
  Elem temp = d->e;
  Dictionary tempChild = d->rightchild;
  delete d;
  d = tempChild;
  return temp;
}
else 
{
  return deleteMin(d->leftchild);
}
}


//Funzione da implementare
Error dict::deleteElem(const Key k, Dictionary& d){
  if (isEmpty(d)) return FAIL;

  if (k == d->e.key)
  {
    if (d->leftchild == emptyNode && d->rightchild == emptyNode) // non ha figli
    {
      delete d;
      d = emptyNode;
      return OK;
    }
    else if (d->rightchild == emptyNode) // ha solo figlio sinistro
    {
      Dictionary temp = d->leftchild;
      delete d;
      d = temp;
    }

    else if (d->leftchild == emptyNode) // ha solo figlio destro
    {
      Dictionary temp = d->rightchild;
      delete d;
      d = temp;
    }
    else
    {
      d->e = deleteMin(d->rightchild);
    }

    return OK;
  }

  if (k < d->e.key)
  {
    return deleteElem(k, d->leftchild);
  }

  else
  {
    return deleteElem(k, d->rightchild);
  }
  return FAIL;
}

//Funzione da implementare
void print(const Dictionary& d) {
  if (isEmpty(d)) return;

  print(d->leftchild);
  cout<<endl;
  cout<< d->e.key << " : " << d->e.value << endl;
  print(d->rightchild);
}

/****************************************************************/
/*              FUNZIONE IMPLEMENTATE                           */
/****************************************************************/
Dictionary readFromFile(string nome_file){
  ifstream ifs(nome_file.c_str()); // apertura di uno stream associato ad un file, in lettura
  if (!ifs) {cout << "\nErrore apertura file, verificare di avere inserito un nome corretto\n"; return emptyDictionary;}  
  return readFromStream(ifs);
}

Dictionary readFromStdin(){
  cout << "\nInserire una sequenza di linee che rispettano la sintassi key: value.<enter>\nDigitare CTRL^ D per terminare l'inserimento\n";
  Dictionary d = readFromStream((std::cin));
  // Questa serve per aggirare un bug di alcune versioni attuali di glibc.
  clearerr(stdin);
  return d;
}

Dictionary readFromStream(istream& str){
  Dictionary d = emptyDictionary; 
  string key, kcopy;
  string value;
  getline (str, key, ':'); 
  getline (str, value); 
  while (!str.eof())  
    {        
      kcopy = key;
      removeBlanksAndLower(kcopy); 
      insertElem(kcopy, value, d);
      getline (str, key, ':'); 
      getline (str, value); 
    }
  str.clear();
  return d;
}
