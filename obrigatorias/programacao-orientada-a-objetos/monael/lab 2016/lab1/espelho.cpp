#include <iostream>

bool espelho(int a, int b){
    int da1, da2, da3, da4, db1, db2, db3, db4;
    
    da1 = a/1000;
    a %= 1000;
    
    da2 = a/100;
    a %= 100;
    
    da3 = a/10;
    da4 = a%10;
    
    db1 = b/1000;
    b %= 1000;
    
    db2 = b/100;
    b %= 100;
    
    db3 = b/10;
    db4 = b%10;
    
    return (da1==db4 && da2==db3 && da3==db2 && da4==db1);
}

int main(){
    int a, b;
    
    std::cin >> a >> b;
    
    std::cout << (espelho(a,b)?"":"nao ") << "espelho" << std::endl;
    
}