#include <iostream>

class Relogio{
    private:
            int hora, minuto, segundo;
            
    public:
            Relogio();
            Relogio(int, int, int);
            int getHora();
            int getMinuto();
            int getSegundo();
            void setHora(int);
            void setMinuto(int);
            void setSegundo(int);
            
            void incrementa();
            void decrementa();
}

Relogio::Relogio(){
    
}

Relogio::Relogio(int hora, int min, int seg){
    this->setHora(hora);
    this->setMinuto(min);
    this->setSegundo(seg);
}

int Relogio::getHora(){
    return this->getHora();
}

int Relogio::getMinuto(){
    return this->getMinuto();
}

int Relogio::getSegundo(){
    return this->getSegundo();
}

void Relogio::setHora(int hora){
    this->setHora(hora);
}

void Relogio::setMinuto(int min){
    this->setMinuto(min);
}

void Relogio::setSegundo(int seg){
    this->setSegundo(seg);
}

void Relogio::incrementa(){
    this->setSegundo(this->getSegundo() + 1);
    
    if(this->getSegundo() > 59){
        this->setSegundo(0);
        this->setMinuto(this->getMinuto() + 1);
        
        if(this->getMinuto() > 59){
            this->setMinuto(0);
            this->setHora(this->getHora() +1);
        }
    }
}

void Relogio::decrementa(){
    this->setSegundo(this->getSegundo() - 1);
    
    if(this->getSegundo() < 0){
        
    }
}

int main(){
    
    Relogio rel(0,0,0);
    
    while(std::cin){
        rel::incrementa();
    }
    
    return 0;
}