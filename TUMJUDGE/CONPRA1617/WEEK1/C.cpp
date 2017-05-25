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

#define NMAX 330

int main(){

  int t;
  cin >> t;
  string dummy;
  getline(cin,dummy);
  char s[NMAX];
  rep(_t,1,t){
    cin.getline(s,NMAX);
    int x = 0;
    int len = 0;
    for(int i=0; i<strlen(s); ++i)
      if(s[i] == '#')
        break;
      else{
        x = x*10 + s[i]-'0';
        len++;
      }
    cout << "Case #" << _t << ": ";
    for(int i=x+len+1; i<strlen(s); ++i)
      cout << s[i];
    for(int i=len+1; i<x+len+1; ++i)
      cout << s[i];
    cout << "\n";
  }


  return 0;
}
