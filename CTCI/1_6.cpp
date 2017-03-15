#include<bits/stdc++.h>
using namespace std;

string stringCompression(string s){
	string res;
	int ct = 0;
	for(int i=0; i<s.length(); ++i){
		if(i == 0||s[i] == s[i-1])
			ct++;
		else if(s[i] != s[i-1]){
			res += s[i-1] + to_string(ct);
			ct = 1;
		}
		if(i == s.length()-1){
			res += s[i] + to_string(ct);
			ct = 1;
		}
	}
	if(s.length() == res.length())
		return s;
	else
		return res;
}


int main(){

	int t;
	cin >> t;
	for(int i=1; i<=t; ++i){
		string s;
		cin >> s;
		printf("Case #%d: %s\n", i, stringCompression(s).c_str());
	}
	
	return 0;
}
