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

typedef pair<double, double> ii;

// globals
#define XMIN -1000
#define XMAX 1000
#define YMIN -1000
#define YMAX 1000
vector<pair<ii,ii> > Polygon;
map<ii,bool> Points;
int n;
int xp, yp;

// WILL CODE IT MYSELF, just wanted to check if it works ;).
// BEGIN REFERENCE from http://www.geeksforgeeks.org/check-if-two-given-line-segments-intersect/

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

    return (val > 0)? 1: 2; // clock or counterclock wise
}

// The main function that returns true if line segment 'p1q1'
// and 'p2q2' intersect.
bool doIntersect(ii p1, ii q1, ii p2, ii q2)
{
    // Find the four orientations needed for general and
    // special cases
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    // General case
    if (o1 != o2 && o3 != o4)
        return true;

    // Special Cases
    // p1, q1 and p2 are colinear and p2 lies on segment p1q1
    if (o1 == 0 && onSegment(p1, p2, q1)) return true;

    // p1, q1 and p2 are colinear and q2 lies on segment p1q1
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;

    // p2, q2 and p1 are colinear and p1 lies on segment p2q2
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;

     // p2, q2 and q1 are colinear and q1 lies on segment p2q2
    if (o4 == 0 && onSegment(p2, q1, q2)) return true;

    return false; // Doesn't fall in any of the above cases
}
// END REFERENCE

bool is_point_in_polygon(ii P){
    int t1 = rand()%2;
    int t2 = rand()%2;
    int x = ((double) rand() / (RAND_MAX)) * 10000*((-1)*t1 + (1-t1));
    int y = ((double) rand() / (RAND_MAX)) * 10000*((-1)*t2 + (1-t2));
    ii Pm = ii(x,y);
    int crossings = 0;
    rep(i,0,Polygon.size()-1){
        if(doIntersect(Polygon[i].fst, Polygon[i].snd, P, Pm)){
            crossings++;
        }
    }
    if(crossings % 2)
        return true;
    else
        return false;
}

int main(){

    srand(time(NULL));
    int T;
    scanf("%d", &T);
    rep(t,1,T){
        cin >> xp >> yp >> n;
        rep(i,0,n-1){
            int x1,y1,x2,y2;
            cin >> x1 >> y1 >> x2 >> y2;
            Polygon.push_back(make_pair(ii(x1,y1), ii(x2,y2)));
            Points[ii(x1,y1)] = true;
            Points[ii(x2,y2)] = true;
        }

        printf("Case #%d: ", t);
        if(is_point_in_polygon(ii(xp,yp)))
            cout << "jackpot";
        else
            cout << "too bad";
        cout << "\n";

        // clear globals
        Polygon.clear();
        Points.clear();
    }

    return 0;
}
