#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<vector<int> > vvi;
typedef pair<int, int> ii;

int get_nr_divs(int n){
    int cnt = (n == 1 ? 1 : 2); // 1 and n itself.
    for(int i=2; i*i<=n; ++i)
        if(n % i == 0){
            cnt += (n/i == i ? 1 : 2);
        }
    return cnt;
}

int main() {

    int A,B;
    cin >> A >> B;
    int cnt = 0;
    for(int i=A; i<=B; ++i){
        cnt += (get_nr_divs(i) % 2);
    }
    cout << cnt << endl;
}
