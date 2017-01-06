#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <bitset>
#include <utility>
using namespace std;

#define rep(i,a,b) for(int i=int(a); i<=int(b); ++i)
#define rev(i,b,a) for(int i=int(b); i>=int(a); --i)
#define rec(i,a,b,c) for(int i=int(a); i<=int(b); i+=int(c))
#define recv(i,a,b,c) for(int i=int(a); i>=int(b); i-=int(c))
#define mp(x,y) make_pair((x),(y))
#define pb(x) push_back((x))
#define all(c) c.begin(), c.end()
#define tr(container, it) for(auto it=(container).begin(); it != (container).end(); ++it)
#define sqr(x) ((x)*(x))
#define sz(a) int((a).size())
#define fst first
#define snd second
#define DBG(code) if(1){ do{ code }while(0); }
#define MOD(a,mod) ((a)+(mod))%(mod)
typedef int T;
typedef vector<T> VT;
typedef pair<T,T> TT;
typedef vector<TT> VTT;

string countAndSay(int n) {
	if(n == 1)
		return "1";
	int i=1;
	string s = "1";
	while(i<=(n-1)){
		string ss;
		int j=0;
		while(j<s.size()){
			char c = s[j];
			j++;
			int ct=1;
			while(j<s.size() && s[j] == c){j++; ct++;}
			ss += to_string(ct) + c;
		}
		s = ss;
		i++;
	}
	return s;
}


int main(){

  return 0;
}
