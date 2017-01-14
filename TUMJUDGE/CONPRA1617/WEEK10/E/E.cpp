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
#define fst first
#define snd second
#define debug 1
#define DBG(code) if(debug){    \
                    do{         \
                    code        \
                    }while(0);  \
                  }
using namespace std;

typedef vector<int> vi;
typedef long long ll;
typedef pair<long, long> ii;
typedef vector<ii> vii;


vector<vector<ii> > G;
vector<long> prev;
vector<vector<long> > H;				// (steps, stairs)
int s;

long bfs(int node){
  long min_steps = LONG_MAX;
	queue<pair<int, ii> > Q;  // (id, steps, stairs)
	Q.push(make_pair(node, make_pair(0,0)));
  H[node][0] = 0;
  H[node][1] = 0;
	while(!Q.empty()){
		pair<int,ii> el = Q.front(); Q.pop();
		int v = el.fst;
		long steps = el.snd.fst;
		long stairs = el.snd.snd;

		for(int i=0; i<G[v].size(); ++i){
      int u = G[v][i].fst;
			if(H[u][0] >= 0){
				if(stairs + G[v][i].snd - H[u][1] != 0)
					min_steps = min(min_steps, steps+1+H[u][0]);
			}else{
				Q.push(make_pair(u, make_pair(steps+1,stairs+G[v][i].snd)));
        H[u][0] = steps+1;
        H[u][1] = stairs+G[v][i].snd;
			}
		}
	}
  return min_steps;
}


int main(){

  int t;
  cin >> t;
  rep(_t,1,t){
    int n,m; cin >> n >> m >> s;
    s--;
    G.resize(n, vector<ii>());
    vector<vector<ii> > E(n, vector<ii>(n));
    H.resize(n,vector<long>(2,-1));
    rep(i,0,m-1){
      int from, to, c; cin >> from >> to >> c;
      from--, to--;
      G[from].pb(ii(to, c));
      G[to].pb(ii(from,-c));
    }
    printf("Case #%d: ", _t);
    long min_steps = bfs(s);
    if(min_steps >= LONG_MAX)
      cout << "possible\n";
    else
      cout << min_steps << "\n";

      G.clear();
      H.clear();
  }
  return 0;
}
