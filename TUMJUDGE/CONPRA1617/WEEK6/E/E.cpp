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


typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef long long ll;


int main(){

  int T;
  scanf("%d", &T);
  rep(t,1,T){
    int n;
    cin >> n;
    vector<vector<int> > G(n,vector<int>(n,0));
    rep(i,0,n-1){
      rep(j,0,n-1){
        cin >> G[i][j];
      }
    }

    // generate all permutations of nodes and take the one with minimum cost
    int min_cost = INF;
    vector<int> tour(n,0);
    rep(i,0,n-1)
      tour[i] = i;
    vector<int> sol(n,0);
    do{
      int current_cost = 0;
      rep(i,0,n-1)
        current_cost += G[tour[i]][tour[(i+1)%n]];
      if(current_cost < min_cost){
        min_cost = current_cost;
        rep(i,0,n-1)
          sol[i] = tour[i];
      }
    }while(next_permutation(tour.begin(), tour.end()));

    printf("Case #%d: ", t);
    rep(i,0,n-1)
      cout << sol[i]+1 << " ";
    cout << "\n";
  }

  return 0;
}
