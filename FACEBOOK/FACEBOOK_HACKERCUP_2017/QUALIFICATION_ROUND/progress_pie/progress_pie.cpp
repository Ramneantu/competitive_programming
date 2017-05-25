#include<bits/stdc++.h>

#define rep(i,a,b) for(int i=int(a); i<=int(b); ++i)
#define rev(i,b,a) for(int i=int(b); i>=int(a); --i)
#define rec(i,a,b,c) for(int i=int(a); i<=int(b); i+=int(c))
#define recv(i,a,b,c) for(int i=int(a); i>=int(b); i-=int(c))
#define mp(x,C) make_pair((x),(C))
#define pb(x) push_back(x)
#define all(c) c.begin(), c.end()
#define tr(container, it) for(auto it=(container).begin(); it != (container).end(); ++it)
#define sqr(x) ((x)*(x))
#define sz(a) int((a).size())
#define mout(M,n,m) rep(i,0,(n)-1){ rep(j,0,(m)-1) cout << (M)[i][j] << " ";  cout << "\n"; }
#define vout(V,a,b,msg) cout << "msg: "; rep(i,a,b)  cout << V[i] << " "; cout << "\n";
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

#define DBG(code) if(0){    \
                    do{         \
                    code        \
                    }while(0);  \
                  }

typedef pair<double, double> ii;

// Given three colinear points p, q, r, the function checks if
// point q lies on line segment 'pr'
bool onSegment(ii p, ii q, ii r)
{
    if (q.fst <= max(p.fst, r.fst) && q.fst >= min(p.fst, r.fst) &&
        q.snd <= max(p.snd, r.snd) && q.snd >= min(p.snd, r.snd))
       return true;

    return false;
}

// To find orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are colinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int orientation(ii p, ii q, ii r)
{
    // See http://www.geeksforgeeks.org/orientation-3-ordered-points/
    // for details of below formula.
    int val = (q.snd - p.snd) * (r.fst - q.fst) -
              (q.fst - p.fst) * (r.snd - q.snd);

    if (val == 0) return 0;  // colinear

	DBG(cout << "val: " << val << endl;)
  if(val > 0)
    return 1;
  return 2;
}

// checks if point Q is inside circle with center P and radius r.
inline bool inside_circle(ii P, int r, ii Q){
	return (double(sqr(P.fst - Q.fst) + sqr(P.snd - Q.snd) - sqr(r)) <= 0);
}

// Checks if point P is inside the box.
//inline in_bounds(ii P){ return (P.fst >= 0 && P.fst <= 100 && P.snd >= 0 && P.snd <= 100);}


// returns true if points is inside circle with percentage p. False otherwise.
bool is_inside(double deg, ii P){

  // if no circle, then all points are white.
	if(deg == 0)
		return false;

  // if circle then point on circle are black.
  ii C = ii(50.0,50.0);
  double r = 50;
	if(deg == 100)
		return inside_circle(C, r, P);

	if(inside_circle(C,r,P)){
  	ii I = make_pair(C.fst + sin((deg*M_PI)*1.0/180)*50, C.snd + cos((deg*M_PI)*1.0/180)*50);
  	DBG(cout << "I: " << I.fst << "," << I.snd << endl;)

  	// Consider where the points lies in the quadrants
  	// Case 1: upper-right
  	if(P.fst >= 50 && P.snd >= 50){
  		if(deg >= 90)
  			return true;
  		if(orientation(C, P, I) != 2)
  			return true;
  	}
  	else if(P.fst >= 50 && P.snd < 50){ // lower-right
      if(deg <= 90)
        return false;
  		else if(deg >= 180)
  			return true;
  		if(orientation(C, P, I) != 2)
  			return true;
  	}
  	else if(P.fst < 50 && P.snd < 50){ // lower-left
      if(deg <= 180)
        return false;
      else if(deg >= 270)
  			return true;
  		if(orientation(C, P, I) != 2)
  			return true;
  	}
  	else if(P.fst < 50 && P.snd >= 50){ // upper-left
      if(deg < 270)
        return false;
      int o = orientation(C, P, I);
  		if(o != 2)
  			return true;
  	}
  }
  return false;
}

int main(){

	int t; cin >> t;
	rep(_t,1,t){
		double p, x, C; cin >> p >> x >> C;
		p = p*36.0/10;
		DBG(cout << "angle: " << p << endl;)
		printf("Case #%d: ", _t);
		if(is_inside(p,ii(x,C)))
			cout << "black\n";
		else
			cout << "white\n";
	}

	return 0;
}
