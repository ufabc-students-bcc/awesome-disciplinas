#include <iostream>
#include <cmath>

class Racional
{
    private:
            int numerador, denominador;
    public:
            Racional();
            Racional(int, int);
            void setNumerador(int);
            void setDenominador(int);
            int getNumerador();
            int getDenominador();
            
            Racional operator + (Racional);
            Racional operator - (Racional);
            Racional operator * (Racional);
            Racional operator / (Racional);
            void reducao();
};

Racional::Racional()
{   }

Racional::Racional(int n, int d)
{
    this->setNumerador(n);
    this->setDenominador(d);
}

void Racional::setNumerador(int n)
{
    this->numerador = n;
}

void Racional::setDenominador(int d)
{
    this->denominador = d;
}

int Racional::getNumerador()
{
    return this->numerador;
}

int Racional::getDenominador()
{
    return this->denominador;
}

Racional Racional::operator + (Racional q)
{
    Racional r;
    r.setNumerador(this->getNumerador()*q.getDenominador() + this->getDenominador()*q.getNumerador());
    r.setDenominador(this->getDenominador()*q.getDenominador());
    return r;
}

Racional Racional::operator - (Racional q)
{
    q.setNumerador(q.getNumerador()*-1);
    return (*this) + q;
}

Racional Racional::operator * (Racional q)
{
    Racional r;
    r.setNumerador(this->getNumerador()*q.getNumerador());
    r.setDenominador(this->getDenominador()*q.getDenominador());
    return r;
}

Racional Racional::operator / (Racional q)
{
    Racional r;
    r.setNumerador(this->getNumerador()*q.getDenominador());
    r.setDenominador(this->getDenominador()*q.getNumerador());
    return r;
}

void Racional::reducao()
{   
    int a, b, r;
    a = std::abs(this->getNumerador());
    b = std::abs(this->getDenominador());
    
    do
    {
        r = a%b;
        a = b;
        b = r;
    }while(r > 0);
    
    this->setNumerador(this->getNumerador()/a);
    this->setDenominador(this->getDenominador()/a);
}

int main()
{
    int n1, d1, n2, d2;
    char op;
    Racional *f1, *f2, fr;
    
    while(std::cin >> n1 >> d1 >> op >> n2 >> d2)
    {
        f1 = new Racional(n1, d1);
        f2 = new Racional(n2, d2);
        
        if(op == '+')
        {
            fr = (*f1) + (*f2);
        }
        else if(op == '-')
        {
            fr = (*f1) - (*f2);
        }
        else if(op == '*')
        {
            fr = (*f1) * (*f2);
        }
        else
        {
            fr = (*f1) / (*f2);
        }
        fr.reducao();
        std::cout << fr.getNumerador() << " " << fr.getDenominador() << std::endl;
        delete f1;
        delete f2;
    }
    return 0;
}