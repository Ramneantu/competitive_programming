#include <queue>
#include <vector>
#include <iostream>
#include <utility>

#define rep(i,a,b) for(int i=int(a); i<=int(b); ++i)
using namespace std;

typedef long long ll;
#define sqr(x) ((x)*(x))
#define mp make_pair
typedef pair<int,int> ii;

vector<pair<ll, ll> > p;

void iS(ll n){
  p.resize(n);
  rep(i,0,n-1){
    p[i].first = i;
    p[i].second = 1;
  }
}
ll fS(ll i){
  if(p[i].first == i)
    return i;
  ll x = fS(p[i].first);
  p[i].first = x;
  return x;
}
bool iSS(ll i, ll j){ return fS(p[i].first) == fS(p[j].first); }
void uS(ll i, ll j){
  ll v = fS(j);
  ll u = fS(i);
  if(p[u].second > p[v].second)
    p[v].first = u;
  else if(p[v].second > p[u].second)
      p[u].first = v;
  else{
    p[u].first = v;
    p[v].second++;
  }
}

int main(){

  int t;
  cin >> t;
  rep(_t,1,t){
    int n;
    cin >> n;

    vector<pair<pair<ll,ll>, ll> > co;
    priority_queue<pair<ll, ii>, vector<pair<ll, ii> >, std::greater<pair<ll, ii> > > PQ;
    n++;
    co.push_back(mp(mp(0,0),100000));
    rep(i, 1, n-1){
      ll x, y, c;
      cin >> x >> y >> c;
      co.push_back(mp(mp(x,y),c));
      rep(j,0,i-1){
        ll S = sqr(x-co[j].first.first) + sqr(y-co[j].first.second);
        if(c >= S && co[j].second >= S)
            PQ.push(mp(S, mp(i,j)));
      }
    }
    iS(n);
    ll E = 0;
    ll T = 0;
    while(!PQ.empty()){
      pair<ll, ii> f = PQ.top(); PQ.pop();
      int u = f.second.first;
      int v = f.second.second;
      ll c = f.first;
      if(!iSS(u,v)){
        uS(u,v);
        T += 2*c;
        E++;
      }
    }
    printf("Case #%d: ", _t);
    if(E < n-1)
      cout << "impossible\n";
    else
      cout << T << "\n";
  }

  return 0;
}
