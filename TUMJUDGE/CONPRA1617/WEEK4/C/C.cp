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

#define DEBUG 0

#define DBG(code) do {\
  if(DEBUG == 1){ \
  code \
} \
}while(0);

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

// globals
vector<vector<TT> > G;
vector<vector<TT> > G2;
vector<T> dist;
map<T,bool> snake_heads;
map<T,bool> tails;
vector<T> distances;
int n,s,l,t;


void add_edges_from(int i, int step, int n){
  int k;
  for(k=i; k+step<n; k+=step){
    if(snake_heads.find(k) == snake_heads.end()){
      G2[k].push_back(TT(k+step,1));
    }
  }
  DBG(cout << "at k:" << k << endl;)
  if(k != n-1){
      if(snake_heads.find(k) == snake_heads.end())
        G2[k].push_back(TT(n-1,1));
  }
}

void copy_graph(){
  G2.clear();
  G2.resize(G.size());
  rep(i,0,G.size()-1)
    rep(j,0,G[i].size()-1)
      G2[i].push_back(G[i][j]);
}


void dijkstra(){
  dist.assign(n,INF);
  dist[0] = 0;
  priority_queue<TT, vector<TT>, greater<TT> > pq;
  pq.push(TT(0,0));
  int steps = 0;
  while(!pq.empty()){
    if(steps > n)
      break;
    TT top = pq.top(); pq.pop();
    int d = top.first, u = top.second;
    if(d == dist[u]){
      steps++;
      for(int i=0; i<G2[u].size(); ++i){
        int v = G2[u][i].first;
        if(dist[u] + G2[u][i].second < dist[v]){
          dist[v] = dist[u] + G2[u][i].second;
          pq.push(TT(dist[v], v));
        }
      }
    }
  }
}

int main(){

  cin >> t;
  rep(_t,1,t){
    cin >> n >> s >> l;
    // clear globals
    G.clear();
    G.resize(n);
    G2.clear();
    G2.resize(n);
    dist.clear();
    dist.resize(n);
    snake_heads.clear();
    tails.clear();
    distances.clear();
    distances.resize(7);
    rep(i,0,n-1)
       dist[i] = INF;
    rep(i,0,6)
      distances[i] = INF;

    rep(i,0,s-1){
      int from,to;
      cin >> from >> to;
      from--; to--;
      G[from].push_back(TT(to,0));
      snake_heads[from] = true;
      tails[to] = true;
     }
    rep(i,0,l-1){
      int from,to;
      cin >> from >> to;
      from--; to--;
      G[from].push_back(TT(to,0));
      tails[to] = true;
    }
    DBG(
      cout << "tails:\n";
      for(map<T,bool>::iterator it=tails.begin(); it!=tails.end(); ++it)
        cout << it->first << " ";
      cout << "\n";
      cout << "G:\n";
      rep(_i,0,G.size()-1){
        cout << _i << ": ";
        rep(_j,0,G[_i].size()-1)
          cout << G[_i][_j].first << " ";
        cout << "\n";
      }
    )

    rep(step,1,6){
      DBG(cout << "step " << step << "\n";)
      copy_graph();
      priority_queue<T, vector<T>, greater<T> > Q;
      Q.push(0);
      vector<bool> visited(n,false);
      for(map<T,bool>::iterator it=tails.begin(); it!=tails.end(); ++it)
        Q.push(it->first);
      while(!Q.empty()){
        int v = Q.top(); Q.pop();
        if(!visited[v]){
          int u = min(v+step, n-1);
          DBG(cout << v << "->" << u << "\n";)
          if(snake_heads.find(v) == snake_heads.end()){
            G2[v].push_back(TT(u, 1));
            if(u != n-1)
              Q.push(u);
          }
          visited[v] = true;
        }
      }

      DBG(
        cout << "G2:\n";
        rep(_i,0,G2.size()-1){
          cout << _i << ": ";
          rep(_j,0,G2[_i].size()-1)
            cout << G2[_i][_j].first << " ";
          cout << "\n";
        }
      )

      dijkstra();
      distances[step] = dist[n-1];
    }
    DBG(cout << "distances: "; rep(_i,1,6) cout << distances[_i] << " "; cout << "\n";)

    cout << "Case #" << _t << ": ";
    int mini = *min_element(distances.begin(), distances.end());
    DBG(cout << "min distance: " << mini << "\n";)
    if(mini >= INF){
      cout << "impossible";
    }
    else{
      bool first = false;
      rep(i,1,6){
        if(distances[i] == mini){
          if(first)
            cout << " ";
          cout << i;
          first = true;
        }
      }
    }
    cout << "\n";
  }

  return 0;
}
