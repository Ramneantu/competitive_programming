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

#define HMAX 16384

ifstream fin("alpin.in");
ofstream fout("alpin.out");
int di[4] = {0,-1,0,1};
int dj[4] = {-1,0,1,0};
int n;
vector<vector<int> > D;
void print_sol(int i, int j){
  if(D[i][j] == 1){
    fout << i+1 << " " << j+1 << endl;
  }
  else{
    rep(k,0,3){
      int ni = i + di[k];
      int nj = j + dj[k];
      if(ni < n && ni >= 0 && nj < n && nj >= 0 && D[ni][nj] == D[i][j]-1){
        print_sol(ni, nj);
        fout << i+1 << " " << j+1 << endl;
        break;
      }
    }
  }
}


int main(){

  fin >> n;
  vector<vector<int> > M(n, vector<int>(n));
  D.resize(n, vector<int>(n,0));
  vector<vector<pair<int,int> > > H(HMAX+1);
  rep(i,0,n-1)
    rep(j,0,n-1){
      fin >> M[i][j];
      H[M[i][j]].push_back(make_pair(i,j));
    }


  int dmax = -1;
  int mi, mj;
  rep(i,0,HMAX){
    rep(j,0,H[i].size()-1){
      int ii = H[i][j].first;
      int jj = H[i][j].second;
      rep(k,0,3){
        int ni = ii + di[k];
        int nj = jj + dj[k];
        if(ni < n && ni >= 0 && nj < n && nj >= 0 &&
          M[ni][nj] < M[ii][jj]){
            D[ii][jj] = max(D[ii][jj], D[ni][nj]);
        }
      }
      D[ii][jj]++;
      if(dmax < D[ii][jj]){
        dmax = D[ii][jj];
        mi = ii;
        mj = jj;
      }
    }
  }

  fout << dmax << endl;
  print_sol(mi,mj);

  return 0;
}
