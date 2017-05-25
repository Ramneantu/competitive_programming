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
using namespace std;

typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef long long ll;

// adj[i] = nodes that have i as parent
vector<vi> adj;

#define MAXN 100001
#define LOGMAXN 17
int P[MAXN][LOGMAXN];
int T[MAXN];
int L[MAXN];

vector<ll> pow2;
ll log_2(ll n){
  ll r = upper_bound(pow2.begin(), pow2.end(), n)-pow2.begin();
  ll l = lower_bound(pow2.begin(), pow2.end(), n)-pow2.begin();
  if(l == r)
    return l-1;
  return l;
}

void process(int N)
{
    pow2.push_back(1);
    rep(i,1,17)
      pow2.push_back((1<<i));

    int i, j;

//we initialize every element in P with -1
    for (i = 0; i < N; i++)
        for (j = 0; 1 << j < N; j++)
            P[i][j] = -1;

//the first ancestor of every node i is T[i]
    for (i = 0; i < N; i++)
        P[i][0] = T[i];

//bottom up dynamic programing
    for (j = 1; 1 << j < N; j++)
       for (i = 0; i < N; i++)
           if (P[i][j - 1] != -1)
               P[i][j] = P[P[i][j - 1]][j - 1];
}

int query(int N, int p, int q)
{
    if(p == 0 || q == 0)
      return 0;
    int tmp, k, i;

//if p is situated on a higher level than q then we swap them
    if (L[p] < L[q])
        tmp = p, p = q, q = tmp;


/*
//we compute the value of [log(L[p)]
    for (k = 1; 1 << k <= L[p]; k++);
    k--;
    */
    k = log_2(L[p]);

//we find the ancestor of node p situated on the same level
//with q using the values in P
    for (i = k; i >= 0; i--)
        if (L[p] - (1 << i) >= L[q])
            p = P[p][i];

    if (p == q)
        return p;

//we compute LCA(p, q) using the values in P
    for (i = k; i >= 0; i--)
        if (P[p][i] != -1 && P[p][i] != P[q][i])
            p = P[p][i], q = P[q][i];

    return T[p];
}



int n;
void dfs(int v, int level){
  L[v] = level;
  if(!adj[v].empty()){
    rep(i,0,adj[v].size()-1)
      dfs(adj[v][i], level+1);
  }
}


int main(){

  ifstream fin("lca.in");
  ofstream fout("lca.out");

  ll n,m;
  fin >> n >> m;
  adj.resize(n+1,vi(0));
  rep(i,1,n-1){
    int node;
    fin >> node;
    node--;
    adj[node].push_back(i);
    T[i] = node;
  }

  dfs(0, 0);
  process(n);

  rep(i,1,m){
    int u,v;
    fin >> u >> v;
    u--;
    v--;
    fout << query(n, u, v)+1 << endl;
  }

  return 0;
}
