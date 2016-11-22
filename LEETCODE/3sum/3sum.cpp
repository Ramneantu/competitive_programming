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
#define mod(a,n) ((a) < 0 ? ((n)+(a)) : ((a)%(n)))
#define mout(M,n,m) rep(i,0,(n)-1){ rep(j,0,(m)-1) cout << (M)[i][j] << " ";  cout << "\n"; }
using namespace std;

#define INF_ULL ULLONG_MAX
#define INF_LL  LLONG_MAX
#define NINF_LL LLONG_MIN
#define INF_L   LONG_MAX
#define NINF_L   LONG_MIN
#define INF_U   UINT_MAX
#define INF     INT_MAX
#define NINF     INT_MIN


typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef long long ll;


class Solution {
public:
    vector<vector<int> > threeSum(vector<int>& nums) {
        vector<vector<int> > res;
        if(nums.size() < 3)
            return res;
        sort(nums.begin(), nums.end());
        for(int a=0; a<=nums.size()-3;){
            int b = a+1;
            int c = nums.size()-1;
            while(b < c){
                if(nums[a]+nums[b]+nums[c]==0){
                    vector<int> triple(3,0);
                    triple[0] = nums[a];
                    triple[1] = nums[b];
                    triple[2] = nums[c];
                    res.push_back(triple);
                    while(nums[b] == nums[b-1] && b < nums.size()) b++;
                    c--;
                    while(nums[c] == nums[c+1] && c > b) c--;
                }
                else if(nums[a]+nums[b]+nums[c]<0)
                    b++;
                else
                    c--;
            }
            ++a;
            while(nums[a] == nums[a-1] && a <= nums.size()-3) a++;
        }
        return res;
    }
};

int main(){

  Solution sol;

  int n;
  cin >> n;
  vector<int> nums(n);
  for(int i=0; i<n; ++i){
    cin >> nums[i];
  }

  vector<vector<int> > res = sol.threeSum(nums);
  for(int i=0; i<res.size(); ++i)
    cout << res[i][0] << " " << res[i][1] << " " << res[i][2] << "\n";

  return 0;
}
