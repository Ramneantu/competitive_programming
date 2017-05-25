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

int n,m;
vector<vector<int> > G;
vector<int> C;
int cid;
void dfs(int v){
  C[v] = cid;
  for(int i=0; i<G[v].size(); ++i)
    if(C[G[v][i]] == 0)
      dfs(G[v][i]);
}


int main(){

  freopen("dfs.in", "r", stdin);
  freopen("dfs.out", "w", stdout);

  scanf("%d %d", &n, &m);
  G.resize(n,vector<int>());
  C.resize(n,0);
  for(int i=0; i<m; ++i){
    int from, to;
    scanf("%d %d", &from, &to);
    from--;
    to--;
    G[from].push_back(to);
    G[to].push_back(from);
  }

  cid = 0;
  for(int i=0; i<n; ++i){
    if(C[i] == 0){
      cid++;
      dfs(i);
    }
  }
  printf("%d\n", cid);


  return 0;
}
