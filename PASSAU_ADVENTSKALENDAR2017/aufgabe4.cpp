#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

#define SOUTH 0
#define WEST 1
#define NORTH 2
#define EAST 3

vector<pair<int,int> > dirs {{1,0},{0,-1},{-1,0},{0,1}};

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
    else (d == EAST) {
        return 'O';
    }
}

string pos2letters(pair<int,int> pos) {
    return char((pos.first+1) + int('A')) + char((pos.second+1) + int('A'));
}


pair<pair<int,int>,int> find_word(const vector<vector<char> >& mat, string w) {

    for (int i=0; i<mat.size(); ++i) {
        for (int j=0; j<mat[0].size(); ++j) {
            for (int i)
            int res = find_word_helper(const vector<vector<char> >& mat, string w, int i, int r, int c);
        }
    }
}


int main () {


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

    /*
    for (int i=0; i<mat.size(); ++i) {
        for (int j=0; j<mat[0].size(); ++j) {
            cout << mat[i][j];
        }
        cout << endl;
    }

    cout << endl;
    for (int i=0; i<words.size(); ++i) {
        cout << words[i] << endl;
    }
    */

    for (int i=0; i<words.size(); ++i) {
        pair<pair<int,int>,int> pos = find_word(mat, words[i]);

        if (pos.first.first != -1 && pos.first.second != -1) {
                cout << pos2letters(pos) << dir2letters(pos.second) << endl;
        }
    }


    return 0;
}
