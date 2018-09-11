#include <iostream>

struct Racional{
    
    int a,b;
    
};

struct Racional racional(int x, int y){
    struct Racional f;
    
    f.a = x;
    f.b = y;
    
    return f;
}

struct Racional soma(struct Racional f1, struct Racional f2){
    
    return racional((f1.a*f2.b)+(f1.b*f2.a),(f1.b*f2.b));
    
}

struct Racional neg(struct Racional f){
    
    return racional (f.a*-1, f.b);
    
}

struct Racional sub(struct Racional f1, struct Racional f2){
    
    return soma(f1,neg(f2));
    
}

struct Racional multi(struct Racional f1, struct Racional f2){
    
    return racional((f1.a*f2.a),(f1.b*f2.b));
    
}

struct Racional divisao(struct Racional f1, struct Racional f2){
    
    return racional ((f1.a*f2.b),(f1.b*f2.a));
    
}

int mdc(int a, int b){
     
    if(b == 0){
        if(a<0){
            
            return -a;
        }
        else{
            return a;
        }
    }
    else{
        return mdc(b, a%b);
    }
}

struct Racional reduz(struct Racional *redz){
    int d = mdc((*redz).a, (*redz).b);
     
    redz->a = (*redz).a/d;
    
    redz->b = (*redz).b/d;
     
}

int main(){
    
    int a,b,c,d;
    char op;
    struct Racional f1, f2, fr;
    
   
    
    while(std::cin >> a >> b >> op >>  c >> d){
        
        f1 =  racional(a,b);
        f2 =  racional(c,d);
        
        if(op == '+')
        {
            fr = soma(f1,f2) ;
        }
        else if(op == '-')
        {
            fr = sub(f1,f2);
        }
        else if(op == '*')
        {
            fr = multi(f1,f2);
        }
        else
        {
            fr = divisao(f1,f2);
        }
        
        reduz(&fr);
        std::cout << fr.a << " " << fr.b << std::endl;

    }
    
    
    return 0;
}