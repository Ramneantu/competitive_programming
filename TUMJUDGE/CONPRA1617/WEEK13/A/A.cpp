#include <map>
#include <cassert>
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

#define T long long
#define CLEAR -1

inline T max(T a, T b){
  return (a < b ? b : a);
}

class SegmentTree{
private:
  vector<T> lo;
  vector<T> hi;
  vector<T> delta;
  vector<T> s;
  T n;
public:
  SegmentTree(){}
  SegmentTree(T n){
    n = n;
    lo.resize(4*n+1);
    hi.resize(4*n+1);
    delta.resize(4*n+1);
    s.resize(4*n+1,0);
    init(1,0,n-1);
  }
  void init(T i, T a, T b){
    lo[i] = a;
    hi[i] = b;
    if(a == b)
      return;
    T m = (a+b)/2;
    init(2*i,a,m);
    init(2*i+1, m+1,b);
  }

  void prop(T i){
    if(delta[i] == CLEAR){
      delta[2*i] = delta[2*i+1] = CLEAR;
    }
    else{
      delta[2*i] += delta[i];
      delta[2*i+1] += delta[i];
    }
    delta[i] = 0;
  }

  void update(T i){
    s[i] = 0;
    if(delta[2*i] != CLEAR)
      s[i] += s[2*i] + delta[2*i];
    if(delta[2*i+1] != CLEAR)
      s[i] += s[2*i+1] + delta[2*i+1];
  }

  void increment(T i, T a, T b, T v){
    if(b < lo[i] || hi[i] < a)
      return;

    if(a <= lo[i] && hi[i] <= b){
      delta[i] = max(0, delta[i]) + v;
      return;
    }

    prop(i);
    increment(2*i,a,b,v);
    increment(2*i+1,a,b,v);

    update(i);

  }

  int sum(T i, T a, T b){
    if(b < lo[i] || hi[i] < a)
      return 0;

    if(a <= lo[i] && hi[i] <= b){
      if(delta[i] == CLEAR)
        return 0;
      return s[i] + delta[i];
    }
    prop(i);

    T sumLeft = sum(2*i,a,b);
    T sumRight = sum(2*i+1,a,b);

    update(i);

    return max(0,sumLeft) + max(0,sumRight);
  }

  void zerofy(T i, T a, T b){
    if(b < lo[i] || hi[i] < a)
      return;

    if(a <= lo[i] && hi[i] <= b){
      delta[i] = CLEAR;
      return;
    }

    prop(i);
    zerofy(2*i,a,b);
    zerofy(2*i+1,a,b);
    update(i);
  }

  void zerofy(T a, T b){
    zerofy(1,a,b);
  }
  void increment(T a, T b, T v){
    increment(1,a,b,v);
  }
  T sum(T a, T b){
    return sum(1,a,b);
  }
  void increment(T a,T v){
    increment(1,a,a,v);
  }
  T sum(T a){
    return sum(1,a,a);
  }

};


void prnt(SegmentTree st, T n){
  cout << "ST: ";
  rep(i,0,n-1){
    cout << st.sum(i) << " ";
  }
  cout << endl;
}



int main(){

  #if 0
    {
      // TEST 1
      int n = 4;
      SegmentTree st(n);
      st.increment(0,0,1);
      prnt(st,n);
      assert(st.sum(0,n-1) == 1);
      st.zerofy(1,3);
      prnt(st,n);
      assert(st.sum(0,n-1) == 1);
      st.zerofy(0,2);
      prnt(st,n);
      assert(st.sum(0,n-1) == 0);
    }
    return 0;
  #endif



  int t;
  cin >> t;
  rep(_t,1,t){
    T n, k; cin >> n >> k;
    SegmentTree st(n);

    char c;
    T a,b;
    T caught = 0;
    rep(_k,0,k-1){
      cin >> c;
      if(c == 's'){
        cin >> a; a--;
        DBG(cout << "s " << a << endl;)
        st.increment(a,1);
        DBG(prnt(st,n);)
      }
      else if(c == 'd'){
        cin >> a; a--;
        DBG(cout << "d " << a << endl;)
        if(st.sum(a) > 0){
          st.increment(a,-1);
        }
        DBG(prnt(st,n);)
      }
      else if(c == 'c'){
        cin >> a >> b;
        a--;
        b--;
        DBG(cout << "c " << a << " " << b << endl;)
        caught += st.sum(a,b);
        st.zerofy(a,b);
        DBG(prnt(st,n);)
        DBG(cout << "caught: " << caught << endl;)
      }
    }
    cout << "Case #" << _t << ": " << caught << endl;
  }

  return 0;
}
