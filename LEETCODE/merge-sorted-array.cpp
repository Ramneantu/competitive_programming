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
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    	int i = m-1, j = n-1, k = m+n-1;
    	
		while(i >= 0 && j >= 0)	nums1[k--] = (nums1[i] > nums2[j] ? nums1[i--] : nums2[j--]);
		while(j>=0) nums1[k--] = nums2[j--];
    }
};



int main(){

	int t;
	cin >> t;
	rep(_t,1,t){
		int m,n;
		cin >> m >> n;	
		vector<int> nums1(m+n);
		rep(i,0,m-1)
			cin >> nums1[i];
		vector<int> nums2(n);
		rep(i,0,n-1)
			cin >> nums2[i];
		
		Solution s;
		s.merge(nums1, m, nums2,n);
		
		printf("Case #%d: ", _t);
		rep(i,0,sz(nums1)-1)
			cout << nums1[i] << " ";
		cout << "\n";	
	}

  return 0;
}
