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

int islandPerimeter(vector<vector<int> >& grid) {
    int h = grid.size();
    int w = grid[0].size();
    int di[4] = {0,-1,0,1};
    int dj[4] = {-1,0,1,0};
    int perimeter = 0;
    for(int i=0; i<h; ++i)
        for(int j=0; j<w; ++j)
            if(grid[i][j] == 1){
                for(int k=0; k<4; ++k){
                    int ii = i + di[k];
                    int jj = j + dj[k];
                    if((ii >= 0 && ii < h && jj >= 0 && jj < w && grid[ii][jj] == 0) ||
                    (ii < 0 || ii >= h || jj < 0 || jj >= w))
                        perimeter++;
                }
            }
    return perimeter;
}

int main(){

  int T;
  scanf("%d", &T);
  rep(t,1,T){
    int n,m;
    cin >> n >> m;
    vector<vector<int> > grid(n,vector<int>(m,0));
    rep(i,0,n)
      rep(j,0,m)
        cin >> grid[i][j];

    cout << islandPerimeter(grid) << endl;
  }

  return 0;
}
