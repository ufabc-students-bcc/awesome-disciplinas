#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define eb emplace_back
#define mk make_pair
#define fi first
#define se second

typedef pair<int,int> ii;
typedef vector< pair<int,int> >vii[1010];
const int INF = 0x3f3f3f3f;
vii ind;

struct state {
    int v[2][4];

    state() {}

    void read() {
        for(int i = 0; i < 2; i++)
            for(int j = 0; j < 4; j++) {
                cin >> v[i][j];
                ind[v[i][j]].eb(i,j); 
            }
    }

    bool operator < (const state &b) const {
        for(int i = 0; i < 2; i++) 
            for(int j = 0; j < 4; j++) 
                if(v[i][j] != b.v[i][j])
                    return v[i][j] < b.v[i][j];
        return false;
    }

    int dist() {
        int sum = 0;
        for(int i = 0; i < 2; i++) {
            for(int j = 0; j < 4; j++) {
                if(ind[v[i][j]].size() == 2) {
                    ii tmp = ind[v[i][j]][1];
                    int manhatam = (abs(i - tmp.fi) + abs(j - tmp.se)); 
                    sum += manhatam * v[i][j];
                }
            }
        }
        return sum;
    }
                    

} beg, last; 

struct node {
    state a;
    int realD;
    int aStar;

    node (state a, int realD, int aStar) :
        a(a), realD(realD), aStar(aStar) {}

    
    bool operator > (const node &b) const {
        return realD+ aStar >= b.realD + b.aStar;
        return false;
    }
};

int dir[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};

bool pode(int i, int j) {
    return (i>=0 and j>=0 and i<2 and j<4);
}

int go() {
    map<state, int> dist;
    priority_queue<node, vector<node>, greater<node> >pq;

    dist[beg] = 0;
    pq.push(node(beg, 0LL, beg.dist()));

    while(pq.size()) {
        state at = pq.top().a;
        int dPai = pq.top().realD;
        pq.pop();

        if(at.dist() == 0) 
            return dPai;

        for(int i = 0; i < 2; i++) {
            for(int j = 0; j < 4; j++) {
                for(int k = 0; k < 4; k++) {
                    int ii = i + dir[k][0];
                    int jj = j + dir[k][1];

                    if(!pode(ii, jj)) continue;

                    state next = at;

                    swap(next.v[i][j], next.v[ii][jj]);

                    int realD = next.v[i][j] + next.v[ii][jj];
                    int manhattan = next.dist();

                    if(!dist.count(next) or dist[next] > dPai + manhattan + realD) {
                        dist[next] = dPai + manhattan + realD;
                        pq.push(node(next, dPai + realD, manhattan));
                    }
                }
            }
        }
    }
    return INF;
}
 
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    beg.read();
    last.read();

    cout << go() << endl;
    
    return 0;
}

