#include<bits/stdc++.h>
using namespace std;

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

    int n,m;
    int di[4]={0,-1,0,1};
    int dj[4]={-1,0,1,0};

    bool valid(int i, int j){
        return (i>=0 && i<n && j>=0 && j<m);
    }
    void flood(int i, int j,vector<vector<char>>& board){
        board[i][j] = '1';

        for(int k=0; k<4; ++k){
            int r = i+di[k], c = j+dj[k];
            if(valid(r,c) && board[r][c] == 'O')
                flood(c,r,board);
        }
    }

    void set(vector<vector<char>>& board, char from, char to){
        for(int i=0; i<n; ++i)
            for(int j=0; j<m; ++j)
                if(board[i][j] == from)
                    board[i][j] = to;
    }

    void solve(vector<vector<char>>& board){
        if(board.empty())
            return;
        n = board.size();
        m = board[0].size();

        for(int i=0; i<n; ++i){
            if(board[i][0] == 'O')
                flood(i,0,board);
            if(board[i][m-1] == 'O')
                flood(i,m-1,board);
        }

        for(int j=0; j<m; ++j){
            if(board[0][j] == 'O')
                flood(0,j,board);
            if(board[n-1][j] == 'O')
                flood(n-1,j,board);
        }

        set(board, 'O', 'X');
        set(board, '1', 'O');
    }
};

int main(){



  return 0;
}
