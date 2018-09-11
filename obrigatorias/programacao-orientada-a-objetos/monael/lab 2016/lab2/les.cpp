#include <iostream>

class Lista{
    int *itens;
    int tamanho;
    int quantidade;
    
    public:
        Lista(int);
        void setTamanho(int);
        void setQuantidade(int);
        void setItens(int,int);
        int getTamanho();
        int getQuantidade();
        int getItens(int);
};