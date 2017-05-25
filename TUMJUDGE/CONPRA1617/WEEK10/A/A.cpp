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
#define mout(M,n,m) rep(i,0,(n)-1){ rep(j,0,(m)-1) cout << (M)[i][j] << " ";  cout << "\n"; }
#define vout(V,a,b,msg) cout << msg << ": "; rep(i,a,b)  cout << V[i] << " "; cout << "\n";
#define fst first
#define snd second
#define debug 0
#define DBG(code) if(debug){    \
                    do{         \
                    code        \
                    }while(0);  \
                  }
using namespace std;

typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef long long ll;


int main(){

  int t;
  cin >> t;
  rep(_t,1,t){
		int m, n; cin >> m >> n;
		vector<vector<double> > V(n,vector<double>(4,0));
    rep(i,0,n-1){
    	double l,s; cin >> l >> s;
      V[i][0] = s*1.0 / l;
      V[i][1] = s;
      V[i][2] = l;
      V[i][3] = i;
    }
    sort(all(V));

		int cur_m = 0;
		int i=V.size()-1;
    vector<int> R;
    while(i>=0){
      if(V[i][2] + cur_m > m){
        i--;
      }
      else{
        cur_m += V[i][2];
        R.pb(V[i][3]+1);
        if(cur_m >= m)
          break;
      }
    }

    printf("Case #%d: ", _t);
    rep(i,0,R.size()-1)
      cout << R[i] << " ";
    cout << "\n";
  }

  return 0;
}
