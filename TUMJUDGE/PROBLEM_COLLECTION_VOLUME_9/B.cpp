#include <iostream>
#include <cstring>
#include <vector>
#include <utility>
#include <map>

using namespace std;

#define WHITE 0
#define GRAY 1
#define BLACK 2

bool found_cycle;
vector<int> labels;
vector<vector<int> > G(1, vector<int>(0));

void dfs(int v){
  labels[v] = GRAY;
  for(int i=0; i<G[v].size(); ++i){
    if(labels[G[v][i]] == GRAY){
      found_cycle = true;
    }
    else if(labels[G[v][i]] == WHITE){
      dfs(G[v][i]);
    }
  }
  labels[v] = BLACK;
}


int main(){

  int n;
  cin >> n;

  map<string, int> name2id;

  int nodes = 1;
  for(int i=0; i<n; ++i){
    string dwarf1, dwarf2, relation;
    cin >> dwarf1 >> relation >> dwarf2;
    if(name2id[dwarf1] == 0){
      name2id[dwarf1] = nodes;
      nodes++;
      G.push_back(vector<int>(0));
    }
    if(name2id[dwarf2] == 0){
      name2id[dwarf2] = nodes;
      nodes++;
      G.push_back(vector<int>(0));
    }
    labels.resize(nodes, WHITE);
    if(relation == ">"){
      G[name2id[dwarf1]].push_back(name2id[dwarf2]);
    }
    else if(relation == "<"){
      G[name2id[dwarf2]].push_back(name2id[dwarf1]);
    }
  }

  bool is_possible = true;
  for(int i=1; i<nodes; ++i){
    found_cycle = false;
    if(labels[i] == WHITE)
      dfs(i);
    if(found_cycle){
      is_possible = false;
      break;
    }
  }

  if(is_possible)
    cout << "possible\n";
  else
    cout << "impossible\n";

  return 0;
}
