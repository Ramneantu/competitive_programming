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

typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef long long ll;

    int majorityElement(vector<int>& nums) {
        int count = 1;
        int maj_elem = nums[0];
        for(int i=1; i<nums.size(); ++i){
            if(nums[i] == maj_elem)
                count++;
            else
                count--;
            if(count == 0){
                maj_elem = nums[i];
                count = 1;
            }
        }
        count = 0;
        for(int i=0; i<nums.size(); ++i)
            count += (nums[i] == maj_elem);
        if(2*count > nums.size())
        	return maj_elem;
		return -1;
    }


int main(){
  	int t;
	cin >> t;
	while(t--){
		int n;
		cin >> n;
		vector<int> A(n,0);
		rep(i,0,n-1){
			cin >> A[i];
		}
		cout << majorityElement(A) << endl;
	}


  return 0;
}
