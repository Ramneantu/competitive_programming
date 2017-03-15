#include <bits/stdc++.h>
using namespace std;


void rotateLayer(vector<vector<int> >& A, int l){
	
	// greater/less or EQUAL is used for the limits.

	int left = l;
	int right = A.size()-l-1;
	int up = l;
	int down = A.size()-l-1;
	int n = A.size() - 2*l; 

	//printf("left: %d up: %d right: %d down: %d n: %d\n", left, up, right, down, n);

	for(int i=0; i<n-1; ++i){
		int tmp = A[up][left + i];
		A[up][left + i] = A[down-i][left];
		A[down-i][left] = A[down][right-i];
		A[down][right-i] = A[up + i][right];
		A[up + i][right] = tmp;
	}
}

void rotateMatrix90(vector<vector<int> >& A){

	int layers = A.size() / 2;
	for(int layer=0; layer < layers; ++layer){
		rotateLayer(A, layer);
	}
}

int main(){
	
	int t; cin >> t;
	for(int i=1; i<=t; ++i){
		int n; cin >> n;
		vector<vector<int> > A(n,vector<int>(n));
		for(int i=0; i<n; ++i)
			for(int j=0; j<n; ++j)
				cin >> A[i][j];
		rotateMatrix90(A);
		printf("Case #%d:\n", i);
		for(int i=0; i<n; ++i){
			for(int j=0; j<n; ++j)
				cout << A[i][j] << " ";
			cout << "\n";
		}	
	}

	return 0;
}
