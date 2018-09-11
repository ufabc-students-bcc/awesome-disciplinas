/* questao3.c */
//exercicio A certo
//exercicio B certo

#include <stdio.h>
#include <stdlib.h>

/* Dica: se tiver que converter um byte (unsigned char) para outro tipo,
   use as funções abaixo. */
int byte_para_int(unsigned char c);
long byte_para_long(unsigned char c);

void imprime_hexadecimal(FILE *stream) {
  /* IMPLEMENTAR */
	int pos = 0;
	int lidos = 0;
	int verificar = 1;
	int continuar = 1;

	while(continuar != 0)
	{
		lidos = 0;
		verificar = 1;
		while(lidos < 8)
		{
			int byte = fgetc(stream);
			if(byte >= 0)
			{
				if(verificar == 1) 
				{
					printf("%05x  ", pos);
					verificar = 0;
				}

				printf("%02x ", byte);
				lidos++;
			}
			else
			{	
				continuar = 0;
				lidos = 8;
			}
			pos++;
		}
		printf("\n");
	}

    fflush(stdout);
}

long le_long_binario(FILE *stream, size_t n) {
  /* IMPLEMENTAR */

	long numero = 0;

	for(int i=0; i < n; i++)
	{
	  int byte = fgetc(stream);
	  int potencia = 1;
	  
	  if(byte < 0) return -1;
	  
	  if(i > 0)
	  {
	    potencia = 256;
  	  for(int j = 1; j < i; j++)
  	  {
  	    potencia = potencia * 256;
  	  }
	  }
	  //printf(" -> %d * %d - \n", byte, potencia);
	  byte = byte * potencia;
	  numero = numero + byte;
	}
	
	//printf("---> %ld <--", numero);
	return numero;

}

long escreve_long_binario(FILE *stream, size_t n, long valor) {
  /* IMPLEMENTAR */
  long *numeros = malloc(sizeof(long)*(n)); //array com os números a serem adicionados
  if(numeros == NULL) return -1;
  
  long valorOriginal = valor;
  
  for(int i = n - 1; i >= 0; i--)
  {
    int potencia = 1;
    
    //calcula a potencia
    if(i > 0)
    {
      potencia = 256;
      
      //se for maior que 1
      for(int j = 1; j < i; j++)
      {
        potencia = potencia * 256;
      }
    }
    
    int numeroQueMultiplica = 0;
    
    if(i > 0)
    {
      //conta quantas vezes é possivel subtrair a potencia atual
      //do valor
      while((valor - potencia) > 0)
      {
        numeroQueMultiplica++;
        valor = valor - potencia;
      }
    }
    else numeroQueMultiplica = valor;
    
    //salva o valor na posição certa
    numeros[i] = numeroQueMultiplica;
    
    fputc(numeroQueMultiplica, stream);
    
    //printf("%d: ->%ld potencia: %d - ",i, numeros[i], potencia);
  }
  
  //escreve na stream
  //fwrite(numeros, n, sizeof(numeros[0]), stream);
  
  long resultado = le_long_binario(stream, n);
  //printf(" -> %ld <- ", resultado);

  free(numeros);
  return valorOriginal;
}

/*
 * ==========================================
 *  DAQUI PARA BAIXO, NÃO MEXA NESTE ARQUIVO 
 * ==========================================
 */
int byte_para_int(unsigned char c) {
  return (c & 0xff);
}

long byte_para_long(unsigned char c) {
  return (c & 0xff);
}

/* TESTES */
#include <stdlib.h>

FILE *abre(const char *arq) {
  FILE *f = fopen(arq, "rb");

  if (f == NULL) {
    fprintf(stderr, "Arquivo %s nao pode ser aberto!\n"
                   "Ele se encontra na mesma pasta que o executavel?\n",
                   arq);
    exit(9);
  }

  return f;
}

#define FLAG_NAO_AGUARDA_ENTER 0
#define FLAG_AGUARDA_ENTER 1
#define FLAG_LIMPA_TELA 2

void testaq3a_parte(const char *arq, const char *esperado,
                    int flags) {
  FILE *f = abre(arq);

  if (flags & FLAG_LIMPA_TELA) {
    fprintf(stderr, "%c[2J%c[;H", 27, 27); /* limpa tela */
  }

  fprintf(stderr, "Vou executar a função imprime_hexadecimal com a\n"
                  "stream aberta a partir de %s. Veja o\n"
                  "resultado abaixo:\n\n", arq);
  imprime_hexadecimal(f);

  fprintf(stderr, "\nCompare com a saída esperada. É igual?\n\n");

  fprintf(stderr, "%s", esperado);

  fprintf(stderr, "\nPressione ENTER para continuar o teste ou Ctrl + C para terminar. ");

  if (flags & FLAG_AGUARDA_ENTER) {
    int ch;
    do { ch = getchar(); } while (ch != '\n' && ch != EOF);
  }
}

void testa_q3a(void) {
  testaq3a_parte("q3ex1.bin", "00000  25 50 44 46 2d 31 2e 34 \n"
                              "00008  0a 25 d0 d4 c5 d8 0a 33 \n"
                              "00010  20 30 20 6f 62 6a 20 3c \n"
                              "00018  3c 0a 2f 4c 65 6e 67 74 \n",
                 FLAG_AGUARDA_ENTER|FLAG_LIMPA_TELA );

  testaq3a_parte("q3ex2.bin", "00000  50 25 46 44 31 2d 34 2e \n"
                              "00008  25 0a d4 d0 d8 \n",
                 FLAG_AGUARDA_ENTER|FLAG_LIMPA_TELA );

  testaq3a_parte("q3ex3.bin", "00000  0a 20 01 \n",
                 FLAG_AGUARDA_ENTER|FLAG_LIMPA_TELA );

  testaq3a_parte("q3ex4.bin", "00000  0a 20 01 22 fa 09 3f \n",
                 FLAG_AGUARDA_ENTER|FLAG_LIMPA_TELA );
}

void testa_q3b(void) {
  FILE *f = abre("q3ex3.bin");
  long n = le_long_binario(f, 3);
  fprintf(stderr, "Leu %d dos primeiros 3 bytes de q3ex3.bin?\n", 0x01200a);
  if (n == 0x01200a) {
    printf("OK\n");
  } else {
    printf("ERRO. Leu %ld\n", n);
  }
  fprintf(stderr, "Próximo le_long_binario de q3ex3.bin retorna -1?\n");
  n = le_long_binario(f, 1);
  if (n == -1) {
    printf("OK\n");
  } else {
    printf("ERRO. Retornou %ld\n", n);
  }
  fclose(f);
  f = abre("q3ex4.bin");
  n = le_long_binario(f, 3);
  fprintf(stderr, "Leu %d dos primeiros 3 bytes de q3ex4.bin?\n", 0x01200a);
  if (n == 0x01200a) {
    printf("OK\n");
  } else {
    printf("ERRO. Leu %ld\n", n);
  }
  n = le_long_binario(f, 4);
  fprintf(stderr, "Leu %d dos primeiros 4 bytes de q3ex4.bin?\n", 0x3f09fa22);
  if (n == 0x3f09fa22) {
    printf("OK\n");
  } else {
    printf("ERRO. Leu %ld\n", n);
  }
  fprintf(stderr, "Próximo le_long_binario de q3ex4.bin retorna -1?\n");
  n = le_long_binario(f, 1);
  if (n == -1) {
    printf("OK\n");
  } else {
    printf("ERRO. Retornou %ld\n", n);
  }
  fclose(f);
}

void testa_q3c(void) {
  FILE *f = fopen("testeq3ex3.bin", "wb");
  if (f == NULL) {
    fprintf(stderr, "ERRO! Não pude abrir testeq3c1.bin.");
    exit(3);
  }
  long val = escreve_long_binario(f, 3, 0x01200a);
  if (val != 0x01200a) {
    fprintf(stderr, "ERRO! escreve_long_binario retornou %ld em vez de %ld.",
                    val, (long)0x01200a);
    exit(1);
  }
  fclose(f);
  f = fopen("testeq3ex4.bin", "wb");
  if (f == NULL) {
    fprintf(stderr, "ERRO! Não pude abrir testeq3ex4.bin.");
    exit(3);
  }
  val = escreve_long_binario(f, 3, 0x01200a);
  if (val != 0x01200a) {
    fprintf(stderr, "ERRO! escreve_long_binario retornou %ld em vez de %ld.",
                    val, (long)0x01200a);
    exit(1);
  }
  val = escreve_long_binario(f, 4, 0x3f09fa22);
  if (val != 0x3f09fa22) {
    fprintf(stderr, "ERRO! escreve_long_binario retornou %ld em vez de %ld.",
                    val, (long)0x3f09fa22);
    exit(1);
  }
  fclose(f);

  fprintf(stderr, "Compare o arquivo q3ex3.bin com testeq3ex3.bin. "
                  "Eles devem ser iguais\n"
                  "Compare o arquivo q3ex4.bin com testeq3ex4.bin. "
                  "Eles devem ser iguais\n");
}

void imprime_ajuda_e_sai(void) {
  fprintf(stderr, "Uso: questao3 a|b|c\n");
  exit(1);
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    imprime_ajuda_e_sai();
  }

  switch (argv[1][0]) {
  case 'a':
    testa_q3a();
  break;
  case 'b':
    testa_q3b();
  break;
  case 'c':
    testa_q3c();
  break;
  default:
    imprime_ajuda_e_sai();
  }
  return 0;
}