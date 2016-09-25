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

vector<int> A;
deque<int> dq;
void insert_into_deque(int pos){
    while(!dq.empty() && A[dq.back()] >= A[pos]){
        dq.pop_back();
    }
    dq.push_back(pos);
}

ll sumKMin(int n, int k){
    ll sum = 0;
    for(int i=0; i<k; ++i)
        insert_into_deque(i);
    sum += A[dq.front()];

    for(int i=k; i<n; ++i){
        if(!dq.empty() && i-k+1 > dq.front())
            dq.pop_front();
        insert_into_deque(i);
        sum += A[dq.front()];
    }
    return sum;
}


int main(){

  freopen("deque.in", "r", stdin);
  freopen("deque.out", "w", stdout);

  int n,k;
  scanf("%d %d", &n, &k);
  A.resize(n);
  for(int i=0; i<n; ++i)
    scanf("%d", &A[i]);

  printf("%lld\n", sumKMin(n,k));

  return 0;
}
