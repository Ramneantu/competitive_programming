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

template<typename T>
void egcd(T a, T b, T &d, T &x, T &y) {
    if (b == 0) {
        d = a;
        x = 1;
        y = 0;
    }
    else {
        T x0, y0;
        egcd(b, a%b, d, x0, y0);
        x = y0;
        y = x0 - (a/b) * y0;
    }
}

int main(){

  freopen("inversmodular.in", "r", stdin);
  freopen("inversmodular.out", "w", stdout);

  ll a,n;
  cin >> a >> n;

  ll d, x,y;
  egcd(a,n,d,x,y);

  while(x < 0){
    x += n;
  }
  cout << x << endl;


  return 0;
}
