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

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};



typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef long long ll;

class SnakeGame {
private:
    queue<pair<int,int> > F;
    deque<pair<int,int> > S;
    int score;
    int w, h;
public:
    /** Initialize your data structure here.
        @param width - screen width
        @param height - screen height 
        @param food - A list of food positions
        E.g food = [[1,1], [1,0]] means the first food is positioned at [1,1], the second is at [1,0]. */
    SnakeGame(int width, int height, vector<pair<int, int>> food)
    {
        for(auto f : food){
            F.push(f);
        }
        S.push_back(make_pair(0,0));
        score = 0;
        w = width;
        h = height;
    }
    
    bool in_boundary(pair<int,int> p)
    { 
        return p.first >= 0 && p.first < h && p.second >= 0 && p.second < w;
    }
    
    pair<int,int> get_move(pair<int,int> cur, string dir)
    {
        if(dir == "U")
            return make_pair(cur.first-1, cur.second);
        else if(dir == "D")
            return make_pair(cur.first+1, cur.second);
        else if(dir == "L")
            return make_pair(cur.first, cur.second-1);
        else
            return make_pair(cur.first, cur.second+1);
    }
    
    /** Moves the snake.
        @param direction - 'U' = Up, 'L' = Left, 'R' = Right, 'D' = Down 
        @return The game's score after the move. Return -1 if game over. 
        Game over when snake crosses the screen boundary or bites its body. */
    int move(string direction)
    {
        // move snake
        S.push_front(get_move(S.front(), direction));
        auto tail = S.back();
        S.pop_back();
        
        // check if in boundary
        if(!in_boundary(S.front()))
            return -1;

        // check if collision with itself
        for(auto it=S.begin()+1; it!= S.end(); ++it)
            if(*it == S.front())
                return -1;

        // check if found food
        if(!F.empty() && F.front() == S.front()){
            S.push_back(tail);
            F.pop();
            score++;            
        }
        
        return score;
    }
};

int main(){



  return 0;
}
