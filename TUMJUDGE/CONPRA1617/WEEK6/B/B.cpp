#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <bitset>
#include <utility>
using namespace std;

//  Globals
/*
  Mappings in G
  - free: 0
  - tool: 1
  - obstacle: -1
*/
vector<vector<int> > G;
vector<vector<int> > seen;
int di[4] = {0,-1,0,1};
int dj[4] = {-1,0,1,0};
int nr_tools;
int si, sj;
int w,h;

int ct;
bool search(int i, int j, int nr_tools_collected){
  ct++;
  seen[i][j] = 1;
  if(nr_tools_collected == nr_tools){
    return true;
  }
  if(G[i][j] == 1){ // we found a tool
    nr_tools_collected += 1;
  }
  if(nr_tools_collected == nr_tools){
    return true;
  }

  for(int k=0; k<4; ++k){
    int ii = i + di[k];
    int jj = j + dj[k];
    if(ii >= 0 && ii < h && jj >= 0 && jj < w && (G[ii][jj] == 0 || G[ii][jj] == 1) && seen[ii][jj] == 0){
      if(search(ii,jj,nr_tools_collected))
        return true;
    }
  }
  seen[i][j] = 0;
  return false;
}


int main(){

  int T;
  cin >> T;
  for(int t=1; t<=T; ++t){
    cin >> w >> h;
    // clear globals
    nr_tools = 0;
    G.clear();
    seen.clear();
    ct = 0;

    // read
    G.resize(h,vector<int>(w,0));
    seen.resize(h,vector<int>(w,0));
    for(int i=0; i<h; ++i){
      for(int j=0; j<w; ++j){
        char c;
        cin >> c;
        if(c == '_'){
          G[i][j] = 0;
        }
        else if(c == 'T'){
          G[i][j] = 1;
          nr_tools++;
        }
        else if(c == 'L'){
          si = i;
          sj = j;
          G[i][j] = 0;
        }
        else if(c == '#'){
          G[i][j] = -1;
          seen[i][j] = 1;
        }
      }
    }

    /*
    for(int i=0; i<h; ++i){
      for(int j=0; j<w; ++j)
        cout << G[i][j] << " ";
      cout << "\n";
    }

    for(int i=0; i<h; ++i){
      for(int j=0; j<w; ++j)
        cout << seen[i][j] << " ";
      cout << "\n";
    }*/

    printf("Case #%d: ", t);
    if(search(si,sj,0))
      cout << "yes";
    else
      cout<< "no";
    cout << "\n";

    //cout << "ct: " << ct << endl;
  }

  return 0;
}
