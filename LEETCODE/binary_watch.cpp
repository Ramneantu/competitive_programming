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



 int bin_to_dec(vector<int> A){ 
 // first is lowest bit
     int n = 0;
     for(int i=0; i<A.size(); ++i)
         n += (1<<i)*A[i];
     return n;
 }
 
 
 vector<string> readBinaryWatch(int num) {
     vector<string> res;
     vector<int> A(10-num,0);
     for(int i=0; i<num; ++i)
         A.push_back(1);
     do{ 
         vector<int> h;
         for(int i=0; i<4;++i)
             h.push_back(A[i]);
         vector<int> m;
         for(int i=4; i<A.size(); ++i)
             m.push_back(A[i]); 
         int hour = bin_to_dec(h);
         int min  = bin_to_dec(m);
         if(hour <= 11 && min <= 59){
             string s_hour = to_string(hour);
             string s_min;
             if(min < 10) 
                 s_min = "0" + to_string(min);
             else
                 s_min = to_string(min);
             res.push_back(s_hour + ":" + s_min);
         }
     }while(next_permutation(A.begin(), A.end()));
 
  return res;
 }


int main(){
	
	int n;
	cin >> n;
	vector<string> res = readBinaryWatch(n);
	for(int i=0; i<res.size(); ++i)
		cout << res[i] << endl;


  return 0;
}
