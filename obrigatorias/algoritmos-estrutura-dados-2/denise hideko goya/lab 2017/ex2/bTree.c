// Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "bTree.h"

// Define a quantidade total de filhos no:
#define ORDEM (3)

struct btNo {
    int ehFolha;                  // 0 se n eh uma folha, outro valor se for uma folha.
    int numChaves;                // Quantidade total de chaves no no
    int chaves[ORDEM];            // Vetor com chaves (o ultimo elemento eh usado como auxiliar)
    struct btNo *filhos[ORDEM+1]; // Vetor com ponteiros para os filhos (o ultimo elemento eh usado como auxiliar)
};

bTree btCriar(void) {
    bTree b;
    b = malloc(sizeof(*b));
    assert(b);                   // Confere se a memoria foi corretamente alocada
// 	memset(b, 0x00, sizeof(*b)); // Atribui 0 para todos os campos
    b->ehFolha = 1;              // A raiz, inicialmente, eh uma folha!
    b->numChaves = 0;
    return b;
}

void btDestruir(bTree b) {
    if(b == NULL)
        return;
    
    int i;
    if(!b->ehFolha) { // Destruir todos os filhos primeiro, caso existir...
        for(i = 0; i < b->numChaves + 1; i++) {
            btDestruir(b->filhos[i]);
        }
    }
    free(b);
}

// Realiza uma busca binaria em um vetor e retorna o indice da chave
int buscarChave(int n, const int *a, int chave)
{
    int lo;
    int hi;
    int mid;

    lo = -1;
    hi = n;

    while(lo + 1 < hi) {
        mid = (lo+hi)/2;
        if(a[mid] == chave) {
            return mid;
        } else if(a[mid] < chave) {
            lo = mid;
        } else {
            hi = mid;
        }
    }

    return hi;
}

int btBuscar(bTree b, int chave)
{
    int pos;
    if(b->numChaves == 0) { // Caso nao ter chaves, retornar...
        return 0;
    }

    pos = buscarChave(b->numChaves, b->chaves, chave); // Encontrar o indice da chave

    if(pos < b->numChaves && b->chaves[pos] == chave) {  // Chave encontrada!!!
        return 1;
    } else {
        return(!b->ehFolha && btBuscar(b->filhos[pos], chave)); // Chave nao encontrada, tentar no noh filho, se existir...
    }
}

bTree inserirInterno(bTree b, int chave, int *mediana);
void btInserir(bTree b, int chave)
{
    bTree b1;    // Novo no esquerda
    bTree b2;    // Novo no direita
    int mediana; // Elemento do meio (que subira)

    b2 = inserirInterno(b, chave, &mediana);

    if(b2) { // A raiz precisa se dividir: eh preciso criar uma nova raiz!
        b1 = malloc(sizeof(*b1));
        assert(b1);
        memmove(b1, b, sizeof(*b)); // Copia lista
        b->numChaves = 1;
        b->ehFolha = 0;
        b->chaves[0] = mediana;
        b->filhos[0] = b1;
        b->filhos[1] = b2;
    }
}
bTree inserirInterno(bTree b, int chave, int *mediana)
{
    int pos;
    int mid;
    bTree b2;

    pos = buscarChave(b->numChaves, b->chaves, chave); // Obter posicao da chave no no atual

    if(pos < b->numChaves && b->chaves[pos] == chave) { // A chave ja existe, abortar!
        return 0;
    }

    if(b->ehFolha) { // Encontrou a folha para inserir. Inserir na posicao correta!
        memmove(&b->chaves[pos+1], &b->chaves[pos], sizeof(*(b->chaves)) * (b->numChaves - pos)); // Todas as chaves acima de pos move um espaco acima
        b->chaves[pos] = chave;
        b->numChaves++;
    } else {
        b2 = inserirInterno(b->filhos[pos], chave, &mid); // Inserir chave em um filho...
        if(b2) { // A folha filha foi dividida, inserir a chave em b...
            memmove(&b->chaves[pos+1], &b->chaves[pos]  , sizeof(*(b->chaves)) * (b->numChaves - pos)); // Todos as chaves acima de pos move um espaco acima
            memmove(&b->filhos[pos+2], &b->filhos[pos+1], sizeof(*(b->chaves)) * (b->numChaves - pos)); // Todos os filhos acima de pos move um espaco acima
            b->chaves[pos]   = mid;
            b->filhos[pos+1] = b2;
            b->numChaves++;
        }
    }

    if(b->numChaves >= ORDEM) { // Verificar se eh preciso dividir b
        mid = b->numChaves/2; // Obter indice da chave mediana
        *mediana = b->chaves[mid]; // Copiar valor da chave mediana para ser utilizado na funcao que chamou
        b2 = malloc(sizeof(*b2)); // Criar nova folha!
        b2->numChaves = b->numChaves - mid - 1;
        b2->ehFolha = b->ehFolha;

        memmove(b2->chaves, &b->chaves[mid+1], sizeof(*(b->chaves)) * b2->numChaves); // Copiar a metade dos elementos de b para b2
        if(!b->ehFolha) { // Se nao for folha, copiar os filhos tambem!
            memmove(b2->filhos, &b->filhos[mid+1], sizeof(*(b->filhos)) * (b2->numChaves + 1));
        }
        b->numChaves = mid; // Agora b tem metade dos elementos
        return b2;
    } else { // Nada precisa ser feito...
        return 0;
    }
}

//funcionou
int btAltura(bTree b) {
	if(b == NULL)
	    return -1;
	    
	//inicia com zero
	int n = 0;
	
	//se não for folha, conta a altura dos filhos
	if(b->ehFolha == 0)
	{
	    int i,  max = -1;
	    
	    for(i =0; i<b->numChaves; i++)
	    {
	        int alt = btAltura(b->filhos[i]);
	        
	        if(alt > max)
	            max = alt;
	    }
	    
	    n = max + 1;
	}
	
	return n;
}

int btContaNos(bTree b) {
	if(b == NULL)
	    return 0;
	    
	//inicia
	int i, n = 1;
	
	//se não for folha, conta a altura dos filhos
	if(b->ehFolha == 0)
	{
	    for(i =0; i<b->numChaves + 1; i++)
	    {
	        n += btContaNos(b->filhos[i]);
	    }
	}
	
	return n;
}

void btImprimirChaves(bTree b) 
{
	if(b == NULL)
	{
	    printf("\n");
	    return;
	}
	    
	int i=0;
	
	for(i;i<b->numChaves;i++)
	{
	    printf("%i,", b->chaves[i]);
	}
	
	//se não for folha, conta a altura dos filhos
	if(b->ehFolha == 0)
	{
	    for(i =0; i<b->numChaves + 1; i++)
	    {
	        btImprimirChaves(b->filhos[i]);
	    }
	}
}

//remove de uma folha
void btRemoveDaFolha (bTree b, int idx)
{
 
    // Move tudo pra tras
    for (int i=idx+1; i<n; ++i)
        b->chaves[i-1] = b->chaves[i];
 
    // Reduce the count of keys
    b->numChaves--;
 
    return;
}

//remove de uma não folha
void btRemoveDaNaoFolha(bTree b, int idx)
{
 
    int k = b->chaves[idx];
 
    if (b->filhos[idx]->numChaves >= t)
    {
        
        BTree *cur=b->filhos[idx];
        while (!cur->ehFolha)
            cur = cur->filhos[cur->numChaves];
     
        int pred cur->chaves[cur->numChaves-1];
        
        b->chaves[idx] = pred;
        
        btRemover(b->filhos[idx], pred);
    }
 
    else if  (C[idx+1]->n >= t)
    {
        BTree *cur = b->filhos[idx+1];
        while (!cur->ehFolha)
            cur = cur->filhos[0];
     
        int succ cur->chaves[0];
        
        b->chaves[idx] = succ;
        btRemover(b->filhos[idx+1], succ);
    }
 
    else
    {
        merge(b, idx);
        btRemover(b->filhos[idx],k);
    }
    return;
}

void merge(bTree b, int idx)
{
    BTree *child = b->filhos[idx];
    BTree *sibling = b->filhos[idx+1];
 
    child->chaves[ORDEM-1] = b->chaves[idx];
 
    for (int i=0; i<sibling->numChaves; ++i)
        child->chaves[i+ORDEM] = sibling->chaves[i];
        
    if (!child->ehFolha)
    {
        for(int i=0; i<=sibling->numChaves; ++i)
            child->filhos[i+t] = sibling->filhos[i];
    }
 
    for (int i=idx+1; i<n; ++i)
        b->chaves[i-1] = b->chaves[i];
 
    for (int i=idx+2; i<=n; ++i)
        b->filhos[i-1] = b->filhosC[i];
 
    child->numChaves += sibling->numChaves+1;
    b->numChaves--;
 
    delete(sibling);
    return;
}

//remover uma chave
void btRemover(bTree b, int k)
{
    int idx;
    if(b->numChaves == 0) { // Caso nao ter chaves, retornar...
        return 0;
    }

    idx = buscarChave(b->numChaves, b->chaves, k); // Encontrar o indice da chave
 
    if(pos < b->numChaves && b->chaves[idx] == k) {  // Chave encontrada!!!
    {
        if (b->ehFolha)
            removeDaFolha(b, idx);
        else
            removeDaNaoFolha(b, idx);
    }
    else
    {
 
        if (b->ehFolha)
        {
            cout << "A chave "<< k <<" não existe na árvore\n";
            return;
        }
 
        bool flag = ( (idx==b->numChaves)? true : false );
 
        if (b->filhos[idx]->numChaves < ORDEM)
            preenche(b, idx);
 
        if (flag && idx > b->numChaves)
            btRemover(b->filhos[idx-1],k);
        else
            b->filhos[idx]->remove(k);
    }
    return;
}

void preenche(bTree b, int idx)
{
 
    if (idx!=0 && b->filhos[idx-1]->numChaves>=ORDEM)
        emprestaAnterior(b,idx);
 
    else if (idx!=b->numChaves && b->filhos[idx+1]->numChaves>=ORDEM)
        emprestaProximo(b,idx);
 
    else
    {
        if (idx != b->numChaves)
            merge(b,idx);
        else
            merge(b,idx-1);
    }
    return;
}

void emprestaAnterior(bTree b, int idx)
{
 
    BTree *child=b->filhos[idx];
    BTree *sibling=b->filhos[idx-1];
 
    for (int i=child->numChaves-1; i>=0; --i)
        child->chaves[i+1] = child->chaves[i];
 
    if (!child->ehFolha)
    {
        for(int i=child->numChaves; i>=0; --i)
            child->filhos[i+1] = child->filhos[i];
    }
 
    child->chaves[0] = b->chaves[idx-1];
 
    if (!b->ehFolha)
        child->filhos[0] = sibling->filhos[sibling->numChaves];
 
    b->chaves[idx-1] = sibling->chaves[sibling->numChaves-1];
 
    child->numChaves += 1;
    sibling->numChaves -= 1;
 
    return;
}
 

void emprestaProximo(bTree b, int idx)
{
 
    BTree *child=b->filhos[idx];
    BTree *sibling=b->filhos[idx+1];
 
    child->chaves[(child->numChaves)] = b->chaves[idx];
 
    if (!(child->ehFolha))
        child->filhos[(child->numChaves)+1] = sibling->filhos[0];
 
    b->chaves[idx] = sibling->chaves[0];
 
    for (int i=1; i<sibling->numChaves; ++i)
        sibling->chaves[i-1] = sibling->chaves[i];
 
    if (!sibling->ehFolha)
    {
        for(int i=1; i<=sibling->numChaves; ++i)
            sibling->filhos[i-1] = sibling->filhos[i];
    }
 
    child->numChaves += 1;
    sibling->numChaves -= 1;
 
    return;
}

void btImprimirArvore(bTree b) {
	int totNos;
	bTree *fila;
	int *nivel;
	int p = 0; // Posicao atual
	int n = 0; // Numero de elementos

	int nivel_atual = -1;
	
	totNos = btContaNos(b);
	fila   = (bTree*) malloc(sizeof(*fila)  * totNos);
	nivel  = (int*)   malloc(sizeof(*nivel) * totNos);
	nivel[n] = 0;
	fila [n] = b;
	n++;
	
	while(p < n) {
		int i;
		int prox_nivel = nivel[p];
		bTree t = fila[p++];
		
		for(i = 0; i < t->numChaves+1 && !(t->ehFolha); i++) {
			nivel[n]  = prox_nivel + 1;
			fila[n++] = t->filhos[i];
		}
	
		if(nivel_atual != prox_nivel) {
			if(prox_nivel != 0)
				printf("\n");
			printf("%i: ", prox_nivel+1);
			nivel_atual = prox_nivel;
		}
	
		printf("[");
		for(i = 0; i < t->numChaves; i++) {
			printf("%i", t->chaves[i]);
			if(i != t->numChaves-1)
				printf(",");
		}
		printf("] ");
	}
	
	printf("\n");
	
	if(fila != NULL)
	    free(fila);
	    
	if(nivel != NULL)
	    free(nivel);
}
