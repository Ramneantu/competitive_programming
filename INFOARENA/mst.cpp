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
typedef int ll;

ifstream fin("apm.in");
ofstream fout("apm.out");

priority_queue<pair<ll, ii>, vector<pair<ll, ii> >, std::greater<pair<ll, ii> > > EdgeList;

vector<pair<ll, ll> > p;

void initSet(ll n){
  p.resize(n+1);
  rep(i,1,n){
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

int main(){





  int n,m;
  fin >> n >> m;
  rep(i, 0, m-1){
    int x,y,c;
    fin >> x >> y >> c;
    EdgeList.push(make_pair(c, make_pair(x,y)));
  }

  ll mst_cost = 0;
  initSet(n);
  vector<pair<int, int> > Edges;
  while(!EdgeList.empty()){
    pair<ll, ii> front = EdgeList.top(); EdgeList.pop();
    if(!isSameSet(front.second.first, front.second.second)){
      mst_cost += ll(front.first);
      unionSet(front.second.first, front.second.second);
      Edges.push_back(make_pair(front.second.first, front.second.second));
    }
  }
  fout << mst_cost << "\n" << Edges.size() << "\n";
  rep(i,0,Edges.size()-1)
    fout << Edges[i].first << " " << Edges[i].second << "\n";


  return 0;
}
