#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <map>
#include <utility>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<vector<int> > vvi;
typedef pair<int, int> ii;

string lookAndSay(int N) {
    string s = "1";
    N--;
    while(N--){
        string ss;
        int cnt = 0;
        for(int i=0; i<int(s.size()); ++i){
            if(i == 0){
                cnt++;
            }
            else{
                if(s[i] == s[i-1]){
                    cnt++;
                }
                else{
                    ss += to_string(cnt) + s[i-1];
                    cnt = 1;
                }
            }
        }
        s = ss + to_string(cnt) + s[s.size()-1];
    }
    return s;
}
   
int main() {
    int N;
    cin >> N;
    cout << lookAndSay(N);
}

