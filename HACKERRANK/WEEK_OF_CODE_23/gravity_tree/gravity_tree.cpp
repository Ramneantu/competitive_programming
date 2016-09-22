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
using namespace std;

typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef unsigned long long ll;

// adj[i] = nodes that have i as parent
vector<vi> adj;
// dp[i] = (size of subtree root at i, sum(di), sum(di^2))
vector<pair<int, pair<ll,ll> > > dp;

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


//we compute the value of [log(L[p)]
    for (k = 1; 1 << k <= L[p]; k++);
    k--;

    //k = log_2(L[p]);

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
  /*
  cout << "dp by node when in node: " << v << "\n";
  rep(i,1,n)
    cout << dp[i].first << " " << dp[i].second.first << " " << dp[i].second.second << "\n";
  cout << "\n";
  */
  if(!adj[v].empty()){
    // init dp for current node
    dp[v].first += 1;
    rep(i,0,adj[v].size()-1){
      dfs(adj[v][i], level+1);
      //update size
      //printf("%d gets update from %d:\n", v, adj[v][i]);
      //printf("dist from %d: %d\n", adj[v][i], dp[adj[v][i]].first);
      dp[v].first += dp[adj[v][i]].first;
      // update sum of di
      dp[v].second.first += dp[adj[v][i]].first + dp[adj[v][i]].second.first;
      //printf("di from %d: %lld\n", adj[v][i], dp[adj[v][i]].second.first);
      // update sum of di^2
      dp[v].second.second += dp[adj[v][i]].first + 2*dp[adj[v][i]].second.first + dp[adj[v][i]].second.second;
    }
  }
}


int get_dist_between(int n, int u, int v){
  int lca = query(n, u,v);
  if(lca == u)
    return L[v]-L[u];
  else if(lca == v)
    return L[u]-L[v];
  else
    return L[u] + L[v] - 2*L[lca];
}



int main() {

    cin >> n;
    adj.resize(n+1,vi(0));
    dp.resize(n+1, make_pair(0,make_pair(0,0)));
    rep(i,1,n-1){
      int node;
      cin >> node;
      node--;
      adj[node].push_back(i);
      T[i] = node;
    }
    rep(i,0,n-1)
      if(adj[i].empty()){
        dp[i].first = 1;
        dp[i].second.first = 0;
        dp[i].second.second = 0;
      }

    dfs(0, 0);
    process(n);

    /*
    rep(i,0, n-1)
      printf("node %d: level=%d, parent=%d\n", i, L[i], T[i]);
    cout << "\n";
    */

/*
    rep(i,0,n-1){
      cout << i << ": (size, di, di^2): " << dp[i].first << " " << dp[i].second.first << " " << dp[i].second.second << " :: ";
      rep(j,0,adj[i].size()-1)
        cout << adj[i][j] << " ";
      cout << "\n";
    }
*/


    int q;
    cin >> q;
    rep(i,1,q){
      int u,v;
      cin >> u >> v;
      u--;
      v--;
      int dist = get_dist_between(n, u, v);
      int lca = query(n, u, v);
  //    printf("u=%d, parent=%d, v=%d, parent=%d, lca=%d, dist=%d\n", u, T[u], v, T[v], lca, dist);
      if(lca == v){
        ll d = 1;
        int w = u;
        ll acc = 0;
        int prev = u;
        do{
          if(T[w] == T[v] && prev == v){
          //  cout << "break\n";
            break;
          }
          w = T[w];
          //cout << "w=" << w << endl;
          rep(k,0,adj[w].size()-1){
            if(adj[w][k] != prev){
              //cout << "n=" << adj[w][k] << endl;
              acc += dp[adj[w][k]].first*sqr(d+1) + 2*(d+1)*dp[adj[w][k]].second.first + dp[adj[w][k]].second.second;
              //cout << "add=" << dp[adj[w][k]].first*sqr(d+1) + 2*(d+1)*dp[adj[w][k]].second.first + dp[adj[w][k]].second.second << endl;
              //printf("add=%d*%lld+%d*%lld*%lld+%lld\n", dp[adj[w][k]].first, sqr(d+1), 2, d+1, dp[adj[w][k]].second.first, dp[adj[w][k]].second.second);
              //cout << "acc=" << acc << endl;
            }
           }
           acc += sqr(d);
           //printf("add=%lld*%lld\n", d, d);
          d++;
          prev = w;
          //cout << "acc=" << acc << endl;
        }while(w != T[v]);
        cout << acc + dp[u].second.second << endl;
      }
      else
        cout << dp[v].second.second + 2*dist*dp[v].second.first + sqr(dist)*dp[v].first << endl;
    }

    return 0;
}
