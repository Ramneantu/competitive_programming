#include <iostream>
#include <algorithm>
#include <numeric>
#include <set>
#include <map>
#include <queue>
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <cstring>
#include <cctype>
#include <cassert>
#include <limits>
#include <functional>
#include <bitset>
#include <utility>

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

template<typename T>
void egcd(T a, T b, T &d, T &x, T &y) {
    if (b == 0) {
        d = a;
        x = 1;
        y = 0;
    }
    else {
        T x0, y0;
        egcd(b, a%b, d, x0, y0);
        x = y0;
        y = x0 - (a/b) * y0;
    }
}

inline double norm(ll x1, ll y1){ return sqrt(x1*x1 + y1*y1); }

ll find(ll a, ll b, ll c){

    ll x,y, d;
    egcd(a,b,d, x, y);
    x *= (c/d);
    y *= (c/d);
    ll a_d = a/d;
    ll b_d = b/d;


    ll res;
    ll min_dist = 100000000000;
    double x_min = c*1.0 / ((b*1.0/a)*b + a);
    ll k_min = (x_min - x) * (d*1.0 / b);
    ll k_zero = (-x)*(d*1.0 / b) + 1;

    // determine the integral minimum position.
    if(x + k_zero * b_d > 0){
        min_dist = norm(x+k_zero*b_d, y-k_zero*a_d);
        res = x + k_zero * b_d;
    }
    for(int i=-1; i<=1; ++i)
        if(norm(x + (k_min+i)*b_d, y - (k_min+i)*a_d) < min_dist && x + (k_min+i)*b_d > 0){
            min_dist = norm(x + (k_min+i)*b_d, y - (k_min+i)*a_d);
            res = x + (k_min+i)*b_d;
        }
    return res;
}



int main() {


    int q;
    cin >> q;
    while(q--){
        ll a, b, c;
        cin >> a >> b >> c;
        ll x = find(a,b,c);
        cout << x << " " << c/b - (a*x/b) << endl;
    }

  return 0;
}
