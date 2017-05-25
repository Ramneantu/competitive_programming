#include<bits/stdc++.h>

#define rep(i,a,b) for(int i=int(a); i<=int(b); ++i)
#define rev(i,b,a) for(int i=int(b); i>=int(a); --i)
#define mp(x,y) make_pair((x),(y))
#define pb(x) push_back(x)
#define all(c) c.begin(), c.end()
#define tr(container, it) for(auto it=(container).begin(); it != (container).end(); ++it)
#define sqr(x) ((x)*(x))
using namespace std;

typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef long long ll;

int mod_clip(int v, int mod){
  v = v % mod;
  if(v<0)
    return mod + v;
  return v;
}


int find_left(string s, int pos){
  if(s[pos] != 'A')
    return pos;
  int i = mod_clip(pos-1, s.size());
  while(i != pos){
    if(s[i] != 'A')
      return i;
    i = mod_clip(i-1, s.size());
  }
  return i;
}

int find_right(string s, int pos){
  if(s[pos] != 'A')
    return pos;
  int i = mod_clip(pos+1, s.size());
  while(i != pos){
    if(s[i] != 'A')
      return i;
    i = mod_clip(i+1, s.size());
  }
  return i;
}

int dist_left(int pos, int l, int n){
  if(pos >= l)
    return pos-l;
  else
    return pos+n-l;
}

int dist_right(int pos, int r, int n){
  if(pos <= r)
    return r-pos;
  else
    return r+n-pos;
}

int main(){

  int T;
  cin >> T;
  string dummy;
  for(int t=1; t<=T; ++t){
    string line;
    cin >> line;
    int n = line.size();

    int total = 0;
    for(int i=0; i<line.size(); ++i)
      if(line[i] != 'A'){
        int letter_dist = line[i]-'A';
        total += min(letter_dist, 26-letter_dist);
      }

    int best = 100000000;
    int moves;
    for(int i=0; i<line.size(); ++i){
      if(line[i] != 'A'){
        string s = line;
        int pos = i;
        if(i < n-i){
          moves = i;
          rep(k,0,i)
            s[k] = 'A';
        }
        else{
          moves = n-i;
          rev(k,s.size()-1,i)
            s[k] = 'A';
        }

        int l = find_left(s, pos);
        int r = find_right(s, pos);

        int ct = 0;
        while(l != r){
          int go_left = dist_left(pos, l, n);
          int go_right = dist_right(pos, r, n);

          if(go_left == 0 && go_right == 0)
            break;

          if(go_left < go_right){
            moves += go_left;
            pos = l;
            s[pos] = 'A';
            l = find_left(s, pos);
          }
          else{
            moves += go_right;
            pos = r;
            s[pos] = 'A';
            r = find_right(s, pos);
          }

        }
        moves += min(dist_left(pos, l, n), dist_right(pos, r, n));
        best = min(best, moves);
      }
    }
    if(best >= 100000000)
      best = 0;
    printf("Case #%d: %d\n", t, best + total);
  }

  return 0;
}
