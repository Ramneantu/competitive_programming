#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<vector<int> > vvi;
typedef pair<int, int> ii;

inline int getMaxDiff(int a, int b){
    return max(a-b, b-a);
}

int fourXtremes(int a, int b, int c, int d) {
    int mx = INT_MIN;
    mx = max(mx, getMaxDiff(a,b));
    mx = max(mx, getMaxDiff(a,c));
    mx = max(mx, getMaxDiff(a,d));
    mx = max(mx, getMaxDiff(b,c));
    mx = max(mx, getMaxDiff(b,d));
    mx = max(mx, getMaxDiff(c,d));
    return mx;
}
int main() {
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    cout << fourXtremes(a, b, d, c) << "\n";
    return 0;
}
