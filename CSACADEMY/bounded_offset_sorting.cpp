#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<vector<int> > vvi;
typedef pair<int, int> ii;

void sort(vector<int>& v, int M) {
    priority_queue<int, vector<int>, greater<int> > P;
    int k = 0, i = 0;

    while(true){
        if(P.size() == M+1 || (i == v.size())){
            v[k++] = P.top(); P.pop();
        }
        if(i < v.size()){
            P.push(v[i++]);
        }
        if(P.empty())
            break;
    }
}
   
int main() {
    int N, M;
    cin >> N >> M;
    vector<int> v;
    for (int i = 0; i < N; ++i) {
        int val;
        cin >> val;
        v.push_back(val);
    }
    sort(v, M);
    for (auto& val : v) {
        cout << val << " ";
    }
    return 0;
}

