void scambia(vector<int>& v, int i, int j)
{ 
  int tmp = v[j];
  v[j] = v[i];
  v[i] = tmp;
}


/**************************************************************************************
				SELECTION SORT
***************************************************************************************/
void selectionSort(vector<int>& v)
{
   int current_min_index;
   unsigned int size = v.size();
   for (unsigned int i=0; i<size; ++i)
   { 
     current_min_index = i;
     for (unsigned int j=i+1;j<size; ++j)
        if (v[current_min_index] > v[j])
            current_min_index = j;
     scambia(v, i, current_min_index);
   }
}



/**************************************************************************************
				INSERTION SORT
***************************************************************************************/
void insertionSort(vector<int>& v)
{
   int current, prev;
   unsigned int size = v.size();
   for (unsigned int i=1; i<size; ++i)
   { current=i; 
     prev=i-1;
     while(prev>=0 && v[current]<v[prev])
        {
         scambia(v, current, prev);
         --current;
         --prev;
        }
   }
}


/**************************************************************************************
				BUBBLESORT
***************************************************************************************/
void bubbleSort(vector<int>& v)
{
   unsigned int size = v.size();
   bool scambiati;
   for (unsigned int i=1; i<size; ++i)
      {
      scambiati = false;
      for (unsigned int j=0; j<size-i; ++j)
          if(v[j]>v[j+1])
            { 
              scambia(v, j, j+1);
              scambiati = true;
            }
      if (!scambiati) return;
      }
}



/**************************************************************************************
				LETTURA
***************************************************************************************/
vector<int> leggiVettoreDaFile(string nome_file)
{
    ifstream ifs(nome_file.c_str()); // apertura di uno stream associato ad un file, in lettura
    vector<int> v;        // vettore di dati (numeri interi diversi da -1000000
    int dato;
    ifs>>dato;
    if (!ifs) throw runtime_error("Errore inserimento dati\n");
    while (dato!=-1000000)  // assumiamo che il segnale di fine input nel file sia il numero "meno un milione", -1000000
        {          
        v.push_back(dato);   // put into vector
        ifs>>dato;
        if (!ifs) throw runtime_error("Errore inserimento dati\n");
        }
return v;
}

/**************************************************************************************
				SCRITTURA
***************************************************************************************/
void stampaVettoreEDurataSuStream(const vector<int>& v, string info, double duration, ofstream& ofs) // notare passaggio per "const reference" di v
{
    ofs << info;
    cout << info;
    for (unsigned int i=0; i<v.size(); ++i)
       {
       ofs << v[i] << "\n";
       cout << v[i] << "\n";
       }
    ofs << info << "\nDurata dell'esecuzione in microsecondi: " << duration << endl;
    cout << info << "\nDurata dell'esecuzione in microsecondi: " << duration << endl;
    cout << "\nPremere un carattere qualunque per andare avanti: ";
    char ch;
    cin >> ch;
}

/**************************************************************************************
				MERGESORT
***************************************************************************************/

void ms(vector<inr>& v, unsigned int inizio, unsigned int fine)
{
   if (inizio<fine)
   {
      usigned int centro = (inzio+fine)/2;
      ms(v, inizio, centro);
      ms(v, centro+1, fine);
      fondi(v,inizio, centro, fine);
      
   }
}

void mergeSort(vector <int> & v)
{
   if (v.size()!=0)
   {
      ms(v, 0, v.size()-1);
   }
}