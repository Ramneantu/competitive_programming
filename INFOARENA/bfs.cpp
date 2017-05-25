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
using namespace std;

typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef long long ll;

ifstream fin("bfs.in");
ofstream fout("bfs.out");

vector<vector<ll> > G;
vector<ll> dist;
ll edge_cost = 1;
void bfs(ll s){
  vector<bool> visited(G.size(),false);
  queue<ll> Q;
  Q.push(s);
  dist[s] = 0;
  visited[s] = true;
  while(!Q.empty()){
    ll v = Q.front(); Q.pop();
    for(ll i=0; i<G[v].size(); ++i){
        ll u = G[v][i];
        if(!visited[u]){
          Q.push(u);
          dist[u] = dist[v] + edge_cost;
          visited[u] = true;
        }
    }
  }
  visited.clear();
  G.clear();
}

int main(){

  ll n,m,s;
  fin >> n >> m >> s;
  G.resize(n+1);
  dist.resize(n+1, -1);
  for(ll i=0; i<m; ++i){
    ll from, to;
    fin >> from >> to;
    G[from].push_back(to);
  }

  bfs(s);
  for(ll i=1; i<=n; ++i)
    fout << dist[i] << " ";



  return 0;
}
