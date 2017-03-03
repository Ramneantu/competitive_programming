#include <map>
#include <cstring>
#include <iostream>
#include <cstdlib>
using namespace std;

int main(){

	int t; cin >> t;
	for(int _t=1; _t<=t; _t++){
		string s; cin >> s;
		int k; cin >> k;

		map<char,int> F;
		int cnt = 0;
		for(int i=0; i<s.size(); ++i){
			F[s[i]]++;
			if(F[s[i]] == 1)
				cnt++;
		}
		int i=0;
		int j=s.size()-1;
		while(i<j){
			cout << i << " " << j << " cnt: " << cnt << endl;
			if(cnt == k)
				break;
			if(cnt < k){
				i = -1;
				break;
			}
			if(F[s[i]] == 1){
				F[s[i]]--;
				cnt--;
				i++;
			}
			else{
				F[s[j]]--;
				cnt -= (F[s[i]] == 0);
				j--;
			}
		}
		printf("Case #%d: ", _t);
		if(i == -1)
			cout << "impossible\n";
		else
			cout << s.substr(i,j-i+1) << endl;
	}

}
