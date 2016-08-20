#include <iostream>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <utility>
#include <cmath>
#include <algorithm>

using namespace std;

typedef long long ll;
#define NMAX 60


// combinations to avoid overflow
ll C(ll n, ll k){
  ll r = 1;
  ll d;
  for(d=1; d<=k; ++d){
    r *= n--;
    r /= d;
  }
  return r;
}


int main(){

  int T;
  cin >> T;
  for(int t=1; t<=T; ++t){
    ll m, n, k, res;
    vector<pair<ll, ll> > pairs;
    cin >> m;

    res = 0;
    // for k=1 find all possible n such that n choose k = m
    k = 1;
    n = m;
    if (n > 2){
      pairs.push_back(make_pair(n,k));
      pairs.push_back(make_pair(n,n-k));
      res += 2;
    }
    else if(n == 2){
      pairs.push_back(make_pair(n,k));
      res += 1;
    }

    // for k=2 find all possible n such that n choose k = m
    k = 2;
    double delta = 1+8*m;
    double sqrt_delta = sqrt(delta);
    //cout << "delta: " << delta << " sqrt(delta): " << sqrt_delta << "\n";
    if((int)sqrt_delta*(int)sqrt_delta == (int)delta){
      n = 0.5*(1 + sqrt_delta);
      //cout << "n: " << n << "\n";
      if(n == 4){
        pairs.push_back(make_pair(n,k));
        res += 1;
      }
      else if(n > 4){
        pairs.push_back(make_pair(n,k));
        pairs.push_back(make_pair(n,n-k));
        res += 2;
      }
    }

    // for k>=3 find all possible n such that n choose k = m
    k = 3;
    while(1){

      ll comb_2k_k = C(2*k, k);
      //cout << "2k choose k: " << comb_2k_k << "\n";
      if (comb_2k_k > m){
        break;
      }

      n = 2*k;
      bool found = false;
      ll comb_n_k = comb_2k_k;
      while(1){
        //cout << "n choose k(" << n << "," << k << "): " << comb_n_k << "\n";
        if(comb_n_k == m){
          found = true;
          break;
        }
        if(comb_n_k > m){
          break;
        }
        n++;
        comb_n_k = C(n, k);
      }
      if(found){
        if(n == 2*k){
          pairs.push_back(make_pair(n,k));
          res += 1;
        }
        else if(n > 2*k){
          pairs.push_back(make_pair(n,k));
          pairs.push_back(make_pair(n,n-k));
          res += 2;
        }
      }
      k++;
    }

    sort(pairs.begin(), pairs.end());
    cout << "Case #" << t << ":\n";
    cout << res << "\n";
    for(int i=0; i<pairs.size(); ++i){
      cout << "(" << get<0>(pairs[i]) << "," << get<1>(pairs[i]) << ") ";
    }
    cout << "\n";
  }

  return 0;
}
