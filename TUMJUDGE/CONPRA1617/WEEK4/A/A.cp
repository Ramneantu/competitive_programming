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

typedef long T;
typedef pair<T,T> TT;
#define INF LONG_MAX/2


int main(){

  int t;
  cin >> t;
  rep(_t,1,t){
    int n,m;
    cin >> n >> m;
    vector<vector<TT> > G(n);
    rep(i,1,m){
      int v,w,c;
      cin >> v >> w >> c;
      v--; w--;
      G[v].push_back(TT(w,c));
      G[w].push_back(TT(v,c));
    }

    vector<T> dist(n, INF);
    dist[0] = 0;
    priority_queue<TT, vector<TT>, greater<TT> > pq;
    pq.push(TT(0,0));

    while(!pq.empty()){
      TT top = pq.top(); pq.pop();
      int d = top.first, u = top.second;
      if(d == dist[u]){
        for(int i=0; i<G[u].size(); ++i){
          int v = G[u][i].first;
          int weight_u_v = G[u][i].second;
          if(dist[u] + weight_u_v < dist[v]){
            dist[v] = dist[u] + weight_u_v;
            pq.push(TT(dist[v], v));
          }
        }
      }
    }
    printf("Case #%d: %ld\n", _t, dist[n-1]);
  }

  return 0;
}
