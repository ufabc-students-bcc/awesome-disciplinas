#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "bTree.h"

int
main(int argc, char **argv)
{
    bTree b;
    int i;

    b = btCriar();
    assert(b);

    assert(btBuscar(b, 12) == 0);
    btInserir(b, 12);
    assert(btBuscar(b, 12) == 1);
	printf("### Teste 1 ###\nN = 1\nAltura = %i\nNumero de nos = %i\n", btAltura(b), btContaNos(b));
    btDestruir(b);

    b = btCriar();
    for(i = 0; i < 100; i++) {
        assert(btBuscar(b, i) == 0);
        btInserir(b, i);
        assert(btBuscar(b, i) == 1);
    }
    for(i = 0; i < 100; i++) {
        assert(btBuscar(b, i) == 1);
        btInserir(b, i);
        assert(btBuscar(b, i) == 1);
    }
	printf("### Teste 2 ###\nN = 100\nAltura = %i\nNumero de nos = %i\n", btAltura(b), btContaNos(b));
    btDestruir(b);

    b = btCriar();
    for(i = 0; i < 10000000; i += 2) {
        assert(btBuscar(b, i) == 0);
        btInserir(b, i);
        assert(btBuscar(b, i+1) == 0);
        assert(btBuscar(b, i) == 1);
    }
	printf("### Teste 3 ###\nN = 10000000\nAltura = %i\nNumero de nos = %i\n", btAltura(b), btContaNos(b));
    btDestruir(b);


    b = btCriar();
    printf("### Teste 4 ###");
    for(i = 1; i <= 15; i++) {
		printf("--- Inserir: %i ---\n", i);
        btInserir(b, i);
		btImprimirArvore(b);
		btImprimirChaves(b);
		printf("Altura = %i\nNumero de nos = %i\n", btAltura(b), btContaNos(b));
    }
    btDestruir(b);

    return 0;
}
