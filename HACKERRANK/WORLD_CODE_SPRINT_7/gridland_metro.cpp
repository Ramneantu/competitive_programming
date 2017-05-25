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
#define mout(M,n,m) rep(i,0,(n)-1){ rep(j,0,(m)-1) cout << (M)[i][j] << " ";  cout << "\n"; }
using namespace std;

typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef long long ll;


int main(){

    map<ll, pair<vector<ll>, vector<ll> > > S;
    vector<pair<ll, pair<ll, ll> > > T;
    ll n, m, k;
    cin >> n >> m >> k;
    rep(i,0,k-1){
        ll r, c1, c2;
        cin >> r >> c1 >> c2;
        T.push_back(make_pair(r, make_pair(c1, c2)));
        S[c1].first.push_back(i);
        S[c2].second.push_back(i);
    }

    ll rows = n;
    ll last = 0;
    ll cells = 0;
    vector<ll> open(n,0);
    tr(S, it){
        ll pos = it->first;
        vector<ll> L = it->second.first;
        vector<ll> R = it->second.second;
        cells += rows*(pos-last);
        for(ll i=0; i<R.size(); ++i){
            open[T[R[i]].first]--;
            if(open[T[R[i]].first] == 0)
                rows++;
        }
        for(ll i=0; i<L.size(); ++i){
            if(open[T[L[i]].first] == 0)
                rows--;
            open[T[L[i]].first]++;
        }
        last = pos;
    }
    cout << cells << endl;



  return 0;
}
