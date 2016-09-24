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

ifstream fin("kfib.in");
ofstream fout("kfib.out");

#define MOD 666013

void matmul(ll A[][2], ll B[][2], ll C[][2]){
  C[0][0] = ((A[0][0]*B[0][0])%MOD + (A[0][1]*B[1][0])%MOD)%MOD;
  C[0][1] = ((A[0][0]*B[0][1])%MOD + (A[0][1]*B[1][1])%MOD)%MOD;
  C[1][0] = ((A[1][0]*B[0][0])%MOD + (A[1][1]*B[1][0])%MOD)%MOD;
  C[1][1] = ((A[1][0]*B[0][1])%MOD + (A[1][1]*B[1][1])%MOD)%MOD;
}

ll fib(ll k){
  if(k == 0)
    return 0;
  if(k < 3)
    return 1;

  ll Z[2][2], R[2][2];
  Z[0][0] = 0; Z[0][1] = Z[1][0] = Z[1][1] = 1;
  R[0][1] = R[1][0] = 0;
  R[0][0] = R[1][1] = 1;
  ll AUX[2][2];
  k--;
  while(k){
    if(k%2){
      k--;
      matmul(Z, R, AUX);
      R[0][0] = AUX[0][0];
      R[0][1] = AUX[0][1];
      R[1][0] = AUX[1][0];
      R[1][1] = AUX[1][1];
    }else{
      k >>= 1;
      matmul(Z,Z,AUX);
      Z[0][0] = AUX[0][0];
      Z[0][1] = AUX[0][1];
      Z[1][0] = AUX[1][0];
      Z[1][1] = AUX[1][1];
    }
  }
  return R[1][1];
}


int main(){

  ll k;
  fin >> k;
  fout << fib(k) << "\n";

  return 0;
}
