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

typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef long long ll;

int di[8] = {0,-1,-1,-1,0,1,1,1};
int dj[8] = {-1,-1,0,1,1,1,0,-1};
int rmax = 0;
vector< vector<int> > grid;
int n,m;
int dfs(int i, int j){
    int cnt = 0;
    grid[i][j] = 2;
    for(int k=0; k<8; ++k){
        int ii = i+di[k];
        int jj = j+dj[k];
        if(ii >= 0 && ii < n && jj >= 0 && jj < m && grid[ii][jj] == 1)
            cnt += dfs(ii, jj);
    }
    return 1+cnt;
}


int get_biggest_region(vector< vector<int> > &grid) {
    for(int i=0; i<grid.size(); ++i)
        for(int j=0; j<grid[i].size(); ++j)
            if(grid[i][j] == 1)
                rmax = max(rmax, dfs(i,j));
    return rmax;
}

int main(){
    cin >> n;
    cin >> m;
    grid.resize(n,vector<int>(m));
    for(int grid_i = 0;grid_i < n;grid_i++){
       for(int grid_j = 0;grid_j < m;grid_j++){
          cin >> grid[grid_i][grid_j];
       }
    }
    cout << get_biggest_region(grid) << endl;
    return 0;
}
