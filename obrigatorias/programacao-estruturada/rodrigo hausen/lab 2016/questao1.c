/* questao1.c */
//tudo errado (p2)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct pilha_char {
	char *dado;
	struct pilha_char *proximo;
	struct pilha_char *anterior;
};

int corretamente_aninhados(const char *s) {
  /* IMPLEMENTAR */
	struct pilha_char *primeiro = malloc(sizeof(struct pilha_char *));
	primeiro->dado = NULL;
	primeiro->anterior = NULL;
	
	int tamanho = strlen(s);
	char p = '(';
	char ap = ')';
	char c = '[';
	char ac = ']';
	char c1 = '{';
	char ac1 = '}';
	
	//coloca na pilha
	for(int i = 0; i < tamanho; i++)
	{
	    struct pilha_char *novo = malloc(sizeof(struct pilha_char *));
	    int teveNovo = 0;
	    
	    if(novo == NULL) return 0;
	    
	    if(s[i] == p)
	    {
	        novo->dado = &p;
	        novo->anterior = primeiro;
	        primeiro->proximo = novo;
	        
	        primeiro = novo;
	        teveNovo = 1;
	    }
	    
	    if(s[i] == c)
	    {
	        novo->dado = &c;
	        novo->anterior = primeiro;
	        primeiro->proximo = novo;
	        
	        primeiro = novo;
	        teveNovo = 1;
	    }
	    
	    if(s[i] == c1)
	    {
	        novo->dado = &c1;
	        novo->anterior = primeiro;
	        primeiro->proximo = novo;
	        
	        primeiro = novo;
	        teveNovo = 1;
	    }
	    
	    if(s[i] == ap)
	    {
	        puts("p");
	        if(novo->dado != &p) return 0;
	        
	        novo = primeiro;
	        primeiro = primeiro->anterior;
	    }
	    
	    if(s[i] == ac)
	    {
	        printf("%s",novo->dado);
	        if(novo->dado != &c) return 0;
	        
	        novo = primeiro;
	        primeiro = primeiro->anterior;
	    }
	    
	    if(s[i] == ac1)
	    {
	        puts("c1");
	        if(novo->dado != &c1) return 0;
	        
	        novo = primeiro;
	        primeiro = primeiro->anterior;
	    }
	    
	    if(teveNovo == 0) free(novo);
	}
	
	if(primeiro->dado != NULL) return 0;
	return 1;
}

/* ==========================================
 *  DAQUI PARA BAIXO, NÃO MEXA NESTE ARQUIVO 
 * ==========================================
 */
/* testes */
#include <stdio.h>

#define TRUE 1
#define FALSE 0

struct test {
  const char *s;
  int esperado;
};

const char *vouf(int valor) {
  return valor ? "VERDADEIRO" : "FALSO";
}

int main(void) {
  struct test tests[] = {
    { "", TRUE },
    { "foo bar baz", TRUE },
    { "{ [ ] ( ) }", TRUE },
    { "foo { bar [ baz ] 123 ( 456 ) 9 };", TRUE },
    { "(", FALSE },
    { "]", FALSE },
    { "{ [ }", FALSE },
    { "{ [ } ]", FALSE },
    { "{ [ ( ] ) }" , FALSE }
  };

  size_t i;
  int ok = 1;
  for (i=0; i < sizeof(tests)/sizeof(tests[0]); ++i) {
    struct test *t = &tests[i];
    int resultado = corretamente_aninhados(t->s);
    if (!resultado == !t->esperado) {
      fprintf(stderr, "OK para \"%s\" (resultado é %s)\n",
                      t->s, vouf(t->esperado));
    } else {
      fprintf(stderr, "ERRO para \"%s\" (resultado é %s, mas devia ser %s)\n",
                      t->s, vouf(resultado), vouf(t->esperado));
      ok = 0;
    }
  }

  return !ok;
}