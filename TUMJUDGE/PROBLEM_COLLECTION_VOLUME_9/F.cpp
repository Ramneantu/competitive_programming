#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

#define REP(i, a, b) for(ll i=ll(a); i <= ll(b); ++i)
#define NMAX 60000

typedef long long ll;
typedef pair<ll, ll> ii;


priority_queue<pair<ll, ii> > EdgeList;
vector<ll> pset(NMAX);

void initSet(ll _size) {
  pset.resize(_size);
  REP(i, 1, _size)
    pset[i] = i;
}

ll findSet(ll i){
  return (pset[i] == i) ? i : (pset[i] = findSet(pset[i]));
}

void unionSet(ll i, ll j){
  pset[findSet(i)] = findSet(j);
}

bool isSameSet(ll i, ll j){
  return findSet(i) == findSet(j);
}

int main(){

  ll n, m, l;
  ll availableCost = 0;
  cin >> n >> m >> l;
  REP(i, 1, m){
    ll a, b, c;
    cin >> a >> b >> c;
    EdgeList.push(make_pair(-c, make_pair(a, b)));
    if(i <= l)
      availableCost += c;
  }

  //cout << "availableCost: " << availableCost << "\n";

  // Kruskal
  ll mst_cost = 0;
  initSet(n);
  ll mst_edges = 0;
  while(!EdgeList.empty()){
    pair<ll, ii> front = EdgeList.top(); EdgeList.pop();
    //cout << "pick: " << front.second.first << "-" << front.second.second << " " << -front.first << "\n";
    if(!isSameSet(front.second.first, front.second.second)){
      mst_cost += ll(-front.first);
      mst_edges++;
      unionSet(front.second.first, front.second.second);
    }
    if(mst_edges == n)
      break;

      /*
      REP(i, 1, n)
        cout << pset[i] << " ";
      cout << "\n";
      */
  }


  /*
  // check if you have only one connected component, a MST!
  REP(i, 1, n)
    cout << pset[i] << " ";
  cout << "\n";
  */

  // check if availableCost >= mst_cost
  bool is_possible = true;
  REP(i, 2, n)
    if(pset[i] != pset[i-1])
      is_possible = false;
  if(mst_cost > availableCost)// || !is_possible)
    cout << "impossible\n";
  else
    cout << "possible\n";


  /*
  cout << "availableCost: " << availableCost << "\n";
  while(!EdgeList.empty()){
    cout << EdgeList.top().second.first << " " << EdgeList.top().second.second << " " << EdgeList.top().first << "\n";
    EdgeList.pop();
  }
  */

  return 0;
}
