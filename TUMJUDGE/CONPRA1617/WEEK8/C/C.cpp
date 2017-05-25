#include<bits/stdc++.h>

#define rep(i,a,b) for(int i=int(a); i<=int(b); ++i)
#define rev(i,b,a) for(int i=int(b); i>=int(a); --i)
#define rec(i,a,b,c) for(int i=int(a); i<=int(b); i+=int(c))
#define recv(i,a,b,c) for(int i=int(a); i>=int(b); i-=int(c))
#define mp(x,y) make_pair((x),(y))
#define pb(x) push_back(x)
#define all(c) c.begin(), c.end_node()
#define tr(container, it) for(auto it=(container).begin(); it != (container).end_node(); ++it)
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


typedef long long ll;
typedef double T;
typedef pair<T,T> TT;

// global
#define NMAX 101
int G[NMAX][NMAX];
vector<vector<TT> > S;
TT start_node, end_node;

// BEGIN REFERENCE from http://www.geeksforgeeks.org/check-if-two-given-line-segments-intersect/

// Given three colinear points p, q, r, the function checks if
// point q lies on line segment 'pr'
bool onSegment(TT p, TT q, TT r)
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
int orientation(TT p, TT q, TT r)
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
bool doIntersect(TT p1, TT q1, TT p2, TT q2)
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
// end_node REFERENCE

inline ostream& operator<<(ostream& os, TT P){
  os << P.fst << "," << P.snd;
  return os;
}


int bfs(map<int,bool> lines2start, map<int,bool> lines2end, int n){
  queue<pair<int,int> > Q;
  for(map<int,bool>::iterator it=lines2start.begin(); it!=lines2start.end(); ++it)
    if(it->snd == true)
      Q.push(make_pair(it->fst, 0));
  vector<bool> seen(n,false);

  while(!Q.empty()){
    pair<int,int> e = Q.front(); Q.pop();
    int v = e.fst;
    int d = e.snd;
    if(lines2end[v] == true)
      return d;
    seen[v] = true;
    rep(i,0,n-1){
      if(G[v][i] == 1 && !seen[i]){
        Q.push(make_pair(i, d+1));
      }
    }
  }
  return -1;
}

ostream& operator<<(ostream& os, pair<TT,TT> S1){
  os << S1.fst << " -- " << S1.snd;
  return os;
}

int main(){

  int m,n;
  double x,y;

  int t;
  cin >> t;
  rep(_t,1,t){
    cin >> n;
    S.resize(n,vector<TT>());
    cin >> start_node.fst >> start_node.snd >> end_node.fst >> end_node.snd;
    rep(i,0,n-1){
      cin >> m;
      rep(j,0,m-1){
        cin >> x >> y;
        S[i].push_back(TT(x,y));
      }
    }

    // maps lines on which start and end node are.
    map<int,bool> lines2start;
    map<int,bool> lines2end;
    // build graph
    rep(i,0,sz(S)-1){
      rep(j,0,sz(S[i])-2){
        pair<TT,TT> S1 = make_pair(S[i][j], S[i][j+1]);
        if(orientation(S1.fst, start_node, S1.snd) == 0 && onSegment(S1.fst, start_node, S1.snd)){
          lines2start[i] = true;
        }
        if(orientation(S1.fst, end_node, S1.snd) == 0 && onSegment(S1.fst, end_node, S1.snd)){
          lines2end[i] = true;
        }
        rep(k,i+1, sz(S)-1)
          rep(l,0,sz(S[k])-2){
            pair<TT,TT> S2 = make_pair(S[k][l], S[k][l+1]);
            if(doIntersect(S1.fst, S1.snd, S2.fst, S2.snd)){
              G[i][k] = G[k][i] = 1;
            }
          }
      }
    }

    cout << "Case #" << _t << ": ";
    int d = bfs(lines2start, lines2end, n);
    if(d == -1)
      cout << "impossible";
    else
      cout << d;
    cout << "\n";

    // clear globals
    rep(i,0,NMAX-1)
      rep(j,0,NMAX-1)
        G[i][j] = 0;
    S.clear();
    lines2start.clear();
    lines2end.clear();
  }

  return 0;
}
