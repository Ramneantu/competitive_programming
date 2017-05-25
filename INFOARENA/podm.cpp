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
#define mout(M,n,m) rep(i,1,(n)){ rep(j,1,(m)) cout << (M)[i][j] << " ";  cout << "\n"; }
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
typedef unsigned long long ll;

int main(){

  freopen("podm.in", "r", stdin);
  freopen("podm.out", "w", stdout);

  int n;
  scanf("%d", &n);
  vector<pair<ll,ll> > M(n+1);
  vector<vector<ll> > D(n+2, vector<ll>(n+2, INF_ULL));
  scanf("%lld %lld", &M[1].first, &M[1].second);
  rep(i,2,n){
    int v;
    scanf("%lld", &M[i].second);
    M[i].first = M[i-1].second;
  }

  rep(i,1,n)
    D[i][i] = 0;
  rep(i,1,n-1)
    D[i][i+1] = M[i].first * M[i].second * M[i+1].second;

  rep(k,2,n)
    rep(i,1,n-k)
      rep(j,i,i+k)
        D[i][i+k] = min(D[i][i+k], D[i][j] + D[j+1][i+k] + M[i].first*M[j].second*M[i+k].second);

  printf("%lld\n", D[1][n]);

  return 0;
}
