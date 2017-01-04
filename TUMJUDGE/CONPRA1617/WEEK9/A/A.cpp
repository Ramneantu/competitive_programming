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
#define mout(M,n,m) rep(i,0,(n)-1){ rep(j,0,(m)-1) cout << (M)[i][j] << " ";  cout << "\n"; }
#define vout(V,a,b,msg) cout << msg << ": "; rep(i,a,b)  cout << V[i] << " "; cout << "\n";
#define fst first
#define snd second
#define debug 0
#define DBG(code) if(debug){    \
                    do{         \
                    code        \
                    }while(0);  \
                  }
using namespace std;

typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef long long ll;

#include <algorithm>
#include <vector>
#include <climits>
#include <iostream>
using namespace std;

const int maxnodes = 5000;


// REFERENCE: https://sites.google.com/site/indy256/algo_cpp/dinic_flow
int nodes = maxnodes, src, dest;
int dist[maxnodes], q[maxnodes], work[maxnodes];
int capacity[maxnodes][maxnodes];

struct Edge {
  int to, rev;
  int f, cap;
};

vector<Edge> g[maxnodes];

// Adds bidirectional edge
void addEdge(int s, int t, int cap){
  Edge a = {t, g[t].size(), 0, cap};
  Edge b = {s, g[s].size(), 0, cap};
  g[s].push_back(a);
  g[t].push_back(b);
}

bool dinic_bfs() {
  fill(dist, dist + nodes, -1);
  dist[src] = 0;
  int qt = 0;
  q[qt++] = src;
  for (int qh = 0; qh < qt; qh++) {
    int u = q[qh];
    for (int j = 0; j < (int) g[u].size(); j++) {
      Edge &e = g[u][j];
      int v = e.to;
      if (dist[v] < 0 && e.f < e.cap) {
        dist[v] = dist[u] + 1;
        q[qt++] = v;
      }
    }
  }
  return dist[dest] >= 0;
}

int dinic_dfs(int u, int f) {
  if (u == dest)
    return f;
  for (int &i = work[u]; i < (int) g[u].size(); i++) {
    Edge &e = g[u][i];
    if (e.cap <= e.f) continue;
    int v = e.to;
    if (dist[v] == dist[u] + 1) {
      int df = dinic_dfs(v, min(f, e.cap - e.f));
      if (df > 0) {
        e.f += df;
        g[v][e.rev].f -= df;
        return df;
      }
    }
  }
  return 0;
}

int maxFlow(int _src, int _dest) {
  src = _src;
  dest = _dest;
  int result = 0;
  while (dinic_bfs()) {
    fill(work, work + nodes, 0);
    while (int delta = dinic_dfs(src, INT_MAX))
      result += delta;
  }
  return result;
}

int main() {

  int tests; cin >> tests;
  rep(_t,1,tests){
    int n, k, m, l;
    cin >> n >> k >> m >> l;
    nodes = 1 + n + k + m + 1;
    src = 0;
    dest = nodes-1;
    rep(i,0, maxnodes-1)
      rep(j,0, maxnodes-1)
        capacity[i][j] = 0;
    rep(i,0,maxnodes-1){
      dist[i] = q[i] = work[i] = 0;
      g[i].clear();
    }

    rep(_l, 0, l-1){
      int from, where, cap; cin >> from >> where >> cap;
      if (cap != 0){
        capacity[from][where] = cap;
        addEdge(from, where, capacity[from][where]);
      }
    }

    // add super s and t with INT_MAX capacity
    // n fountains, m wrapping stations
    rep(i,1,n){
      capacity[src][i] = INT_MAX;
      addEdge(src, i, capacity[src][i]);
    }
    rep(i,n+k+1,nodes-2){
      capacity[i][dest] = INT_MAX;
      addEdge(i,dest,capacity[i][dest]);
    }


    DBG(
      cout << "G:\n";
      rep(i,0,nodes-1){
        cout << i << ": ";
        rep(j,0,nodes-1)
          if(capacity[i][j] > 0)
            cout << j << "(" << capacity[i][j] << ") ";
        cout << "\n";
      }
    )


    cout << "Case #" << _t << ": " << maxFlow(0,nodes-1) << "\n";
  }
  return 0;
}
