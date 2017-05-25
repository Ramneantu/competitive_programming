#include<bits/stdc++.h>

#define rep(i,a,b) for(int i=int(a); i<=int(b); ++i)
#define mp(x,y) make_pair((x),(y))
#define pb(x) push_back((x))
#define all(c) c.begin(), c.end()
#define tr(container, it) for(auto it=(container).begin(); it != (container).end(); ++it)
#define sqr(x) ((x)*(x))
#define sz(a) int((a).size())
#define mout(M,n,m) rep(i,0,(n)-1){ rep(j,0,(m)-1) cout << (M)[i][j] << " ";  cout << "\n"; }
#define vout(V,a,b,msg) cout << msg << ": "; rep(i,a,b)  cout << V[i] << " "; cout << "\n";
using namespace std;

#define INF     INT_MAX

#define fst first
#define snd second

#define debug 0
#define DBG(code) if(debug){    \
                    do{         \
                    code        \
                    }while(0);  \
                  }

typedef pair<int, int> ii;


// globals
#define NMAX 500
int n;
map<int,int> Nodes2ObstacleId;          // map node to its obstacle id
vector<pair<ii,ii> > Segments;          // vector with all Segments as ii,ii
double G[NMAX][NMAX];                   // graph G
map<int,ii> Nodes2Points;               // map node ids to the cartesian coordinates
map<ii, int> Points2Nodes;              // map cartesian coordinates to points
vector<double> dist;                    // distances of nodes from start -- used in Dijkstra
vector<int> parent;                     // parent of a node on the shotest path -- used in Dijkstra


// BEGIN REFERENCE from http://www.geeksforgeeks.org/check-if-two-given-line-segments-intersect/
bool onSegment(ii p, ii q, ii r){
    if (q.fst <= max(p.fst, r.fst) && q.fst >= min(p.fst, r.fst) &&
        q.snd <= max(p.snd, r.snd) && q.snd >= min(p.snd, r.snd))
       return true;
    return false;
}
int orientation(ii p, ii q, ii r){
    int val = (q.snd - p.snd) * (r.fst - q.fst) -
              (q.fst - p.fst) * (r.snd - q.snd);
    if (val == 0) return 0;
    return (val > 0)? 1: 2;
}
bool doIntersect(ii p1, ii q1, ii p2, ii q2){
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);
    if (o1 != o2 && o3 != o4)
        return true;
    if (o1 == 0 && onSegment(p1, p2, q1)) return true;
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;
    if (o4 == 0 && onSegment(p2, q1, q2)) return true;
    return false;
}
// END REFERENCE
inline bool p_equal(ii p, ii q){ return p.fst == q.fst && p.snd == q.snd; }
inline double get_dist(ii P, ii Q){ return sqrt(sqr(P.fst - Q.fst) + sqr(P.snd - Q.snd)); }
bool doIntersect_soft(ii p1, ii q1, ii p2, ii q2){
  if(!doIntersect(p1,q1,p2,q2)) return false;
  if(p_equal(p1, p2)||p_equal(p1, q2)||p_equal(q1, p2)||p_equal(q1, q2)) return false;
  return true;
}

void new_node(int x, int y, int& node, int o){
  ii P = mp(x,y);
  Points2Nodes[P] = node;
  Nodes2Points[node] = P;
  Nodes2ObstacleId[node] = o;
  node++;
}
void new_polygon(int x,int y,int w, int h, int o,int& node){
  int _x[] = {0,w,w,0};
  int _y[] = {0,0,h,h};
  rep(i,0,3)
    new_node(x+_x[i],y+_y[i],node,o);
  rep(i,0,3){
    ii P1 = mp(x+_x[i],y+_y[i]);
    ii P2 = mp(x+_x[(i+1)%4],y+_y[(i+1)%4]);
    Segments.pb(mp(P1,P2));
    G[Points2Nodes[P1]][Points2Nodes[P2]] = G[Points2Nodes[P2]][Points2Nodes[P1]] = get_dist(P1,P2);
  }
}
void print_graph(){
  DBG(
    cout << "G:\n";
    rep(i,0,n-1){
      printf("%d(%d,%d, ob_id: %d): ", i, Nodes2Points[i].fst, Nodes2Points[i].snd, Nodes2ObstacleId[i]);
      rep(j,0,n-1)
        if(G[i][j] > 0)
          printf("%d(%d,%d)[%.3lf] ", j, Nodes2Points[j].fst, Nodes2Points[j].snd, G[i][j]);
      printf("\n");
    }
  )
}
void build_graph(){
  map<ii,int>::iterator it,jt;
  for(it=Points2Nodes.begin(); it!= Points2Nodes.end(); ++it){
    int v = it->snd;
    ii P = it->fst;
    for(jt=next(it,1); jt!= Points2Nodes.end(); ++jt){
      int u = jt->snd;
      ii Q = jt->fst;
      if(Nodes2ObstacleId[v] != Nodes2ObstacleId[u]){
        bool visible = true;
        rep(i,0,Segments.size()-1){
          if(doIntersect_soft(P, Q, Segments[i].fst, Segments[i].snd)){
            visible = false;
            break;
          }
        }
        if(visible){
          G[v][u] = G[u][v] = get_dist(P,Q);
        }
      }
    }
  }
  print_graph();
}
void read_data(){
  rep(i,0,NMAX-1)
    rep(j,0,NMAX-1)
      G[i][j] = 0;
  n = 1;
  int w,h,o;
  cin >> w >> h >> o;
  rep(_o,0,o-1){
    int x,y,_w,_h;
    cin >> x >> y >> _w >> _h;
    new_polygon(x,y,_w,_h,_o,n);
  }
  int x,y;
  cin >> x >> y;
  int _id = 0;
  new_node(x,y,_id,-1);
  cin >> x >> y;
  new_node(x,y,n,-2);
  print_graph();
}
void print_path(int node){
  if(parent[node] == node){
    printf("(%d,%d)", Nodes2Points[node].fst, Nodes2Points[node].snd);
    return;
  }
  else{
    print_path(parent[node]);
    printf(" (%d,%d)", Nodes2Points[node].fst, Nodes2Points[node].snd);
  }
}

void dijkstra(){
  dist.assign(n,INF/2);
  parent.resize(n, 0);
  rep(i,0,parent.size()-1)
    parent[i] = i;
  dist[0] = 0;
  priority_queue<pair<double, int> , vector<pair<double, int> >, greater<pair<double, int> > > pq;
  pq.push(mp(0.0,0));
  int steps = 0;
  while(!pq.empty()){
    if(steps > n)
      break;
    pair<double, int> top = pq.top(); pq.pop();
    double d = top.fst;
    int v = top.snd;
    if(d == dist[v]){
      steps++;
      rep(u,0,n-1){
        if(G[v][u] > 0){
          if(dist[v] + G[v][u] < dist[u]){
            dist[u] = dist[v] + G[v][u];
            parent[u] = v;
            pq.push(mp(dist[u], u));
          }
        }
      }
    }
  }
  DBG(vout(dist,0,n-1,"dist"));
}

int main(){

  int t; cin >> t;
  rep(_t,1,t){
    read_data();

    build_graph();
    dijkstra();

    cout << "Case #" << _t << ": ";
    print_path(n-1);
    cout << "\n";

    Nodes2ObstacleId.clear();
    Nodes2Points.clear();
    Points2Nodes.clear();
    parent.clear();
    dist.clear();
    Segments.clear();
  }

  return 0;
}
