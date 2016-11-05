#include <utility>
#include <vector>
#include <queue>
#include <iostream>

#define rep(i,a,b) for(int i=int(a); i<=int(b); ++i)

typedef int ll;
using namespace std;
typedef pair<ll,ll> ii;

vector<ii> p;

void initSet(ll n){
  p.resize(n);
  rep(i,0,n-1){
    p[i].first = i;
    p[i].second = 1;
  }
}
ll findSet(ll i){
  if(p[i].first == i)
    return i;
  ll pi = findSet(p[i].first);
  p[i].first = pi;
  return pi;
}
bool isSameSet(ll i, ll j){ return findSet(p[i].first) == findSet(p[j].first); }
void unionSet(ll i, ll j){
  ll pj = findSet(j);
  ll pi = findSet(i);
  if(p[pi].second > p[pj].second)
    p[pj].first = pi;
  else if(p[pj].second > p[pi].second)
      p[pi].first = pj;
  else{
    p[pi].first = pj;
    p[pj].second++;
  }
}

vector<vector<int> > G;
vector<int> parent;
vector<int> visited;
void dfs(int v){
  visited[v] = 1;
  rep(i,0,G[v].size()-1){
    int u = G[v][i];
    if(!visited[u]){
      parent[u] = v;
      dfs(u);
    }
  }
}

int main(){
ll t;
cin >> t;
rep(_t,1,t){
ll n;
  cin >> n;
  priority_queue<pair<ll,ii> > PQ;
  rep(i,0,n-1){
    rep(j,0,n-1){
      ll c;
      cin >> c;
      if(c > 0){
        PQ.push(make_pair(-c,make_pair(i,j)));
      }
    }
  }
  visited.assign(n,0);
  parent.assign(n,0);
  G.assign(n,vector<int>());
  ll mc = 0;
  initSet(n);
  while(!PQ.empty()){
    pair<ll, ii> f = PQ.top(); PQ.pop();
    ll u = f.second.first;
    ll v = f.second.second;
    ll c = -f.first;
    if(!isSameSet(u,v)){
      G[u].push_back(v);
      G[v].push_back(u);
      //cout << u+1 << "--" << v+1 << " = " << c << endl;
      unionSet(u,v);
    }
  }
  dfs(0);
  printf("Case #%d: ", _t);
  vector<int> path(n);
  int k=0;
  for(int i=n-1; i > 0; i = parent[i]){
//    cout << parent[i] << " ";
    path[k++] = i;
  }
  cout << 1 << " ";
  for(int i=k-1; i>=0; --i)
    cout << path[i]+1 << " ";

  cout << "\n";
  }

  return 0;
}
