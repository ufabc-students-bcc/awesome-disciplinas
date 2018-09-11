#include <iostream>
#include "ordenacao.hpp"
#include <time.h>
#include <random>
#include <algorithm>    // std::sort

using namespace std;

int main(int argc, char** argv) {

    uniform_int_distribution<int> uidist;
    mt19937 rng;
    int n;
    int *v;
    double tmili;
    int testes = 6;
    clock_t start;
    clock_t stop;
    double valores[testes];
    v = new int[65610000];
    
    //                0     1       2      3       4        5        6        7         8   
    int casos[9] = {10000, 30000, 90000, 270000, 810000, 2430000, 7290000, 21870000, 65610000};
    int dados[5][10];
    
    for(int indice = 0; indice < 9; indice++)
    {
        n = casos[indice];
        
        /*
        Heap sort - 0
        */
        
        cout << "Heap sort:" << endl;
        
        for(int i=0; i<testes; i++){
            rng.seed(i);
            for(int j=0; j<n; j++){
               v[j] = uidist(rng); 
            } 
            start = clock();
            Luana::Ordenacao<int>::heapsort(v, n);
            stop = clock();
            tmili =  (double)((stop-start)*1000/CLOCKS_PER_SEC);
            cout << i+1 <<"º teste: "<< tmili << endl;
            valores[i] = tmili;
        }
        
        for(int i=1; i<testes; i++) valores[0] = valores[0] + valores[i];
        valores[0] = valores[0]/6;
        cout << "média do tempo: " << valores[0] << endl;
        cout << "Start: " << start << " - stop: " << stop << endl;
        
        dados[0][indice] = valores[0];
        
        /*
        Quick sort - 1
        */
        
        cout << endl << "Quick sort: (" << casos[indice] << ")" << endl;
        
        for(int i=0; i<testes; i++){
            rng.seed(i);
            for(int j=0; j<n; j++){
               v[j] = uidist(rng); 
            } 
            start = clock();
            Luana::Ordenacao<int>::quicks(v, 0, n);
            stop = clock();
            tmili =  (double)((stop-start)*1000/CLOCKS_PER_SEC);
            cout << i+1 <<"º teste: "<< tmili << endl;
            valores[i] = tmili;
        }
        
        for(int i=1; i<testes; i++) valores[0] = valores[0] + valores[i];
        valores[0] = valores[0]/6;
        cout << "média do tempo: " << valores[0] << endl;
        
        dados[1][indice] = valores[1];
        
        
        /*
        Merge sort - 2
        */
        
        cout << endl << "Merge sort: (" << casos[indice] << ")" << endl;
        
        for(int i=0; i<testes; i++){
            rng.seed(i);
            for(int j=0; j<n; j++){
               v[j] = uidist(rng); 
            } 
            start = clock();
            Luana::Ordenacao<int>::mergesort(v, n);
            stop = clock();
            tmili =  (double)((stop-start)*1000/CLOCKS_PER_SEC);
            cout << i+1 <<"º teste: "<< tmili << endl;
            valores[i] = tmili;
        }
        
        for(int i=1; i<testes; i++) valores[0] = valores[0] + valores[i];
        valores[0] = valores[0]/6;
        cout << "média do tempo: " << valores[0] << endl;
        
        dados[2][indice] = valores[2];
        
        /*
        std sort - 3
        */
        
        cout << endl << "std::sort: (" << casos[indice] << ")" << endl;
        
        for(int i=0; i<testes; i++){
            rng.seed(i);
            for(int j=0; j<n; j++){
               v[j] = uidist(rng); 
            } 
            start = clock();
            std::sort(v, v+n);
            stop = clock();
            tmili =  (double)((stop-start)*1000/CLOCKS_PER_SEC);
            cout << i+1 <<"º teste: "<< tmili << endl;
            valores[i] = tmili;
        }
        
        for(int i=1; i<testes; i++) valores[0] = valores[0] + valores[i];
        valores[0] = valores[0]/6;
        cout << "média do tempo: " << valores[0] << endl;
        
        dados[3][indice] = valores[3];
        
        /*
        qsort - 4
        */
        
        cout << endl << "qsort: (" << casos[indice] << ")" << endl;
        
        for(int i=0; i<testes; i++){
            rng.seed(i);
            for(int j=0; j<n; j++){
               v[j] = uidist(rng); 
            } 
            start = clock();
            qsort(v, n, sizeof(int), Luana::Ordenacao<int>::comparador);
            stop = clock();
            tmili =  (double)((stop-start)*1000/CLOCKS_PER_SEC);
            cout << i+1 <<"º teste: "<< tmili << endl;
            valores[i] = tmili;
        }
        
        for(int i=1; i<testes; i++) valores[0] = valores[0] + valores[i];
        valores[0] = valores[0]/6;
        cout << "média do tempo: " << valores[0] << endl;
        
        dados[4][indice] = valores[4];
    }
    
} 
