import copy

folhas = []

class Tree:
    def __init__(self,
                 estado,
                 filhos=None,
                 pai=None,
                 g=0,
                 h=0,
                 terminal=False,
                 obj=False,
                 coords=[]):
        self.estado = estado
        self.filhos = filhos
        self.cavalosCoords = coords

        self.g = g
        self.h = h

        self.eh_terminal = terminal
        self.eh_obj = obj

        self.pai = pai

    def __str__(self):
        return self.estado


def acoes(estado):
    grid, pos = estado
    posicoes = [(i, j) for i in range(1, 9) for j in range(1, 9)]
    return list(set(posicoes) - set(pos))


def resultado(estado, acao):
    i, j = acao
    grid, pos = estado
    table = copy.deepcopy(grid)
    table[i - 1][j - 1] = 'K'

    pos2 = copy.deepcopy(pos)
    pos2.append(acao)
    return (table, pos2)


def casasAtacadas(state):
    grid, pos = state
    ataca = set([])
    for x in pos:
        ataca = ataca.union(atacando(x))

    return len(ataca)


def obj(state):
    return casasAtacadas(state) == 64


def atacando(pos):
    i, j = pos
    final = set([])

    provisorio = [(i + 2, j + 1), (i + 2, j - 1), (i - 2, j + 1), (i - 2,
                                                                   j - 1),
                  (i + 1, j + 2), (i - 1, j + 2), (i + 1, j - 2), (i - 1,
                                                                   j - 2)]
    for x, y in provisorio:
        if (x > 0 and x < 9) and (y > 0 and y < 9):
            final.add((x, y))

    return final


def folha(tree):
    return tree.filhos is None or len(tree.filhos) == 0


def consideraG(tp):
    g = tp[0].g
    h = tp[1]
    return h + g


def melhor_filho(tree):
    
    menor = folhas[0]
    for t in folhas:
        if (t.h + t.g) < (menor.h + menor.g):
            menor = t
    folhas.remove(menor)
    return menor, menor.h + menor.g

def expande(tree):
    if folha(tree):
        raiz = tree
        filho = tree
    else:
        filho, score = melhor_filho(tree)
        raiz = filho

    objetivo = False
    menor = 10000

    filho.filhos = {}
    for pos in acoes(filho.estado):

        estado = resultado(filho.estado, pos)

        objetivo = objetivo or obj(estado)
        filho.filhos[pos] = Tree(
            estado,
            filhos=None,
            g=filho.g + 1,
            h=heuristica(estado),
            pai=filho,
            terminal=objetivo,
            obj=objetivo)
        folhas.append(filho.filhos[pos])
        if filho.h + filho. g < menor:
            menor = filho.h
        if (obj(estado)):
            raiz = filho.filhos[pos]

    print('Falta atacar ', menor, ' casas')
    return (raiz, objetivo)


def heuristica(estado):
    atacadas = casasAtacadas(estado)
    return 64 - atacadas


def astar():
    estado = ([[' ' for _ in range(1, 9)] for _ in range(1, 9)], [])
    tree = Tree(estado, g=0, h=heuristica(estado))

    objetivo = False
    while not objetivo:
        tree, objetivo = expande(tree)

    return tree


def main():
    tree = astar()
    grid, pos = tree.estado
    for x in grid:
        print(x)


if __name__ == '__main__':
    main()
