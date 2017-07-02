#include <bits/stdc++.h>
using namespace std;

int main(){
    int g;
    cin >> g;
    for(int a0 = 0; a0 < g; a0++){
        int n;
        int m;
        int x;
        cin >> n >> m >> x;
        vector<int> a(n);
        for(int a_i = 0; a_i < n; a_i++){
           cin >> a[a_i];
        }
        vector<int> b(m);
        for(int b_i = 0; b_i < m; b_i++){
           cin >> b[b_i];
        }
        
        long long cur_sum = 0;
        int i = 0;
        int max_rem = 0;
        while(i<n && cur_sum + a[i] <= x){
            cur_sum += a[i++];
        }
        max_rem = i;
        
        int j = 0;
        while(j < m && i>= 0){
            cur_sum += b[j++];
            while(cur_sum > x && i > 0){
                i--;
                cur_sum -= a[i];
            }
            if(cur_sum <= x)
                max_rem = max(max_rem, i+j);
        }

        cout << max_rem << endl;
    }
    return 0;
}
