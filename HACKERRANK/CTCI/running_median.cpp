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
#define mod(a,n) ((a) < 0 ? ((n)+(a)) : ((a)%(n)))
#define mout(M,n,m) rep(i,0,(n)-1){ rep(j,0,(m)-1) cout << (M)[i][j] << " ";  cout << "\n"; }
using namespace std;

typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef long long ll;

int main(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(int a_i = 0;a_i < n;a_i++){
       cin >> a[a_i];
    }

    priority_queue<int, vector<int>, less<int> > max_heap;
    priority_queue<int, vector<int>, greater<int> > min_heap;

    cout.setf(ios::fixed,ios::floatfield);
    cout.precision(1);

    if(n == 1)
        cout << a[0]*1.0 << endl;
    else if(n == 2){
        cout << a[0]*1.0 << endl;
        cout << 0.5*(a[0]+a[1]) << endl;
    }
    else{
        cout << a[0]*1.0 << endl;
        cout << 0.5*(a[0]+a[1]) << endl;
        if(a[0] < a[1]){
            max_heap.push(a[0]);
            min_heap.push(a[1]);
        }
        else{
            min_heap.push(a[0]);
            max_heap.push(a[1]);
        }
        for(int i=2; i<a.size(); ++i){
            int mi = min_heap.top();
            int ma = max_heap.top();
            if(a[i] >= mi){
                if(min_heap.size() > max_heap.size()){
                    min_heap.pop();
                    max_heap.push(mi);
                }
                min_heap.push(a[i]);
            }
            else if(a[i] <= ma){
                if(max_heap.size() > min_heap.size()){
                    max_heap.pop();
                    min_heap.push(ma);
                }
                max_heap.push(a[i]);
            }
            else if(a[i] >= ma && a[i] <= mi){
                if(max_heap.size() > min_heap.size()){
                    min_heap.push(a[i]);
                }
                else{
                    max_heap.push(a[i]);
                }
            }
            int mi_sz = min_heap.size();
            int ma_sz = max_heap.size();
            if(mi_sz < ma_sz){
                cout << max_heap.top()*1.0 << endl;
            }
            else if(ma_sz < mi_sz){
                cout << min_heap.top()*1.0 << endl;
            }
            else{
                cout << (min_heap.top() + max_heap.top())*0.5 << endl;
            }
        }
    }

    return 0;
}
