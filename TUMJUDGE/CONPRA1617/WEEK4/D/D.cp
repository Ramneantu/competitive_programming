#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <bitset>
#include <utility>

#define rep(i,a,b) for(int i=int(a); i<=int(b); ++i)
#define rev(i,b,a) for(int i=int(b); i>=int(a); --i)
#define rec(i,a,b,c) for(int i=int(a); i<=int(b); i+=int(c))
#define recv(i,a,b,c) for(int i=int(a); i>=int(b); i-=int(c))
#define mp(x,y) make_pair((x),(y))
#define pb(x) push_back(x)
#define all(c) c.begin(), c.end()
#define tr(container, it) for(auto it=(container).begin(); it != (container).end(); ++it)
#define sqr(x) ((x)*(x))
#define sz(a) int((a).size())
#define mod(a,n) ((a) < 0 ? ((n)+(a)) : ((a)%(n)))
#define mout(M,n,m) rep(i,0,(n)-1){ rep(j,0,(m)-1) cout << (M)[i][j] << " ";  cout << "\n"; }
using namespace std;

typedef int T;
typedef pair<T,T> TT;
#define INF INT_MAX/2
#define fst first
#define snd second


// globals
int t;
vector<TT> used;
vector<vector<T> > G;
char M[201][201];
T n,m;
int N;
int di[4] = {0,-1,0,1};
int dj[4] = {-1,0,1,0};
int start, fin;
int uses = 0;
vector<T> dist;
vector<T> parent;
vector<bool> visited;


// helpers
bool valid(T i,T j){
  if (i >= 1 && i <= n && j >= 1 && j <= m)
    return true;
  return false;
}
int grid2graph(int i, int j, int level){
  return n*m*level + m*(i-1) + j;
}
inline void graph2grid(int v, int &row, int& col, int &level){
  if(v >= 1 && v <= n*m)
    level = 0;
  else if(v > n*m && v <= n*m*2)
    level = 1;
  else if(v > n*m*2 && v <= n*m*3)
    level = 2;
  else if(v > n*m*3 && v <= n*m*4)
    level = 3;
  if(level > 0)
    v-= n*m*level;

  int tmp = v / m;
  if(tmp == 0){
    row = 1;
    col = v;
  }
  else{
    row = tmp;
    if(v%m > 0)
      row++;
    col = v % m;
    if(col == 0)
      col = m;
  }
}




// algorithm
void bfs(int s){
  rep(i,1,N){
    visited[i] = false;
    parent[i] = i;
    dist[i] = INF;
  }
  queue<T> Q;
  Q.push(s);
  dist[s] = 0;
  visited[s] = true;
  while(!Q.empty()){
    int v = Q.front(); Q.pop();
    //cout << "v: " << v << "\n";
    for(int i=0; i<G[v].size(); ++i){
        int u = G[v][i];
        if(!visited[u]){
          //cout << "u: " << u << "\n";
          Q.push(u);
          parent[u] = v;
          dist[u] = dist[v] + 1;
          visited[u] = true;
        }
    }
  }
}
void find_device_uses(int v){
  if(v == start)
    return;
  int p = parent[v];
  int vi,vj,vl,pi,pj,pl;
  graph2grid(v,vi,vj,vl);
  graph2grid(p,pi,pj,pl);
  if(vl != pl){
    //cout << "vi,pi: " << vi <<"," << pi << " vj,pj: " << vj << "," << pj << "\n";
    if(vi != pi)
      used[uses].fst = min(vi,pi)+1;
    else
      used[uses].fst = vi;
    if(vj != pj)
      used[uses].snd = min(vj,pj)+1;
    else
      used[uses].snd = vj;
    uses++;
  }
  find_device_uses(p);
}


int main(){

  cin >> t;
  rep(_t,1,t){
    cin >> m >> n;
    N = n*m*4;
    used.clear();
    G.clear();
    dist.clear();
    parent.clear();
    visited.clear();
    used.resize(3,TT(-1,-1));
    G.resize(N+1);
    dist.resize(N+1);
    parent.resize(N+1);
    visited.resize(N+1);
    uses = 0;
    rep(i,1,n)
      rep(j,1,m)
        cin >> M[i][j];

    rep(i,1,n){
      rep(j,1,m){
        if(M[i][j] == '@'){
          for(int k=0; k<=1; ++k){
            int si = i + di[k];
            int sj = j + dj[k];
            int fi = i + di[k+2];
            int fj = j + dj[k+2];
            if(valid(si,sj) && valid(fi,fj) && M[si][sj] != '@' && M[fi][fj] != '@'){
              for(int kk=0;kk<=2; ++kk){
                  int n11 = grid2graph(si,sj,kk);
                  int n12 = grid2graph(fi,fj,kk+1);
                  int n21 = grid2graph(fi,fj,kk);
                  int n22 = grid2graph(si,sj,kk+1);
                  G[n11].push_back(n12);
                  G[n21].push_back(n22);
              }
            }
          }
        }
        else if(M[i][j] != '@'){
          if(M[i][j] == '*'){
            start = grid2graph(i, j, 0);
          }
          if(M[i][j] == '_'){
            if(i == 1 || i == n || j == 1 || j == m){
              fin = grid2graph(i,j,0);
            }
          }
          rep(k,0,1){
            int ii = di[k] + i;
            int jj = dj[k] + j;
            if(valid(ii,jj) && M[ii][jj] != '@'){
              for(int kk=0; kk<=3; ++kk){
                int n1 = grid2graph(i, j, kk);
                int n2 = grid2graph(ii,jj,kk);
                //cout << "normal: " << i << "," << j << "->" << ii << "," << jj << " nodes: " << n1 << "->" << n2 << "\n";
                G[n2].push_back(n1);
                G[n1].push_back(n2);
              }
            }
          }
        }
      }
    }


/*
    int __r,__c,__l;
    graph2grid(start,__r,__c,__l);
    cout << "start: " << start << " grid: " << __r << "," << __c << "," << __l << "\n";
    graph2grid(fin,__r,__c,__l);
    cout << "fin: " << fin << " grid: " << __r << "," << __c << "," << __l << "\n";

    rep(i,1,N){
      cout << i << ": ";
      rep(j,0,G[i].size()-1)
        cout << G[i][j] << " ";
      cout << "\n";
    }
*/


    bfs(start);
    int mini = INF;
    int node = 0;
    int fi,fj,fl;
    graph2grid(fin,fi,fj,fl);
    rep(i,0,3){
      int tmp = grid2graph(fi,fj,i);
      //cout << "tmp:" << tmp << " dist: " << dist[tmp] << "\n";
      if(mini > dist[tmp]){
        mini = dist[tmp];
        node = tmp;
      }
    }
    //cout << "min: " << mini << " node: " << node << "\n";
    find_device_uses(node);


    cout << "Case #" << _t << ":\n";
    rep(i,0,used.size()-1)
      if(used[i].fst == -1 && used[i].snd == -1)
        cout << "unused\n";
      else
        cout << used[i].snd << " " << used[i].fst << "\n";
  }



  return 0;
}
