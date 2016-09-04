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
#include <complex>

#define rep(i,a,b) for(int i=int(a); i<=int(b); ++i)
#define rev(i,b,a) for(int i=int(b); i>=int(a); --i)
#define mp(x,y) make_pair((x),(y))
#define pb(x) push_back(x)
#define all(c) c.begin(), c.end()
#define tr(container, it) for(auto it=(container).begin(); it != (container).end(); ++it)
#define sqr(x) ((x)*(x))
using namespace std;
using namespace complex_literals;

typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef long long ll;
typedef long double ld;

template<typename T1, typename T2>
void mod_clip(T1 &v, T2 mod){
  v = v % mod;
  if(v < 0)
    v = mod+v;
}

int main(){

  int q;
  cin >> q;
  while(q--){
      ld a,b;
      ll k,m;
      cin >> a >> b >> k >> m;

      complex<ld> res = complex<ld>(1,0);
      complex<ld> base = complex<ld>(a, b);
      ll real, imag;
      while(k > 0){
          if(k % 2){
              res *= base;
              real = res.real();
              imag = res.imag();
              mod_clip(real, m);
              mod_clip(imag, m);
              res = complex<ld>(real, imag);
          }
          k >>= 1;
          base = pow(base, 2);
          real = base.real();
          imag = base.imag();
          mod_clip(real, m);
          mod_clip(imag, m);
          base = complex<ld>(real, imag);
      }
      cout << ll(res.real()) << " " << ll(res.imag()) << endl;
  }

  return 0;
}
