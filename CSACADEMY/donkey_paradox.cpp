#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<vector<int> > vvi;
typedef pair<int, int> ii;

inline int l1(ii p, ii q){
    return abs(p.first-q.first) + abs(p.second - q.second);
}

int main() {
    
    int N,M;
    cin >> N >> M;
    ii h1, h2;
    cin >> h1.first >> h1.second >> h2.first >> h2.second;
    int cnt = 0;
    for(int i=1; i<=N; ++i){
        for(int j=1; j<=M; ++j){
            if(l1(h1,ii(i,j)) == l1(h2,ii(i,j)))
                cnt++;
        }
    }
    cout << cnt << endl;
}
