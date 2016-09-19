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
typedef long long ll;

int main(){

  // read data
  ifstream fin("cmlsc.in");
  ofstream fout("cmlsc.out");

  int m,n;
  fin >> m >> n;
  vector<int> A(m+1,0);
  vector<int> B(n+1,0);
  rep(i,1,m)
    fin >> A[i];
  rep(i,1,n)
    fin >> B[i];

  // compute length of longest common subsequence
  vector<vector<int> > opt(m+1, vector<int>(n+1,0));
  rep(i,1,m)
    rep(j,1,n)
      opt[i][j] = (A[i] == B[j] ? opt[i-1][j-1]+1 : max(opt[i-1][j], opt[i][j-1]));
  fout << opt[m][n] << endl;

  // compute the sequence
  vector<int> seq;
  int i,j;
  for(i=m, j=n; j>=1 && i>=1;)
    if(A[i] == B[j])
      seq.push_back(A[i]), i--, j--;
    else if(opt[i-1][j] < opt[i][j-1])
      j--;
    else
      i--;
  rev(i,seq.size()-1,0)
    fout << seq[i] << " ";

  return 0;
}
