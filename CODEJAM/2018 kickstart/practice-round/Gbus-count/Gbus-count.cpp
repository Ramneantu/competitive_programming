#include <iostream>
#include <map>
#include <vector>
using namespace std;

/*
Start with an array Diff(maxcities+1, 0).
For each a,b pair, do D[a]+= x and D[b+1]-= x, where in our case x = 1 always. 
This operation encodes the fact that all elements in the interval [a,b] are increased by x.
After this create a prefix sum array, psum, where psum[0] = 0, and psum[i] = psum[i-1]+Diff[i]. This basically encodes the final
value at position i, after all the a,b operations were performed.
The answers for any position i, lies in psum[i].
*/

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
