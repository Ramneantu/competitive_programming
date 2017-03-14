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

void print(vector<vector<int> >& C){
	rep(i,1,sz(C)-1){
		rep(j,1,sz(C[i])-1)
			cout << C[i][j] << " ";
		cout << "\n";
	}
	cout << "\n";
}


int main(){

	int t; cin >> t;
	rep(_t,1,t){
		int n,m;
		cin >> n >> m;
		vector<vector<int> > C(n+1,vector<int>(m+1,0));
		rep(i,1,n){
			rep(j,1,m){
				cin >> C[i][j];
			}
		}
		rep(i,1,sz(C)-1)
			sort(C[i].begin(), C[i].end());


		
		vector<vector<int> > S(n+1,vector<int>(m+1,0));
		rep(i,1,n)
			rep(j,1,m)
				if(j == 1)
					S[i][j] = C[i][j];
				else
					S[i][j] = S[i][j-1] + C[i][j];

		print(S);	

		vector<vector<int> > D(n+1, vector<int>(m+1,INT_MAX));
		rep(j,0,m-1)
			D[1][j] = S[1][j+1] + (j+1)*(j+1); 
		rep(i,2,n){
			rep(j,0,m){
				rep(k,j+1,m)
					D[i][j] = min(D[i][j], D[i-1][]	
			}
		}

	
		print(D);				

	}

	return 0;
}
