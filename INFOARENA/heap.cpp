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
using namespace std;

typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef long long ll;

vector<int> H(200001, 0);
vector<int> A(200001, 0);
vector<int> P(200001, 0);
void hswap(int i, int j){
  int old_order_i = H[i];
  int old_order_j = H[j];
  int tmp = H[i];
  H[i] = H[j];
  H[j] = tmp;
  P[old_order_i] = j;
  P[old_order_j] = i;
}

void percolate(int n, int i){
  while(i >= 1){
    if(A[H[i]] < A[H[i/2]]){
      hswap(i, i/2);
      i /= 2;
    }
    else
      break;
  }
}

void sift(int n, int i){

  while(i <= n){
    if(2*i+1 <= n){
      if(A[H[i]] < A[H[2*i]] && A[H[i]] < A[H[2*i+1]])
        break;
      if(A[H[2*i]] < A[H[2*i+1]]){
        hswap(i, 2*i);
        i = 2*i;
      }
      else{
        hswap(i, 2*i+1);
        i = 2*i+1;
      }
    }
    else if(2*i <= n){
      if(A[H[i]] < A[H[2*i]])
        break;
      hswap(i, 2*i);
      i = 2*i;
    }
    else  // we are at a leaf.
      break;
  }
}

/**
  A: vector of inserted elements, A[i] = v, the i-th value inserted is v. 1 <= i <= n
  H: heap which contains the positions of the elements in A, i.e. H[i] = j, the i-th node in the
     heap has the j-th element in A, i.e. H[i] contains the j-th element inserted in A.
  P: P[i] = j, the i-th element inserted is in node j in the heap

  Find min: H[1]
  insert


**/


int main(){

  freopen("heapuri.in", "r", stdin);
  freopen("heapuri.out", "w", stdout);

  int n, N;
  scanf("%d", &N);
  int nn = 0;
  n = 0;
  while(N--){
    int op, x;
    scanf("%d", &op);
    if(op == 1){
      n++;
      nn++;
      scanf("%d", &A[nn]);
      H[n] = nn;
      P[nn] = n;
      percolate(n, n);
    }
    else if(op == 2){
      scanf("%d", &x);
      int pos = P[x];
      P[x] = -1;
      H[pos] = H[n];
      n--;
      if(A[H[pos]] < A[H[pos/2]])
        percolate(n,pos);
      else if((2*pos <= n && A[H[pos]] > A[H[2*pos]]) || (2*pos+1 <= n && (A[H[pos]] > A[H[2*pos]] || A[H[pos]] > A[H[2*pos+1]])))
        sift(n, pos);
    }
    else if(op == 3){
      printf("%d\n", A[H[1]]);
    }
  }

  return 0;
}
