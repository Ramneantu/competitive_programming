#include <iostream>
#include <map>
#include <vector>
using namespace std;


int main () {

	int T;
	cin >> T;
	for (int t=1; t<=T; ++t) {
		int N;
		cin >> N;
		vector<long long> D(5002,0);
		for (int i=0; i<N; i++) {
			int a, b;
			cin >> a >> b;
			D[a]++;
			D[b+1]--;
		}

		vector<long> psums(5002, 0);
		for (int i=1; i<D.size(); ++i) {
			psums[i] += psums[i-1] + D[i];
		}
	
		int P;
		cin >> P;
		cout << "Case #" << t << ": ";
		for (int i=0; i<P; ++i) {
			int p;
			cin >> p;
			cout << psums[p] << " ";

		}
		cout << endl;
	}

	return 0;
}