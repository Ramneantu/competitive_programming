#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;

int main(){

  vector<pair<double, int> > servings;
  int n, m;
  cin >> n >> m;
  for(int i=0; i<n; ++i){
    string s;
    int amount;
    double nom;
    cin >> s >> amount >> nom;
    servings.push_back(make_pair(-nom, amount));
  }
  sort(servings.begin(), servings.end());
  double totalNoms = 0;
  int i = 0;
  while(m>0 && i < servings.size()){
    int amount = min(m, get<1>(servings[i]));
    totalNoms += amount*(-get<0>(servings[i]));
    m -= amount;
    i++;
  }
  cout << totalNoms << "\n";

  return 0;
}
