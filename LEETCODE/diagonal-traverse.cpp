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
    vector<int> findDiagonalOrder(vector<vector<int>>& matrix) {
        vector<int> res;
        if(matrix.empty())
            return res;
        queue<pair<int,pair<int,int> > > Q;
        map<pair<int,int>,bool> vis;
        Q.push(make_pair(0,make_pair(0,0)));
        vis[make_pair(0,0)] = true;
        vector<int> tmp;
        int lvl = 0;
        int rev = true;
        while(!Q.empty()){
            pair<int,pair<int,int> > e = Q.front(); Q.pop();
            int i = e.first, j = e.second.first, l = e.second.second;
            if(l > lvl){
                if(rev)
                    for(int k=tmp.size()-1; k>=0; k--)
                        res.push_back(tmp[k]);
                else
                    for(int k=0; k<tmp.size(); ++k)
                        res.push_back(tmp[k]);
                tmp.clear();
                rev = !rev;
                lvl = l;
            }
            tmp.push_back(matrix[i][j]);

            if(j+1 < matrix[0].size() && vis.find(make_pair(i,j+1)) == vis.end()){
                Q.push(make_pair(i,make_pair(j+1,l+1)));
                vis[make_pair(i,j+1)] = true;
            }
            if(i+1 < matrix.size() && vis.find(make_pair(i+1,j)) == vis.end()){
                Q.push(make_pair(i+1,make_pair(j,l+1)));
                vis[make_pair(i+1,j)] = true;
            }
        }
        if(rev)
            for(int k=tmp.size()-1; k>=0; k--)
                res.push_back(tmp[k]);
        else
            for(int k=0; k<tmp.size(); ++k)
                res.push_back(tmp[k]);
        return res;
    }
};

int main(){



  return 0;
}
