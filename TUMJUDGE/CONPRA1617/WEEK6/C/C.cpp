#include <vector>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cassert>

using namespace std;

#define NMAX 9

// Globals
vector<vector<int> > G;
//vector<vector<bool> > rows;
//vector<vector<bool> > cols;

bool verify_solution(){
  for(int i=0; i<NMAX; ++i)
    for(int j=0; j<NMAX; ++j){
      for(int k=0; k<NMAX; ++k)
        if((k != i && G[k][j] == G[i][j])||(k != j && G[i][k] == G[i][j]))
          return false;
      int is = i - i%3;
      int js = j - j%3;
      for(int _i=0; _i<3; _i++)
        for(int _j=0; _j<3; _j++)
          if(is+_i != i && js+_j != j && G[is+_i][js+_j] == G[i][j])
            return false;
    }
    return true;
}


void print_solution(){
  for(int i=0; i<NMAX; ++i){
    for(int j=0; j<NMAX; ++j)
      cout << G[i][j];
    cout << "\n";
  }
}

bool is_valid_move(int i, int j, int digit){
  for(int k=0; k<NMAX; ++k)
    if(G[i][k] == digit || G[k][j] == digit)
      return false;
  int is = i - i%3;
  int js = j - j%3;
  for(int _i=0; _i<3; _i++)
    for(int _j=0; _j<3; _j++)
      if(G[is+_i][js+_j] == digit)
        return false;
  return true;
}

bool solve(){
  int i = -1;
  int j = -1;
  // try to find next empty place.
  for(int _i=0; _i<NMAX; ++_i)
    for(int _j=0; _j<NMAX; ++_j)
      if(G[_i][_j] == 0){
        i = _i;
        j = _j;
        break;
      }
  if(i==-1 && j== -1){
    print_solution();
    return true;
  }
  else{
    for(int digit=1; digit<=9; ++digit){
      if(is_valid_move(i,j,digit)){
        G[i][j] = digit;
        if(solve())
          return true;
        G[i][j] = 0;
      }
    }

  }
  return false;
}



int main(){

  int T;
  cin >> T;
  for(int t=1; t<=T; ++t){
    G.resize(9, vector<int>(9, 0));
    //rows.resize(10, vector<bool>(10, false));
    //cols.resize(10, vector<bool>(10, false));
    for(int i=0; i<NMAX; ++i)
      for(int j=0; j<NMAX; ++j){
        char c;
        cin >> c;
        if(c == '?'){
          G[i][j] = 0;
        }
        else{
          G[i][j] = c - '0';
        }
      }


    printf("Case #%d:\n", t);
    solve();
    if(t<T)
      cout << "\n";

    //assert(verify_solution() == true);

    G.clear();
    //rows.clear();
    //cols.clear();
  }


  return 0;
}
