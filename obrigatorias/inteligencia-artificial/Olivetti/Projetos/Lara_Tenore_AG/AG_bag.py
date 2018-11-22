#Lara Tenore Ferreira RA: 11030616
#algoritmo genetico
#problema da mochila usando livros com pesos aleatorios

import copy
import random

#Global
num_livros = 10
tam_populacao = 20
max_carga = 30
num_ciclos = 1000
populacao = []
pesos = []
scores_aptidao = [0.0]*tam_populacao
aux_populacao = [[0]*50]*50
taxaPopAux = -1

def selecaoSimples():
	return random.randint(0,tam_populacao-1)

def atribuiPesos():
        global pesos
        
        for i in range(num_livros-1):
            pesos.append(random.randint(1,3))

        print("PESOS: "+str(pesos)+"\n")

def criacaoPI():
		global populacao

		for i in range(tam_populacao):
			ind = []
			for i in range(num_livros):
				ind.append(random.randint(0,1))
			populacao.append(ind)
		print("POPULACAO: "+str(populacao))


def bestIndividuo():
		global populacao,scores_aptidao
		m = 0

		for i in range(1,tam_populacao-1):
			if scores_aptidao[m] < scores_aptidao[i]:
				m = i
		
		print("Best: " + scores_aptidao[m] + " >>>>> ");
		print(" " + populacao[m][i]+"\n")

def addPopAux(des):
		global taxaPopAux
		global aux_populacao

		taxaPopAux +=1
		aux_populacao[taxaPopAux] = des.copy()
        

def cruzamentoSimples():		
		global scores_aptidao
		global populacao

		i1 = -1
		i2 = -1
		ind1 = [0] * num_livros
		ind2 = [0] * num_livros
		des1 = [0] * num_livros
		des2 = [0] * num_livros

		#I1 SELECIONA O INDICE DO MELHOR EM scores_aptidao
		#I2 SELECIONA INDICE ALEATORIAMENTE (SELECAO SIMPLES)
		i1 = scores_aptidao.index(max(scores_aptidao))
		i2 = selecaoSimples()
		
		while i1 == i2:
			i2 = selecaoSimples()
		
		for i in range(num_livros-1):
			ind1[i] = populacao[i1][i]
			ind2[i] = populacao[i2][i]
		
		for i in range(num_livros-1):
			if i < num_livros/2:
				des2[i] = ind2[i]
				des1[i] = ind1[i]
			else:
				des2[i] = ind1[i]
				des1[i] = ind2[i]
		
		addPopAux(des1)
		addPopAux(des2)

def mutacao():
		global populacao
		
		i1 = -1;
		ind1 = [0]*num_livros
		i1 = selecaoSimples()
		
		for a in range(num_livros-1):
			ind1[a] = populacao[i1][a]
		
		i = random.randint(0,num_livros-1)
		
		if ind1[i] == 1:
			ind1[i] = 0
		else:
			ind1[i] = 1

		addPopAux(ind1)

def avaliacao():
		global scores_aptidao

		peso = 0.0

		for a in range(tam_populacao-1):
			for b in range(num_livros-1):
				peso += populacao[a][b] * pesos[b]

			if peso > max_carga:
				peso = 0.0

			scores_aptidao[a] = peso
			peso = 0.0

def bestIndividuo():
		m = 0

		for i in range(tam_populacao-1):
			if scores_aptidao[m] < scores_aptidao[i]:
				m = i

		print("Best: " + str(scores_aptidao[m]) + " >>>>> ");
		print(" " + str(populacao[m])+"\n")
        
def substituicao():
		global taxaPopAux
		global populacao

		populacao = copy.deepcopy(aux_populacao[:tam_populacao])
		taxaPopAux = -1

#INICIO
ciclo = 0

#CRIACAO DA POPULACAO INICIAL E SELECAO INICIAL
atribuiPesos()
criacaoPI()
avaliacao()
bestIndividuo()

#INICIO DOS CRUZAMENTOS E MUTACOES
while ciclo < num_ciclos:
	for i in range(9):
		cruzamentoSimples()
		mutacao()
		mutacao()
		substituicao()
		avaliacao()
		bestIndividuo()
		
		ciclo+=1
