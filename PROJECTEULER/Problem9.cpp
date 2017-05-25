#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {

    int t;
    cin >> t;
    while(t--){
        ll res = 0;
        ll N;
        cin >> N;
        for(ll b = 1; b < N; ++b){
            ll z = N*N - ((b*N)<<1);
            ll n = (N-b)<<1;
            if(z%n == 0){
                ll a = z/n;
                ll c = N-a-b;
                if(a*a + b*b == c*c)
                    res = max(res, a*b*c);
            }
        }
       if(res == 0)
           cout << -1 << endl;
        else
            cout << res << endl;
    }

    return 0;
}
