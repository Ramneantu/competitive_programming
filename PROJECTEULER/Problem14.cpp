#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

unordered_map<long, pair<ll, ll> > ps;

void collatz(ll i){
  if(i <= 1){
    if(ps.find(i) == ps.end())
      ps.insert(make_pair(i, make_pair(i,1)));
    return;
  }
  if(ps.find(i) != ps.end())
    return;
  if(i % 2 == 0){
    collatz(i/2);
    ps.insert(make_pair(i, make_pair(i/2, 1+get<1>(ps[i/2]))));
  }
  else{
    collatz(3*i+1);
    ps.insert(make_pair(i, make_pair(3*i+1, 1+get<1>(ps[3*i+1]))));
  }
}

int main(){

  chrono::high_resolution_clock::time_point t1, t2;
  ll longest = 1;
  ll nr;
  t1 = chrono::high_resolution_clock::now();
  for(ll i=1; i<=999999; ++i){
    collatz(i);
    if(longest < get<1>(ps[i])){
      longest = get<1>(ps[i]);
      nr = i;
    }
  }
  cout << "collatz longest < 1mio: " << nr << " " << longest << " steps" <<  endl;
  t2 = chrono::high_resolution_clock::now();
  ll duration = chrono::duration_cast<chrono::microseconds>( t2 - t1 ).count();
  cout << "Duration: " << duration << " microseconds" << endl;


  return 0;
}
