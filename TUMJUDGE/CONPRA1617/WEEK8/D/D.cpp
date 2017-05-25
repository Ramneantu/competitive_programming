#include<bits/stdc++.h>

#define rep(i,a,b) for(ll i=int(a); i<=int(b); ++i)
#define rev(i,b,a) for(ll i=int(b); i>=int(a); --i)
#define rec(i,a,b,c) for(ll i=int(a); i<=int(b); i+=int(c))
#define recv(i,a,b,c) for(ll i=int(a); i>=int(b); i-=int(c))
#define mp(x,y) make_pair((x),(y))
#define pb(x) push_back(x)
#define all(c) c.begin(), c.end()
#define tr(container, it) for(auto it=(container).begin(); it != (container).end(); ++it)
#define sqr(x) ((x)*(x))
#define sz(a) int((a).size())
#define mout(M,n,m) rep(i,0,(n)-1){ rep(j,0,(m)-1) cout << (M)[i][j] << " ";  cout << "\n"; }
#define vout(V,a,b,msg) cout << msg << ": "; rep(i,a,b)  cout << V[i] << " "; cout << "\n";
using namespace std;

#define INF_ULL ULLONG_MAX
#define INF_LL  LLONG_MAX
#define NINF_LL LLONG_MIN
#define INF_L   LONG_MAX
#define NINF_L   LONG_MIN
#define INF_U   UINT_MAX
#define INF     INT_MAX
#define NINF     INT_MIN
#define fst first
#define snd second

//#define DBG 0

typedef long long ll;

class Rational{
private:
  ll x;
  ll y;
public:
  Rational() : x(0), y(1) {}
  Rational(ll x, ll y) : x(x), y(y) {}
  Rational(const Rational &copy) : x(copy.x), y(copy.y) {}
  friend ostream& operator<<(ostream& os, Rational r){
    if(r.x == 0)
      os << 0;
    else
      os << r.x << "/" << r.y;
    return os;
  }
  static ll gcd(ll a, ll b) {
      ll t;
      while (b) {
          t = b;
          b = a % b;
          a = t;
      }
      return a;
  }
  Rational operator-(Rational B){
    ll num = this->x*B.y - B.x*this->y;
    ll denom = this->y * B.y;
    ll d = gcd(num, denom);
    num /= d;
    denom /= d;
    return Rational(num,denom);
  }
  Rational operator+(Rational B){
    ll num = this->x*B.y + B.x*this->y;
    ll denom = this->y * B.y;
    ll d = gcd(num, denom);
    num /= d;
    denom /= d;
    return Rational(num,denom);
  }
  Rational operator/(Rational B){
    ll num = this->x*B.y;
    ll denom = this->y*B.x;
    ll d = gcd(num, denom);
    num /= d;
    denom /= d;
    return Rational(num,denom);
  }
  friend Rational operator*(ll val, Rational& B){
    ll num = B.x*val;
    ll denom = B.y;
    ll d = Rational::gcd(num, denom);
    num /= d;
    denom /= d;
    return Rational(num,denom);
  }
  Rational& operator*=(ll val){
    this->x *= val;
    ll d = gcd(this->x, this->y);
    this->x /= d;
    this->y /= d;
    return *this;
  }
  Rational operator*(Rational B){
    ll num = this->x*B.x;
    ll denom = this->y*B.y;
    ll d = gcd(num, denom);
    num /= d;
    denom /= d;
    return Rational(num,denom);
  }
  static Rational _abs(Rational P){
    Rational res;
    res.x = abs(P.x);
    res.y = abs(P.y);
    return res;
  }
  inline bool operator==(Rational B){ return this->x == B.x && this->y == B.y; }
};

typedef pair<Rational,Rational> TT;
TT operator* (ll val, TT& rhs){
  rhs.first *= val;
  rhs.second *= val;
  return rhs;
}
TT operator-(TT& P, TT& Q){
  TT res;
  res.first = P.first - Q.first;
  res.second = P.second - Q.second;
  return res;
}
TT operator+(TT& P, TT& Q){
  TT res;
  res.first = P.first + Q.first;
  res.second = P.second + Q.second;
  return res;
}
ostream& operator<<(ostream& os, TT& P){
  os << P.first << ", " << P.second;
  return os;
}


inline Rational get_area(TT P, TT Q, TT R){
  return Rational::_abs((P.first*(Q.second - R.second) + Q.first*(R.second - P.second) + R.first*(P.second - Q.second)) * Rational(1,2));
}
Rational get_area(vector<TT> Ps){
  Rational area;
  ll j = 1;
  while(j <= Ps.size()-2){
    Rational area_triangle = get_area(Ps[0], Ps[j], Ps[j+1]);
    area = area + area_triangle;
    j++;
  }
  return area;
}
TT get_convex_combination(TT P, TT Q, Rational alpha){
  TT res;
  res.first = alpha*(Q.first-P.first) + P.first;
  res.second = alpha*(Q.second-P.second) + P.second;
  return res;
}


int main(){

  int t;
  cin >> t;
  rep(_t,1,t){
    int n, m;
    cin >> n >> m;
    vector<TT> Ps;
    vector<TT> newPs;
    rep(i,0,n-1){
      int x,y;
      cin >> x >> y;
      Ps.pb(make_pair(Rational(x,1), Rational(y,1)));
    }
    Rational alpha = Rational(1,m);
    Rational truncated_area;
    rep(i,0,Ps.size()-1){
      TT left_marker = get_convex_combination(Ps[i], Ps[((i-1) < 0 ? n-1 : i-1)], alpha);
      TT right_marker = get_convex_combination(Ps[i], Ps[(i+1)%n], alpha);
      Rational area = get_area(left_marker, Ps[i], right_marker);
      truncated_area = truncated_area + area;
      if(left_marker.first == right_marker.first
        && left_marker.second == right_marker.second){
        newPs.pb(left_marker);
      }
      else{
        newPs.pb(left_marker);
        newPs.pb(right_marker);
      }
    }

    Rational total_area = get_area(Ps);
    cout << "Case #" << _t << ": " << truncated_area/total_area << endl;

    // clear globals
    Ps.clear();
    newPs.clear();
  }

  return 0;
}
