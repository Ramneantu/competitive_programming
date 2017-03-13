#include<bits/stdc++.h>
using namespace std;

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

class Solution {
public:
    int lengthLongestPath(string input) {
        int maxlength = 0;
        istringstream sin(input);
        map<int,int> H;
        for(string line; getline(sin, line);){
            int depth = line.find_last_of('\t') + 1;
            int curlen = int(line.length()) - depth + 1;
            curlen -= depth == 0 ? 1 : 0;
            if(line.find('.') != string::npos){ // we have a filename.
                maxlength = max(maxlength, depth > 0 ? H[depth-1] + curlen : curlen);
            }
            else
                H[depth] = depth > 0 ? H[depth-1] + curlen : curlen;
        }
        return maxlength;
    }
};

int main(){



  return 0;
}
