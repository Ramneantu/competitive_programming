#include <iostream>
#include <cassert>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

#define REP(i, a, b) for(int i=int(a); i <= int(b); ++i)
typedef long long ll;


ll nCk(ll n, ll k){
  ll res = 1;

  if(k > n)
    return -1;
  if(k == 0)
    return 1;
  REP(i, 1, k){
    res *= n+1-i;
    res /= i;
  }
  return res;
}

ll binsearch(ll val, ll left, ll right, ll k){
  while(left <= right){
    //cout << "left: " << left << " right: " << right << endl;
    // compute new value
    ll mid = left + (right - left)/2;
    //cout << "mid: " << mid << endl;
    ll nk = nCk(mid, k);
    //cout << "mid choose 1: " << nk << endl;
    if (nk == val)
      return mid;
    if(nk > val)
      right = mid-1;
    else
      left = mid+1;
  }
  return -1;
}

int main(){

  int T;
  cin >> T;
  REP(t, 1, T){
    ll m;
    cin >> m;
    vector<pair<int, int> > pairs;
    ll k, n, res = 0;
    // find n such that n choose k = m, with starting k = 1
    k = 1;
    while(nCk(2*k, k) <= m){
      ll left = 2*k;
      ll right = nCk(m, k); // right bound is maximum m choose k
      ll n = binsearch(m, left, right, k);
      if(n != -1){
        if(n == 2*k){
          res += 1;
          pairs.push_back(make_pair(n, k));
        }
        else{
          res += 2;
          pairs.push_back(make_pair(n, k));
          pairs.push_back(make_pair(n, n-k));
        }
      }
      k++;
    }
    sort(pairs.begin(), pairs.end());
    printf("Case #%d:\n%lld\n", t, res);
    for(int i=0; i<pairs.size(); ++i)
      cout << "(" << get<0>(pairs[i]) << "," << get<1>(pairs[i]) << ") ";
    cout << endl;
  }
  return 0;
}
