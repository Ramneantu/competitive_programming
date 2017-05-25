#include<bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(int i=int(a); i<=int(b); ++i)
#define sqr(x) ((x)*(x))

// Forward declarations
struct PointHom;
typedef struct PointHom PointHom_T;
struct LineHom;
typedef struct LineHom LineHom_T;


// HOMOGENEOUS POINT
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

//  HOMOGENEOUS LINE
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

bool is_valid(PointHom_T X1, PointHom_T X2, PointHom_T X3, PointHom_T X, PointHom_T M){
  T o1 = CCW(to_2d_point(X1), to_2d_point(X2), to_2d_point(X));
  TT _mx3 = to_2d_point(M) - to_2d_point(X3);
  _mx3.first *= 2.0;
  _mx3.second *= 2.0;
  TT _x3 = to_2d_point(X3);
  _mx3.first += _x3.first;
  _mx3.second += _x3.second;
  T o2 = CCW(to_2d_point(X1), to_2d_point(X2), _mx3);
  if(o1 * o2 < 0)
    return false;
  return true;
}


int main(){

  int t;
  cin >> t;
  rep(_t,1,t){
    vector<PointHom_T> X1(3), X2(3);
    rep(i,0,2){
      cin >> X1[i].x >> X1[i].y;
      normalize(X1[i]);
    }
    rep(i,0,2){
      cin >> X2[i].x >> X2[i].y;
      normalize(X2[i]);
    }


    PointHom_T M1 = project(X1[2], LineHom_T(X1[0], X1[1]));
    normalize(M1);
    PointHom_T M2 = project(X2[2], LineHom_T(X2[0], X2[1]));
    normalize(M2);
    PointHom_T X = cross(LineHom_T(X1[2], M1), LineHom_T(X2[2], M2));

    bool intersection = true;
    if(is_inf(X))
      intersection = false;
    else{
      normalize(X);
      if(!is_valid(X1[0], X1[1], X1[2], X, M1)||!is_valid(X2[0], X2[1], X2[2], X, M2))
        intersection = false;
    }

    printf("Case #%d: ", _t);
    if(intersection)  printf("%.4f %.4f\n", X.x, X.y);
    else
      cout << "strange\n";
  }

  return 0;
}
