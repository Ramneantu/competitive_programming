#include <iostream>
#include <map>
#include <utility>
#include <cstring>
#include <cstdlib>

using namespace std;

int main(){

  string team1, team2;
  int goals1, goals2;
  map<string, pair<int, int> > teams; // (wins, losses)

  int T;
  cin >> T;
  for(int t=1; t<=T; ++t){
    for(int m=1; m<=16; ++m){
      cin >> team1 >> team2 >> goals1 >> goals2;

      if(goals1 > goals2){
        teams[team1].first += 1;
        teams[team2].second += 1;
      }
      else{
        teams[team2].first += 1;
        teams[team1].second += 1;
      }
    }
    string res = "";
    for(map<string, pair<int, int> >::iterator it=teams.begin(); it != teams.end(); ++it){
      if(it->second.second == 0){
        res = it->first;
        break;
      }
    }
    cout << "Case #" << t << ": " << res << "\n";

    teams.clear();
  }

  return 0;
}
