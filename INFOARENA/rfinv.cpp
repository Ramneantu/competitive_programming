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
#define mod(a,n) ((a) < 0 ? ((n)+(a)) : ((a)%(n)))
using namespace std;

typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef unsigned long long ll;

const ll inf = ll(1000001);

int main(){

  ifstream fin("rfinv.in");
  ofstream fout("rfinv.out");

  int t;
  fin >> t;
  while(t--){
      int n, m;
      fin >> n >> m;
      vector<vector<ll> > M(n, vector<ll>(n,0));
      vector<vector<ll> > A(n, vector<ll>(n,0));
      vector<vector<ll> > P(n, vector<ll>(n,0));
      rep(i,0,m-1){
        int a,b;
        fin >> a >> b;
        a--, b--;
        P[a][b] = 1;
        P[b][a] = 1;
      }
      int ok = 1;
      rep(i,0,n-1)
        rep(j,0,n-1)
          fin >> M[i][j];

      rep(i,0,n-1){
        rep(j,0,n-1){
          if(P[i][j] != 0)
            A[i][j] = M[i][j];
          else if(P[i][j] == 0){
            if(i == j)
              A[i][j] = 0;
            else
              A[i][j] = inf;
            }
        }
      }

      // roy-floyd on A.
      rep(k,0,n-1)
        rep(i,0,n-1)
          rep(j,0,n-1)
              A[i][j] = min(A[i][j], A[i][k] + A[k][j]);

      rep(i,0,n-1){
        rep(j,0,n-1){
          if(A[i][j] >= inf)
            A[i][j] = 0;
          if(A[i][j] != M[i][j])
            ok = 0;
        }
      }


      if(!ok)
        fout << "NU\n";
      else
        fout << "DA\n";
  }

  return 0;
}
