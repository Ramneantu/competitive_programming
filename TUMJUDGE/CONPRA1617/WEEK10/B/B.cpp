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
#define DBG(code) if(0){    \
                    do{         \
                    code        \
                    }while(0);  \
                  }
using namespace std;

typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef long long ll;


bool cmp(ii a, ii b){
  if(a.fst == b.fst){
    return (a.snd > b.snd);
  }
  return (a.fst < b.fst);
}

int main(){

  int t;
  cin >> t;
  rep(_t,1,t){
    int l,n,r; cin >> l >> n >> r;
    vector<ii> Ls(n); // .first = d, .second  =p
    rep(i,0,n-1){
      int centre; cin >> centre;
			Ls[i].fst = centre-r;
      Ls[i].snd = centre+r;
    }
    sort(all(Ls));

    bool possible = true;
    int last = 0;
    int i=0;
    int max_right = -1;
    int ct = 0;
    while(i<Ls.size()){
      if(Ls[i].fst <= last){
        max_right = max(max_right, Ls[i].snd);
        if(max_right >= l)
          break;
        i++;
      }
      else{
        if(max_right == -1){
          possible = false;
          break;
        }
        ct++;
        DBG(cout << Ls[i].fst << " -- " << Ls[i].snd << "\n";)
        last = max_right;
        max_right = -1;
      }
    }
    if(max_right >= l){
      if(i < Ls.size())
    	 ct++;
      DBG(cout << Ls[i].fst << " -- " << Ls[i].snd << "\n";)
    }
    else
      possible = false;
    printf("Case #%d: ", _t);
    if(possible)
      cout << ct << "\n";
    else
      cout << "impossible\n";
  }

  return 0;
}
