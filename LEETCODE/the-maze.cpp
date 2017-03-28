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

		vector<pair<int,int> > direction = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
		map<pair<int,int>, bool> H;
		pair<int,int> dest;
		vector<vector<int> > maze;

		inline bool inBounds(pair<int,int> pos){
			return pos.first >= 0 && pos.first < maze.size() && pos.second >= 0 && pos.second < maze[0].size();
		}

		inline bool isWall(pair<int,int> pos){
			if((inBounds(pos) && maze[pos.first][pos.second])||(!inBounds(pos)))
				return true;
			return false;
		}

		pair<int,int> roll(pair<int,int> pos, pair<int,int> dir){
			while(!isWall({pos.first+dir.first,pos.second+dir.second})){
				pos.first += dir.first, pos.second += dir.second;
			}
			return pos;
		}

		bool dfs(pair<int,int> pos){
			if(pos == dest){ // goal reached
				return true;
			}
			H[pos] = true; // mark as visited.

			for(auto d : direction){
				auto next = roll(pos,d);
				if(!H[next]){
					if(dfs(next))
						return true;
				}
			}
			return false;
		}

    bool hasPath(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
			this->maze = maze;
			this->dest = {destination[0], destination[1]};
			return dfs({start[0], start[1]});
    }
};

int main(){

	int T; cin >> T;
	for(int t=1; t<=T; ++t){
		int n,m;
		cin >> n >> m;
		vector<vector<int> > maze(n, vector<int>(m,0));
		for(int i=0; i<n; ++i)
			for(int j=0; j<m; ++j)
				cin >> maze[i][j];
		vector<int> start(2), dest(2);
		cin >> start[0] >> start[1] >> dest[0] >> dest[1];

		printf("Case #%d: ", t);
		Solution S;
		if(S.hasPath(maze, start, dest))
			cout << "true";
		else
			cout << "false";
		cout << endl;
	}


  return 0;
}
