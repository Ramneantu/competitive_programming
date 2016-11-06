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
#include <chrono>

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
typedef long long ll;

vector<pair<ll, ll> > p;
vector<ll> sizes;
vector<vector<int> > hates;

void initSet(ll n){
  p.resize(n);
  sizes.resize(n);
  rep(i,0,n-1){
    p[i].first = i;
    p[i].second = 1;
    sizes[i] = 1;
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
int unionSet(ll i, ll j){
  ll pj = findSet(j);
  ll pi = findSet(i);
  if(p[pi].second > p[pj].second){
    p[pj].first = pi;
    sizes[pi] += sizes[pj];
    return pi;
  }
  else if(p[pj].second > p[pi].second){
      p[pi].first = pj;
      sizes[pj] += sizes[pi];
      return pj;
  }
  else{
    p[pi].first = pj;
    p[pj].second++;
    sizes[pj] += sizes[pi];
    return pj;
  }
}

int main(){


  chrono::high_resolution_clock::time_point t1, t2;
  ll duration;

  t1 = chrono::high_resolution_clock::now();
  /*
  int t;
  cin >> t;
  rep(_t,1,t){
    int n,m;
    cin >> n >> m;
    initSet(n);
    hates.clear();
    hates.resize(n,vector<int>());
    vector<pair<int,int> > F;
    vector<pair<int,int> > H;
    rep(i,0,m-1){
      char c;
      int x,y;
      cin >> c >> x >> y;
      x--;
      y--;
      if(c == 'F')
        F.push_back(make_pair(x,y));
      else
        H.push_back(make_pair(x,y));
    }
    rep(i,0,F.size()-1)
      unionSet(F[i].first, F[i].second);
    rep(i,0,H.size()-1){
      int sx = findSet(H[i].first);
      int sy = findSet(H[i].second);
      hates[sx].push_back(sy);
      hates[sy].push_back(sx);
    }

    for(int i=0; i<hates.size(); ++i)
      for(int j=1; j<hates[i].size(); ++j)
        unionSet(hates[i][0], hates[i][j]);
    int set_0 = findSet(0);
    int total = 0;
    rep(i,0,n-1){
      int si = findSet(i);
      if(findSet(i) == set_0)
        total++;
    }

    cout << "Case #" << _t << ": ";
    if(2*total > n)
      cout << "yes\n";
    else
      cout << "no\n";
  }
  */
  vector<vector<int> > V(200000, vector<int>(100, 0));
  rep(i,0, 200000-1)
    rep(j,0,99)
        V[i][j]++;
  t2 = chrono::high_resolution_clock::now();
  duration = chrono::duration_cast<chrono::milliseconds>( t2 - t1 ).count();
  cout << "Duration: " << duration << " milliseconds" << endl;

  return 0;
}
