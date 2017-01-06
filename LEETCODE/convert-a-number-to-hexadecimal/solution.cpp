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
#define mout(M,n,m) rep(i,0,(n)-1){ rep(j,0,(m)-1) cout << (M)[i][j] << " ";  cout << "\n"; }
#define vout(V,a,b,msg) cout << "msg: "; rep(i,a,b)  cout << V[i] << " "; cout << "\n";
using namespace std;

#define INF_ULL ULLONG_MAX
#define INF_LL  LLONG_MAX
#define NINF_LL LLONG_MIN
#define INF_L   LONG_MAX
#define NINF_L   LONG_MIN
#define INF_U   UINT_MAX
#define INF     INT_MAX
#define NINF     INT_MIN
#define fst first
#define snd second

#define debug 0
#define DBG(code) if(debug){    \
                    do{         \
                    code        \
                    }while(0);  \
                  }

typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef long long ll;

class Solution {
public:
    string toHex(int num) {
      unsigned int _n;
      if(num < 0){
          _n = -num;
          _n = _n ^ 0x7fffffff;
          _n = _n + 1;
          _n = _n | (1<<31);
          //cout << _n << endl;
      }
      else{
          _n = num;
      }
      map<int,char> M = {{0, '0'},{1, '1'},{2, '2'},{3, '3'},{4, '4'},{5, '5'},{6, '6'},{7, '7'},{8, '8'},
                         {9, '9'}, {10, 'a'}, {11, 'b'}, {12, 'c'}, {13, 'd'}, {14, 'e'}, {15, 'f'}};
      string res = "";
      int ones_byte = 0xf;
      int offset = 0;
      for(int i=0; i<8; ++i){
          int _byte = (_n & ones_byte) >> offset;
          //cout << "byte: " << _byte << endl;
          res += M[_byte];
          offset += 4;
          ones_byte <<= 4;
          //cout << "res: " << res << endl;
      }
        string res_f;
        int i=0;
        reverse(res.begin(), res.end());
        while(i<res.size()-1 && res[i] == '0') i++;
        while(i<res.size()){
            res_f += res[i];
            i++;
        }
      return res_f;
    }
};

int main(){



  return 0;
}
