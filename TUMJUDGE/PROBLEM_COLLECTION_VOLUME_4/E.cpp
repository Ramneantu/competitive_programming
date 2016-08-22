#include <iostream>
#include <utility>
#include <cstring>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

map<char, pair<int, int> > coord;
vector<pair<int, string> > words;

int dist(char c1, char c2){
  return abs(get<0>(coord[c1]) - get<0>(coord[c2])) + abs(get<1>(coord[c1]) - get<1>(coord[c2]));
}

int distw(string s1, string s2){
  int d = 0;
  for(int i=0; i<s1.size(); ++i)
    d += dist(s1[i], s2[i]);
  return d;
}


int main(){

  coord['q'] = make_pair(0,0);
  coord['w'] = make_pair(0,1);
  coord['e'] = make_pair(0,2);
  coord['r'] = make_pair(0,3);
  coord['t'] = make_pair(0,4);
  coord['y'] = make_pair(0,5);
  coord['u'] = make_pair(0,6);
  coord['i'] = make_pair(0,7);
  coord['o'] = make_pair(0,8);
  coord['p'] = make_pair(0,9);

  coord['a'] = make_pair(1,0);
  coord['s'] = make_pair(1,1);
  coord['d'] = make_pair(1,2);
  coord['f'] = make_pair(1,3);
  coord['g'] = make_pair(1,4);
  coord['h'] = make_pair(1,5);
  coord['j'] = make_pair(1,6);
  coord['k'] = make_pair(1,7);
  coord['l'] = make_pair(1,8);

  coord['z'] = make_pair(2,0);
  coord['x'] = make_pair(2,1);
  coord['c'] = make_pair(2,2);
  coord['v'] = make_pair(2,3);
  coord['b'] = make_pair(2,4);
  coord['n'] = make_pair(2,5);
  coord['m'] = make_pair(2,6);


  /*
  // test dist
  cout << dist('w', 'e') << endl;
  cout << dist('e', 'w') << endl;
  cout << dist('w', 'w') << endl;
  cout << dist('w', 'z') << endl;
  */

  /*
  // test distw
  cout << distw("ifpv", "icpc") << endl;
  cout << distw("icpc", "ifpv") << endl;
  */


  int T;
  cin >> T;
  for(int t=1; t<=T; ++t){
    string s;
    int n;
    cin >> s >> n;
    for(int i=0; i<n; ++i){
      string s2;
      cin >> s2;
      words.push_back(make_pair(distw(s, s2), s2));
    }
    sort(words.begin(), words.end());

    cout << "Case #" << t << ":\n";
    for(int i=0; i<words.size(); ++i)
      cout << get<1>(words[i]) << " " << get<0>(words[i]) << endl;

    words.clear();
  }

  return 0;
}
