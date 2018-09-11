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

// imprime A[n-k..n], precedido da mensagem msg
void imprimeUltimasPosicoesVetor (tipoChave A[], long int n, long int k, char msg[]) 
{
    long int i;
    
	printf ("%s", msg);
    
	for (i=n; i>n-k; i--)
	{
		printf("%ld ", A[i]);
	}

	printf ("\n");
}

void PartialInsertionSort(tipoChave v[], tipoChave n, tipoChave k){
    int i, j, inicio, aux;
    
    for (i=1; i<n; i++){
        aux = v[i];
        
        if (i> k-1)
            inicio = k-1;
        else
            inicio = i-1;
            
        for (j=inicio; j>=0 && v[j]>aux; j--)
            v[j+1] = v[j];
            
        v[j+1] = aux;
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
	PartialInsertionSort(A, n, k);
	printf("Tempo total: %fs.", (float)(get_time() - tempo_inicial)/1000000.0f);
	//imprimeVetor(A, k, "\nVetor ordenado com InsertionSort Parcial: \n");

	free(A);

	return 0;
}
