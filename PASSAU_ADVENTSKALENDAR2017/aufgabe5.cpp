#include <iostream>
#include <vector>
#include <utility>
#include <limits.h>
using namespace std;

typedef long long ll;

int main() {

    int n;
    cin >> n;
    vector<vector<ll> > dp(n, vector<ll>(2,LLONG_MAX));

    vector<pair<int,int> > c(n);

    for (size_t i = 0; i < n; i++) {
        cin >> c[i].first >> c[i].second;
    }

    dp[0][0] = c[0].first;
    dp[0][1] = c[0].second;

    for (int i=1; i<n; ++i) {
        dp[i][0] = dp[i-1][1] + c[i].first;
        dp[i][1] = min(dp[i-1][0], dp[i-1][1]) + c[i].second;
    }

    cout << min(dp[n-1][0], dp[n-1][1]) << endl;

    return 0;
}
