#include<bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(int i=int(a); i<=int(b); ++i)

int main(){

  vector<vector<int> > mat;
  string s;
  while(getline(cin, s)){
    mat.push_back(vector<int>(0));
    istringstream iss(s);
    int val;
    while(iss >> val)
      mat[mat.size()-1].push_back(val);
  }
  int N = mat.size();
  int M = mat[0].size();
  int max_prod = 0;
  rep(i,0,N-4){
    rep(j,0,M-1){
      max_prod = max(max_prod, mat[i][j] * mat[i+1][j] * mat[i+2][j] * mat[i+3][j]);
      if(j<=M-4){
        max_prod = max(max_prod, mat[i][j] * mat[i+1][j+1] * mat[i+2][j+2] * mat[i+3][j+3]);
        if(i%4 == 0)
          rep(k,0,3)
            max_prod = max(max_prod, mat[i+k][j] * mat[i+k][j+1] * mat[i+k][j+2] * mat[i+k][j+3]);
      }
      if(j>=3 && j<=M-1)
        max_prod = max(max_prod, mat[i][j] * mat[i+1][j-1] * mat[i+2][j-2] * mat[i+3][j-3]);
    }
  }
  cout << max_prod << endl;

  return 0;
}
