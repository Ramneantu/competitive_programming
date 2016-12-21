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

// Forward declarations
struct PointHom;
typedef struct PointHom PointHom_T;
struct LineHom;
typedef struct LineHom LineHom_T;

/**
  HOMOGENEOUS POINT
**/
typedef double T;
typedef pair<double, double> TT;
struct PointHom {
  T x;
  T y;
  T z;
  PointHom() : x(0.0), y(0.0), z(1.0) {}
  PointHom(T x, T y, T z) : x(x), y(y), z(z) {}
  PointHom(LineHom_T l);
};
PointHom_T cross(PointHom_T P, PointHom_T Q);

/**
  HOMOGENEOUS LINE
**/
struct LineHom {
  T a;
  T b;
  T c;
  LineHom() : a(0), b(0), c(0) {}
  LineHom(T a, T b, T c) : a(a), b(b), c(c) {}
  LineHom(PointHom_T P, PointHom_T Q){
    PointHom_T res = cross(P,Q);
    a = res.x;
    b = res.y;
    c = res.z;
  }
  LineHom(PointHom_T P){
    a = P.x;
    b = P.y;
    c = P.z;
  }
};


PointHom_T::PointHom(LineHom_T l){
  x = l.a;
  y = l.b;
  z = l.c;
}


ostream& operator<<(ostream& os, const PointHom_T& p){
  os << p.x << " " << p.y << " " << p.z;
  return os;
}
ostream& operator<<(ostream& os, const LineHom_T& l){
  os << l.a << " " << l.b << " " << l.c;
  return os;
}
PointHom_T cross(PointHom_T P, PointHom_T Q){
    PointHom_T res;
    res.x = P.y*Q.z - P.z*Q.y;
    res.y = P.z*Q.x - P.x*Q.z;
    res.z = P.x*Q.y - P.y*Q.x;
    return res;
}
inline bool is_inf(PointHom_T P){ return abs(P.z) <= 1e-13; }
bool normalize(PointHom_T& P){
  if(is_inf(P))
    return false;
  P.x = P.x*1.0 / P.z;
  P.y = P.y*1.0 / P.z;
  P.z = 1.0;
  return true;
}
LineHom_T cross(LineHom_T P, LineHom_T Q){
    LineHom_T res;
    res.a = P.b*Q.c - P.c*Q.b;
    res.b = P.c*Q.a - P.a*Q.c;
    res.c = P.a*Q.b - P.b*Q.a;
    return res;
}
bool is_point_on_line(PointHom_T P, LineHom_T l){
  return P.x * l.a + P.y * l.b + P.z * l.c == 0.0;
}
inline bool is_inf(LineHom_T l){ return l.a == 0.0 && l.b == 0.0 && l.c == 1.0; }
bool normalize(LineHom_T& l){
  if(is_inf(l))
    return false;
  l.a = l.a*1.0 / sqrt(sqr(l.a) + sqr(l.b));
  l.b = l.b*1.0 / sqrt(sqr(l.a) + sqr(l.b));
  l.c = l.c*1.0 / sqrt(sqr(l.a) + sqr(l.b));
  return true;
}

PointHom_T project(PointHom_T P, LineHom_T l){
  // compute direction
	LineHom_T dir = cross(l, LineHom_T(0,0,1));
  LineHom_T m = cross(LineHom_T(P), LineHom_T(dir.b,-dir.a,0));
  return PointHom(cross(m, l));
}

T CCW(TT P0, TT P1, TT P2){
  return (P1.first - P0.first) * (P2.second - P0.second) - (P2.first - P0.first) * (P1.second - P0.second);
}

TT to_2d_point(PointHom_T P){
  TT p2d;
  normalize(P);
  p2d.first = P.x;
  p2d.second = P.y;
  return p2d;
}

TT operator-(TT p, TT q){
    return TT(p.first-q.first,p.second-q.second);
}

LineHom_T get_altitude(PointHom_T A, PointHom_T B, PointHom_T C){
  PointHom_T projA = project(A, LineHom_T(B,C));
  normalize(projA);
  LineHom_T altA(projA, A);
  return altA;
}

PointHom_T get_middle(PointHom_T A, PointHom_T B){
  PointHom mAB;
  mAB.x = (A.x + B.x)*0.5;
  mAB.y = (A.y + B.y)*0.5;
  mAB.z = 1.0;
  return mAB;
}

LineHom_T get_median(PointHom_T A, PointHom_T B, PointHom_T C){
  PointHom mBC = get_middle(B,C);
  LineHom_T medA(A,mBC);
  return medA;
}

int main(){

  int t;
  cin >> t;
  rep(_t,1,t){
    double x, y;
    cin >> x >> y;
    PointHom_T A(x,y,1.0);

    cin >> x >> y;
    PointHom_T B(x,y,1.0);

    cin >> x >> y;
    PointHom_T C(x,y,1.0);


    // compute altitude intersection
    LineHom_T altA = get_altitude(A,B,C);
    LineHom_T altB = get_altitude(B,A,C);
    LineHom_T altC = get_altitude(C,A,B);

    PointHom_T altI(cross(altA, altB));
    normalize(altI);


    // compute median intersection
    LineHom_T medA = get_median(A, B, C);
    LineHom_T medB = get_median(B, A, C);

    PointHom_T medI(cross(medA, medB));
    normalize(medI);



    // compute bisector intersection
    PointHom mAB = get_middle(A, B);
    PointHom mBC = get_middle(B, C);
    LineHom_T lBC(B,C);
    LineHom_T bisA(-lBC.b,lBC.a,lBC.b*mBC.x - lBC.a*mBC.y);

    LineHom_T lAB(A,B);
    LineHom_T bisC(-lAB.b,lAB.a,lAB.b*mAB.x - lAB.a*mAB.y);

    PointHom_T bisI(cross(bisA, bisC));
    normalize(bisI);

    cout << "Case #" << _t << ":\n";
    printf("%.10lf %.10lf\n", medI.x, medI.y);
    printf("%.10lf %.10lf\n", altI.x, altI.y);
    printf("%.10lf %.10lf\n", bisI.x, bisI.y);
  }

  return 0;
}
