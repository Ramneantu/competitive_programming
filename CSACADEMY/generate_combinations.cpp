#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<vector<int> > vvi;
typedef pair<int, int> ii;

void genComb(int N, int K, int i, vector<int>& sol){
    if(i == K){
        for(int j=0; j<K; ++j)
            cout << sol[j] << " ";
        cout << "\n";
    }
    else{
        for(int j=(i == 0 ? 1 : sol[i-1]+1); j<=N; ++j){
            sol[i] = j;
            genComb(N,K,i+1,sol);
        }
    }
}

void generateCombinations(int N, int K) {
    vector<int> sol(K,0);
    genComb(N,K,0,sol);
}
int main() {
    int N, K;
    cin >> N >> K;
    generateCombinations(N, K);
    return 0;
}
