#include<bits/stdc++.h>

#define rep(i,a,b) for(int i=int(a); i<=int(b); ++i)

using namespace std;
typedef pair<int,int> ii;

int main(){

int t;
cin >> t;
rep(_t,1,t){
  int n;
  cin >> n;
  vector<vector<ii> > G(n);
  rep(i,0,n-1){
    rep(j,0,n-1){
      int c;
      cin >> c;
      if(c>0) G[j].push_back(ii(i,c));
    }
  }
  vector<int> m(n,0);
  vector<int> v(n,0);
  priority_queue<ii> PQ;
  int mc = 0;
  PQ.push(ii(0,0));
  while (!PQ.empty()) {
    ii z = PQ.top(); PQ.pop();
    int u = z.second;
    int c = z.first;
    if (!v[u]){
      m[u] = max(m[u],c);
      v[u] = 1;
      rep(j,0,G[u].size()-1){
        int e = G[u][j].first;
        int c = G[u][j].second;
        if (!v[e]){
          PQ.push(ii(c, e));
          m[e] = max(m[e],c);
        }
        else m[e] = max(m[e],c);
      }
    }
    else
      m[u] = max(m[u],c);
  }
  rep(i,1,n-1)
    mc += m[i];
  printf("Case #%d: %d\n", _t, mc);
  }
  return 0;
}
