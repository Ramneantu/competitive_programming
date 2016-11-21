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

typedef int T;
typedef pair<T,T> TT;

vector<vector<T> > G;
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
    int n;
    cin >> n;
    G.resize(n,vector<T>());
    vector<vector<TT> > Gt(n);
    indeg.assign(n,0);
    sorted.assign(n,0);
    vector<T> dist(n,-1);
    T end_cost = 0;
    rep(from,0,n-1){
      int p,s;
      cin >> p >> s;
      if(from == n-1)
        end_cost = p;
      if(from == 0)
        dist[0] = 0;
      rep(j,1,s){
        int to;
        cin >> to;
        to--;
        G[from].push_back(p);
        Gt[to].push_back(TT(from,p));
        indeg[to]++;
      }
    }
    rep(i,0,n-1){
      int v = sorted[i];
      rep(j,0,Gt[i].size()-1)
        if(dist[i] < Gt[i][j].second + dist[Gt[i][j].first])
          dist[i] = Gt[i][j].second + dist[Gt[i][j].first];
    }
    printf("Case #%d: %d\n", _t, dist[n-1] + end_cost);
  }


  return 0;
}
