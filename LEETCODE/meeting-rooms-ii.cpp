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


// Definition for an interval.
struct Interval {
   int start;
   int end;
   Interval() : start(0), end(0) {}
   Interval(int s, int e) : start(s), end(e) {}
};

class Solution {
public:
    int minMeetingRooms(vector<Interval>& intervals) {
			int neededRooms = 0, availableRooms = 0;
			vector<pair<int,int> > events; // first = event time, second = interval id.
			for(int i=0; i<intervals.size(); ++i){
				// 1 means event starts, 0 means it ends.
				events.push_back(make_pair(intervals[i].start, 1));
				events.push_back(make_pair(intervals[i].end, 0));
			}
			sort(events.begin(), events.end());

			for(auto e : events){
				if(e.second == 1){ // it's an event start.
					if(!availableRooms){
						neededRooms++;
						availableRooms++;
					}
					availableRooms--;
				}
				else{ // this event ended.
					availableRooms++;
				}
			}
			return neededRooms;
    }
};

void read(vector<Interval>& intervals){
	string s;
	getline(cin, s);
	stringstream iss(s);
	int a,b;
	while(iss >> a >> b){
		intervals.push_back(Interval(a,b));
	}
}

int main(){

	int t;
	cin >> t;
	string dummy;
	getline(cin, dummy);
	for(int i=1; i<=t; ++i){
		vector<Interval> intervals;
		read(intervals);
		Solution S;
		printf("Case #%d: %d\n", i, S.minMeetingRooms(intervals));
	}


  return 0;
}
