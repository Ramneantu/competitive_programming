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
#define mod(a,n) ((a) < 0 ? ((n)+(a)) : ((a)%(n)))
using namespace std;

typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef long long ll;

const ll inf = ll(1000001);


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    ll n,k;
    cin >> n >> k;
    vector<pair<double, pair<ll, ll> > > P;
    for(ll i=0; i<n; ++i){
        ll p, d;
        cin >> p >> d;
        if(p == 0)
          P.push_back(make_pair(0, make_pair(p,d)));
        else
          P.push_back(make_pair(d*1.0/p, make_pair(p,d)));
    }
    sort(P.begin(), P.end());

/*
    tr(P, it)
         cout << it->first << " " << it->second.first << " " << it->second.second << endl;
         */

    ll res = 0;
    ll i;
    ll c=0;
    for(i=P.size()-1; i>=0 && c < k; --i){
        res += P[i].second.first;
        c++;
    }
    for(; i>=0; --i)
        res -= P[i].second.second;
    if(res < 0)
        cout << 0;
    else
        cout << res;
    cout << endl;
    return 0;
}
