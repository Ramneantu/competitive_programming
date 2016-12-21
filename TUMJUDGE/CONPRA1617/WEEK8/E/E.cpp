#include <map>
#include <set>
#include <list>
#include <cassert>
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
#define mout(M,n,m) rep(i,0,(n)-1){ rep(j,0,(m)-1) cout << (M)[i][j] << " ";  cout << "\n"; }
#define vout(V,a,b,msg) cout << msg << ": "; rep(i,a,b)  cout << V[i] << " "; cout << "\n";
using namespace std;

#define INF_ULL ULLONG_MAX
#define INF_LL  LLONG_MAX
#define NINF_LL LLONG_MIN
#define INF_L   LONG_MAX
#define NINF_L   LONG_MIN
#define INF_U   UINT_MAX
#define INF     INT_MAX
#define NINF     INT_MIN
#define fst first
#define snd second

#define debug 0
#define DBG(code) if(debug){    \
                    do{         \
                    code        \
                    }while(0);  \
                  }

typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef long long ll;

inline double to_rad(int deg){ return deg*M_PI*1.0 / 180; }

string transform(string s, map<char,string> & Prods){
  string new_s;
  rep(i,0,sz(s)-1){
    if(s[i] != '-' && s[i] != '+'){
      new_s += Prods[s[i]];
    }
    else{
      new_s += s[i];
    }
  }
  return new_s;
}

int main(){

  int t;
  cin >> t;
  rep(_t,1,t){
    map<char, string> Prods;
    int n, d, a;
    string s;
    cin >> n >> d >> a >> s;
    rep(i,0,n-1){
      string q;
      cin >> q;
      Prods[q[0]] = q.substr(3);
    }
    DBG(
      for(map<char,string>::iterator it = Prods.begin(); it!=Prods.end(); ++it)
        cout << it->first << "=>" << it->second << endl;
    )

    rep(i,0,d-1)
      s = transform(s, Prods);

    DBG(cout << s << endl;)

    cout << "Case #" << _t << ":\n";
    double alpha = 0;
    double x = 0;
    double y = 0;
    rep(i,0,sz(s)-1){
      if(s[i] == '-'){
        alpha -= to_rad(a);
      }
      else if(s[i] == '+'){
        alpha += to_rad(a);
      }
      else{
        printf("%.16lf %.16lf\n", x, y);
        x += cos(alpha);
        y += sin(alpha);
      }
    }
    printf("%.16lf %.16lf\n", x, y);
    cout << "\n";
  }

  return 0;
}
