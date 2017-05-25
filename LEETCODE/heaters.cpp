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

    bool fits(int rad, vector<int>& houses, vector<int>& heaters){
        //printf("rad: %d\n", rad);
        int j=0;
        for(int i=0;i<heaters.size(); ++i){
            int l = heaters[i]-rad;
            int r = heaters[i]+rad;
            while(j < houses.size()){
                if(houses[j] < l)
                    return false;
                if(houses[j] > r)
                    break;
                j++;
            }
        }
        if(j < houses.size())
            return false;
        return true;
    }

    int findRadius(vector<int>& houses, vector<int>& heaters) {
        sort(houses.begin(), houses.end());
        sort(heaters.begin(), heaters.end());
        long r = 1e9;
        long l = 0;
        int min_rad = INT_MAX;
        while(l <= r){
            long m = l + (r-l)/2;
            if(fits(m,houses,heaters)){
                min_rad = m;
                r = m-1;
            }
            else{
                l = m+1;
            }
        }
        return min_rad;
    }
};


int main(){

  Solution s;
  int t;cin>>t;
  rep(_t,1,t){
    int n,m;cin>>n>>m;
    vector<int> houses(n);
    vector<int> heaters(m);
    rep(i,0,n-1)
      cin>>houses[i];
    rep(i,0,m-1)
      cin>>heaters[i];
    printf("Case #%d: %d\n", _t, s.findRadius(houses,heaters));
  }

  return 0;
}
