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


void MinHeapify (tipoChave A[], long int m, long int i) 
{
	long int e, d, menor;
	tipoChave aux;
	e = 2*i;
	d = 2*i +1;
	
	if (e<=m && A[e]<A[i])
		menor = e;
	else
		menor = i;
		
	if (d<=m && A[d]<A[menor])
		menor = d;
		
	if (menor!=i) {
		aux = A[menor];
		A[menor] = A[i];
		A[i] = aux;
		MinHeapify (A, m, menor);
	}	
}

void BuildMinHeap(tipoChave A[], long int n) 
{
	long int i;
	for (i=n/2; i>=1; i--)
		MinHeapify (A, n, i);
}

void PartialHeapSort(tipoChave A[], long int n, long int k) 
{
	// IMPLEMENTAR!!!
	// - Na primeira iteração, o menor item que está em A[0] (raiz do heap) é trocado com o item que está em A[n-1].
	// - Em seguida o heap é refeito.
	// - Novamente o menor está em A[0], troque-o com A[n-1].
	// - Repita as duas últimas operações até que o k-ésimo menor esteja seja trocado com A[n-k].
	// - Ao final, os k menores estão nas k últimas posições do vetor A.
	BuildMinHeap(A, n);
	tipoChave i, aux, m = n;
	for(i=n; i>n-k; i--){
		aux = A[1];
		A[1] = A[i];
		A[i] = aux;
		m = m - 1;
		MinHeapify(A, m, 1);
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
	PartialHeapSort(A, n, k);
	printf("Tempo total: %fs.", (float)(get_time() - tempo_inicial)/1000000.0f);
	//imprimeVetor(A, k, "\nVetor ordenado com HeapSort Parcial: \n");

	free(A);

	return 0;
}
