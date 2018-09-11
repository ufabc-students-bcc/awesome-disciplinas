#include <stdio.h>
#include <stdlib.h>
#include <string.h>


 
// Altura maxima da arvore de Huffman.
#define MAX_TREE_HT 100

// Mapa dos codigos do alfabeto gerado.
// O valor de A[c][0] contem o numero de bits do codigo do caractere c. Se 0, nao ha codificacao disponivel.
// Os valores de A[c][1..n], sendo n = A[c][0], pode ser 0 ou 1, de acordo com o codigo do caractere gerado.
typedef char codes_t[255][MAX_TREE_HT+1];



//////////////
// MIN-HEAP //
 
struct MinHeapNode
{
	char conteudo;
	unsigned frequencia;
	struct MinHeapNode *esquerda, *direita;
};
 
struct MinHeap
{
	unsigned tamanho;
	unsigned capacidade;
	struct MinHeapNode **array;
};
 
struct MinHeapNode* novoNo(char conteudo, unsigned frequencia)
{
	struct MinHeapNode* temp = (struct MinHeapNode*) malloc(sizeof(struct MinHeapNode));
	temp->esquerda = temp->direita = NULL;
	temp->conteudo = conteudo;
	temp->frequencia = frequencia;
	return temp;
}
 
struct MinHeap* createMinHeap(unsigned capacidade)
{
	struct MinHeap* minHeap =
		 (struct MinHeap*) malloc(sizeof(struct MinHeap));
	minHeap->tamanho = 0;
	minHeap->capacidade = capacidade;
	minHeap->array =
	(struct MinHeapNode**)malloc(minHeap->capacidade * sizeof(struct MinHeapNode*));
	return minHeap;
}
 
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b)
{
	struct MinHeapNode* t = *a;
	*a = *b;
	*b = t;
}
 

void minHeapify(struct MinHeap* minHeap, int idx)
{
	int menor = idx;
	int esquerda = 2 * idx + 1;
	int direita = 2 * idx + 2;
 
	if (esquerda < minHeap->tamanho &&
	    minHeap->array[esquerda]->frequencia < minHeap->array[menor]->frequencia)
	  menor = esquerda;
 
	if (direita < minHeap->tamanho &&
	    minHeap->array[direita]->frequencia < minHeap->array[menor]->frequencia)
	  menor = direita;
 
	if (menor != idx)
	{
		swapMinHeapNode(&minHeap->array[menor], &minHeap->array[idx]);
		minHeapify(minHeap, menor);
	}
}
 
int temTamanhoIgualAUm(struct MinHeap* minHeap)
{
	return (minHeap->tamanho == 1);
}
 
struct MinHeapNode* extractMin(struct MinHeap* minHeap)
{
	struct MinHeapNode* temp = minHeap->array[0];
	minHeap->array[0] = minHeap->array[minHeap->tamanho - 1];
	--minHeap->tamanho;
	minHeapify(minHeap, 0);
	return temp;
}

void insertMinHeap(struct MinHeap* minHeap, struct MinHeapNode* minHeapNode)
{
	++minHeap->tamanho;
	int i = minHeap->tamanho - 1;
	while (i && minHeapNode->frequencia < minHeap->array[(i - 1)/2]->frequencia)
	{
		minHeap->array[i] = minHeap->array[(i - 1)/2];
		i = (i - 1)/2;
	}
	minHeap->array[i] = minHeapNode;
}
 
void buildMinHeap(struct MinHeap* minHeap)
{
	int n = minHeap->tamanho - 1;
	int i;
	for (i = (n - 1) / 2; i >= 0; --i)
		minHeapify(minHeap, i);
}
 
int ehFolha(struct MinHeapNode* root)
{
	return !(root->esquerda) && !(root->direita) ;
}

struct MinHeap* createAndBuildMinHeap(char alfabeto[], int frequencia[], int tamanho)
{
	struct MinHeap* minHeap = createMinHeap(tamanho);
	int i;
	
	for (i = 0; i < tamanho; ++i)
		minHeap->array[i] = novoNo(alfabeto[i], frequencia[i]);
	minHeap->tamanho = tamanho;
	buildMinHeap(minHeap);
	return minHeap;
}
 
// MIN-HEAP //
//////////////



void criarAlfabeto(char *texto, int tamanho_texto, char *alfabeto[], int *frequencia[], int *tamanho)
{
	int i, j;
	int caracteres[255];
	memset(&caracteres, 0x00, sizeof(caracteres));
	
	for(i = 0; i < tamanho_texto; i++)
	{
		if(caracteres[texto[i]] == 0)
			(*tamanho)++;
		caracteres[texto[i]]++;
	}
	*alfabeto  = (char*) malloc(*tamanho * sizeof(char));
	*frequencia = (int*) malloc(*tamanho * sizeof(int));
	
	for(i = 0, j = 0; i < 255; i++)
	{
		if(caracteres[i])
		{
			(*alfabeto)  [j] = i;
			(*frequencia)[j] = caracteres[i];
			j++;
		}
	}
}

struct MinHeapNode* buildHuffmanTree(char alfabeto[], int frequencia[], int tamanho)
{
	// IMPLEMENTAR!!!
	
	struct MinHeapNode *esquerda, *direita, *top;
	
	// Passo 1: Criar e Construir o MinHeap com capacidade igual ao tamanho.
	struct MinHeap* minHeap = createAndBuildMinHeap(alfabeto, frequencia, tamanho);
 
	while (!temTamanhoIgualAUm(minHeap))
	{
		// Passo 2: Extrair os dois caracteres/nos com menor frequencia da heap.
		esquerda = extractMin(minHeap);
		direita = extractMin(minHeap);
		
		// Passo 3: Criar um novo no interno com frequencia igual a soma dos nos extraidos da heap.
		// '$' eh um valor especial utilizado em nos intermediarios, nao utilizado!
		// top = novoNo('$', ???)(char conteudo, unsigned frequencia)
		// top->esquerda = ???
		// top->direita = ???
		// insertMinHeap
		top = novoNo('$', esquerda->frequencia + direita->frequencia);
        top->esquerda = esquerda;
        top->direita = direita;
        
        insertMinHeap(minHeap, top);
	}
 
	// Passo 4: Extrair o no raiz, que representa a raiz da arvore de huffman!
	return extractMin(minHeap);
}

void _generateCodesArray(struct MinHeapNode *root, codes_t codes, int aux[], int top)
{
	if (root->esquerda)
	{
		aux[top] = 0;
		_generateCodesArray(root->esquerda, codes, aux, top + 1);
	}
 
	if (root->direita)
	{
		aux[top] = 1;
		_generateCodesArray(root->direita, codes, aux, top + 1);
	}
 
	if (ehFolha(root))
	{
		int i;
		codes[root->conteudo][0] = top;
		for (i = 1; i <= top; i++)
		{
			codes[root->conteudo][i] = aux[i-1];
		}
	}
}
void generateCodesArray(struct MinHeapNode *root, codes_t codes)
{
	int aux[MAX_TREE_HT];
	memset(aux, 0x00, sizeof(aux));
	memset(codes, 0x00, sizeof(codes_t));
	_generateCodesArray(root, codes, aux, 0);
}

long sizeOfTextCompressed(char *texto, long tamanho, codes_t codes)
{
	long bits = 0;
	int i;
	
	//percorre todo o texto e conta os bits
	for(i = 0; i < tamanho; i++)
	{
		bits += codes[texto[i]][0];
	}
	
	// IMPLEMENTAR
	return bits;
}

void printCodesArray(codes_t codes)
{
	int i;
	printf("Codigos de Huffman gerados:\n");
	for(i = 0; i < 255; i++)
	{
		if(codes[i][0])
		{
			int j;
			if((char)i == '\r')
				printf("\\r: ");
			else if((char) i == '\n')
				printf("\\n: ");
			else if((char) i == '\t')
				printf("\\t: ");
			else
				printf("%c : ", (char) i);

			for (j = 1; j <= codes[i][0]; ++j)
				printf("%d", codes[i][j]);
			printf("\n");
		}
	}
}

void encode(char *texto, int tamanho, codes_t codes)
{
	int bits = 0;
	int i;
	//char *resultado;
	int index = 0;
	
	//percorre todo o texto e conta os bits
	for(i = 0; i < tamanho; i++)
	{
		//guarda o numero de bits do codigo
		bits = codes[texto[i]][0];
		
		int j;
		
		//verifica se existe valor para mostrar
		if (bits)
		{ 
			for(j=1; j <= bits; ++j)
			{
				printf("%d", codes[texto[i]][j]);
			}
		}
	}
	
	//exibe o resultado
	//printf("%s", resultado);
}

int main(int argc, char **argv)
{
	char *alfabeto;
	int *frequencia;
	int tamanho;
	int i;

	FILE *file;
	char *texto;
	int tamanho_texto;

	if(argc < 2)
	{
		printf("%s <arquivo_de_entrada>\n", argv[0]);
		abort();
	}

	file = fopen(argv[1], "r");
	if (!file)
	{
		printf("Arquivo \'%s\' invalido!\n", argv[1]);
		abort();
	}

	fseek(file, 0L, SEEK_END);
	tamanho_texto = ftell(file);
	fseek(file, 0L, SEEK_SET);
	
	texto = (char*) malloc(tamanho_texto);
	fread(texto, 1, tamanho_texto, file);
	fclose(file);
	//printf("Texto \'%s\' lido. Total de caracteres: %d.\n", argv[1], tamanho_texto);

	criarAlfabeto(texto, tamanho_texto, &alfabeto, &frequencia, &tamanho);

	//printf("Tamanho do alfabeto: %d\n Frequencia:\n", tamanho);
	/*for(i = 0; i < tamanho; i++)
	{
		if(alfabeto[i] == '\r')
			printf("\'\\r\': %d\n", frequencia[i]);
		else if(alfabeto[i] == '\n')
			printf("\'\\n\': %d\n", frequencia[i]);
		else if(alfabeto[i] == '\t')
			printf("\'\\t\': %d\n", frequencia[i]);
		else
			printf("\'%c\' : %d\n", alfabeto[i], frequencia[i]);
	}*/

	struct MinHeapNode* root = buildHuffmanTree(alfabeto, frequencia, tamanho);
 
	codes_t codes;
 	generateCodesArray(root, codes);
 
	//printCodesArray(codes);

	int quantidadeDeBits = sizeOfTextCompressed(texto, tamanho_texto, codes);
	//printf("O texto comprimido por Huffman contem %d bits (originalmente era %d bits).\n", quantidadeDeBits, tamanho_texto * 8);
	//printf("O arquivo comprimido tem %.2f%% do tamanho original.\n", 100.0f * quantidadeDeBits / (tamanho_texto * 8.0f));

	//imprime versão codificada
	encode(texto, tamanho_texto, codes);

	free(texto);
	free(alfabeto);
	free(frequencia);

	return 0;
}
