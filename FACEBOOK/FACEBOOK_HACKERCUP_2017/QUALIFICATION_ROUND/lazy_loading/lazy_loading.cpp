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
#define mp(x,C) make_pair((x),(C))
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

#define DBG(code) if(0){    \
                    do{         \
                    code        \
                    }while(0);  \
                  }

typedef pair<double, double> ii;


int main(){

  int N = 50;
	int t; cin >> t;
	rep(_t,1,t){
    int n; cin >> n;
    vector<int> W(n,0);
    rep(i,0,n-1) cin >> W[i];
    sort(W.begin(), W.end());

    DBG(rep(i,0,W.size()-1)
      cout << W[i] << " ";
    cout << "\n";)


    int max_trips = 0;
    int i_available = 0;
    int i_weight = W.size()-1;
    while(i_weight >= 0){
      int val = W[i_weight];
      i_weight--;
      int necessary_weights = N / val;
      if(N%val > 0)
        necessary_weights++;
      necessary_weights--; // we used the heaviest weight.

      DBG(cout << "necessary weights: " << necessary_weights << endl;)

      max_trips++;
      i_available += necessary_weights;

      DBG(cout << "i_weight: " << i_weight << " i_available: " << i_available << endl;)

      if((i_weight-i_available+1)*W[i_weight] < 50)
        break;
    }

    printf("Case #%d: %d\n", _t, max_trips);
	}

	return 0;
}
