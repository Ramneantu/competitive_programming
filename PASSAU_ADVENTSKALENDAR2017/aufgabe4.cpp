#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <utility>
using namespace std;

#define SOUTH 0
#define WEST 1
#define NORTH 2
#define EAST 3


#define DEBUG 0
#define DBG(code) if (DEBUG) {do { code }while(0); }

vector<pair<int,int> > dirs;

char dir2letters(int d) {
    if (d == SOUTH) {
        return 'S';
    }
    else if (d == WEST) {
        return 'W';
    }
    else if (d == NORTH) {
        return 'N';
    }
    else {
        return 'O';
    }
}

string pos2letters(pair<int,int> pos) {
    string res;
    res += char((pos.first) + int('A'));
    res += char((pos.second) + int('A'));
    return res;
}

bool find_word_helper(const vector<vector<char> >& mat, string w, int i, int j, int p, int dir) {
    if (p >= w.size())
        return true;
    if ((i<0||i>=mat.size())) {
        if (p>=w.size()) {
            return true;
        }
        else {
            return false;
        }
    }
    if ((j<0||j>=mat[0].size()) && p>=w.size()) {
        if (p>=w.size()) {
            return true;
        }
        else {
            return false;
        }
    }

    if (w[p] != mat[i][j])
        return false;

    return find_word_helper(mat, w, i+dirs[dir].first, j+dirs[dir].second, p+1, dir);
}


pair<pair<int,int>,int> find_word(const vector<vector<char> >& mat, string w) {

    pair<pair<int,int>,int> sol;
    sol.first = make_pair(-1,-1);
    for (int i=0; i<mat.size(); ++i) {
        for (int j=0; j<mat[0].size(); ++j) {
            if (mat[i][j] == w[0]) {
                for (int k=0; k<dirs.size(); ++k) {
                    bool res = find_word_helper(mat, w, i+dirs[k].first, j+dirs[k].second, 1, k);
                    if (res) {
                        DBG(cout << w << ": " << i << ", " << j << endl;)
                        sol.first = make_pair(i,j);
                        sol.second = k;
                        return sol;
                    }
                }
            }
        }
    }
    return sol;
}


int main () {


    dirs.push_back(make_pair(1,0));
    dirs.push_back(make_pair(0,-1));
    dirs.push_back(make_pair(-1,0));
    dirs.push_back(make_pair(0,1));

    vector<vector<char> > mat;
    vector<string> words;
    int n = 0;
    string line;
    bool read_word_mat = false;
    while (getline(cin, line)) {
        if (line.empty()) {
            read_word_mat = true;
        }
        else {
            if (!read_word_mat) {
                vector<char> row;
                for (int i=0; i<line.size(); ++i)
                    row.push_back(line[i]);
                mat.push_back(row);
            }
            else {
                words.push_back(line);
            }
        }
    }

    for (int i=0; i<words.size(); ++i) {
        pair<pair<int,int>,int> pos = find_word(mat, words[i]);

        if (pos.first.first != -1 && pos.first.second != -1) {
                cout << pos2letters(pos.first) << dir2letters(pos.second);
        }
    }
    cout << endl;


    return 0;
}
