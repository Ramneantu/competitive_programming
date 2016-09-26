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

using namespace std;

int alternating(string s, char c1, char c2){
    char last_c = '\0';
    int i=0;
    int len = s.length();
    char c;
    int l = 0;
    while(i<len){
        c = s[i];
        if(c == c1){
            if(last_c == c1)
                return -1;
            last_c = c1;
            l++;
        }
        else if(c == c2){
            if(last_c == c2)
                return -1;
            last_c = c2;
            l++;
        }
        i++;
    }
    return l;
}


int main(){
    int len;
    cin >> len;
    string s;
    cin >> s;
    set<char> S;
    for(int i=0; i<s.length(); ++i)
        S.insert(s[i]);

    int max_len = -1;
    for(set<char>::iterator it=S.begin(); it!=S.end(); ++it){
        for(set<char>::iterator jt=S.begin(); jt!=S.end(); ++jt)
            if(it != jt)
                max_len = max(max_len, alternating(s, *it, *jt));
    }
    max_len = max(0, max_len);
    cout << max_len << endl;

    return 0;
}
