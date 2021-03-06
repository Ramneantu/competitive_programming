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

ifstream fin("combinari.in");
ofstream fout("combinari.out");

int n, k;
vector<int> sol;

void comb(int pos){
  if(pos == k+1){
    rep(i,1,k)
      if(i < k)
        fout << sol[i] << " ";
      else
        fout << sol[i] << "\n";
  }
  else{
    for(int i=sol[pos-1]+1; i<=n; ++i){
      sol[pos] = i;
      comb(pos+1);
    }
  }
}


int main(){

  fin >> n >> k;
  sol.resize(k+1,0);
  comb(1);


  return 0;
}
