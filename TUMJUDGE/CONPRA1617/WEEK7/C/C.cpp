#include <map>
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
#define mod(a,n) ((a) < 0 ? ((n)+(a)) : ((a)%(n)))
#define mout(M,n,m) rep(i,0,(n)-1){ rep(j,0,(m)-1) cout << (M)[i][j] << " ";  cout << "\n"; }
using namespace std;

#define debug 0
#define DBG(code) if(debug == 1) \
do{ \
code \
}while(0);

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


typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef long long ll;
typedef long double T;
typedef pair<T,T> TT;


int n;
vector<TT> Points;

inline T CCW(TT P0, TT P1, TT P2){
  return (P1.fst - P0.fst) * (P2.snd - P0.snd) - (P2.fst - P0.fst) * (P1.snd - P0.snd);
}

TT get_centre_of_mass(){
  T C_x = 0;
  T C_y = 0;
  rep(i,0,n-1){
    C_x += Points[i].fst;
    C_y += Points[i].snd;
  }
  return TT(C_x * 1.0 / n, C_y * 1.0 / n);
}

inline bool is_on_segment(TT P, TT P1, TT P2){
  if(P1.fst == P2.fst){
    if(P.snd >= min(P1.snd, P2.snd) && P.snd <= max(P1.snd, P2.snd))
      return true;
    else
      return false;
  }
  if(P.fst >= min(P1.fst, P2.fst) && P.fst <= max(P1.fst, P2.fst))
    return true;
  return false;
}

bool isProjectedPointOnLineSegment(TT v1, TT v2, TT p)
{
  T x1 = v1.fst; T y1 = v1.snd;
  T x2 = v2.fst; T y2 = v2.snd;
  T x3 = p.fst; T y3 = p.snd;

  T k = ((y2-y1) * (x3-x1) - (x2-x1) * (y3-y1))*1.0 / ((y2-y1)*(y2-y1) + (x2-x1)*(x2-x1));
  T x4 = x3 - k * (y2-y1);
  T y4 = y3 + k * (x2-x1);

  DBG(
    printf("X': %.5Lf,%.5Lf\n", x4, y4);
  )
  return is_on_segment(TT(x4,y4), v1, v2);
}

inline bool center_of_mass_valid(TT C, TT P, TT Q){
  return isProjectedPointOnLineSegment(P,Q,C);
}

bool is_stable(TT P, TT Q, TT C, int idp, int idc){
  if(!center_of_mass_valid(C,P,Q))
    return false;
  bool first_element = true;
  T ccw, new_ccw;
  rep(i,0,n-1){
    if(i!= idp && i != idc){
      if(!first_element){
        new_ccw = CCW(P,Q,Points[i]);
        if(new_ccw == 0)
          return false;
        if((ccw > 0 && new_ccw < 0) || (ccw < 0 && new_ccw > 0))
          return false;
        ccw = new_ccw;
      }{
        ccw = CCW(P,Q,Points[i]);
        if(ccw == 0)
          return false;
        first_element = false;
      }
    }
  }
  return true;
}

int main(){

  int t;
  scanf("%d", &t);
  rep(_t,1,t){
    cin >> n;
    rep(i,0,n-1){
      T x,y;
      cin >> x >> y;
      Points.push_back(make_pair(x,y));
    }

    TT C = get_centre_of_mass();
    DBG(
      printf("Center of mass: %.5Lf, %.5Lf\n", C.fst, C.snd);
    )

    int rotations = 0;
    rep(i,0,n-1){
      DBG(
        printf("%.2Lf,%.2Lf -- %.2Lf,%.2Lf is ", Points[i].fst, Points[i].snd, Points[(i+1)%n].fst, Points[(i+1)%n].snd);
      )
      if(is_stable(Points[i], Points[(i+1)%n], C, i, (i+1)%n)){
        rotations++;
        DBG(
          printf("STABLE\n");
        )
      }
      else{
        DBG(
          printf("UNSTABLE\n");
        )
      }
    }
    printf("Case #%d: %d\n", _t, rotations);

    // clear globals
    Points.clear();

  }

  return 0;
}
