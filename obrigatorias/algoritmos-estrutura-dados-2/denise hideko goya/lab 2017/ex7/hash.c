#include <stdio.h>
#include <stdlib.h>

#define M 2039
// Tamanho da tabela.

#define hash(v, M) (v % M)
// Transforma uma chave v em um índice no intervalo 0..M-1.

#define tipoChave long int

struct tipoObj {
   tipoChave chave;
   char valor;
};
typedef struct tipoObj tipoObjeto;

tipoObjeto objetonulo;

// Definição de um nó das listas de colisões.
typedef struct node *link;
struct node {
   tipoObjeto obj; 
   link       next;
} ;
typedef struct node STnode;

// Tabela que aponta para as M listas de colisões.
link *tab;
// Inicializa uma tabela de símbolos que, espera-se, armazenará 
// cerca de 10000 objetos. A espinha dorsal da tabela será um 
// vetor tab[0..M-1].
//
void STinit() 
{ 
   int h;
   tab = malloc(M * sizeof (link));
   for (h = 0; h < M; h++) 
      tab[h] = NULL; 
}

//verifica a quantidade máxima de colisões
int maisColisoes()
{
   int h;
   int max = 0;
   
   for (h = 0; h < M; h++) 
   {
      int n = calculaTamanho(tab[h]);
      
      if(n > max)
         max = n;
   }
   
   return max;
}

int semChave()
{
   int h;
   int max = 0;
   
   for (h = 0; h < M; h++) 
   {
      if(tab[h] == NULL)
         max++;
   }
   
   return max;
}

//calcula quantidade de colisoes
int calculaTamanho(link teste)
{
   if(teste == NULL)
      return 0;
   
   int tamanho = 1;
   
   tamanho += calculaTamanho(teste->next);
   
   return tamanho;
}

// Insere obj na tabela de símbolos.
//
void STinsert(tipoObjeto obj) 
{ 
   int h;
   tipoChave v = obj.chave;
   h = hash(v, M);

//printf ("ra=%d hash=%d\n", obj.chave, h);

   //insere na frente da lista
   link novo = malloc(sizeof (STnode));
   novo->obj = obj;
   novo->next = tab[h];
   tab[h] = novo;
}

// Devolve um objeto cuja chave é v. Se tal objeto não existe,
// a função devolve um objeto fictício com chave nula.
//
tipoObjeto STsearch(tipoChave v) 
{ 
   link t;
   int h;
   h = hash(v, M);
   for (t = tab[h]; t != NULL; t = t->next) 
      if (t->obj.chave == v) break;
   if (t != NULL) return t->obj;
   return objetonulo;
}

int existe(tipoChave chave)
{
   tipoObjeto obj = STsearch(chave);
   return obj.chave != objetonulo.chave;
}

/****************************************************************************
/* Completar estatisticas, para calcular e exibir:
/*  . quantidade de chaves na tabela hash
/*  . fator de carga da tabela hash
/*  . maior comprimento das listas de colisões
/*  . quantidade de compartimentos da tabela sem chave
/****************************************************************************/
void estatisticas (int n) 
{
	printf ("Quantidade de chaves = %d\n",n);

	printf ("Fator de Carga = %f\n", (double )n/ (double) M);

	printf ("Maior comprimento das listas de colisões: %d\n", maisColisoes());

	printf ("Compartimentos sem chave: %d\n", semChave());

}

int main()
{
    tipoChave ra;
	tipoObjeto *obj;

	STinit();
	objetonulo.chave = 0; // Chaves "válidas" são estritamente positivas

	scanf("%ld", &ra);
	
	int n = 0;

	// le uma sequencia de RAs, encerrada por um negativo
	while (ra >0) {
		if (!existe(ra)) { // se chave nao existe na tabela, insere
			obj = malloc(sizeof (tipoObjeto));
			obj->chave = ra;
			STinsert(*obj);
			
			n++;
		}
    	scanf("%ld", &ra);
	}
	
	estatisticas(n);	

}

