#include<bits/stdc++.h>

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
#define vout(A,l,r) rep(i,l,r) cout << A[i] << " "; cout << "\n";
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
typedef unsigned long long ull;
typedef int ul;

vector<ul> V, temp;
vector<ul> buckets(256,0);
ul N,A,B,C;
#define ONES_BYTE 0xFF
#define TOTAL_BYTES sizeof(V[0])


inline ul key(ul value, ul exp){
  return ((value >> (exp * 8)) & ONES_BYTE);
}

void count_sort(vector<ul> &A, vector<ul> &B, int exp){
  rep(i,0,buckets.size()-1)
    buckets[i] = 0;

  rep(i,0,A.size()-1)
    buckets[key(A[i], exp)]++;

  vector<ul> index(N,0);
  index[0] = 0;
   for(int i = 1; i < 256; i++)
       index[i] = index[i-1] + buckets[i-1];

  // write elements sorted by exp into temporary array
  for(int i=0; i<B.size(); ++i){
    B[index[key(A[i], exp)]++] = A[i];
  }
}

void radix_sort(){
  rep(exp,0,TOTAL_BYTES-1)
    if(exp%2 == 0)
      count_sort(V,temp,exp);
    else
      count_sort(temp,V,exp);
}

int main(){

  freopen("radixsort.in", "r", stdin);
  freopen("radixsort.out", "w", stdout);

  // read data
  cin >> N >> A >> B >> C;
  V.resize(N,0);
  temp.resize(N,0);
  ull x = B;
  V[0] = x;
  rep(i,1,N-1){
    V[i] = ((ull)(A * x) % C + B) % C;
    x = V[i];
  }

  radix_sort();

  // output
  for(int i=0; i<N; i+=10)
    cout << V[i] << " ";
  cout << "\n";

  return 0;
}
