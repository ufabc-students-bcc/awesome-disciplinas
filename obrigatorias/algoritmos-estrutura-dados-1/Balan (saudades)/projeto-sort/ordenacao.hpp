#ifndef _ORDENACAO_H
#define _ORDENACAO_H

namespace Luana{
    template <typename T>
    class Ordenacao {
        public:
            //heapsort
            static void heapsort(T *vet, int n);
            
            //Merge sort
            static void mergesort(T *vet, int n);
            
            //Quick sort
            static void quicks(T *vet, int l, int r);
            
            //Comparador
            static int comparador(const void * a, const void * b);

        private:
            //heapsort
            static void heapify(T *vet, int pai, int heapsize);

            //merge sort
            static void m_sort(T *vet, T *aux, int esq, int dir);
            
            static void merge(T *vet, T *aux, int esq, int meio, int dir);
    };

    /*
    * Métodos para rodar a heapsort
    */
    
    template <typename T>
    void Ordenacao<T>::heapify(T *vet, int pai, int heapsize) {
        int fl, fr, imaior;
        fl = (pai << 1) + 1;
        fr = fl + 1;
        while (true) {
            if ((fl < heapsize) && (vet[fl] > vet[pai])) imaior = fl;
            else imaior = pai;
            if ((fr < heapsize) && (vet[fr] > vet[imaior])) imaior = fr;
            if (imaior != pai){
                T aux = vet[pai];
                vet[pai] = vet[imaior];
                vet[imaior] = aux;
                pai = imaior;
                fl = (pai << 1) + 1;
                fr = fl + 1;
            }
            else break;
        }
    }

    template <typename T>
    void Ordenacao<T>::heapsort(T *vet, int n) {
        int i;
        for (i=(n>>1)-1; i>=0; i--) heapify(vet, i, n);
        for (i=n-1; i > 0; i--) {
            T aux = vet[0];
            vet[0] = vet[i];
            vet[i] = aux;
            heapify(vet, 0, i);
        }
    }
    
    /*
    * Métodos para rodar Merge Sort
    */
    
   
   template <typename T>
   void Ordenacao<T>::mergesort(T *vet, int n) {
        T *aux = new T[n]; // Alocação do vetor auxiliar
        
        m_sort(vet, aux , 0, n-1);
        
        delete aux;
    }
    
    template <typename T>
    void Ordenacao<T>::m_sort(T *vet, T *aux, int esq, int dir) {
        
        if (dir <= esq) return;
        
        int meio = (dir + esq) >> 1;
        
        m_sort(vet, aux, esq, meio); // Primeira chamada
        m_sort(vet, aux, meio+1, dir); // Segunda chamada
        
        if (vet[meio]<=vet[meio+1]) return;
        
        merge(vet, aux, esq, meio, dir); // Intercala as metades
    }
    
    template <typename T>
    void Ordenacao<T>::merge(T *vet, T *aux, int esq, int meio, int dir) {
        int i, j, k;
        i = k = esq; j = meio+1;
        
        while ((i <= meio) && (j <= dir)) {
            if (vet[i] < vet[j]) aux[k++] = vet[i++];
            
            else aux[k++] = vet[j++];
        }
        
        while (i <= meio) aux[k++] = vet[i++];
        while (j <= dir) aux[k++] = vet[j++];
        while (esq<=dir) vet[esq] = aux[esq++];
    }
    
    /*
    * Métodos para rodar Quick sort
    */
    
    template <typename T>
    void Ordenacao<T>::quicks(T *vet, int l, int r) {
        if (r <= l) return;
        
        int i, j;
        i = (l+r)/2; // Troca a posição l com a posição central
        
        T pivo = vet[i]; vet[i] = vet[l]; vet[l] = pivo;
        
        i = l; j = r;
        
        while (true) {
            while ((j > i) && (vet[j] > pivo)) j--;
            
            if (i==j) break;
            
            vet[i] = vet[j]; i++;
            
            while ((i < j) && (vet[i] < pivo)) i++;
            
            if (i==j) break;
            
            vet[j] = vet[i]; j--;
        }
        
        vet[i] = pivo;
        
        quicks(vet, l, i-1);
        quicks(vet, i+1, r);
    }
    
    template <typename T>
    int Ordenacao<T>::comparador (const void * a, const void * b){
        return ( *(int*)a - *(int*)b );
    }


}
#endif
