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

bool is_prime(ll n){
    if(n < 2)
        return false;
    if(n == 2)
        return true;
    ll lim = ll(sqrt(n));
    for(ll i=2; i<=lim; ++i)
        if(n%i == 0)
            return false;
    return true;
}


int main(){
    int p;
    cin >> p;
    for(int a0 = 0; a0 < p; a0++){
        ll n;
        cin >> n;
        if(is_prime(n))
            cout << "Prime\n";
        else
            cout << "Not prime\n";
    }
    return 0;
}
