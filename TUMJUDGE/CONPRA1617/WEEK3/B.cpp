#include<bits/stdc++.h>

#define rep(i,a,b) for(int i=int(a); i<=int(b); ++i)
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
  T k = fS(p[i].fst);
  p[i].fst = k;
  return k;
}
bool iSS(T i, T j){ return fS(p[i].fst) == fS(p[j].fst); }
void uS(T i, T j){
  T k = fS(j);
  T l = fS(i);
  if(p[l].snd > p[k].snd)
    p[k].fst = l;
  else if(p[k].snd > p[l].snd)
      p[l].fst = k;
  else{
    p[l].fst = k;
    p[k].snd++;
  }
}

int main(){


  int ts;
  cin >> ts;
  rep(t,1,ts){
    int n, m;
    cin >> n >> m;

    priority_queue<pair<T, TT> > PQ;

    rep(i, 0, m-1){
      int a, b, c;
      cin >> a >> b >> c;
      PQ.push(make_pair(-c, make_pair(a-1,b-1)));
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
        C -= c;
        uS(u,v);
        E++;
      }
    }
    printf("Case #%d: ", t);
    if(E < n-1)
      cout << "impossible\n";
    else
      cout << C << "\n";
  }



  return 0;
}
