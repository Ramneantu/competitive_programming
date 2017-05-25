#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<vector<int> > vvi;
typedef pair<int, int> ii;

void genPar(int N, int i, int closed, int open, vector<int>& sol){
    if(i == 2*N){
        for(int j=0; j<2*N; ++j)
            if(sol[j])
                cout << "(";
            else
                cout << ")";
        cout << endl;
    }
    else{
        if(open == N){
            sol[i] = 0;
            genPar(N,i+1,closed+1,open,sol);
        }
        else{
            sol[i] = 1;
            genPar(N,i+1,closed,open+1,sol);
            
            if(closed < open){
                sol[i] = 0;
                genPar(N,i+1,closed+1,open,sol);    
            }
        }
    }
}

void generateParentheses(int N) {
    vector<int> sol(2*N,0);
    genPar(N,0,0,0,sol);
}
int main() {
    int N;
    cin >> N;
    generateParentheses(N);
    return 0;
}

