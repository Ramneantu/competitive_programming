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

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};



typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef long long ll;

class Solution {
public:
    int findNthDigit(int n) {
        if(n <= 9)
            return n;
        n -= 9;
        long long digs = 2;
        long long tens = 10;
        while(true){
            if(n <= tens*digs*9) // found group
                break;
            n -= tens*digs*9;
            tens *= 10;
            digs++;
        }
        long long nn = tens + n/digs - 1;
        if(n%digs)
            nn++;
        long long divten;
        if(n%digs)
            divten = (long long)(pow(10,digs - n%digs));
        else
            divten = (long long)(pow(10,n%digs));
        return (nn/divten)%10;
    }
};

int main(){



  return 0;
}
