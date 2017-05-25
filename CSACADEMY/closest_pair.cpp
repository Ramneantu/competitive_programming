#include<bits/stdc++.h>
using namespace std;

int closestPair(vector<int>& first, vector<int>& second) {
    sort(first.begin(), first.end());
    sort(second.begin(), second.end());
    int i=0, j = 0, last = -1, from = -1;
    int mi = INT_MAX;
    while(i < int(first.size()) && j < int(second.size())){
        if(first[i] < second[j]){
            if(last != -1){
                if(from == 2)
                    mi = min(mi, abs(first[i]-last));                
            }
            from = 1;
            last = first[i];
            i++;
        }
        else if(first[i] > second[j]){
            if(last != -1){
                if(from == 1)
                    mi = min(mi, abs(second[j]-last));
            }
            last = second[j];
            from = 2;
            j++;
        }
        else{
            mi = 0;
            break;
        }
    }
    return mi;
}

int main() {
    int n; cin >> n;
    vector<int> first, second;
    for (int i = 0; i < n; ++i) {
        int val; cin >> val;
        first.push_back(val);
    }
    for (int i = 0; i < n; ++i) {
        int val; cin >> val;
        second.push_back(val);
    }
    cout << closestPair(first, second) << "\n";
    return 0;
}

