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

class SegmentTree{
public:
  vector<int> lo;
  vector<int> hi;
  vector<int> delta;
  vector<int> s;
  int n;
  SegmentTree(){}
  SegmentTree(int n){
    n = n;
    int nn = 4*n+1;
    lo.resize(nn);
    hi.resize(nn);
    delta.resize(nn);
    s.resize(nn,0);
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
    delta[2*i] = max(delta[2*i], delta[i]);
    delta[2*i+1] = max(delta[2*i+1], delta[i]);
  }

  void update(int i){
    s[i] = max(delta[i], max(s[i], max(max(s[2*i], delta[2*i]), max(s[2*i+1], delta[2*i+1]))));
  }

  void upgrade(int i, int a, int b, int v){
    if(b < lo[i] || hi[i] < a)
      return;

    if(a <= lo[i] && hi[i] <= b){
      delta[i] = v;
      return;
    }

    prop(i);
    upgrade(2*i,a,b,v);
    upgrade(2*i+1,a,b,v);

    update(i);

  }

  int maxim(int i, int a, int b){
    if(b < lo[i] || hi[i] < a)
      return 0;

    if(a <= lo[i] && hi[i] <= b){
      return max(s[i],delta[i]);
    }
    prop(i);

    int maxLeft = maxim(2*i,a,b);
    int maxRight = maxim(2*i+1,a,b);

    update(i);

    return max(maxLeft,maxRight);
  }

  void upgrade(int a, int b, int v){
    upgrade(1,a,b,v);
  }
  int maxim(int a, int b){
    return maxim(1,a,b);
  }
};

int main(){

  int t;
  cin >> t;
  rep(_t,1,t){
    int n,k; cin>>n>>k;
    SegmentTree st(n+1);
    vector<int> hs;
    rep(i,0,k-1){
      int w,h,p; cin>>w>>h>>p;
      int l = p, r = p+w-1;

      int mx = st.maxim(l,r);
      st.upgrade(l,r,mx+h);
      mx = st.maxim(0,n-1);
      hs.push_back(mx);
    }
    printf("Case #%d: ", _t);
    rep(i,0,sz(hs)-1)
      cout<<hs[i]<<" ";
    cout<<"\n";

  }


  return 0;
}
