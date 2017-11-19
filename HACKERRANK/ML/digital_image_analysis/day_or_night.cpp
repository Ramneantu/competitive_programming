#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
using namespace std;


int main() {
    
    string line;
    double mean = 0;
    int n_pixels = 0;
    while(getline(cin, line)) {
        string tok;
        istringstream iss(line);
        while (iss >> tok) {
            istringstream is(tok);
            int v;
            double tmp = 0;
            while (is >> v) {
                tmp += v;
                if (is.peek() == ',') {
                    is.ignore();
                }
            }
            tmp /= 3;
            mean += tmp;
            n_pixels++;
        }
    }
    mean /= n_pixels;
    
    if(mean < 80) {
        cout << "night";
    }
    else {
        cout << "day";
    }
    
    return 0;
}

