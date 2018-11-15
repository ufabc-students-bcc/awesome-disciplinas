#!/usr/bin/env python
# marioAstar.py
# Author: Fabrício Olivetti de França
#
# A* algorithm for Super Mario World
# using RLE

import sys
import os
import pickle
import retro

from rominfo import *
from utils import *

sys.setrecursionlimit(10000)

# quais movimentos estarão disponíveis
moves = {'direita':128, 'corre':130, 'pula':131, 'spin':386, 'esquerda':64}

# raio de visão (quadriculado raio x raio em torno do Mario)
raio = 6

# Classe da árvore de jogos para o Super Mario World
class Tree:
    def __init__(self, estado, filhos=None, pai=None, g=0, h=0, terminal=False, obj=False):
        self.estado   = estado
        self.filhos   = filhos # lista de filhos desse nó
        
        self.g = g
        self.h = h
        
        self.eh_terminal = terminal
        self.eh_obj      = obj
        
        self.pai = pai # apontador para o pai, útil para fazer o backtracking

    def __str__(self):
        return self.estado
  
def melhor_filho(tree):
    '''
    Encontra o melhor filho do nós representado por tree.
    
    Entrada: tree, o nó atual da árvore
    Saída:   a tupla (t, f) com t sendo o melhor filho de tree e f a heurística g+h
             retorna None caso o nó seja terminal
    '''
    
    # Implemente as tarefas abaixo e remove a instrução pass.
    
    # 1) Se o nó é terminal, retorna None
    if tree.eh_terminal:
        return None
    
    # 2) Se o nó não tem filhos, retorna ele mesmo e seu f
    if folha(tree):
        return (tree, tree.g + tree.h)
    
    # 3) Para cada filho de tree, aplica melhor_filho e filtra aqueles que resultarem em None
    melhores = []
    for k, v in tree.filhos.items():
        melhores.append(melhor_filho(v))
    
    melhores = list(filter(lambda item: item is not None, melhores))
    
    # Separa a lista de tuplas (melhores) em duas listas separadas
    nos, scores = [], []
    for no, score in melhores:
        nos.append(no)
        scores.append(score)

    # 4) Se todos os filhos resultarem em terminal, marca tree como terminal e retorna None    
    if all(no.eh_terminal == True for no in nos):
        tree.eh_terminal = True
        return None
    
    # 5) Caso contrário retorna aquele com o menor f
    menor = min(melhores, key = lambda x:x[1])
    print(menor)
    no, score = menor
    print(no)
    return (no, score)

# Nossa heurística é a quantidade
# de passos mínimos estimados para
# chegar ao final da fase
def heuristica(estado, x):
#    return (4800 - x)/8
    estNum = np.reshape(list(map(int, estado.split(','))), (2*raio+1,2*raio+1))
    dist = np.abs(estNum[:raio+1,raio+2:raio+7]).sum()
    return ((4800 - x)/8) + 0.3*dist
 
# Verifica se chegamos ao final   
def checaObj(estado, x):
    return x>4800

# Verifica se um nó é uma folha 
def folha(tree):
    """ Verifica se tree é um nó folha. """
    if tree.filhos is None:
        return True
    return False

# Joga uma partida usando uma
# sequência de ações
def emula(acoes, env, mostrar):

    env.reset()

    while len(acoes)>0 and (not env.data.is_done()):
        a = acoes.pop(0)
        estado, xn, y = getState(getRam(env), raio)
        performAction(a, env)
        if mostrar:
            env.render()

    estado, x, y = getState(getRam(env), raio)
    
    return estado, x, env.data.is_done()
    
# Expande a árvore utilizando a heurística
def expande(tree, env, mostrar):
    '''Expande a árvore utilizando a heurística.
    
    Entrada: o nó raiz, o ambiente do retro Gym, booleano se devemos mostrar ou não a tela do jogo
    Saída:   a própria raiz E se atingiu o objetivo
    '''
    
    acoes = []
   
    # Se a árvore já for um nó folha
    # não tem ações a serem feitas 
    if folha(tree):
        raiz  = tree
        filho = tree
    else:

        # Busca pelo melhor nó folha
        filho, score = melhor_filho(tree)   
        print(filho, score)  
    
        # Retorna para a raiz gravando as ações efetuadas
        raiz = filho
        # 1) Enquanto o pai de raiz não for None
        # 2) Atribua raiz a uma variável neto
        # 3) faça raiz = seu próprio pai
        # 4) verifique qual a ação de raiz leva ao nó neto
        # 5) faça um append dessa ação na lista acoes
        #print(raiz)
        while raiz.pai != None:
            neto = raiz
            raiz = raiz.pai
            for acao, no in raiz.filhos.items():
                if no == neto:
                    acoes.append(moves[acao])


        print(acoes) 
        
        # inverte a lista de ações e imprime para debug
        acoes.reverse()
        print('ACOES:  (  ', len(acoes), ' ): ',  acoes)
        
    # Vamos assumir que não atingiu o objetivo
    obj = False

    # Gera cada um dos filhos e verifica se atingiu objetivo
    filho.filhos = {}
    maxX         = 0
    for k, v in moves.items():
        estado, x, over = emula(acoes + [v], env, mostrar)
        maxX            = max(x, maxX)
        obj             = obj or checaObj(estado, x)
        filho.filhos[k] = Tree(estado, g=filho.g + 1, h=heuristica(estado,x),
                                pai=filho, terminal=over, obj=obj)
    
    print('FALTA: ', heuristica(estado, maxX))
        
    return raiz, obj

# Verifica se a árvore já atingiu o objetivo
def atingiuObj(tree):
    ''' Verifica se atingiu o objetivo 
    
    Entrada: um nó da árvore
    Saída:   (True, acoes) se atingiu o objetivo, sendo acoes a sequência de ações para chegar até ele.
             (False, [])  se não atingiu o objetivo
    '''
    
    # Complete as tarefas a seguir e remova a instrução pass
    
    # 1) Se o nó é terminal, retorna o valor de eh_obj e a lista vazia de ações
    if tree.eh_terminal:
        return (tree.eh_obj, [])
    
    # 2) Se o conjunto de filhos é None, retorna falso e lista vazia, pois não atingiu o obj
    if (tree.filhos is None):
        return(False, [])

    if all(v is None for v in tree.filhos):
        return (False, [])

    # 3) Se nenhum dos anteriores retornou, para cada movimento "k" e valor "v" possível do dicionário moves:
    #       chama recursivamente atingiuObj com o filho do movimento "k" e recebe obj, acoes
    #       Se obj for verdadeiro, retorna obj e a lista de acoes concatenado com "v"
    for k, v in moves.items():
        obj, acoes = atingiuObj(tree.filhos[k])
        if obj == True:
            return (obj, acoes.append(k))

    # 4) Se chegar ao final do laço sem retorna, retorne falso e vazio
    return (False, [])
           
    

# Gera a árvore utilizando A*
def astar():
    
    # Se devemos mostrar a tela do jogo (+ lento) ou não (+ rápido)
    mostrar = True
 
    # Gera a árvore com o estado inicial do jogo 
    env = retro.make(game='SuperMarioWorld-Snes', state='YoshiIsland1', players=1)    
    env.reset()
    estado, x, y = getState(getRam(env), raio)  
    tree         = Tree(estado, g=0, h=heuristica(estado,x))

    # Se já existe alguma árvore, carrega
    if os.path.exists('AstarTree.pkl'):
        tree = pickle.load(open('AstarTree.pkl', 'rb'))

    # Repete enquanto não atingir objetivo    
    obj, acoes  = atingiuObj(tree)

    while not obj:
        tree, obj = expande(tree, env, mostrar)

        # Grava estado atual da árvore por segurança
        fw = open('AstarTree.pkl', 'wb')
        pickle.dump(tree, fw)
        fw.close()
        
    obj, acoes = atingiuObj(tree)
    mostrar    = True
    emula(acoes, mostrar)

    return tree
  
def main():  
  tree = astar()
    
if __name__ == "__main__":
  main()
