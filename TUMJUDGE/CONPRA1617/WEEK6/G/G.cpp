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
#define UNASSIGNED -1


typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef long long ll;

vector<vector<int> > G;
vector<int> colors;
int nr_colors,n,m;


inline bool is_valid_move(int node, int color){
  rep(i,0,G[node].size()-1)
    if(colors[G[node][i]] == color)
      return false;
  return true;
}

bool search(int node){
  if(node == G.size())
    return true;
  else{
    rep(color,1,nr_colors){
      if(is_valid_move(node,color)){
        colors[node] = color;
        if(search(node+1))
          return true;
        colors[node] = UNASSIGNED;
      }
    }
    return false;
  }
  return false;
}



int main(){

  int T;
  scanf("%d", &T);
  rep(t,1,T){
    cin >> n >> m >> nr_colors;
    // init
    G.resize(n,vector<int>());
    colors.resize(n,UNASSIGNED);
    rep(i,0,m-1){
      int from, to;
      cin >> from >> to;
      from--; to--;
      G[from].push_back(to);
      G[to].push_back(from);
    }

    printf("Case #%d: ", t);
    if(search(0))
      rep(i,0,colors.size()-1)
        cout << colors[i] << " ";
    else
      cout << "impossible";
    cout << "\n";

    // clear globals
    G.clear();
    colors.clear();
  }

  return 0;
}
