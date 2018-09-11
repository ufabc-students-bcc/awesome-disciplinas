/* questao2.c */
//Dados corretos (p2)

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct carta {
  char figura;
  char naipe;
};

/* Retorna um inteiro entre 0 e n-1 */
size_t sorteia(size_t n);

int imprime_carta(const struct carta *carta, FILE *stream) {
  /* IMPLEMENTAR */

	char *naipe;
	char *figura;

	naipe = '\0';
	figura = '\0';

	if(carta->figura == 'A') figura = "as de";
	if(carta->figura == '2') figura = "2 de";
	if(carta->figura == '3') figura = "3 de";
	if(carta->figura == '4') figura = "4 de";
	if(carta->figura == '5') figura = "5 de";
	if(carta->figura == '6') figura = "6 de";
	if(carta->figura == '7') figura = "7 de";
	if(carta->figura == '8') figura = "8 de";
	if(carta->figura == '9') figura = "9 de";
	if(carta->figura == 'X') figura = "10 de";
	if(carta->figura == 'J') figura = "valete de";
	if(carta->figura == 'Q') figura = "dama de";
	if(carta->figura == 'K') figura = "rei de";

	if(carta->naipe == 'e') naipe = "espadas";
	if(carta->naipe == 'p') naipe = "paus";
	if(carta->naipe == 'o') naipe = "ouros";
	if(carta->naipe == 'c') naipe = "copas";

	if(naipe == '\0') 
	{
		puts("CARTA INVALIDA");
		return 1;
	}

	if(figura == '\0') 
	{
		puts("CARTA INVALIDA");
		return 1;
	}

	printf("%s %s", figura, naipe);

	return 1;
}

struct carta *cria_baralho(void) {
  /* IMPLEMENTAR */
	char *naipes = "ecop";
	char *figuras = "A23456789XJQK";
	int pos = 0; //posição no array
	int i;
	int j;

	struct carta *baralho = (struct carta *) malloc(52 * sizeof(struct carta *));
	if(baralho == NULL) return 0;

	for(i = 0; i < 4; i++)
	{
		for(j = 0; j < 13; j++)
		{
			baralho[pos].figura = figuras[j];
			baralho[pos].naipe = naipes[i];
			pos++; 
		}
	}

	return baralho;
}

void embaralha(struct carta *cartas, size_t n) {
  /* IMPLEMENTAR */
	int tamanho = (int) n;
	int i;

	for(i = tamanho - 1; i >= 0; i--)
	{
			int sorteado = sorteia(n);
			struct carta auxiliar = cartas[i];
			cartas[i] = cartas[sorteado];
			cartas[sorteado] = auxiliar;
	}
}

/* ==========================================
 *  DAQUI PARA BAIXO, NÃO MEXA NESTE ARQUIVO 
 * ==========================================
 */
size_t sorteia(size_t n) {
  return (size_t)(1.0*n*rand()/(RAND_MAX+1.0));
}

/* TESTES */
#include <string.h>

void testaq2a() {
  struct carta exemplos[] = { { 'X', 'p' },
                              { 'A', 'c' },
                              { '7', 'e' },
                              { 'K', 'o' },
                              { 'Z', 'p' } };

  fprintf(stderr, "Vou executar imprime_carta para as "
                  "%zu cartas de exemplo.\n\n",
                  sizeof(exemplos)/sizeof(exemplos[0]));
  size_t i;
  for (i = 0; i < sizeof(exemplos)/sizeof(exemplos[0]); ++i) {
    printf("%zu) ", i+1);
    imprime_carta(exemplos + i, stdout);
    puts("");
  }
  fprintf(stderr, "\nCompare o resultado acima com o esperado:\n\n");
  fprintf(stderr, "1) 10 de paus\n");
  fprintf(stderr, "2) as de copas\n");
  fprintf(stderr, "3) 7 de espadas\n");
  fprintf(stderr, "4) rei de ouros\n");
  fprintf(stderr, "5) CARTA INVALIDA\n");
  fprintf(stderr, "\nConfira se a sua função fez a impressão "
                  "EXATAMENTE como acima.\nConfira, em especial, o "
                  "espaçamento entre palavras e entre linhas,\n"
                  "maiúsculas/minúsculas e a descrição das cartas.\n\n");
}

static const struct carta baralho_completo[] = {
  { 'A', 'e' }, { '2', 'e' }, { '3', 'e' }, { '4', 'e' },
  { '5', 'e' }, { '6', 'e' }, { '7', 'e' }, { '8', 'e' },
  { '9', 'e' }, { 'X', 'e' }, { 'J', 'e' }, { 'Q', 'e' },
  { 'K', 'e' },
  { 'A', 'c' }, { '2', 'c' }, { '3', 'c' }, { '4', 'c' },
  { '5', 'c' }, { '6', 'c' }, { '7', 'c' }, { '8', 'c' },
  { '9', 'c' }, { 'X', 'c' }, { 'J', 'c' }, { 'Q', 'c' },
  { 'K', 'c' },
  { 'A', 'o' }, { '2', 'o' }, { '3', 'o' }, { '4', 'o' },
  { '5', 'o' }, { '6', 'o' }, { '7', 'o' }, { '8', 'o' },
  { '9', 'o' }, { 'X', 'o' }, { 'J', 'o' }, { 'Q', 'o' },
  { 'K', 'o' },
  { 'A', 'p' }, { '2', 'p' }, { '3', 'p' }, { '4', 'p' },
  { '5', 'p' }, { '6', 'p' }, { '7', 'p' }, { '8', 'p' },
  { '9', 'p' }, { 'X', 'p' }, { 'J', 'p' }, { 'Q', 'p' },
  { 'K', 'p' }
};

int testaq2b() {
  fprintf(stderr, "Testando baralho gerado por cria_baralho...\n");
  struct carta *baralho = cria_baralho();
  size_t i;
  int erro = 0;
  for (i = 0; i<52; ++i) {
    if (baralho[i].figura != baralho_completo[i].figura ||
        baralho[i].naipe != baralho_completo[i].naipe) {
      fprintf(stderr, "Carta diferente para i=%zu "
                      "(é '%c', '%c' mas deveria ser '%c', '%c')\n",
             i, baralho[i].figura, baralho[i].naipe,
             baralho_completo[i].figura, baralho_completo[i].naipe);
      ++erro;
    }
  }
  printf("%d erro(s) encontrado(s)\n", erro);
  fprintf(stderr, "Vou desalocar região de memória alocada "
                  "por cria_baralho.\n");
  fprintf(stderr, "O programa deve terminar normalmente, "
                  "sem falha de segmentação.\n");
  free(baralho);
  fprintf(stderr, "Região desalocada. Terminando programa\n");
  return erro;
}

int compara_carta(const void *c1, const void *c2) {
  struct carta *carta1 = (struct carta *)c1;
  struct carta *carta2 = (struct carta *)c2;
  char str1[3] = { carta1->figura, carta1->naipe, '\0' };
  char str2[3] = { carta2->figura, carta2->naipe, '\0' };
  return strcmp(str1, str2);
}

#include <time.h>

#define NTRIES 50

int testaq2c() {

  struct carta baralho_teste[] = {
    { 'A', 'e' }, { '2', 'e' }, { '3', 'e' }, { '4', 'e' },
    { '5', 'c' }, { '6', 'c' }, { '7', 'c' }, { '8', 'c' },
    { '9', 'o' }, { 'X', 'o' }, { 'J', 'o' }, { 'Q', 'o' },
    { '9', 'p' }, { 'X', 'p' }, { 'J', 'p' }, { 'Q', 'p' },
    { 'K', 'e' }
  };
  size_t n = sizeof(baralho_teste)/sizeof(baralho_teste[0]);

  struct carta baralho_teste_copia1[n];
  struct carta baralho_teste_copia2[n];

  qsort(baralho_teste, n, sizeof(struct carta), compara_carta);
  memcpy(baralho_teste_copia1, baralho_teste, sizeof(baralho_teste));
  memcpy(baralho_teste_copia2, baralho_teste, sizeof(baralho_teste));

  embaralha(baralho_teste_copia1, n);
  embaralha(baralho_teste_copia2, n);

  if (memcmp(baralho_teste, baralho_teste_copia1,
             sizeof(baralho_teste)) == 0) {
    fprintf(stderr, "Baralho não foi embaralhado!\n");
    return 1;
  }

  if (memcmp(baralho_teste_copia1, baralho_teste_copia2,
             sizeof(baralho_teste)) == 0) {
    fprintf(stderr, "Embaralhamento incorreto!\n"
                    "A função embaralha é determinística!\n");
    return 1;
  }

  qsort(baralho_teste_copia1, n, sizeof(struct carta), compara_carta);

  if (memcmp(baralho_teste, baralho_teste_copia1,
             sizeof(baralho_teste)) != 0) {
    fprintf(stderr, "Função embaralha está corrompendo o baralho!\n");
    return 1;
  }

  fprintf(stderr, "Função embaralha provavelmente funciona.\n");

  return 0;
}

void ajuda_e_sai(void) {
  fprintf(stderr, "Uso: questao2 a|b|c\n");
  exit(2);
}

int main(int argc, char *argv[]) {
  srand(time(NULL)); /* inicializa gerador aleatório */

  if (argc > 1) {
    switch(argv[1][0]) {
    case 'a':
      testaq2a();
      return 0;
    case 'b':
      return testaq2b();
    case 'c':
      return testaq2c();
    }
  }
}