#include <stdio.h>
#include <stdlib.h>

#define tipoChave long int

// imprime A[1..n], precedido da mensagem msg
void imprimeVetor (tipoChave A[], int n, char msg[]) 
{
    int i;
    
	printf ("%s", msg);
    
	for (i=1; i<=n; i++)
	{
		printf("%ld ", A[i]);
	}

	printf ("\n");
}

// codifique MaxHeapify
void MaxHeapify (tipoChave A[], int m, int i) 
{
	int e = 2 * i;
	int d = 2 * i + 1;
	int maior = 0;
	
	if((e <= m) && (A[e] > A[i]))
		maior = e;
	else
		maior = i;
		
	if((d <= m) && (A[d] > A[maior]))
		maior = d;
		
	if(maior != i)
	{
		long int aux = A[i];
		A[i] = A[maior];
		A[maior] = aux;
		
		MaxHeapify(A, m, maior);
	}
}

// codifique BuildMaxHeap
void BuildMaxHeap(tipoChave A[], int n) 
{
	int i;
	
	for(i = n/2; i > 0; i--)
		MaxHeapify(A, n, i);
}

// codifique HeapSort
// imprima o heap construido antes de ordenar
void HeapSort(tipoChave A[], int n) 
{
	
	//pré processamento
	BuildMaxHeap(A, n);
	
	// efetue a impressao do heap construido antes de sua ordenacao
	// e confira se esta ok
	imprimeVetor(A, n, "\n heap constuido: \n");
	
	int m = n;
	int i;
	
	for(i = n; i > 1; i--)
	{
		long int aux = A[1];
		A[1] = A[i];
		A[i] = aux;
		
		m = m - 1;
		MaxHeapify(A, m, 1);
	}
	
}


void main () 
{
	int i, n;
	
	scanf("%d", &n);
	tipoChave A[n+1];
	
	for (i=1; i<=n; i++)
		scanf("%ld", &A[i]);

	imprimeVetor(A, n, "\n vetor lido: \n");
	
	HeapSort(A, n);

	imprimeVetor(A, n, "\n vetor ordenado com HeapSort: \n");

}
