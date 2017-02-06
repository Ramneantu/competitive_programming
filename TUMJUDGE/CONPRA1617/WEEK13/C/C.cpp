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

typedef vector<int> VI;
typedef pair<int, int> II;
typedef vector<II> VII;
typedef long long ll;
typedef vector<VI> VVI;

const int INF = 1000000000;

struct MaxFlow {
  int N;
  VVI cap, flow;
  VI dad, Q;

  MaxFlow(int N) :
    N(N), cap(N, VI(N)), flow(N, VI(N)), dad(N), Q(N) {}

  void AddEdge(int from, int to, int cap) {
    this->cap[from][to] += cap;
  }

  int BlockingFlow(int s, int t) {
    fill(dad.begin(), dad.end(), -1);
    dad[s] = -2;

    int head = 0, tail = 0;
    Q[tail++] = s;
    while (head < tail) {
      int x = Q[head++];
      for (int i = 0; i < N; i++) {
        if (dad[i] == -1 && cap[x][i] - flow[x][i] > 0) {
          dad[i] = x;
          Q[tail++] = i;
        }
      }
    }

    if (dad[t] == -1) return 0;

    int totflow = 0;
    for (int i = 0; i < N; i++) {
      if (dad[i] == -1) continue;
      int amt = cap[i][t] - flow[i][t];
      for (int j = i; amt && j != s; j = dad[j])
        amt = min(amt, cap[dad[j]][j] - flow[dad[j]][j]);
      if (amt == 0) continue;
      flow[i][t] += amt;
      flow[t][i] -= amt;
      for (int j = i; j != s; j = dad[j]) {
        flow[dad[j]][j] += amt;
        flow[j][dad[j]] -= amt;
      }
      totflow += amt;
    }

    return totflow;
  }

  int GetMaxFlow(int source, int sink) {
    int totflow = 0;
    while (int flow = BlockingFlow(source, sink))
      totflow += flow;
    return totflow;
  }
};

int main(){

  int t;
  cin >> t;
  rep(_t,1,t){
    int n,m,b; cin >> n >> m >> b;
    int nodes = 1 + n + m + b + 1;
    MaxFlow mf(nodes);
    int src = 0;
    int dest = nodes-1;

    vector<II> prefs(n+1);
    rep(i,1,n){
      cin >> prefs[i].fst >> prefs[i].snd; // meal, bev
    }


    #if 1
    int E = 0;
    // from meal to person
    int from, to;
    rep(i,1,n){
      from = prefs[i].fst;
      to = i+m;
      //capacity[from][to] = 1;
      //addEdge(from, to, capacity[from][to]);
      mf.AddEdge(from, to, 1);

      DBG(printf("add: %d -> %d\n", from, to);)
      E++;

      // from person to bev
      from = m+i;
      to = m + n + prefs[i].snd;
      //capacity[from][to] = 1;
      //addEdge(from, to, capacity[from][to]);
      mf.AddEdge(from, to, 1);

      DBG(printf("add: %d -> %d\n", from, to);)
      E++;
    }

    // from source to meals
    rep(i,1,m){
      from = 0;
      to = i;
      //capacity[from][to] = 1;
      //addEdge(from, to, capacity[from][to]);
      mf.AddEdge(from, to, 1);

      DBG(printf("add: %d -> %d\n", from, to);)
      E++;
    }

    // from bevs to sink
    rep(i,1,b){
      from = m + n + i;
      to = dest;
      //capacity[from][to] = 1;
      //addEdge(from, to, capacity[from][to]);
      mf.AddEdge(from, to, 1);

      DBG(printf("add: %d -> %d\n", from, to);)
      E++;
    }
    DBG(cout << "added " << E << " edges.\n";)
    #else
    // src -> persons
    int from, to;
    rep(i,1,n){
      from = src;
      to = i;
      capacity[from][to] = 1;
      addEdge(from, to, capacity[from][to]);
    }

    // pers -> meal AND 1 constraint -> bev
    rep(i,1,n){
      from = i;
      to = n+prefs[i].fst;
      capacity[from][to] = 1;
      addEdge(from, to, capacity[from][to]);

      // 1 constraint -> bev
      from = n + m + prefs[i].fst;
      to = n + m + m + prefs[i].snd;
      capacity[from][to] = 1;
      addEdge(from, to, capacity[from][to]);
    }

    // meal -> 1 constraint
    rep(i,1,m){
      from = n+i;
      to = n+m+i;
      capacity[from][to] = 1;
      addEdge(from, to, capacity[from][to]);
    }


    // bev -> dest
    rep(i,1,b){
      from = n+m+m+i;
      to = dest;
      capacity[from][to] = 1;
      addEdge(from, to, capacity[from][to]);
    }

    #endif
    //printf("Case #%d: %d\n", _t, maxFlow(src,dest));
    printf("Case #%d: %d\n", _t, mf.GetMaxFlow(src,dest));

    // clear
    /*
    rep(i,0, maxnodes-1)
      rep(j,0, maxnodes-1)
        capacity[i][j] = 0;
    rep(i,0,maxnodes-1){
      dist[i] = q[i] = work[i] = 0;
      g[i].clear();
    }
    */
  }

  return 0;
}
