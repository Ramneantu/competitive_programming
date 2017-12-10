#include <iostream>
#include <map>
#include <utility>
#include <string>
#include <vector>
using namespace std;


int main() {

    int n_divs, n;

    cin >> n_divs >> n;

    vector<pair<int, string> > arr;

    for (int i = 0; i < n_divs; i++) {
        int d;
        string s;
        cin >> d >> s;
        arr.push_back(make_pair(d, s));
    }

    for (int i = 0; i < n; i++) {
        int v;
        cin >> v;

        bool divisible = false;
        for (int j = 0; j < n_divs; j++) {
            if (v % arr[j].first == 0) {
                if (divisible) {
                    cout << " ";
                }
                cout << arr[j].second;
                divisible = true;
            }
        }
        if (!divisible) {
            cout << v;
        }
        if (i < n-1)
            cout << endl;
    }

    return 0;
}
