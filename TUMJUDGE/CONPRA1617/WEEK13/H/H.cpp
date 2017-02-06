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

void dijkstra(int src, int nodes, vector<long>& dist, vector<vector<ii> >& G){
  dist.assign(nodes,INT_MAX);
  dist[src] = 0;
  priority_queue<pair<long,int> , vector<pair<long,int> >, greater<pair<long,int> > > pq;
  pq.push(ii(0,src));
  while(!pq.empty()){
    ii top = pq.top(); pq.pop();
    long d = top.fst;
    int v = top.snd;
    if(d == dist[v]){
      rep(i,0,sz(G[v])-1){
        int u = G[v][i].fst;
        int c = G[v][i].snd;
        if(dist[v] + c < dist[u]){
          dist[u] = dist[v] + c;
          pq.push(make_pair(dist[u], u));
        }
      }
    }
  }
}


int main(){

  int t;
  cin >> t;
  rep(_t,1,t){
    int n,m,s;
    cin >> n >> m >> s;

    vector<vector<ii> >G(n, vector<ii>());
    rep(_m,0,m-1){
      int from,to;
      int c;
      cin >> from >> to >> c;
      from--, to--;
      G[from].push_back(make_pair(to, c));
      G[to].push_back(make_pair(from, c));
    }
    vector<bool> sts(n, false);
    rep(_s,1,s){
      int st; cin >> st; st--;
      sts[st] = true;
    }
    vector<long> dist(n,0);
    dijkstra(0, n, dist, G);
    long mi = LONG_MAX;
    rep(i,0,n-1)
      if(sts[i])
        mi = min(mi, dist[i]);


    printf("Case #%d: %d ", _t, int(mi));
    rep(i,0,n-1){
      if(sts[i] && dist[i] == mi)
        cout << i+1 << " ";
    }
    cout << endl;
  }

  return 0;
}
