typedef struct btNo *bTree;

bTree btCriar(void);
void  btDestruir(bTree t);
int   btBuscar(bTree t, int chave);
void  btInserir(bTree t, int key);
int   btAltura(bTree t);
int   btContaNos(bTree t);
void  btImprimirChaves(bTree b);
void  btImprimirArvore(bTree b);
