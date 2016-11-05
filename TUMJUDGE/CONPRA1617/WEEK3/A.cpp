#include <queue>
#include <vector>
#include <iostream>

#define rep(i,a,b) for(int i=int(a); i<=int(b); ++i)
#define mp make_pair
#define fst first
#define snd second
using namespace std;

typedef long T;
typedef pair<T,T> TT;

vector<TT> p;

void iS(T n){
  p.resize(n);
  rep(i,0,n-1){
    p[i].fst = i;
    p[i].snd = 1;
  }
}
T fS(T i){
  if(p[i].fst == i)
    return i;
  T pi = fS(p[i].fst);
  p[i].fst = pi;
  return pi;
}
bool iSS(T i, T j){ return fS(p[i].fst) == fS(p[j].fst); }
void uS(T i, T j){
  T pj = fS(j);
  T pi = fS(i);
  if(p[pi].snd > p[pj].snd)
    p[pj].fst = pi;
  else if(p[pj].snd > p[pi].snd)
      p[pi].fst = pj;
  else{
    p[pi].fst = pj;
    p[pj].snd++;
  }
}

int main(){

  int ts;
  cin >> ts;
  rep(t,1,ts){
    int n;
    cin >> n;

    vector<pair<TT, T> > co;
    priority_queue<pair<T, TT> > PQ;

    rep(i, 0, n-1){
      T x, y, z;
      cin >> x >> y >> z;
      co.push_back(mp(mp(x,y),z));
      rep(j,0,i-1)
        PQ.push(mp(-(abs(x-co[j].fst.fst) + abs(y-co[j].fst.snd) + abs(z-co[j].snd)), mp(i,j)));
    }

    iS(n);
    T C = 0;
    T E = 0;
    while(!PQ.empty()){
      pair<T, TT> e = PQ.top(); PQ.pop();
      T u = e.snd.fst;
      T v = e.snd.snd;
      T c = e.fst;
      if(!iSS(u,v)){
        C += -c;
        uS(u,v);
        E++;
      }
      if(E == n-1)
        break;
    }
    printf("Case #%d: %ld\n", t, C);
  }

  return 0;
}
