#include<bits/stdc++.h>
using namespace std;


class Stack{

private:
	vector<int> S;
	vector<int> tail;
public:
	Stack(int n){
		S.resize(n);
		tail.resize(2);
		tail[0] = 0, tail[1] = n-1;
	}

	bool empty(int s){
		if(s == 0)
			return tail[0] == 0;
		else
			return tail[1] == S.size()-1;
	}

	bool full(){
		return tail[0] - tail[1] > 0;
	}

	int top(int s){
		if(empty(s)){
			cout << "Stack empty\n";
			return INT_MAX;
		}
		if(s == 0)
			return S[tail[s]-1];
		else
			return S[tail[s]+1];
	}

	void push(int s, int v){
		if(full()){
			cout << "Full capacity\n";
			return;
		}
		if(s == 0)
			S[tail[s]++] = v;
		else
			S[tail[s]--] = v;
	}

	int pop(int s){
		int v = top(s);
		if(v == INT_MAX)
			return INT_MAX;
		if(s == 0)
			tail[0]--;
		else
			tail[1]++;
		return v;
	}
};


int main(){

	Stack S(3);
	assert(S.empty(0) == true);
	assert(S.empty(1) == true);

	S.push(0,1);
	assert(S.empty(0) == false);
	assert(S.top(0) == 1);

	S.push(1,2);
	assert(S.empty(1) == false);
	assert(S.top(1) == 2);

	S.push(0,2);
	assert(S.top(0) == 2);
	
	S.push(0,2);

	S.pop(0);
	S.pop(0);
	assert(S.empty(0) == true);

	return 0;
}
