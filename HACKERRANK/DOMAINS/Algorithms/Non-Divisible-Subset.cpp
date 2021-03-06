#include<bits/stdc++.h>
/**
TAGS: modulo-arithmetic greedy
**/

#define rep(i,a,b) for(int i=int(a); i<=int(b); ++i)
#define rev(i,b,a) for(int i=int(b); i>=int(a); --i)
#define mp(x,y) make_pair((x),(y))
#define pb(x) push_back(x)
#define all(c) c.begin(), c.end()
#define tr(container, it) for(auto it=(container).begin(); it != (container).end(); ++it)
#define sqr(x) ((x)*(x))
using namespace std;

typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef long long ll;


struct sort_second {
    bool operator()(const std::pair<int,int> &left, const std::pair<int,int> &right) {
        return left.second > right.second;
    }
};

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int n,k;
    cin >> n >> k;
    map<int, int> R;
    rep(i,0,n-1){
        int v;
        cin >> v;
        R[v%k]++;
    }
    vector<pair<int, int> > arr(all(R));
    sort(all(arr), sort_second());

    vector<int> sol;
    int total = 0;
    rep(i,0,arr.size()-1){
        int ct = get<1>(arr[i]);
        int r = get<0>(arr[i]);
        bool add = true;
        rep(j,0,sol.size()-1)
            if((sol[j]+r) % k == 0)
                add = false;
        if(add){
          sol.pb(r);
          total += ct;
        }
    }
    cout << total << endl;


    return 0;
}
