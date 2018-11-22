# Cavalos dominantes

O prolema de dominação consiste em posicionar várias peças de xadrez de um determinado tipo de forma a atacar todas as casas não ocupadas do tabuleiro (ou todas as 64 casas, como foi feito aqui).
Este problema é um caso especial do problema de cobertura de vértices, que é [NP-Completo](https://en.wikipedia.org/wiki/Mathematical_chess_problem#Domination_problems).
Este algoritmo tenta encontrar uma solução para o caso em que todas 

# Algoritmo

O algoritmo escolhido foi o A*, utilizando como h(x) o número de casas ainda não atacadas e g(x) crescendo em 1 a cada nível da árvore.

## Resultado

O algoritmo encontra rapidamente uma solução não ótima, utilizando 17 cavalos para cobrir todo o tabuleiro enquanto a solução ótima utiliza 14.

    ['K', ' ', ' ', ' ', ' ', ' ', ' ', ' ']
    [' ', ' ', 'K', ' ', 'K', ' ', ' ', ' ']
    [' ', ' ', 'K', ' ', ' ', ' ', 'K', ' ']
    ['K', ' ', ' ', ' ', 'K', 'K', 'K', ' ']
    ['K', ' ', ' ', ' ', 'K', ' ', 'K', ' ']
    [' ', ' ', 'K', ' ', ' ', ' ', 'K', ' ']
    [' ', ' ', 'K', ' ', 'K', ' ', ' ', ' ']
    [' ', ' ', ' ', ' ', 'K', ' ', ' ', ' ']
    // 'K' são posições com cavalos
    // ' ' são casas vazias
  
Como o maior número de casas que um cavalo pode atacar é 8, provavelmente, mudar g(x) para aumentar em 7 a cada nível da árvore faria com que o algoritmo encontrasse uma solução ótima, porém aumentar o crescimento de g(x) para além de 1 já faz com que o programa demore muito para terminar.

	Ramon Neres Teixeira Jardim
	RA: 11068616
