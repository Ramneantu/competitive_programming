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
#define vout(A,l,r) rep(i,l,r) cout << A[i] << " ";
using namespace std;

#define INF_ULL ULLONG_MAX
#define INF_LL  LLONG_MAX
#define NINF_LL LLONG_MIN
#define INF_L   LONG_MAX
#define NINF_L   LONG_MIN
#define INF_U   UINT_MAX
#define INF     INT_MAX
#define NINF     INT_MIN


typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef int ll;

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

vector<int> v;
vector<bool> married;

int main(){

  int t;
  scanf("%d", &t);
  for(int _t=1; _t<=t; ++_t){
    int a,b,c;
    scanf("%d %d %d", &a, &b, &c);
    initSet(a);
    v.resize(a+1);
    married.resize(a+1);
    rep(i,1,a)
      married[i] = false;
    rep(i,1,a-1)
      scanf("%d", &v[i]);
    rep(i,1,b){
      int from, to;
      scanf("%d %d", &from, &to);
      unionSet(from, to);
    }
    rep(i,1,c){
      int from, to;
      scanf("%d %d", &from, &to);
      married[from] = married[to] = true;
      unionSet(from, to);
    }
    int max_v = -1;
    rep(i,1,a-1)
      if(!married[i] && !isSameSet(i,a))
        if(v[i] > max_v)
          max_v = v[i];
    if(max_v == -1)
      printf("Case #%d: impossible\n", _t);
    else
      printf("Case #%d: %d\n", _t, max_v);
  }


  return 0;
}
