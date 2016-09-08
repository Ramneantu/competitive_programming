#include <iostream>
#include <algorithm>
#include <numeric>
#include <set>
#include <map>
#include <queue>
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <cstring>
#include <cctype>
#include <cassert>
#include <limits>
#include <functional>
#include <bitset>
#include <utility>

#define rep(i,a,b) for(ll i=ll(a); i<=ll(b); ++i)
#define rev(i,b,a) for(ll i=ll(b); i>=ll(a); --i)
#define mp(x,y) make_pair((x),(y))
#define pb(x) push_back(x)
#define all(c) c.begin(), c.end()
#define tr(container, it) for(auto it=(container).begin(); it != (container).end(); ++it)
#define sqr(x) ((x)*(x))
using namespace std;

typedef unsigned long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;


priority_queue<pair<ll, ii> > EdgeList;
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

  ll n, m, l;
  ll availableCost = 0;
  cin >> n >> m >> l;
  rep(i, 1, m){
    ll a, b, c;
    cin >> a >> b >> c;
    EdgeList.push(make_pair(-c, make_pair(a, b)));
    if(i <= l)
      availableCost += c;
  }

  // Kruskal
  ll mst_cost = 0;
  initSet(n);
  ll mst_edges = 0;
  while(!EdgeList.empty()){
    pair<ll, ii> front = EdgeList.top(); EdgeList.pop();
    if(!isSameSet(front.second.first, front.second.second)){
      mst_cost += ll(-front.first);
      unionSet(front.second.first, front.second.second);
      mst_edges++;
    }
  }

  //cout << mst_cost << endl;

  if(mst_cost > availableCost || mst_edges < n-1)
    cout << "impossible\n";
  else
    cout << "possible\n";

  return 0;
}
