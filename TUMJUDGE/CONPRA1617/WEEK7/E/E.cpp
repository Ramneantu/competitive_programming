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
#define mod(a,n) ((a) < 0 ? ((n)+(a)) : ((a)%(n)))
#define mout(M,n,m) rep(i,0,(n)-1){ rep(j,0,(m)-1) cout << (M)[i][j] << " ";  cout << "\n"; }
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
#define DBG(code) if(debug == 1) \
do{ \
code \
}while(0);

typedef double T;
typedef pair<T,T> TT;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef long long ll;

// globals
#define XMIN 0
#define XMAX 300
#define YMIN 0
#define YMAX 300
int n;
vector<TT> Ps;

struct Point
{
	int x, y;
};

Point points[120000];
int points_size;

// REFERENCE from http://www.geeksforgeeks.org/convex-hull-set-2-graham-scan/.

// A globle point needed for sorting points with reference
// to the first point Used in compare function of qsort()
Point p0;

// A utility function to find next to top in a stack
Point nextToTop(stack<Point> &S)
{
	Point p = S.top();
	S.pop();
	Point res = S.top();
	S.push(p);
	return res;
}

// A utility function to swap two points
void swap(Point &p1, Point &p2)
{
	Point temp = p1;
	p1 = p2;
	p2 = temp;
}

// A utility function to return square of distance
// between p1 and p2
int distSq(Point p1, Point p2)
{
	return (p1.x - p2.x)*(p1.x - p2.x) +
		(p1.y - p2.y)*(p1.y - p2.y);
}

// To find orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are colinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int orientation(Point p, Point q, Point r)
{
	int val = (q.y - p.y) * (r.x - q.x) -
			(q.x - p.x) * (r.y - q.y);

	if (val == 0) return 0; // colinear
	return (val > 0)? 1: 2; // clock or counterclock wise
}

// A function used by library function qsort() to sort an array of
// points with respect to the first point
int compare(const void *vp1, const void *vp2)
{
Point *p1 = (Point *)vp1;
Point *p2 = (Point *)vp2;

// Find orientation
int o = orientation(p0, *p1, *p2);
if (o == 0)
	return (distSq(p0, *p2) >= distSq(p0, *p1))? -1 : 1;

return (o == 2)? -1: 1;
}

// Prints convex hull of a set of n points.
stack<Point> S;
void convexHull()
{
// Find the bottommost point
int ymin = points[0].y, min = 0;
for (int i = 1; i < points_size; i++)
{
	int y = points[i].y;

	// Pick the bottom-most or chose the left
	// most point in case of tie
	if ((y < ymin) || (ymin == y &&
		points[i].x < points[min].x))
		ymin = points[i].y, min = i;
}

// Place the bottom-most point at first position
swap(points[0], points[min]);

// Sort n-1 points with respect to the first point.
// A point p1 comes before p2 in sorted ouput if p2
// has larger polar angle (in counterclockwise
// direction) than p1
p0 = points[0];
qsort(&points[1], points_size-1, sizeof(Point), compare);

// If two or more points make same angle with p0,
// Remove all but the one that is farthest from p0
// Remember that, in above sorting, our criteria was
// to keep the farthest point at the end when more than
// one points have same angle.
int m = 1; // Initialize size of modified array
for (int i=1; i<points_size; i++)
{
	// Keep removing i while angle of i and i+1 is same
	// with respect to p0
	while (i < points_size-1 && orientation(p0, points[i],
									points[i+1]) == 0)
		i++;


	points[m] = points[i];
	m++; // Update size of modified array
}

// If modified array of points has less than 3 points,
// convex hull is not possible
if (m < 3) return;

// Create an empty stack and push first three points
// to it.
S.push(points[0]);
S.push(points[1]);
S.push(points[2]);

// Process remaining n-3 points
for (int i = 3; i < m; i++)
{
	// Keep removing top while the angle formed by
	// points next-to-top, top, and points[i] makes
	// a non-left turn
	while (orientation(nextToTop(S), S.top(), points[i]) != 2)
		S.pop();
	S.push(points[i]);
}

// Now stack has the output points, print contents of stack
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

inline T CCW(TT P0, TT P1, TT P2){
  return (P1.fst - P0.fst) * (P2.snd - P0.snd) - (P2.fst - P0.fst) * (P1.snd - P0.snd);
}

bool is_point_in_polygon(TT P){
			bool neg = false;
			bool pos = false;
			//printf("is point: %.3lf,%.3lf in polygon ?\n", P.fst, P.snd);
			rep(i,0,Ps.size()-1){
	    	T ccw = CCW(Ps[i],Ps[(i+1)%Ps.size()],P);
				//printf("CCW of %.3lf,%.3lf -- %.3lf,%.3lf -- %.3lf,%.3lf: %.3lf\n", Ps[i].fst,Ps[i].snd,Ps[(i+1)%Ps.size()].fst,Ps[(i+1)%Ps.size()].snd,P.fst, P.snd, ccw);
				if(ccw < 0)
					neg = true;
				else if(ccw > 0)
					pos = true;
			}
			if(neg && pos)
				return false;
			//printf("YES point: %.3lf,%.3lf is in polygon\n", P.fst, P.snd);
			return true;
}


void get_garden_integer_coordinates(int xmin, int xmax, int ymin, int ymax){
	points_size = 0;
	Point _P;
	rep(_x,xmin, xmax){
		rep(_y,ymin,ymax){
			if(is_point_in_polygon(TT(_x,_y))){
				_P.x = _x;
				_P.y = _y;
				points[points_size++] = _P;
			}
		}
	}
}


int main(){

  int t;
  scanf("%d", &t);
  rep(_t,1,t){
		int xmin = 301;
		int xmax = -1;
		int ymin = 301;
		int ymax = -1;
    cin >> n;
    Ps.resize(n);
    rep(i,0,n-1){
      T x,y;
      cin >> x >> y;
      Ps[i].fst = x;
      Ps[i].snd = y;
			xmin = min(xmin, int(x));
			xmax = max(xmax, int(x));
			ymin = min(ymin, int(y));
			ymax = max(ymax, int(y));
    }
		get_garden_integer_coordinates(xmin, xmax, ymin, ymax);
		//get_garden_integer_coordinates(XMIN,XMAX,YMIN,YMAX);

		printf("Case #%d:\n", _t);
		if(points_size == 0){
			cout << 0 << endl;
		}
		else if(points_size == 1){
			cout << 1 << endl << points[0].x << " " << points[0].y << endl;
		}
		else{
  		convexHull();
			if(S.size() == 0){
				Point Pmin, Pmax;
				Pmin.x = 301;
				Pmin.y = 301;
				Pmax.x = -1;
				Pmax.y = -1;
				rep(i,0,points_size-1){
					if(points[i].x < Pmin.x){
						Pmin.x = points[i].x;
						Pmin.y = points[i].y;
					}
					else if(points[i].x == Pmin.x){
						if(points[i].y < Pmin.y){
							Pmin.x = points[i].x;
							Pmin.y = points[i].y;
						}
					}
					if(points[i].x > Pmax.x){
						Pmax.x = points[i].x;
						Pmax.y = points[i].y;
					}
					else if(points[i].x == Pmin.x){
						if(points[i].y > Pmin.y){
							Pmax.x = points[i].x;
							Pmax.y = points[i].y;
						}
					}
				}
				cout << 2 << endl;
				cout << Pmin.x << " " << Pmin.y << endl;
				cout << Pmax.x << " " << Pmax.y << endl;
			}
			else{
				cout << S.size() << endl;
			  while (!S.empty())
			  {
			    Point p = S.top(); S.pop();
			    cout << p.x << " " << p.y << endl;
			  }
			}
		}
    // clear globals
    Ps.clear();
    points_size = 0;
	}

  return 0;
}
