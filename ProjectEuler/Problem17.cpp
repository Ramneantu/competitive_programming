#include <iostream>
#include <algorithm>
#include <numeric>
#include <set>
#include <map>
#include <queue>
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <cstring>
#include <cctype>
#include <cassert>
#include <limits>
#include <functional>
#include <bitset>
#include <utility>
#include <unordered_map>

#define rep(i,a,b) for(int i=int(a); i<=int(b); ++i)
#define rev(i,b,a) for(int i=int(b); i>=int(a); --i)
#define mp(x,y) make_pair((x),(y))
#define pb(x) push_back(x)
#define all(c) c.begin(), c.end()
#define tr(container, it) for(auto it=(container).begin(); it != (container).end(); ++it)
#define sqr(x) ((x)*(x))
using namespace std;

typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef long long ll;

int main(){

  vector<pair<string, int> > d = {{"one", 3}, {"two", 3}, {"three", 5}, {"four", 4}, {"five", 4}, {"six", 3}, {"seven", 5}, {"eight", 5}, {"nine", 4}, {"ten", 3},
  {"eleven", 6}, {"twelve", 6}, {"thirteen", 8}, {"fourteen", 8}, {"fifteen", 7}, {"sixteen", 7}, {"seventeen", 9}, {"eighteen", 8}, {"nineteen", 8},
  {"twenty", 6}, {"thirty", 6}, {"forty", 5}, {"fifty", 5}, {"sixty", 5}, {"seventy", 7}, {"eighty", 6}, {"ninety", 6}, {"hundred", 7}, };
  ll total = 0;
  // count [1-19]
  rep(i,0,18)
    total += get<1>(d[i]);

  ll up_to_nine = 0;
  rep(i,0,8)
    up_to_nine += get<1>(d[i]);

  // count [20-99]
  ll twenty_99 = 0;
  rep(i,19,26){
    total = total + 10*get<1>(d[i]) + up_to_nine;
    twenty_99 += 10*get<1>(d[i]) + up_to_nine;
  }

  ll up_to_99 = total;
  total += 9*get<1>(d[27]) + up_to_nine + 8+3;
  rep(i, 1, 9){
    total += (get<1>(d[i]) + 7 + 3)*99 + up_to_99;
  }
  cout << total << endl;

  return 0;
}
