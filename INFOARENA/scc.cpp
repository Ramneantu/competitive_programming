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

typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef long long ll;

ifstream fin("ctc.in");
ofstream fout("ctc.out");

vector<vector<int> > G;
vector<vector<int> > TG;
vector<bool> seen;
stack<int> S;
vector<vector<int> > SCC;

void dfs_G(int v){
  seen[v] = true;
  rep(i,0,G[v].size()-1)
    if(!seen[G[v][i]])
      dfs_G(G[v][i]);
  S.push(v);
}

void dfs_TG(int v){
  seen[v] = true;
  SCC.back().push_back(v);
  rep(i,0,TG[v].size()-1)
    if(!seen[TG[v][i]])
      dfs_TG(TG[v][i]);
}


int main(){

  int n, m;
  fin >> n >> m;
  G.resize(n+1);
  TG.resize(n+1);
  seen.resize(n+1,false);
  rep(i,0,m-1){
    int from, to;
    fin >> from >> to;
    G[from].push_back(to);
    TG[to].push_back(from);
  }

  rep(i,1,n)
    if(!seen[i])
      dfs_G(i);

  rep(i,0,seen.size()-1)
    seen[i] = false;
  while(!S.empty()){
      int v = S.top(); S.pop();
      if(!seen[v]){
        SCC.push_back(vector<int>());
        dfs_TG(v);
      }
  }
  fout << SCC.size() << endl;
  rep(i,0,SCC.size()-1){
    rep(j,0,SCC[i].size()-1)
      fout << SCC[i][j] << " ";
    fout << "\n";
  }

  return 0;
}
