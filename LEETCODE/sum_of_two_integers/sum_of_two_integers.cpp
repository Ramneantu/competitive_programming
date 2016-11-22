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

long add(long a, long b){
  int getSum(int a, int b) {
    bitset<32> a_bin(a);
    bitset<32> b_bin(b);
    int c = 0;
    bitset<32> n_bin(0);
    for(int i=0; i<=31; ++i){
      n_bin[i] = a_bin[i] ^ b_bin[i] ^ c;
      if((a_bin[i] && b_bin[i]) || ((a_bin[i] || b_bin[i]) && c))
        c = 1;
      else
        c = 0;
    }
    /**
     * If n_bin has bit 31 set to 1, it means it's a negative number.
     * So convert it to its positive counterpart by two's complement, convert it into decimal base and add a - sign.
     */
    if(n_bin[31])
      return -((n_bin.flip().to_ulong())+1);
    else
      return n_bin.to_ulong();
  }
}



int main(){

  long n = -1;
  //cout << bitset<32>(n).to_string() << endl;

  int T;
  cin >> T;
  rep(t,1,T){
    long a,b;
    cin >> a >> b;
    cout << add(a,b) << endl;
  }

  return 0;
}
