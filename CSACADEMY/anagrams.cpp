#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<vector<int> > vvi;
typedef pair<int, int> ii;

int main() {
    int N;
    cin >> N;
    map<string, int> H;
    for(int i=0; i<N; ++i){
        string s;
        cin >> s;
        sort(s.begin(), s.end());
        H[s]++;
    }
    int ma = 0;
    for(auto it=H.begin(); it!=H.end(); ++it)
        ma = max(ma, it->second);
    cout << ma << endl;
}
