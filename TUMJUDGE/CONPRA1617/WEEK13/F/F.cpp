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

// REFERENCE OF GRAHAM ALGORITHM from http://www.geeksforgeeks.org/convex-hull-set-2-graham-scan/.
// Don't worry, WILL CODE IT MYSELF!

struct Point
{
	double x, y;
};

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
void convexHull(Point points[], int n)
{
// Find the bottommost point
int ymin = points[0].y, min = 0;
for (int i = 1; i < n; i++)
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
qsort(&points[1], n-1, sizeof(Point), compare);

// If two or more points make same angle with p0,
// Remove all but the one that is farthest from p0
// Remember that, in above sorting, our criteria was
// to keep the farthest point at the end when more than
// one points have same angle.
int m = 1; // Initialize size of modified array
for (int i=1; i<n; i++)
{
	// Keep removing i while angle of i and i+1 is same
	// with respect to p0
	while (i < n-1 && orientation(p0, points[i],
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

Point points[1001];


int main(){

  int t;
  cin >> t;
  rep(_t,1,t){
    int n; cin >> n;
    rep(i,0,n-1){
      cin >> points[i].x >> points[i].y;
    }
    convexHull(points, n);

    double A = 0;
    vector<pair<double,double> > Ps;
    while(!S.empty()){
      Point p = S.top(); S.pop();
      //cout << p.x << ", " << p.y << endl;
      Ps.push_back(make_pair(p.x, p.y));
    }

    for(int i=0; i<Ps.size(); ++i)
      A += (Ps[i].first * Ps[(i+1)%Ps.size()].second - Ps[i].second * Ps[(i+1)%Ps.size()].first);
    A *= -1.0;
    printf("Case #%d: %.6lf\n", _t, A);

  }

  return 0;
}
