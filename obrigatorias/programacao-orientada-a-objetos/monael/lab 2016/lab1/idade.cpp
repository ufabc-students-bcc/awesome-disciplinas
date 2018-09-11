#include <iostream>

int main(){
    int anoA, anoN;
    std::string nome;
    
    std::cin >> anoA >> nome >> anoN;
    
    std::cout << nome << ", voce completa " << (anoA - anoN) << " anos de idade neste ano." << std::endl;
    return 0;
}