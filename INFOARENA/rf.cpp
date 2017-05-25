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
using namespace std;

typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef long long ll;

const int INF = int(100001);

int main(){

  ifstream fin("rf.in");
  ofstream fout("rf.out");

  int n;
  fin >> n;
  vector<vector<int> > M(n, vector<int>(n,0));
  vector<vector<int> > A(n, vector<int>(n,1));
  rep(i,0,n-1)
    rep(j,0,n-1)
      fin >> M[i][j];

  rep(i,0,n-1)
    rep(j,0,n-1)
    if(i == j){
      M[i][j] = 0;
      A[i][j] = 0;
    }
    else if(i != j && M[i][j] == 0)
      M[i][j] = INF;

  rep(k,0,n-1)
    rep(i,0,n-1)
      rep(j,0,n-1)
        if(M[i][j] > M[i][k] + M[k][j]){
          M[i][j] = M[i][k] + M[k][j];
          A[i][j] = A[i][k] + A[k][j];
        }
        else if (M[i][j] == M[i][k] + M[k][j]) {
          A[i][j] = max(A[i][j], A[i][k] + A[k][j]);
        }

  rep(i,0,n-1){
    rep(j,0,n-1)
        fout << M[i][j] << " ";
    fout << "\n";
  }
  rep(i,0,n-1){
    rep(j,0,n-1)
        fout << A[i][j] << " ";
    fout << "\n";
  }

  return 0;
}
