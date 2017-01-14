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
#define vout(V,a,b,msg) cout << msg << ": "; rep(i,a,b)  cout << V[i] << " "; cout << "\n";
#define fst first
#define snd second
#define debug 0
#define DBG(code) if(debug){    \
                    do{         \
                    code        \
                    }while(0);  \
                  }
using namespace std;

typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef long long ll;


inline int ch2idx(char c){
    if(c == 'A')
        return 0;
    if(c == 'C')
        return 1;
    if(c == 'G')
        return 2;
    if(c == 'T')
        return 3;
    return -1;
}

int main(){

  int t;
  cin >> t;
  rep(_t,1,t){
    int n,m; cin >> n >> m;
    vector<string> H(n);
    vector<string> M(m);
    rep(i,0,n-1)
      cin >> H[i];
    rep(i,0,m-1)
      cin >> M[i];

    vector<vector<int> > D(16, vector<int>(16,0));
    rep(i,0,sz(H)-1)
      rep(j,0,sz(M)-1)
        rep(k,0,sz(H[i])-1){
          int c = ch2idx(H[i][k]);
          int r = ch2idx(M[j][k]);
          if(c > r)
            D[r][c]++;
          else
            D[c][r] ++;
        }

      vector<int> V;
      rep(i,0,3)
          rep(j,i+1,3)
              V.pb(D[i][j]);
      sort(all(V));

      int best_score = -1;
      rep(i, 0, 10)
        rep(j, 0, 10)
          rep(k, 0, 10)
            rep(l, 0, 10)
              if((i+j+k+l)%2 == 0){
                int score = i*D[0][0] + j*D[1][1] + k*D[2][2] + l*D[3][3];
                score += V[5]*10 + V[4]*10 + V[0]*(-10) + V[1]*(-10) + V[2]*(-10) + V[3]*(10-(i+j+k+l)/2);
                best_score = max(best_score, score);
              }
      printf("Case #%d: %d\n", _t, best_score);
  }

  return 0;
}
