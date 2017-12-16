#include <iostream>
#include <fstream>
#include <utility>
#include <map>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <sstream>
#include <queue>
using namespace std;

#define DEBUG 1
#define DBG(code) { if (DEBUG) { do { code }while(0); } }


class IRGB {
private:
    size_t rows_;
    size_t cols_;
    vector<vector<vector<uint8_t> > > mat_;

public:
    IRGB () {}

    IRGB (size_t rows, size_t cols) : rows_(rows), cols_(cols) {
        init (rows_, cols_);
    }

    size_t rows() { return rows_; }

    size_t cols() { return cols_; }

    void read (string filename) {

    }

    void read () {

    }

    void init (size_t rows, size_t cols) {
        mat_.resize(rows_, vector<vector<uint8_t> >(cols_,vector<uint8_t>(3,0)));
    }

    vector<uint8_t> at (int r, int c) {
        return mat_[r][c];
    }

    void at (int r, int c, uint8_t red, uint8_t green, uint8_t blue) {
        mat_[r][c][0] = red;
        mat_[r][c][1] = green;
        mat_[r][c][2] = blue;
    }

};

class IGRAY {
private:
    size_t rows_;
    size_t cols_;
    vector<vector<double> > mat_;

public:
    IGRAY () {}

    IGRAY (size_t rows, size_t cols) : rows_(rows), cols_(cols) {
        init (rows_, cols_);
    }

    size_t rows () { return rows_; }

    size_t cols () { return cols_; }

    void init (size_t rows, size_t cols) {
        mat_.resize (rows_, vector<double>(cols_, 0));
    }

    double at (int r, int c) {
        return mat_[r][c];
    }

    void at (int r, int c, double g) {
        mat_[r][c] = g;
    }

};

IGRAY rgb2gray (IRGB& img) {
    IGRAY gray(img.rows(), img.cols());

    for (int r = 0; r < img.rows(); ++r) {
        for (int c = 0; c < img.cols(); ++c) {
            auto rgb = img.at(r,c);
            gray.at(r,c, 0.299 * rgb[0]+ 0.587 * rgb[1] + 0.114 * rgb[2]);
        }
    }
    return gray;
}




int main() {


    return 0;
}
