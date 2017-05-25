#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<vector<int> > vvi;
typedef pair<int, int> ii;

int main() {
    long long N,M,X,Y;
    cin >> N >> M >> X >> Y;
    long long l = 0;
    long long r = N;
    while(l < r){
        long long m = l + (r-l)/2;
        if(M + (N-m) * Y >= m * X){
            l = m+1;
        }
        else{
            r = m-1;
        }
    }
    if(M + (N-l) * Y >= l * X)
        cout << l;
    else
        cout << l-1;

}
