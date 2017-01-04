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

const int maxnodes = 335;


// REFERENCE: https://sites.google.com/site/indy256/algo_cpp/dinic_flow
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

int main(){

  int tests; cin >> tests;
  rep(_t,1,tests){
    int n, m; cin >> n >> m;
    nodes = 1 + n + m + 1;
    src = 0;
    dest = nodes-1;
    team_to_match_nodes.clear();
    team_to_match_nodes.resize(n+1);

    vector<int> wins(n+1, 0);
    rep(_w, 1, n)
      cin >> wins[_w];

    rep(_m, 1, m){
      int _t1,_t2; cin >> _t1 >> _t2;
      int t1 = min(_t1, _t2);
      int t2 = max(_t1, _t2);
      team_to_match_nodes[t1][n+_m] = true;
      team_to_match_nodes[t2][n+_m] = true;
    }

    printf("Case #%d: ", _t);
    rep(team, 1, n){
      bool edge_added;
      int wmax = wins[team] + team_to_match_nodes[team].size();
      // build graph
      // source to all teams
      rep(i,0, maxnodes-1)
        rep(j,0, maxnodes-1)
          capacity[i][j] = 0;
      rep(i,0,maxnodes-1){
        dist[i] = q[i] = work[i] = 0;
        g[i].clear();
      }

      edge_added = false;
      rep(i, 1, n){
        if(i != team){
          capacity[src][i] = wmax - wins[i];
          addEdge(src, i, capacity[src][i]);
        }
      }
      // teams to their matches except current team.
      rep(i,1,n){
        if(i != team){
          for(map<int,bool>::iterator it=team_to_match_nodes[i].begin(); it != team_to_match_nodes[i].end(); ++it){
            if(it->snd){
              if(team_to_match_nodes[team].find(it->fst) == team_to_match_nodes[team].end()){
                capacity[i][it->fst] = 1;
                addEdge(i,it->fst, 1);
                edge_added = true;
              }
            }
          }
        }
      }

      // all matches to sink
      rep(i, n+1, nodes-2){
        capacity[i][dest] = 1;
        addEdge(i, dest, 1);
      }


      DBG(
        printf("\ncapacity graph for team: %d\n", team);
        rep(i,0,nodes-1){
          cout << i << ": ";
          rep(j,0,nodes-1)
            if(capacity[i][j] > 0)
              cout << j << "(" << capacity[i][j] << ") ";
          cout << "\n";
        })

      // get max_flow
      int max_flow = maxFlow(src, dest);

      DBG(
        printf("max flow: %d\n", max_flow);
        cout << "flow from source:\n";
        rep(i,0,sz(g[src])-1)
          printf("%d(%d)\n", g[src][i].to, g[src][i].f);)

      bool won = true;
      if(m - max_flow - team_to_match_nodes[team].size() != 0){
        if(edge_added){
          won = false;
        }
      }
      else{
        rep(i,0,sz(g[src])-1){
          int wins_current_team = wins[team] + team_to_match_nodes[team].size();
          int wins_other_team = g[src][i].f + wins[g[src][i].to];
          DBG(printf("wins current team %d: %d, team %d: %d\n", team, wins_current_team, g[src][i].to, wins_other_team);)
          if(g[src][i].to != team && wins_other_team > wins_current_team){
            won = false;
            break;
          }
        }
      }
        if(won){
          if(team == 1)
            cout << "yes";
          else
            cout << " yes";
        }
        else{
          if(team == 1)
            cout << "no";
          else
            cout << " no";
        }
    }
    cout << "\n";
  }

  return 0;
}
