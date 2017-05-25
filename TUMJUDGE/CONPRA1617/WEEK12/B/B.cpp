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

const int MOD = 1000000007;

class SegmentTree{
private:
  vector<int> lo;
  vector<int> hi;
  vector<int> delta;
  vector<int> s;
  int n;
public:
  SegmentTree(){}
  SegmentTree(int n){
    n = n;
    lo.resize(4*n+1);
    hi.resize(4*n+1);
    delta.resize(4*n+1);
    s.resize(4*n+1,0);
    init(1,0,n-1);
  }
  void init(int i, int a, int b){
    lo[i] = a;
    hi[i] = b;
    if(a == b)
      return;
    int m = (a+b)/2;
    init(2*i,a,m);
    init(2*i+1, m+1,b);
  }

  void prop(int i){
    delta[2*i] += delta[i];
    delta[2*i+1] += delta[i];
    delta[i] = 0;
  }

  void update(int i){
    s[i] = s[2*i] + delta[2*i] + s[2*i+1] + delta[2*i+1];
  }

  void increment(int i, int a, int b, int v){
    if(b < lo[i] || hi[i] < a)
      return;

    if(a <= lo[i] && hi[i] <= b){
      delta[i] += v;
      return;
    }

    prop(i);
    increment(2*i,a,b,v);
    increment(2*i+1,a,b,v);

    update(i);

  }

  int sum(int i, int a, int b){
    if(b < lo[i] || hi[i] < a)
      return 0;

    if(a <= lo[i] && hi[i] <= b){
      return s[i] + delta[i];
    }
    prop(i);

    int sumLeft = sum(2*i,a,b);
    int sumRight = sum(2*i+1,a,b);

    update(i);

    return sumLeft + sumRight;
  }

  void increment(int a, int b, int v){
    increment(1,a,b,v);
  }

  int sum(int a, int b){
    return sum(1,a,b);
  }

};



int main(){

  int t;
  cin >> t;
  rep(_t,1,t){
    int n,k; cin >> n >> k;
    char c;
    int l,r,q;
    int total=0;
    SegmentTree st(n+1);
    rep(i,0,k-1){
      cin>>c;
      if(c=='i'){
        cin>>l>>r>>q;
        st.increment(l,r,q);
      }
      else if(c=='q'){
        cin>>q;
        total = (total + st.sum(q,q) % MOD ) % MOD;
      }
    }
    printf("Case #%d: %d\n", _t, total%MOD);
  }

  return 0;
}
