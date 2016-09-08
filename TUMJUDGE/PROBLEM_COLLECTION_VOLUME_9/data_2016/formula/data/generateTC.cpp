#include <list>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cfloat>
#include <climits>
#include <numeric>
#include <iomanip>

using namespace std;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const double PI = 2.0 * acos(0.0);


typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<string> vs;

#define sz(c) int((c).size())
#define all(c) (c).begin(), (c).end()
#define FOR(i,a,b) for (int i = (a); i < (b); i++)
#define FORS(i,a,b,s) for (int i = (a); i < (b); i=i+(s))
#define FORD(i,a,b) for (int i = int(b)-1; i >= (a); i--)
#define FORIT(i,c) for (__typeof__((c).begin()) i = (c).begin(); i != (c).end(); i++)

typedef pair<double,double> pdd;
#define MAXINT 2000000
#define HALFMAXINT (MAXINT/2)

int main(){
	int seed; cin >> seed;
	srand(seed);
	set<pdd> points;
	FOR(i,0,3){
		pdd p;
		while (1){
			p.first = int(rand() % MAXINT - HALFMAXINT) / 1000;
			p.second = int(rand() % MAXINT - HALFMAXINT) / 1000;
			if (!points.count(p)) break;
		}
		points.insert(p);
		cout << p.first << " " << p.second << endl;
	}
	cout << double(rand() % MAXINT) / 1000 << endl;
}









