#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<vector<int> > vvi;
typedef pair<int, int> ii;

vector<int> arrayIntersection(vector<int>& first, vector<int>& second) {
    map<int,int> H, G;
    vector<int> res;
    int sol = 1;
    if(sol == 0){ // O(n), O(n) space
        for(int i=0; i<first.size(); ++i)
            H[first[i]]++;
        for(int i=0; i<second.size(); ++i)
            G[second[i]]++;
        for(auto it=H.begin(); it!=H.end(); ++it)
            if(G.find(it->first) != G.end()){
                int n = min(it->second, G[it->first]);
                for(int j=0; j<n; ++j)
                    res.push_back(it->first);
            }
    }
    else if(sol == 1){ // O(n), O(n) space with one hashtable        
        for(int i=0; i<first.size(); ++i)
            H[first[i]]++;
        for(int i=0; i<second.size(); ++i)
            if(H[second[i]] > 0){
                res.push_back(second[i]);
                H[second[i]]--;
            }
    }
    return res;
}

int main(){

	int N, M;
	vector<int> A(N);
	vector<int> B(M);
	for(int i=0; i<N; ++i)
		cin >> A[i];
	for(int i=0; i<M; ++i)
		cin >> B[i];
	
	vector<int> I = arrayIntersection(A,B);

	cout << I.size() << endl;
	for(int i=0; i<I.size(); ++i)
		cout << I[i] << " ";
	
	return 0;
}
