#ifndef __MM_H__
#define __MM_H__

#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

#define pb push_back
#define fi first
#define sec second

typedef pair<int,int> ii;
const int INF = 0x3f3f3f3f;
const int N = 3;

struct No {
	int m[N][N];
	No(){
		for(int i = 0; i < N; i++) {
			for(int j = 0; j < N; j++) {
				m[i][j] = 0;
			}
		}
	};

	No(int s[][N]) {
		for(int i = 0; i < N; i++) {
			for(int j = 0; j < N; j++) {
				m[i][j] = s[i][j];
			}
		}
	};

	void insert(ii pos, int player) {
		m[pos.fi][pos.sec] = player;
	}
};


void printTable(No state);
bool ehTerminal(No state);
No iaTurn(No state, int symbol);
No playerTurn(No state, int symbol);
void printWinner(No state);

#endif