#include <cstdio>
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<vector<int> > vvi;
typedef pair<int, int> ii;


int main() {
    int n;
    cin >> n;
    vector<long long> m(3,0);
    for(int i=0; i<n; ++i){
        int v;
        cin >> v;
        m[v%3]++;
    }
    cout << m[0] * (m[0]-1) / 2 + m[1] * m[2] << endl;
    return 0;
}
