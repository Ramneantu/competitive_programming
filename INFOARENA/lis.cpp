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

typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef long long ll;

vector<ll> A;
vector<ll> R;
vector<ll> T;
int best_len = 0;
int best_pos = 0;

void LIS(int n){
  R.resize(n,-1);
  T.push_back(0);
  for(int i=1; i<n; ++i){
    if(A[i] > A[T.back()]){
      R[i] = T.back();
      best_pos = i;
      T.push_back(i);
      best_len++;
    }
    else if(A[i] < A[T[0]]){
      T[0] = i;
    }
    else{
      int l=0;
      int r=T.size()-1;
      while(l<r){
        int m = l + (r-l)/2;
        if(A[i] > A[T[m]])
          l = m+1;
        else
          r = m;
      }
      if(A[i] < A[T[l]]){
        if(l>0)
          R[i] = T[l-1];
        T[l] = i;
      }
    }
  }
}

void print_LIS(int i){
  if(R[i] == -1){
    cout << A[i] << " ";
  }
  else{
    print_LIS(R[i]);
    cout << A[i] << " ";
  }
}

int main(){

  freopen("scmax.in", "r", stdin);
  freopen("scmax.out", "w", stdout);

  int n;
  scanf("%d", &n);
  A.resize(n);
  for(int i=0; i<n; ++i)
    scanf("%lld", &A[i]);

  LIS(n);
  cout << best_len+1 << endl;
  print_LIS(best_pos);



  return 0;
}
