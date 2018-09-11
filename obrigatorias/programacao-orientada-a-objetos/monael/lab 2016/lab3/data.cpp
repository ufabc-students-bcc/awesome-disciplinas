#include <iostream>

class Data
{
    private:
            int dia, mes, ano;
    public:
            Data(int, int, int);
            
            void setDia(int);
            void setMes(int);
            void setAno(int);
            int getDia();
            int getMes();
            int getAno();
            int getDiasDoMes();
            
            Data operator ++(int);
            Data operator --(int);
            
            bool isBissexto(int);
            Data aumentaMes();
            Data diminuiMes();
};

Data::Data(int dia, int mes, int ano){
    this->setDia(dia);
    this->setMes(mes);
    this->setAno(ano);
}

void Data::setDia(int dia)
{
    this->dia = dia;
}

void Data::setMes(int mes)
{
    this->mes = mes;
}

void Data::setAno(int a)
{
    this->ano = a;
}

int Data::getDia()
{
    return this->dia;
}

int Data::getMes()
{
    return this->mes;
}

int Data::getAno()
{
    return this->ano;
}

int Data::getDiasDoMes(){
    int dias = 0;
    
    //meses de 31 dias
    if((mes == 1) || (mes == 3) || (mes == 5) || (mes == 7) || (mes == 8) || (mes == 10) || (mes == 12)){
        
        dias = 31;    
            
    //meses de 30 dias    
    } else if((mes == 4) || (mes == 6) || (mes == 9) || (mes == 11)){
        
        dias = 30;
        
    //fevereiro    
    } else {
    
        if(isBissexto(ano)){
            //fevereiro tem 29 dias
            
            dias = 29;
            
        } else {
            //fevereiro tem 28 dias
            
            dias = 28;
        }
    }
    
    return dias;
}



Data Data::operator ++(int){
    Data d(this->getDia(), this->getMes(), this->getAno()); 
    
    if(this->getDia() < this->getDiasDoMes()){
        
         this->setDia(this->getDia() + 1);
         
    } else {
        
        this->setDia(1);
        this->aumentaMes();
        
    }
    
    return d;
}

Data Data::operator --(int){
    Data d(this->getDia(), this->getMes(), this->getAno());
    
    if(this->getDia() > 1){
        this->setDia(this->getDia() - 1);
    }else{
        this->diminuiMes();
    }
    
    return d;
}


bool Data::isBissexto(int ano){
    bool retorno = false;
    
    if(ano%4 == 0){
        retorno = true;
    }
    
    return retorno;
}

Data Data::aumentaMes(){
    
    if(this->getMes() < 12){
        this->setMes(this->getMes() + 1);
    } else {
        this->setAno(this->getAno() + 1);
        this->setMes(1);
    }
}

Data Data::diminuiMes(){
    if(this->getMes() > 1){
        this->setMes(this->getMes() - 1);
    }else{
        this->setMes(12);
        this->setAno(this->getAno() - 1);
    }
    
    this->setDia(this->getDiasDoMes());
}

int main()
{
    int nTestes;
    
    std::cin >> nTestes;
    
    for(int i = 0; i < nTestes; i++){
        int dia, mes, ano, nComandos;
        string comandos("");
        std::cin >> dia >> mes >> ano;
        
        Data d(dia,mes,ano);
        
        std::cin >> nComandos;
        std::cin >> comandos;
        
        for(int j = 0; j < nComandos; j++){
            
        }
        
        std::cout << comandos;
    }
    
    delete nTestes;
    
    return 0;
}