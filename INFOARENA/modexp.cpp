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
typedef long long ll;

ll modexp(ll a, ll b, ll m){
  if(b == 0)
    return 1;
  a = mod(a,m);
  ll res = 1;
  while(b > 0){
    if(b%2){
      res = mod(res*a, m);
      b--;
    }
    else{
      b /= 2;
      a = mod(a*a,m);
    }
  }
  return res;
}


int main(){

  freopen("lgput.in", "r", stdin);
  freopen("lgput.out", "w", stdout);


  ll n, p, mod;
  mod = 1999999973;
  cin >> n >> p;
  cout << modexp(n,p,mod) << endl;


  return 0;
}
