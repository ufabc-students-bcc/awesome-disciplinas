#include <stdio.h>
#include <stdlib.h>

struct Aresta {
    int origem, destino;
};
typedef struct Aresta aresta;
 
struct Grafo {
    int V; // Numero de vertices
    int E; // Numero de arestas
    
    // O grafo eh representado por um vetor de arestas
    aresta* VetorDeArestas; 
};
typedef struct Grafo grafo;

grafo* criarGrafo(int V, int E) {
    grafo* g = (grafo*) malloc( sizeof(grafo) );
    g->V = V;
    g->E = E;
    
    g->VetorDeArestas = (aresta*) malloc(g->E * sizeof(aresta) );
 
    return g;
}
 
// Funcao que procura o representante do elemento i
int Find_Set(int pai[], int i) {
    if (pai[i] == i)
        return i;
    return Find_Set(pai, pai[i]);
}
 
// Funcao que junta os conjuntos de x e y.
void Union(int pai[], int x, int y) {
    int rx = Find_Set(pai, x);
    int ry = Find_Set(pai, y);
    pai[rx] = ry;
}
 
// Funcao utilizada para verificar se o grafo tem ou nao ciclo
int temCiclo( grafo* g ) {
    int i, j;
    int pai[g->V];
 
    for (i=0; i<g->V; i++)
        pai[i] = i;

    for(j=0; j<g->E; j++) {
        int rx = Find_Set(pai, g->VetorDeArestas[j].origem);
        int ry = Find_Set(pai, g->VetorDeArestas[j].destino);
 
        if (rx==ry)
            return 1;
            
        Union(pai, rx, ry);
    }
    return 0;
}
 

int main()
{
    int nV, nE, k;
    scanf("%d", &nV);
    scanf("%d", &nE);
    
    grafo* g = criarGrafo(nV, nE);
 
    for(k=0; k<g->E; k++) {
        int p, q;
        scanf("%d", &p);
        scanf("%d", &q);
        g->VetorDeArestas[k].origem = p;
        g->VetorDeArestas[k].destino = q;    
    }

    if (temCiclo(g))
        printf("\nGrafo contem ciclo\n");
    else
        printf("\nGrafo nao contem ciclo\n");
}

