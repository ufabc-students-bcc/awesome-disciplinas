from random import choice


armarios_disponiveis =[ [0,0] , [0,1] , [0,2] , [0,4] , [0,5] , [0,6] , [0,7] , [0,8] , [0,9] , [0,10], [0,11], [0,12],
                        [1,1] , [1,2], [1,3] , [1,4] , [1,6], [1,9], [1,11] , [1,12],
                        [2,0] , [2,1] , [2,4] , [2,5] , [2,6] , [2,8] , [2,9] , [2,10] , [2,11] , [2,12],
                        [3,0] , [3,3] , [3,4] , [3,5] , [3,8] , [3,10] , [3,11],
                        [4,0] , [4,1] , [4,2] , [4,3] , [4,5] , [4,6] , [4,7] , [4,8] , [4,9] , [4,11] ]                         
alvo = [2,12]
posicao_atual = [2,0]
CUSTO_MOVIMENTO = 1
custo_atual = 0
custo_otimo = 100000
iteracoes = 10000000
caminho_otimo = []
caminho_ja_percorrido = [2,0]
posicao_nova=[1,1]
print("\n")

for a in range(iteracoes):

    if (0 < posicao_nova[0] < 4 ):
        posicao_nova[0] = posicao_atual[0] + choice([-1, 0, 1])
    if (0 < posicao_nova[1] < 12):
        posicao_nova[1] = posicao_atual[1] + choice([-1, 0, 1])
    
    if posicao_nova[0] == 0:
        posicao_nova[0] = posicao_atual[0] + choice([0, 1])
    if posicao_nova[1] == 0:
        posicao_nova[1] = posicao_atual[1] + choice([0, 1])
    
    if posicao_nova[0] == 4:
        posicao_nova[0] = posicao_atual[0] + choice([0, -1])
    if posicao_nova[1] == 12:
        posicao_nova[1] = posicao_atual[1] + choice([0, -1])
    
    if posicao_nova[0] < 0:
        posicao_nova[0] = posicao_atual[0] + 1
    if posicao_nova[1] < 0:
        posicao_nova[1] = posicao_atual[1] + 1
  
    if posicao_nova in armarios_disponiveis and abs(posicao_atual[0]-posicao_nova[0])<=1 and abs(posicao_atual[0]-posicao_nova[0])<=1:
        posicao_atual = posicao_nova
        custo_atual += CUSTO_MOVIMENTO
        
        if posicao_atual not in caminho_ja_percorrido:
                caminho_ja_percorrido.extend(posicao_atual)
                      

        if posicao_atual == alvo:
            if custo_otimo >= custo_atual:
                custo_otimo = custo_atual
                posicao_atual = [2,0]
                custo_atual = 0
                caminho_otimo = caminho_ja_percorrido
                caminho_ja_percorrido = [2,0]
                
            else:
                posicao_atual 
                posicao_atual = [2,0]
                custo_atual = 0
                caminho_ja_percorrido = [2,0]
    print(" % da busca realizada, aguarde... \r ", round((a/iteracoes)*100, 1), end = '')
print("\n")
print("---------------------------RESULTADOS---------------------------------- ")
print("O menor numero de dias encontrado é: ", custo_otimo)  
a=0
b=1
caminho_otimo_ajustado = []
for i in range(int(len(caminho_otimo)/2)):
        caminho_otimo_ajustado.append([caminho_otimo[a], caminho_otimo[b]])
        a+=2
        b+=2
print("O melhor caminho encontrado a ser realizado é: \n", caminho_otimo_ajustado)

#       MATRIX
#   O O O X O O O O O O O O O
#		C O O O O X O X X O X O O
#		V O X X O O O X O O O O A
#		O X X O O O X X O X O O M
#		O O O O X O O O O O X O X
