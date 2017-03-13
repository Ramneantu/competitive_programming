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

class Solution {
public:
    int lengthLongestPath(string input) {
        int maxlength = 0;
        istringstream sin(input);
        map<int,int> H{{-1,-1}};
        for(string line; getline(sin, line);){
            int depth = line.find_last_of('\t') + 1;
            int curlen = int(line.length()) - depth + 1;
            if(line.find('.') != string::npos){ // we have a filename.
                maxlength = max(maxlength, H[depth-1] + curlen);
            }
            else
                H[depth] = H[depth-1] + curlen;
        }
        return maxlength;
    }
};


int main(){



  return 0;
}
