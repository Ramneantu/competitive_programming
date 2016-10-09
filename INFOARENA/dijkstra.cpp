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

#define INF_ULL ULLONG_MAX
#define INF_LL  LLONG_MAX
#define NINF_LL LLONG_MIN
#define INF_L   LONG_MAX
#define NINF_L   LONG_MIN
#define INF_U   UINT_MAX
#define INF     INT_MAX
#define NINF     INT_MIN

#define inf INF_LL

typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef long long ll;

int main(){

  freopen("dijkstra.in", "r", stdin);
  freopen("dijkstra.out", "w", stdout);

  int n,m;
  scanf("%d %d", &n, &m);
  vector<vector<ii> > G(n);
  for(int i=0; i<m; ++i){
    int from, to, cost;
    scanf("%d %d %d", &from, &to, &cost);
    from--;
    to--;
    G[from].push_back(make_pair(to, cost));
  }

  vector<ll> dist(n, inf);
  dist[0] = 0;
  priority_queue<ii, vector<ii>, greater<ii> > pq;
  pq.push(ii(0,0));

  while(!pq.empty()){
    ii top = pq.top(); pq.pop();
    int d = top.first, u = top.second;
    if(d == dist[u]){
      for(int i=0; i<G[u].size(); ++i){
        int v = G[u][i].first;
        int weight_u_v = G[u][i].second;
        if(dist[u] + weight_u_v < dist[v]){
          dist[v] = dist[u] + weight_u_v;
          pq.push(ii(dist[v], v));
        }
      }
    }
  }

  for(int i=1; i<n; ++i)
    if(dist[i] >= inf)
      cout << 0 << " ";
    else
      cout << dist[i] << " ";
    cout << "\n";

  return 0;
}
