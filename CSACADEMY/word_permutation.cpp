#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<vector<int> > vvi;
typedef pair<int, int> ii;

int main() {
    int N;
    cin >> N;
    vector<pair<string,int> > V(N);
    for(int i=0; i<N; ++i){
        cin >> V[i].first;
        V[i].second = i;
    }
    sort(V.begin(), V.end());
    for(int i=0; i<N; ++i)
        cout << V[i].second + 1 << " ";
}
