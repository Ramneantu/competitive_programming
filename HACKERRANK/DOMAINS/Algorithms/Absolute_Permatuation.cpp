#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <bitset>
#include <utility>

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
using namespace std;

typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef long long ll;

bool inline in_bounds(int v, int left, int right){
    return v >= left && v <= right;
}

bool place(int dir, int pos, int k, int n, vector<int> &sol, vector<int> &viz){
    bool possible = false;
    if(dir == 0){
        rec(i,-1,1,2){
            if(in_bounds(pos+i*k, 1, n) && !viz[pos+i*k]){
                viz[pos+i*k] = 1;
                sol[pos] = pos+i*k;
                return true;
            }
        }
    }
    else{
        recv(i,1,-1,2){
            if(in_bounds(pos+i*k, 1, n) && !viz[pos+i*k]){
                viz[pos+i*k] = 1;
                sol[pos] = pos+i*k;
                return true;
            }
        }
    }
    return possible;
}


int main(){
    int t;
    cin >> t;
    for(int a0 = 0; a0 < t; a0++){
        int n;
        int k;
        cin >> n >> k;
        if(n % 2 == 1){
            if(k != 0)
                cout << -1 << endl;
            else{
                rep(i,1,n)
                    cout << i << " ";
                cout << endl;
            }
        }
        else{
            vector<int> sol(n+1,0);
            vector<int> viz(n+1, 0);
            int lim = n/2;
            int l = 1;
            int r = n;
            bool found = true;
            while(l<r){
                if(!place(0, l, k, n, sol, viz)){
                    found = false;
                    break;
                }
                if(!place(1, r, k, n, sol, viz)){
                    found = false;
                    break;
                }
                l++;
                r--;
            }
            if(found){
                rep(i,1,n)
                    cout << sol[i] << " ";
                cout << endl;
            }
            else
                cout << -1 << endl;
        }
    }
        
    return 0;
}
