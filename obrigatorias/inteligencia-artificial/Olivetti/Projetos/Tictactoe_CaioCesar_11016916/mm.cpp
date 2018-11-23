#include "mm.h"

vector<No> acoes(No state, int jogador);
void printTable(No state);
bool ehTerminal(No state);;
int utilidade(No state);
int maxVal(No state, int alfa, int  beta);
int minVal(No state, int alfa, int  beta);
int miniMaxUtil(No state, int tipo, int alfa, int  beta);
No iaTurn(No state, int symbol);
No playerTurn(No state, int symbol);
void printWinner(No state);
bool posValida(No state, ii pos);

vector<No> acoes(No state, int jogador) {
	vector<No> next;
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			if(state.m[i][j] == 0) {
				No tmp = state;
				tmp.insert(ii(i,j), jogador);
				next.pb(tmp);
			}
		}
	}
	return next;
}

bool ehTerminal(No state) {
	int atCheck = 0;

	// Checa horizontal
	for(int i = 0; i < N; i++) {
		atCheck = 0;
		for(int j = 0; j < N; j++) {
			atCheck += state.m[i][j];
		}
		if(abs(atCheck) == 3) {
			return true;
		}
	}
	// Checa vertical
	for(int i = 0; i < N; i++) {
		atCheck = 0;
		for(int j = 0; j < N; j++) {
			atCheck += state.m[j][i];
		}
		if(abs(atCheck) == 3) {
			return true;
		}
	}
	// Checa diagonal
	atCheck = 0;
	for(int i = 0; i < N; i++) {
		atCheck += state.m[i][i];
	}
	if(abs(atCheck) == 3) {
		return true;
	}

	atCheck = 0;
	for(int i = 0; i < N; i++) {
		atCheck += state.m[N-i-1][i];
	}
	if(abs(atCheck) == 3) {
		return true;
	}

	// Checa empate 
	atCheck = 0;
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			if(state.m[i][j] == 0) 
				return false;
		}
	}
	return true;
}

int utilidade(No state) {
	int atCheck = 0;
	// Checa horizontal
	for(int i = 0; i < N; i++) {
		atCheck = 0;
		for(int j = 0; j < N; j++) {
			atCheck += state.m[i][j];
		}
		if(abs(atCheck) == 3)
			return atCheck/abs(atCheck);
	}
	// Checa vertical
	for(int i = 0; i < N; i++) {
		atCheck = 0;
		for(int j = 0; j < N; j++) {
			atCheck += state.m[j][i];
		}
		if(abs(atCheck) == 3)
			return atCheck/abs(atCheck);
	}
	// Checa diagonal
	atCheck = 0;
	for(int i = 0; i < N; i++) {
		atCheck += state.m[i][i];
	}
	if(abs(atCheck) == 3) 
		return atCheck/abs(atCheck);

	atCheck = 0;
	for(int i = 0; i < N; i++) {
		atCheck += state.m[N-i-1][i];
	}
	if(abs(atCheck) == 3) 
		return atCheck/abs(atCheck);

	// Empate 
	return 0;
}

int maxVal(No state, int alfa, int beta) {
	vector<No> next = acoes(state, 1);
	int v = -INF;
	for(No at:next) {
		v = max(miniMaxUtil(at, -1, alfa, beta), v);
		if(v >= beta)
			return v;
		alfa = max(alfa, v);
	}

	return v;
}

int minVal(No state, int alfa, int beta) {
	vector<No> next = acoes(state, -1);
	int v = INF;
	for(No at:next) {
		v = min(miniMaxUtil(at, 1, alfa, beta), v);
		if(v <= alfa)
			return v;
		beta = min(beta, v);
	}
	return v;
}

int miniMaxUtil(No state, int tipo, int alfa, int beta) {
	if(ehTerminal(state)) {
		return utilidade(state);
	}
	if(tipo == 1)
		return maxVal(state, alfa, beta);
	else
		return minVal(state, alfa, beta);
}

No iaTurn(No state, int symbol) {
	printf("\nAI's turn!\n");
	int alfa = -INF;
	int beta = INF;
	vector<No> next = acoes(state, symbol);
	No move;

	int v = -INF;
	for(No at:next){
		int ut = miniMaxUtil(at, -1, alfa, beta);
		if(v < ut) {
			move = at;
			v = ut;
		}
		if(v >= beta) 
			break;
		alfa = max(alfa, v);
	}
	string p = (v == 0?"tie":"IA wins");
	printf("(Prediction: %s)\n", p.c_str());
	return move;
}

No playerTurn(No state, int symbol) {
	printf("\nYour turn!\n");
	ii pos(-1, -1);
	while(!posValida(state, pos)) {
		printf("Insert row and column: ");
		scanf("%d %d", &pos.fi, &pos.sec);
		pos.fi--; pos.sec--;
	}
	state.insert(pos, symbol);
	return state;
}

bool posValida(No state, ii pos) {
	if(pos.fi < 0 and pos.fi > N-1) return false;
	if(pos.sec < 0 and pos.sec > N-1) return false;
	if(state.m[pos.fi][pos.sec] == 0) return true;
	return false;
}

void printTable(No state) {
	char s[3] = {'X', '-', 'O'};
	printf("      1   2   3 \n");
	printf("     ___________\n");
	printf(" 1  | %c | %c | %c \n", s[state.m[0][0]+1], s[state.m[0][1]+1], s[state.m[0][2]+1]);
	printf("    |-----------\n");
	printf(" 2  | %c | %c | %c \n", s[state.m[1][0]+1], s[state.m[1][1]+1], s[state.m[1][2]+1]);
	printf("    |-----------\n");
	printf(" 3  | %c | %c | %c \n", s[state.m[2][0]+1], s[state.m[2][1]+1], s[state.m[2][2]+1]);
}

void printWinner(No state) {
	int winner = utilidade(state);
	string txt = "";
	if(winner == -1) txt = "You win!";
	else if(winner == 0) txt = "Tie!";
	else txt = "AI wins!";
	printf("\nResult: %s\n", txt.c_str());
}
