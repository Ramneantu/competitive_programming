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

// globals
static const int _INF = INT_MAX/2;
vector<double> star_dist;
vector<int> star_parent;
vector<vector<pair<double, int> > > star_G; // star_G[i][j].fst = dist(i,j) star_G[i][j].snd = cap(i,j)
int star_src, star_dest;
vector<vector<int> > colony_G;
int N,M,n,m;
vi Cs;        // C_i for each star system i

void clear_globals(){
  star_dist.clear();
  star_G.clear();
}

double dijkstra(int src, int dest, int nodes){
  star_dist.assign(nodes+1,_INF);
  star_parent.resize(nodes+1, 0);
  rep(i,1,star_parent.size()-1)
    star_parent[i] = i;
  star_dist[src] = 0;
  priority_queue<pair<double, int>  , vector<pair<double, int> >, greater<pair<double, int> > > pq;
  pq.push(mp(star_dist[src],src));
  int steps = 0;
  while(!pq.empty()){
    if(steps > nodes)
      break;
    pair<double,int> top = pq.top(); pq.pop();
    double d = top.fst;
    int v = top.snd;
    if(d == star_dist[v]){
      steps++;
      rep(u,1,nodes){
        if(star_G[v][u].fst > 0){
          if(star_dist[v] + star_G[v][u].fst < star_dist[u]){
            star_dist[u] = star_dist[v] + star_G[v][u].fst;
            pq.push(mp(star_dist[u], u));
            star_parent[u] = v;
          }
        }
      }
    }
  }
  return star_dist[dest];
}


// REFERENCE: https://sites.google.com/site/indy256/algo_cpp/dinic_flow
const int maxnodes = 102;
int nodes = maxnodes, src, dest;
int dist[maxnodes], q[maxnodes], work[maxnodes];
int capacity[maxnodes][maxnodes];
vector<map<int, bool> > team_to_match_nodes;

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

bool dinic_bfs(int nodes) {
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

int dinic(int _src, int _dest, int nodes) {
  src = _src;
  dest = _dest;
  if(src == dest)
    return 0;
  int result = 0;
  while (dinic_bfs(nodes)) {
    fill(work, work + nodes, 0);
    while (int delta = dinic_dfs(src, INT_MAX))
      result += delta;
  }
  return result;
}

int maxFlow(int star){
  rep(i,0, maxnodes-1)
    rep(j,0, maxnodes-1)
      capacity[i][j] = 0;
  rep(i,0,maxnodes-1){
    dist[i] = q[i] = work[i] = 0;
    g[i].clear();
  }
  int src = 0;
  int dest = n-1;
  int from, where, cap;
  rep(j,0,sz(colony_G)-1){
    cap = colony_G[j][2];
    from = colony_G[j][0] - (star-1)*n-1;
    where = colony_G[j][1] - (star-1)*n-1;

    capacity[from][where] = cap;
    addEdge(from, where, capacity[from][where]);
  }
  return dinic(src, dest, n);
}


int main(){

  int t;
  cin >> t;
  rep(_t,1,t){
    cin >> N >> M >> n >> m;
    star_G.resize(N+1, vector<pair<double, int> >(N+1));
    star_src = 1;
    star_dest = N;

    // compute edges between star systems
    int x,y,z;
    vector<vi> coords(N+1, vector<int>(3));
    rep(i,1,N)
      cin >> coords[i][0] >> coords[i][1] >> coords[i][2];

    int from, to, sqr_euclidean;
    rep(i,1,M){
      cin >> from >> to;
      sqr_euclidean = sqr(coords[from][0] - coords[to][0]) +
                      sqr(coords[from][1] - coords[to][1]) +
                      sqr(coords[from][2] - coords[to][2]);
      star_G[from][to].fst = sqrt(sqr_euclidean);
      star_G[from][to].snd = sqr_euclidean;
    }

    colony_G.resize(m, vector<int>(3));
    Cs.assign(N+1, INT_MAX);
    rep(i,1,N){
      rep(j,0,m-1)
        cin >> colony_G[j][0] >> colony_G[j][1] >> colony_G[j][2];
        Cs[i] = maxFlow(i);
    }

    if(n == 1)
      Cs.assign(N+1, INT_MAX);

    double distN = dijkstra(star_src, star_dest, N);

    int cargo;
    bool possible = true;
    if(distN >= _INF)
      possible = false;
    else{
      cargo = INT_MAX;
      int where = star_dest;
      do{
        from = star_parent[where];
        cargo = min(cargo, Cs[where]);
        if(from != where)
          cargo = min(cargo, star_G[from][where].snd);
        if(from == where||where == star_src)
          break;
        where = from;
      }while(true);
      if(cargo == 0)
        possible = false;
    }

    printf("Case #%d: ", _t);
    if(!possible)
      cout << "impossible\n";
    else
      cout << cargo << endl;
    clear_globals();
  }

  return 0;
}
