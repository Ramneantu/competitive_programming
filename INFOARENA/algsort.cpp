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
using namespace std;

typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef long long ll;

ifstream fin("algsort.in");
ofstream fout("algsort.out");

vector<int> q;
template<typename T, typename S>
void merge_sort(S l, S r){
    if(l >= r)
        return;
    S m = l + (r-l)/2;
    merge_sort<T,S>(l, m);
    merge_sort<T,S>(m+1, r);
    vector<T> c;
    S i = l;
    S j = m+1;
    while(i<=m && j<=r){
        if(q[i] > q[j])
            c.push_back(q[j++]);
        else
            c.push_back(q[i++]);
    }
    while(i<=m)
        c.push_back(q[i++]);
    while(j<=r)
        c.push_back(q[j++]);
    rep(i,0,c.size()-1)
        q[i+l] = c[i];
}


int main(){

  int n;
  fin >> n;
  q.resize(n);
  rep(i,0,n-1)
    fin >> q[i];
  merge_sort<int,int>(0,n-1);
  rep(i,0,n-1)
    fout << q[i] << " ";

  return 0;
}
