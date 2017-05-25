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


vector<vector<int> > G;
vector<int> indeg;
vector<int> sorted;
void topsort(){
  queue<int> Q;
  for(int i=1; i<=G.size()-1; ++i)
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

  ifstream fin("sortaret.in");
  ofstream fout("sortaret.out");

  int n,m;
  fin >> n >> m;
  G.resize(n+1);
  indeg.resize(n+1);
  rep(i,0,m-1){
    int from,to;
    fin >> from >> to;
    G[from].push_back(to);
    indeg[to]++;
  }

  topsort();
  rep(i,0,sorted.size()-1)
    fout << sorted[i] << " ";

  return 0;
}
