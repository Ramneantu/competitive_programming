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
#define mout(M,n,m) rep(i,0,(n)-1){ rep(j,0,(m)-1) cout << (M)[i][j] << " ";  cout << "\n"; }
#define vout(V,a,b,msg) cout << "msg: "; rep(i,a,b)  cout << V[i] << " "; cout << "\n";
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

#define debug 0
#define DBG(code) if(debug){    \
                    do{         \
                    code        \
                    }while(0);  \
                  }

typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef long long ll;

class Solution {
public:
    int myAtoi(string str) {
     int sign = 0;
     string nr;
     for(int i=0; i<str.size(); ++i){
        if(str[i] == '+' || str[i] == '-'){
            if(sign == 0){
                if(str[i] == '+')
                    sign = 1;
                else
                    sign = -1;
            }
            else{
                break;
            }
        }
        else if(isalpha(str[i]))
            break;
        else if(str[i] == ' '){
            if(nr.size() > 0 || sign != 0)
                break;
            else
                continue;
        }
        else if(isdigit(str[i]))
            nr += str[i];
     }
     if(sign == 0)
        sign = 1;
     if(nr.size() > 10 && sign < 0)
        return INT_MIN;
     if(nr.size() > 10 && sign > 0)
        return INT_MAX;
    if(nr.size() == 10 && sign < 0 && nr.compare("2147483648") > 0)
        return INT_MIN;
    if(nr.size() == 10 && sign > 0 && nr.compare("2147483647") > 0)
        return INT_MAX;
    int i=0;
    int n = 0;
    while(i<nr.size()){
        n = n*10 + (nr[i]-'0');
        i++;
    }
    if(sign < 0)
        return -n;
    return n;
    }
};

int main(){



  return 0;
}
