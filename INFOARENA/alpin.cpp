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

typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef long long ll;

#define HMAX 16384
#define NMAX 1026
#define SMAX 6200

FILE *f = fopen("alpin.in", "r");
FILE *g = fopen("alpin.out", "w");
int di[4] = {0,-1,0,1};
int dj[4] = {-1,0,1,0};
int n;
int M[NMAX][NMAX];
int D[NMAX][NMAX];
void print_sol(int i, int j){
  if(D[i][j] == 1)
    fprintf(g, "%d %d\n", i, j);
  else{
      if(D[i][j-1] == D[i][j]-1)
        print_sol(i, j-1);
      else if(D[i-1][j] == D[i][j]-1)
          print_sol(i-1, j);
      else if(D[i][j+1] == D[i][j]-1)
          print_sol(i, j+1);
      else if(D[i+1][j] == D[i][j]-1)
          print_sol(i+1, j);
      fprintf(g, "%d %d\n", i, j);
  }
}


int main(){

  fscanf(f, "%d\n", &n);
  vector<vector<pair<int,int> > > H(HMAX+1);
  char s[SMAX];
  char* pch;
  int j;
  rep(i,1,n){
      j=1;
      fgets(s, SMAX, f);
      pch = strtok(s, " ");
      while(pch){
        M[i][j] = atoi(pch);
        H[M[i][j]].push_back(make_pair(i,j));
        j++;
        pch = strtok(NULL, " ");
      }
  }

  rep(i,0,n+1){
    M[0][i] = M[n+1][i] = M[i][0] = M[n+1][i] = -1;
    D[0][i] = D[n+1][i] = D[i][0] = D[n+1][i] = -1;
  }

  int dmax = -1;
  int mi, mj, ii, jj;
  rep(i,0,HMAX){
    rep(j,0,H[i].size()-1){
      ii = H[i][j].first;
      jj = H[i][j].second;
      if(M[ii][jj-1] < M[ii][jj])
          D[ii][jj] = max(D[ii][jj], D[ii][jj-1]);
      if(M[ii-1][jj] < M[ii][jj])
          D[ii][jj] = max(D[ii][jj], D[ii-1][jj]);
      if(M[ii][jj+1] < M[ii][jj])
          D[ii][jj] = max(D[ii][jj], D[ii][jj+1]);
      if(M[ii+1][jj] < M[ii][jj])
          D[ii][jj] = max(D[ii][jj], D[ii+1][jj]);
      D[ii][jj]++;
      if(dmax < D[ii][jj]){
        dmax = D[ii][jj];
        mi = ii;
        mj = jj;
      }
    }
  }

  fprintf(g, "%d\n", dmax);
  print_sol(mi,mj);

  return 0;
}
