#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define tipoChave long int

unsigned long int get_time()
{
	struct timeval tv;
	gettimeofday(&tv,NULL);
	return 1000000 * tv.tv_sec + tv.tv_usec;
}

// imprime A[1..n], precedido da mensagem msg
void imprimeVetor (tipoChave A[], long int n, char msg[]) 
{
    long int i;
    
	printf ("%s", msg);
    
	for (i=1; i<=n; i++)
	{
		printf("%ld ", A[i]);
	}

	printf ("\n");
}


int Particione(tipoChave A[], tipoChave p, tipoChave r) {
    int i, j, x, aux;

    x = A[r];
    i = p-1;

    for (j=p; j<=r-1; j++) {
        if (A[j]<=x) {            /* <-  comparacao */
            i = i+1;
            aux = A[i];
            A[i] = A[j];
            A[j] = aux;
        }
    }

    aux = A[i+1];
    A[i+1] = A[r];
    A[r] = aux;

    return i+1;
}


void PartialQuickSort(tipoChave A[], tipoChave p, tipoChave r, tipoChave k) {
    if (p<r) {
        int q = Particione(A, p, r);
        PartialQuickSort(A, p, q-1, k);
        
        if(q+1<=k)
            PartialQuickSort(A, q+1, r, k);
    }
}


int main (int argc, char **argv)
{
	long int i, n, k;
	
	if(argc < 2)
	{
		printf("Digite o valor de k como argumento!");
		abort();
	}
	k = atol(argv[1]);
	
	scanf("%ld", &n);
	tipoChave *A = (tipoChave*) malloc(sizeof(tipoChave) * (n+1));
	
	for (i=1; i<=n; i++)
		scanf("%ld", &A[i]);

	long int tempo_inicial = get_time();
	PartialQuickSort(A, 0, n, k);
	printf("Tempo total: %fs.", (float)(get_time() - tempo_inicial)/1000000.0f);
	//imprimeVetor(A, k, "\nVetor ordenado com QuickSort Parcial: \n");

	free(A);

	return 0;
}
