#include<bits/stdc++.h>
/**
TAGS: counting, merge
**/

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
using namespace std;

typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef long long ll;


int count_inversions(int l, int r, vector<int> &q){
    if(l >= r)
        return 0;
    int m = l + (r-l)/2;
    int left = count_inversions(l, m, q);
    int right = count_inversions(m+1, r, q);
    vector<int> c;
    int i = l;
    int j = m+1;
    int ct = 0;
    while(i<=m && j<=r){
        if(q[i] > q[j]){
            c.push_back(q[j++]);
            ct += m-i+1;
        }
        else
            c.push_back(q[i++]);
    }
    while(i<=m)
        c.push_back(q[i++]);
    while(j<=r)
        c.push_back(q[j++]);
    rep(i,0,c.size()-1)
        q[i+l] = c[i];

    return left + right + ct;
}


int main(){
    int T;
    cin >> T;
    for(int a0 = 0; a0 < T; a0++){
        int n;
        cin >> n;
        vector<int> q(n);
        for(int q_i = 0;q_i < n;q_i++){
           cin >> q[q_i];
        }
        // your code goes here
        bool correct = true;
        int ct = 0;
        rep(i,0,n-1)
            if(i < q[i]-3){
                correct = false;
                break;
            }
        if(!correct){
            cout << "Too chaotic\n";
        }
        else
            cout << count_inversions(0,n-1,q) << endl;
    }
    return 0;
}
