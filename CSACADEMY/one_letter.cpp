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

vector<int> get_freq(string s){
    vector<int> freq(256,0);
    for(int i=0; i<int(s.size()); ++i)
        freq[s[i]]++;
    return freq;
}

int main() {
    int N;
    cin >> N;
    string s;
    vector<int> freq;
    string res;
    for(int i=0; i<N; ++i){
        cin >> s;
        freq = get_freq(s);
        for(int i=0; i<256; ++i)
            if(freq[i]){
                res += char(i);
                break;
            }
    }
    sort(res.begin(), res.end());
    cout << res << endl;
}
