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

typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef long long ll;

int find_augmenting_path(vector<vi>& Gf, vi& from, int s, int t){
  vector<bool> seen(sz(Gf), false);
  from.assign(sz(Gf),-1);
  queue<int> Q;
  Q.push(s);

  while(!Q.empty()){
    int where = Q.front(); Q.pop();
    seen[s] = true;
    rep(next, 0, sz(Gf[where])-1)
      if(!seen[next] && Gf[where][next] > 0){
        Q.push(next);
        seen[next] = true;
        from[next] = where;
      }
  }

  // find capacity
  int capacity = INT_MAX;
  int where = t;
  while(from[where] > -1){
    int prev = from[where];
    capacity = min(capacity, Gf[prev][where]);
    where = prev;
  }
  return capacity;
}

int  ford_fulkerson(vector<vii> G, int s, int t){
  vector<vi> Gf(sz(G),vector<int>(sz(G)));
  int max_flow = 0;
  vi from(sz(Gf));

  // initialize flow in G with 0,i.e. the residual graph Gf gets the capacities
  // of G.
  rep(i,0,sz(G)-1)
    rep(j,0,sz(G[i])-1)
      Gf[i][j] = G[i][j].snd;

  while(true){
    // find augmenting path and get capacity for it.
    int capacity = find_augmenting_path(Gf, from, s, t);
    // if no augmenting path found, exit loop.
    if(capacity == INT_MAX)
      break;
    // update Gf with new capacity.
    int where = t;
    while(from[where] > -1){
      int prev = from[where];
      Gf[prev][where] -= capacity;
      Gf[where][prev] += capacity;
      where = prev;
    }
    // update max_flow
    max_flow += capacity;
  }
  return max_flow;
}



inline int next_int(string s, int& pos){
  int nr = 0;
  while(s[pos] >= '0' && s[pos] <= '9'){
    nr = nr * 10 + int(s[pos]-'0');
    pos++;
  }
  return nr;
}


int main(){
  int tests; cin >> tests;
  rep(_t,1,tests){
    int n,m; cin >> n >> m;
    int nodes = 1 + n + m + 1;
    int src = 0;
    int dest = nodes-1;

    vector<vector<bool> > presents(n+1, vector<bool>(m+1,false));
    rep(i,1,n){
      string s; cin >> s;
      DBG(
        cout << "s: " << s << endl;
      )
      int pos = 0;
      bool range = false;
      int val;
      while(pos < s.length()){
        if(s[pos] >= '0' && s[pos] <= '9'){
          if(range){
            int vval = next_int(s,pos);
            rep(_i,val, vval)
              if(_i < m+1)
                presents[i][_i] = true;
              range = false;
          }
          else{
            val = next_int(s,pos);
            if(val < m+1)
              presents[i][val] = true;
          }
        }
        else if(s[pos] == '-'){
          range = true;
          pos++;
        }
        else{
          pos++;
        }
      }
    }
    DBG(
      cout << "presents:\n";
      rep(i,1,n){
        cout << i << ": ";
        rep(j,0,sz(presents[i])-1)
          if(presents[i][j])
            cout << j << " ";
        cout << "\n";
      }
    )

    vector<vii> G(nodes, vii(nodes));
    rep(f, 1, n){
      rep(p, 1, m){
        if(presents[f][p]){
          /*
          capacity[f][n+p] = 1;
          addEdge(f, n+p, 1);
          */
          G[f][n+p].snd = 1;
        }
      }
    }

    rep(i,1,n){
      G[src][i].snd = 1;
      /*
      capacity[src][i] = 1;
      addEdge(src, i, 1);
      */
    }
    rep(i,n+1,nodes-2){
      G[i][dest].snd = 1;
      /*
      capacity[i][dest] = 1;
      addEdge(i,dest,1);
      */
    }

    /*
    DBG(
      cout << "G:\n";
      rep(i,0,nodes-1){
        cout << i << ": ";
        rep(j,0,nodes-1)
          if(capacity[i][j] > 0)
            cout << j << "(" << capacity[i][j] << ") ";
        cout << "\n";
      }
    )*/
    DBG(
      cout << "G:\n";
      rep(i,0,nodes-1){
        cout << i << ": ";
        rep(j,0,nodes-1)
          if(G[i][j].snd > 0)
            cout << j << "(" << G[i][j].snd << ") ";
        cout << "\n";
      }
    )

    cout << "Case #" << _t << ": ";
    //if(maxFlow(src, dest) == n)
    if(ford_fulkerson(G, src, dest) == n)
      cout << "yes\n";
    else
      cout << "no\n";
  }

  return 0;
}
