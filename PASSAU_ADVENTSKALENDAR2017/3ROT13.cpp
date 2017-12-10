#include <iostream>
#include <string>
using namespace std;


string rot13(string w) {
    string res;

    for (int i=0; i<w.size(); ++i) {
        res += char((((w[i]-'a')+13) % 26) + int('a'));
    }
    return res;
}

string rot13_n(string w, int n) {
    string res = w;
    for (int i=0; i<n; ++i) {
        res = rot13(w);
    }
    return res;
}


int main () {

    int n;
    cin >> n;

    for (int i=0; i<n; ++i) {
        string s;
        cin >> s;

        cout << rot13_n(s,3) << endl;
    }

    return 0;
}
