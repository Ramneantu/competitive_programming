#include<bits/stdc++.h>
using namespace std;

bool isSubstring(string s1, string s2){
	return s1.find(s2) != string::npos;
}

bool isRotation(string s1, string s2){
	if(s1.length() != s2.length())
		return false;
	string res = s1 + s1;
	return isSubstring(res, s2);
}



int main(){
	int t;
	cin >> t;
	for(int i=1; i<=t; ++i){
		string s1, s2;
		cin >> s1 >> s2;
		printf("Case #%d: ", i);
		cout << boolalpha << isRotation(s1,s2) << endl;
	}
	return 0;
}
