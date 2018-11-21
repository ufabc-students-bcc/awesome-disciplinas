from copy import deepcopy

# A_STAR
def buscaAStar(sts):
    sts     = [sts]   
    obj     = list(filter(atingiuObj, sts))
    n       = 0    
    la      = []   # Lista de açoes
    la.append([0]) # Acão do estado inicial
    while len(obj) == 0:
        st  = melhorNo(sts) 
        ind_melhor = sts.index(st)
        for a in acoes(st):
            s = resultado(st, a)             
            sts.append(s)
            la.append(la[ind_melhor] + [a])

        ind = sts.index(st)
        sts.remove(st)
        la.remove(la[ind])
        n   = n + len(sts)
        obj = list(filter(atingiuObj, sts))
    return obj[0], n, la[sts.index(obj[0])]

#BFS
def buscaLargura(sts):
    sts = [sts]
    obj = list(filter(atingiuObj, sts))
    n   = 0
    while len(obj) == 0:
        new_sts = []
        for s in sts:
            new_sts = [resultado(s, a) for a in acoes(s)] + new_sts 
        sts = new_sts
        obj = list(filter(atingiuObj, sts))
        n   = n + len(sts)
        print(n)
    return obj[0], n

# DFS
def buscaProfundidade(s, n, la):
    if atingiuObj(s): return s, n, la    
    moves = acoes(s)      
    if empty(moves): return None, n, la

    for a in moves:
        n = n + 1
        new_st, n, la = buscaProfundidade(resultado(s,a), n, la)  
        if not empty(new_st):
            la.append(a)
            return new_st, n, la 
    return None, n, la

# Checa se uma lista é vazia
def empty(st):
    if (st):
        return False
    else:
        return True

# É definida pela quantidade de lugares vazios no tabuleiro
def heuristica(st):
    s, score = st
    qtd      = 0
    for i in range(len(s)):
        for j in range(len(s[i])):
            if s[i][j] == 'X':
                qtd = qtd + 1
    return qtd

# Dado uma lista de estados, retorna o nó com menos peças no tabuleiro
def melhorNo(sts):
    maior = -1
    for s, score in sts:
        if score >= maior:
            maior  = score
            melhor = (s, score)     
    return melhor                 

# Gera um novo estado a partir de uma ação a
def resultado(st, a):    
    s            = deepcopy(st)
    s_new, score = s
    pos, acao    = a
    i, j         = pos
    s_new[i][j]  = 'X'
    if acao == 'up':
        s_new[i-1][j] = 'X'
        s_new[i-2][j] = 'O'
    elif acao == 'left':
        s_new[i][j-1] = 'X'
        s_new[i][j-2] = 'O'
    elif acao == 'down':
        s_new[i+1][j] = 'X'
        s_new[i+2][j] = 'O'
    else:
        s_new[i][j+1] = 'X'
        s_new[i][j+2] = 'O'
    
    return (s_new, heuristica(s))

# Retorna todas as ações possíveis de um estado st
def acoes(st):
    s, score = st
    acoes    = []
    for i in range(len(s)):
        for j in range(len(s[i])):
            pos = (i, j)
            for a in acoesFactiveis(st, pos): 
                acoes.append(a)
    return acoes

# Retorna acoes factveis para uma posicao pos em um dado estado s
def acoesFactiveis(st, pos):
    s, score = st
    acoes    = []
    i, j     = pos
    if  s[i][j] != 'O':
        return acoes
    for m, n in movimentos.items():
        # Left
        if m == 0 and j-2 > -1:
            if s[i][j-1] == 'O' and s[i][j-2] == 'X':
                a = (pos, n)
                acoes.append(a)
        # Down
        elif m == 1 and i+2 < len(s):
            if s[i+1][j] == 'O' and s[i+2][j] == 'X':
                a = (pos, n)
                acoes.append(a)
        # Right
        elif m == 2 and j+2 < len(s[0]):
            if s[i][j+1] == 'O' and s[i][j+2] == 'X':
                a = (pos, n)
                acoes.append(a)
        # Up
        elif m == 3 and i-2 > -1:
            if s[i-1][j] == 'O' and s[i-2][j] == 'X':
                a = (pos, n)
                acoes.append(a)    
    return acoes        
                   
# Verifica se um estado s é objetivo
def atingiuObj(st):
    s, score  = st
    contaPeca = 0
    for i in range(len(s)):
        for j in range(len(s[i])):
            if s[i][j] == 'O': 
                contaPeca += 1
                if contaPeca > 1:
                    return False
    return True

# Printa o estado(Tabuleiro)
def printEstado(st):
    s, score = st
    for i in range(len(s)):
        for j in range(len(s[i])):
            print(s[i][j], end=' ')
        print()

def printBusca(b):
    lista_acoes = []
    s0          = estadoInicial()
    n           = 0
    if b == "BFS":
        estado_final, num_s = buscaLargura(s0)
    elif b == "DFS":
        estado_final, num_s, lista_acoes = buscaProfundidade(s0, n, lista_acoes)
    elif b == "ASTAR":
        estado_final, num_s, lista_acoes = buscaAStar(s0)

    print("###############################################################")
    print("\n*****", b,"*****\n")
    print("Estado final:")
    printEstado(estado_final)
    print("\nNúmero de estados visitados: "), print(num_s) 
    print("\nAções realizadas:")
    for i in range(len(lista_acoes)):
        print(i+1,". ",lista_acoes[i])
    print("###############################################################")

def estadoInicial():
    # Estado inicial do tabuleiro
    # '-' = espaços inválidos
    # 'O' = espaços que tem uma peça
    # 'X' = espaços vazios    
    s0   = ([['-', '-', 'O', 'O', 'O', '-', '-'],
             ['-', '-', 'O', 'O', 'O', '-', '-'],
             ['O', 'O', 'O', 'O', 'O', 'O', 'O'],
             ['O', 'O', 'O', 'X', 'O', 'O', 'O'],
             ['O', 'O', 'O', 'O', 'O', 'O', 'O'],
             ['-', '-', 'O', 'O', 'O', '-', '-'],
             ['-', '-', 'O', 'O', 'O', '-', '-']], 0)
    a, b = s0
    s0   = (a, heuristica(s0))  # Atualiza o score do estado inicial
    return s0

def main():
    #printBusca("BFS") # Demora muuuito pra executar
    printBusca("DFS")
    printBusca("ASTAR")

movimentos = {0:'left', 1: 'down', 2:'direita', 3:'up'}

main() 