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
    bool isValidSudoku(vector<vector<char> >& board) {
    	map<char,bool> M;
    	
    	// check rows
    	for(int i=0; i<9; ++i){
    		for(int j=0; j<9; ++j)
    		if(board[i][j] != '.'){
    			if(M.find(board[i][j]) != M.end())
    				return false;
    			else
    				M[board[i][j]] = true;
    		}
    		M.clear();
        }
    	
    	// check columns
    	for(int j=0;j<9; ++j){
    		for(int i=0; i<9; ++i)
    		if(board[i][j] != '.'){
    			if(M.find(board[i][j]) != M.end())
    				return false;
    			else
    				M[board[i][j]] = true;
    		}
    		M.clear();
        }
    
    	// check 3x3 blocks
    	int r = 0;
    	int c = 0;
    	for(int b=1; b<=9; ++b){
            for(int i=0; i<3; ++i)
                for(int j=0; j<3; ++j){
                    int ii = r+i;
                    int jj = c+j;
            		if(board[ii][jj] != '.'){
            			if(M.find(board[ii][jj]) != M.end())
            				return false;
            			else
            				M[board[ii][jj]] = true;
            		}
                }
            M.clear();
            if(b%3 == 0){
                c = 0;
                r += 3;
            }
            else{
                c += 3;
            }
    	}
        return true;
    }
};

int main(){



  return 0;
}
