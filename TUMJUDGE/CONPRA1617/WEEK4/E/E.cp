#include <queue>
#include <cstdio>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <utility>

#define rep(i,a,b) for(int i=int(a); i<=int(b); ++i)
using namespace std;
typedef long T;
typedef pair<T,T> TT;
#define INF INT_MAX
#define fst first
#define snd second
#define mp make_pair
#define DEBUG 0
#define DBG(code) do {\
  if(DEBUG == 1){ \
  code \
} \
}while(0);

// globals
int t;
int n,m,d,D;
int v,w,g;
vector<vector<T> > G;
vector<bool> dungeons;
vector<vector<TT> > M;
vector<TT> p;

void read(){
  G.clear();
  dungeons.clear();
  cin >> n >> m >> d;
  G.resize(n, vector<T>(n,INF));
  dungeons.assign(n, false);
  rep(i,0,n-1)
    G[i][i] = 0;
  rep(i,0,d-1){
    int val;
    cin >> val;
    val--;
    dungeons[val] = true;
  }
  rep(i,0,m-1){
    cin >> v >> w >> g;
    v--; w--;
    if(g < G[v][w])
      G[v][w] = G[w][v] = g;
  }
}


void iS(T n){
  p.resize(n);
  rep(i,0,n-1){
    p[i].fst = i;
    p[i].snd = 1;
  }
}
T fS(T i){
  if(p[i].fst == i)
    return i;
  T pi = fS(p[i].fst);
  p[i].fst = pi;
  return pi;
}
bool iSS(T i, T j){ return fS(p[i].fst) == fS(p[j].fst); }
void uS(T i, T j){
  T pj = fS(j);
  T pi = fS(i);
  if(p[pi].snd > p[pj].snd)
    p[pj].fst = pi;
  else if(p[pj].snd > p[pi].snd)
      p[pi].fst = pj;
  else{
    p[pi].fst = pj;
    p[pj].snd++;
  }
}

int kruskal(){
  priority_queue<pair<T, TT> > PQ;
  rep(i,0,n-1)
    rep(j,i+1,n-1)
      if(dungeons[i] && dungeons[j]){
        PQ.push(mp(-G[i][j], mp(i,j)));
      }
      iS(n);
      T C = 0;
      while(!PQ.empty()){
        pair<T, TT> e = PQ.top(); PQ.pop();
        T u = e.snd.fst;
        T v = e.snd.snd;
        T c = e.fst;
        if(!iSS(u,v)){
          C += -c;
          uS(u,v);
        }
      }
      return C;
}


void roy_floyd(){
  rep(k,0,n-1)
    rep(i,0,n-1)
      rep(j,0,n-1)
        if(G[i][j] > G[i][k] + G[k][j])
          G[i][j] = G[i][k] + G[k][j];
}

/*
void construct_dungeon_graph(){
  M.resize(n,vector<TT>());
  rep(i,0,n-1)
    rep(j,0,n-1)
      if(i != j && dungeons[i] && dungeons[j]){
        M[i].push_back(TT(j,G[i][j]));
      }
}

int prim(int start){
  //declare
  vector<int> visited(n,0);
  priority_queue<TT, vector<TT>, greater<TT> > PQ;
  vector<int> mini(n,INF);

  // init
  int mc = 0;
  int visits = 0;
  rep(i,1,n-1)
    if(dungeons[i])
      PQ.push(TT(INF,i));
  PQ.push(TT(0,start));

  //prim
  while (!PQ.empty()) {
    TT z = PQ.top(); PQ.pop();
    int u = z.second;
    int c = z.first;
    if(c > mini[u]) continue;
    mini[u] = c;
    visited[u] = 1;
    //mc += c;
    rep(j,0,M[u].size()-1){
      int v = M[u][j].first;
      int cost = M[u][j].second;
      if (!visited[v]){
        if(cost < mini[v])
          mini[v] = cost;
        PQ.push(TT(cost, v));
      }
    }
  }
  rep(i,0,n-1)
    if(dungeons[i])
      mc += mini[i];
  return mc;
}
*/

int main(){

  cin >> t;
  rep(_t,1,t){
    read();
    roy_floyd();
    //construct_dungeon_graph();

    DBG(
      cout << "dungeons: ";
      rep(i,0,n-1)
        if(dungeons[i])
          cout << i << " ";
      cout << "\n";
    )

    int mi = INF;
    int node = -1;
    rep(i,0,n-1){
      if(dungeons[i] && G[0][i] < mi){
        mi = G[0][i];
        node = i;
      }
    }
    DBG(cout << "start: " << node << " mi: " << mi << "\n";)
    //int res = prim(node);
    int res = kruskal();
    cout << "Case #" << _t << ": " << res + mi << endl;
  }

  return 0;
}
