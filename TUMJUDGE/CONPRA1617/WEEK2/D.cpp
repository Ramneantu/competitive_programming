#include<bits/stdc++.h>

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

vector<vector<ii> > G;
vector<int> viz;
vector<int> low;
vector<int> parent;
int ct;
vector<int> res;
void dfs(int v){
  viz[v] = low[v] = ct++;
  rep(i,0,G[v].size()-1){
    int u = G[v][i].second;
    if (viz[u] == 0){
      parent[u] = v;
      dfs(u);
      if (low[u] > viz[v])
        res.push_back(G[v][i].first);
      low[v] = min(low[v], low[u]);
    }
    else if (u != parent[v])
      low[v] = min(low[v], viz[u]);
  }
}

int main(){

  int t;
  cin >> t;
  rep(_t,1,t){
    int n,m;
    cin >> n >> m;
    viz.clear();
    parent.clear();
    low.clear();
    res.clear();
    viz.resize(n);
    parent.resize(n);
    low.resize(n);
    rep(i,0,n-1){
      viz[i] = low[i] = 0;
      parent[i] = 0;
    }
    G.clear();
    G.resize(n,vector<ii>());
    rep(i,1,m){
      int from, to;
      cin >> from >> to;
      from--;
      to--;
      G[from].push_back(make_pair(i,to));
      G[to].push_back(make_pair(i,from));
    }

    ct=1;
    dfs(0);
    cout << "Case #" << _t << ": ";
    sort(res.begin(), res.end());
    rep(i,0,res.size()-1)
      cout << res[i] << " ";
    cout << "\n";
  }


  return 0;
}
