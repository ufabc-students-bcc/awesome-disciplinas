class Fila{
    private:
            int itens, inicio, tamanho, final;
    
    public:
            Fila();
            Fila(int);
            void setItems(int);
            void setInicio(int);
            void setTamanho(int);
            void setFinal(int);
            int getItens();
            int getInicio();
            int getTamanho();
            int getFinal();
            bool vazia();
            void enfileirar(int);
            void desenfileirar();
}

Fila::Fila(){
    
}

Fila::Fila(int){
    
}

void Fila::setItems(int){
    
}

void Fila::setInicio(int){
    
}

void Fila::setTamanho(int){
    
}

void Fila::setFinal(int){
    
}

int Fila::getItens(){
    
}

int Fila::getInicio(){
    
}

int Fila::getTamanho(){
    
}

int Fila::getFinal(){
    
}

bool Fila::vazia(){
    
}

void Fila::enfileirar(int){
    
}

void Fila::desenfileirar(){
    int it = -1;
    
    if(!this->vazia()){
        it = this->getItens(1);
        this->setInicio(-1);
    } 
}