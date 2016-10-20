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

#define rep(i,a,b) for(int i=int(a); i<=int(b); ++i)
#define rev(i,b,a) for(int i=int(b); i>=int(a); --i)
#define rec(i,a,b,c) for(int i=int(a); i<=int(b); i+=int(c))
#define recv(i,a,b,c) for(int i=int(a); i>=int(b); i-=int(c))
#define mp(x,y) make_pair((x),(y))
#define pb(x) push_back(x)
#define all(c) c.begin(), c.end()
#define tr(container, it) for(auto it=(container).begin(); it != (container).end(); ++it)
#define sqr(x) ((x)*(x))
#define sz(a) int((a).size())
#define mod(a,n) ((a) < 0 ? ((n)+(a)) : ((a)%(n)))
#define mout(M,n,m) rep(i,0,(n)-1){ rep(j,0,(m)-1) cout << (M)[i][j] << " ";  cout << "\n"; }
using namespace std;

#define INF_ULL ULLONG_MAX
#define INF_LL  LLONG_MAX
#define NINF_LL LLONG_MIN
#define INF_L   LONG_MAX
#define NINF_L   LONG_MIN
#define INF_U   UINT_MAX
#define INF     INT_MAX
#define NINF     INT_MIN


typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef long long ll;

int main(){

  int t;
  cin >> t;
  for(int _t=1; _t<=t; ++_t){
    int n,m;
    cin >> n >> m;
    vector<vector<bool> > M(n+1, vector<bool>(n+1));
    for(int i=0; i<M.size(); ++i)
      for(int j=0; j<M[i].size(); ++j)
        M[i][j] = false;
    int si, sj;
    cin >> sj >> si;
    for(int i=0; i<m; ++i){
      int li, lj, w,h,ri, rj;
      cin >> lj >> li >> w >> h;
      ri = li + h-1;
      rj = lj + w-1;
      for(int ii=li; ii<=ri; ++ii)
        for(int jj=lj; jj<=rj; ++jj)
          M[ii][jj] = true;
    }

    if(M[si][sj] == true)
      M[si][sj] = false;

    /*
    for(int i=1; i<=n; ++i){
      for(int j=1; j<=n; ++j)
        cout << M[i][j] << " ";
      cout << "\n";
    }*/



    int l;
    string s;
    cin >> l >> s;
    int steps=0;
    int points=0;
    int ho = 1;
    deque<pair<int,int> > S;
    S.push_back(make_pair(si,sj));
    map<pair<char, int>, pair<int, int> > A;
    A[make_pair('F', 1)] = make_pair(0, 1);
    A[make_pair('F', 2)] = make_pair(-1, 0);
    A[make_pair('F', 3)] = make_pair(0, -1);
    A[make_pair('F', 4)] = make_pair(1, 0);

    A[make_pair('L', 1)] = make_pair(-1, 0);
    A[make_pair('L', 2)] = make_pair(0, -1);
    A[make_pair('L', 3)] = make_pair(1, 0);
    A[make_pair('L', 4)] = make_pair(0, 1);

    A[make_pair('R', 1)] = make_pair(1, 0);
    A[make_pair('R', 2)] = make_pair(0, 1);
    A[make_pair('R', 3)] = make_pair(-1, 0);
    A[make_pair('R', 4)] = make_pair(0, -1);
    for(int i=0; i<l; ++i){
      pair<int,int> head = S.front();
      int ii =  head.first + A[make_pair(s[i],ho)].first;
      int jj =  head.second + A[make_pair(s[i],ho)].second;
      if(ii > n)
        ii = 1;
      else if(ii < 1)
        ii = n;
      if(jj > n)
        jj = 1;
      else if(jj < 1)
        jj = n;
      // change orientation of head
      if(s[i] == 'L'){
        ho++;
        if(ho == 5)
          ho = 1;
      }
      else if(s[i] == 'R'){
        ho--;
        if(ho <= 0)
          ho = 4;
      }

      // move head
      S.push_front(make_pair(ii,jj));
      if(M[ii][jj] == false)
        S.pop_back();


        /*
        cout << "steps: " << steps << "\n" << "points: " << points << "\n";
        cout << "snake:\n";
        for(int k=0; k<S.size(); ++k)
          cout << S[k].first << "," << S[k].second << "\n";
          */

      // check for collisions
      bool ok = true;
      for(int j=1; j<S.size(); ++j){
        if(S[j].first == S[0].first && S[j].second == S[0].second){
          ok = false;
          break;
        }
      }
      if(!ok)
        break;
      steps++;
      if(M[ii][jj] == true){
        points++;
        M[ii][jj] = false;
      }
    }

    cout << "Case #" << _t << ": " << steps << " " << points << "\n";
  }



  return 0;
}
