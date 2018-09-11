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


void PartialSelectionSort(tipoChave v[], tipoChave n, tipoChave k){
    int i, j, iMin, aux;
    
    for (i=0; i<k; i++){
        iMin = i;
        
        for (j=i+1; j<n; j++){
            if (v[iMin]>v[j])
                iMin = j;
        }
        
        if (iMin!=i){
            aux = v[iMin];
            v[iMin] = v[i];
            v[i] = aux;
        }
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
	PartialSelectionSort(A, n, k);
	printf("Tempo total: %fs.", (float)(get_time() - tempo_inicial)/1000000.0f);
	//imprimeVetor(A, k, "\nVetor ordenado com SelectionSort Parcial: \n");

	free(A);

	return 0;
}
