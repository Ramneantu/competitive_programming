#include<bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=int(a); i<=int(b); ++i)
#define all(V) V.begin(), V.end()

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

		void reverse(string &s, int i, int j){
			while(i<=j){
				swap(s[i++], s[j--]);
			}
		}

		void removeSpaces(string &s){
			int i=0, j=0;
			bool word = false;
			while(j < s.size()){
				if(s[j] == ' '){
					if(word){
						word = false;
						s[i++] = s[j++];
					}
					else{
						j++;
					}
				}
				else{
					if(!word){
						word = true;
					}
					s[i++] = s[j++];
				}
			}
			if(s[i-1] == ' ')
				i--;
			s.erase(s.begin()+i, s.end());
		}

    void reverseWords(string &s) {
			removeSpaces(s);
			int i=0;
			while(i<s.size()){
				if(s[i] != ' '){
					int j = i;
					while(j<s.size() && s[j] != ' ')
						j++;
					reverse(s,i,j-1);
					i=j-1;
				}
				i++;
			}
			reverse(s,0,int(s.size())-1);
    }
};

int main(){

	int T;
	cin >> T;
	string s;
	getline(cin,s);
	rep(t,1,T){
		getline(cin,s);
		printf("[%s]\n", s.c_str());
		Solution S;
		S.reverseWords(s);
		printf("Case #%d: [%s]\n", t, s.c_str());
	}

  return 0;
}
