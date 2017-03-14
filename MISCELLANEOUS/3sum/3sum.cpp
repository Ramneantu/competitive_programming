#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>
using namespace std;

int main(){

	int T;
	cin >> T;
	for(int t=1; t<=T; ++t){
		int N;
		cin >> N;
		vector<int> V(N);
		for(int i=0; i<N; ++i)
			cin >> V[i];
		sort(V.begin(),V.end());
		
		int cnt = 0;
		for(int i=0; i<=N-3; ++i){
			int j = i+1, k = N-1;
			while(j < k){
				int s = V[i] + V[j] + V[k];
				if(s == 0){ // found a triple that sums to 0.
					cnt++;
					k--;
				}
				else if(s < 0){
					j++;	
				}
				else{
					k--;
				}
			}
		}
		printf("Case #%d: %d\n", t, cnt);
	}

	return 0;
}
