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

class Queue {
public:
    stack<int> push_stack;
    stack<int> front_stack;
    
    void pop_from_stack(stack<int>& from, stack<int>& to){
        while(!from.empty()){
            int e = from.top(); from.pop();
            to.push(e);
        }
    }
    
    // Push element x to the back of queue.
    void push(int x) {
        push_stack.push(x);
    }

    // Removes the element from in front of queue.
    void pop(void) {
        int e = peek();
        front_stack.pop();
    }

    // Get the front element.
    int peek(void) {
        if(front_stack.empty()){
            pop_from_stack(push_stack, front_stack);
        }
        return front_stack.top();
    }

    // Return whether the queue is empty.
    bool empty(void) {
        return push_stack.empty() && front_stack.empty();
    }
};

int main(){



  return 0;
}
