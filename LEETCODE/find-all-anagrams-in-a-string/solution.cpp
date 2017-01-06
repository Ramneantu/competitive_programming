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
    vector<int> findAnagrams(string s, string p) {
        map<char,int> pf;
        map<char,int> cf;
        
        vector<int> res;
        if(p.size() > s.size())
        	return res;
        if(p.size() == 0){
            for(int i=0;i<=s.size(); ++i)
                res.push_back(i);
            return res;
        }

        for(int i=0; i<p.size(); ++i){
        	pf[p[i]]++;
        	cf[s[i]]++;
        }
        
        int i=0;
        int dist = 0;
        for(int i=0; i<26; ++i){
            char c = char(97+i);
            dist += abs(pf[c]-cf[c]);
        }

        while(i<=s.size()-p.size()){
        	if(dist == 0)
        		res.push_back(i);
        	cf[s[i]]--;
            if(cf[s[i]]-pf[s[i]] >= 0)
                dist--;
            else
            	dist++;
        	cf[s[i+p.size()]]++;
        	if(cf[s[i+p.size()]] - pf[s[i+p.size()]] <= 0)
        		dist--;
        	else
        		dist++;
        	++i;
        }
        return res;
    }
};


int main(){



  return 0;
}
