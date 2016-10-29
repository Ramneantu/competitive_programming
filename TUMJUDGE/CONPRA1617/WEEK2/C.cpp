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
#define vout(A,l,r) rep(i,l,r) cout << A[i] << " ";
using namespace std;

#define INF_ULL ULLONG_MAX
#define INF_LL  LLONG_MAX
#define NINF_LL LLONG_MIN
#define INF_L   LONG_MAX
#define NINF_L   LONG_MIN
#define INF_U   UINT_MAX
#define INF     INT_MAX
#define NINF     INT_MIN


typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef long long ll;

vector<vector<int> > G;
vector<int> indeg;
vector<int> sorted;
void topsort(){
  queue<int> Q;
  for(int i=0; i<G.size(); ++i)
    if(!indeg[i])
      Q.push(i);
  while(!Q.empty()){
    int v = Q.front(); Q.pop();
    sorted.push_back(v);
    rep(i,0,G[v].size()-1){
      int u = G[v][i];
      indeg[u]--;
      if(indeg[u] <= 0)
        Q.push(u);
    }
  }
}


int main(){

    int t;
    cin >> t;
    rep(_t,1,t){
      int n, m;
      cin >> n >> m;
      G.clear();
      G.resize(n,vector<int>());
      vector<int> v(n,0);
      sorted.clear();
      indeg.clear();
      indeg.resize(n,0);
      rep(i,0,n-1)
        cin >> v[i];
      rep(i,1,m){
        int from, to;
        cin >> from >> to;
        from--;
        to--;
        G[from].push_back(to);
        indeg[to]++;
      }

      topsort();

      int sum = 0;
      for(int i=0; i<sorted.size(); ++i){
        sum += v[sorted[i]];
      }

      printf("Case #%d: %d\n", _t, sum);
    }


  return 0;
}
