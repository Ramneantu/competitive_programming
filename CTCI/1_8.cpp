#include<bits/stdc++.h>
using namespace std;


void setRowZero(vector<vector<int> >& A, int row){
	for(int i=0; i<A[0].size(); ++i)
		A[row][i] = 0;
}

void setColZero(vector<vector<int> >& A, int col){
	for(int i=0; i<A.size(); ++i)
		A[i][col] = 0;
}

void zeroOutMatrix(vector<vector<int> >& A){
	if(A.empty())
		return;
	int N = A.size(), M = A[0].size();
	bool colZero = false, rowZero = false;

	// project zero elements except from the first row and first column, to first row and first column.

	for(int i=0; i<N; ++i)
		if(!A[i][0]){
			colZero = true;
			break;
		}
	for(int j=0; j<M; ++j)
		if(!A[0][j]){
			rowZero = true;
			break;
		}

	// iterate through other elements.
	for(int i=1; i<N; ++i)
		for(int j=1; j<M; ++j)
			if(!A[i][j])
				A[0][j] = A[i][0] = 0;
	
	// set rows to zero based on which elements in the first column are zero.
	for(int i=0; i<N; ++i)
		if(!A[i][0])
			setRowZero(A,i);

	// set cols to zero based on which elements in the first row are zero.
	for(int i=0; i<M; ++i)
		if(!A[0][i])
			setColZero(A,i);

	// set first row and first col to zero if necessary.
	if(rowZero)
		setRowZero(A,0);
	if(colZero)
		setColZero(A,0);
}

int main(){

	int t;
	cin >> t;
	for(int k=1; k<=t; ++k){	
		int M, N;
		cin >> M >> N;
		vector<vector<int> > A(M, vector<int>(N));
		for(int i=0; i<M; ++i)
			for(int j=0; j<N; ++j)
				cin >> A[i][j];
		zeroOutMatrix(A);
	
		printf("Case #%d:\n", k);
		for(int i=0; i<M; ++i){
			for(int j=0; j<N; ++j){
				cout << A[i][j] << " ";
			}
			cout << endl;
		}
	}

	return 0;
}
