#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    stack<pair<int,int> > S;
    for(int i=0; i<n; ++i){
        int op, val;
        cin >> op;
        if(op == 1){
            cin >> val;
            if(S.empty())
                S.push({val,val});
            else if(val > S.top().second)
                S.push({val,val});
            else if(val <= S.top().second)
                S.push({val,S.top().second});
        }
        else if(op == 2)
            S.pop();
        else if(op == 3)
            cout << S.top().second << endl;
    }

    return 0;
}
