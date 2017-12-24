#ifndef COUNT_THE_CIRCLES_HPP
#define COUNT_THE_CIRCLES_HPP

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
#include <cmath>

using namespace std;

#define DEBUG 1
#define DBG(code) { if (DEBUG) { do { code }while(0); } }



/**
 * Kernels
 */
vector<vector<double> > sobel_x =
                            {
                                {-1, 0, 1},
                                {-2, 0, 2},
                                {-1, 0, 1}
                            };

vector<vector<double> > sobel_y = {
                                {-1, -2, -1},
                                { 0,  0,  0},
                                { 1,  2,  1}
                            };


/**
 * Image RGB class
 */
class IRGB {
private:
    size_t rows_;
    size_t cols_;
    vector<vector<vector<int> > > mat_;

public:
    IRGB () {}

    IRGB (size_t rows, size_t cols) : rows_(rows), cols_(cols) {
        init (rows_, cols_);
    }

    size_t rows () { return rows_; }

    size_t cols() { return cols_; }

    void write (string filename) {

        ofstream fout(filename);

        fout << this->rows_ << " " << this->cols_ << endl;

        for (int r = 0; r<rows_; ++r) {
            for (int c = 0; c<cols_; ++c) {
                auto rgb = this->at(r,c);
                fout << rgb[0] << "," << rgb[1] << "," << rgb[2] << " ";
            }
            fout << endl;
        }

        fout.close();
    }

    void read (string filename) {

        ifstream fin (filename);

        int h, w;
        fin >> h >> w;

        init (h,w);

        for (int r = 0; r < h; r++) {
            for (int c = 0; c < w; c++) {
                string tok;
                fin >> tok;
                istringstream iss(tok);
                vector<int> v;
                int val;
                while (iss >> val) {
                    v.push_back(val);
                    if (iss.peek() == ',') {
                        iss.ignore();
                    }
                }

                // necessary to swap v[2] and v[2], because Hackerrank input is BGR, but we want RGB
                this->at(r,c,v[2], v[1], v[0]);
            }
        }
        fin.close();
    }


    void read () {

    }

    void init (size_t rows, size_t cols) {
        rows_ = rows;
        cols_ = cols;
        mat_.resize(rows_, vector<vector<int> >(cols_,vector<int>(3,0)));
    }

    vector<int> at (int r, int c) {
        return mat_[r][c];
    }

    void at (int r, int c, int red, int green, int blue) {
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

    enum class THRESHOLD_TYPE : int
    {
        THRESH_BINARY = 0,
        THRESH_BINARY_INV
    };

    
    IGRAY() {}

    IGRAY(size_t rows, size_t cols) : rows_(rows), cols_(cols) {
        this->init(rows_, cols_);
    }

    size_t rows () { return rows_; }

    size_t cols () { return cols_; }

    inline bool in_bounds(int i, int j) {
        return i >= 0 && i<this->rows_ && j >= 0 && j < this->cols_;
    }


    void init (size_t rows, size_t cols) {
        rows_ = rows;
        cols_ = cols;
        mat_.resize (rows_, vector<double>(cols_, 0));
    }

    double at (int r, int c) {
        return mat_[r][c];
    }

    void at (int r, int c, double g) {
        mat_[r][c] = g;
    }

    vector<vector<double> > gaussian_kernel(int ksize, double sigma) {
        vector<vector<double> > gauss(ksize, vector<double>(ksize,0));
        double sum = 0, s = 2 * sigma * sigma;

        int ksize2 = ksize / 2;

        for (int x = -ksize2; x <= ksize2; x++) {
            for (int y = -ksize2; y <= ksize2; y++) {
                sum += (gauss[x + ksize2][y + ksize2] = exp(-(x * x + y * y) / s) / s / M_PI);
            }
        }

        for (auto& row : gauss)
            for (auto& x : row)
                x /= sum;

        return gauss;
    }

    /**
     * Convolves this.mat_ with kernel. Uses Border reflection for padding.
     */
    IGRAY convolve (vector<vector<double> > kernel) {
        IGRAY res(this->rows_, this->cols_);

        int kh = kernel.size();
        int kh2 = kh / 2;
        int kw = kernel[0].size();
        int kw2 = kw / 2;

        for (int r = 0; r < this->rows_; ++r) {
            for (int c = 0; c < this->cols_; ++c) {
                double sum = 0;
                for (int i = -kh2; i<=kh2; ++i) {
                    for (int j = -kw2; j<=kw2; ++j) {
                        int ii = i + kh2;
                        int jj = j + kw2;
                        int rr = r + i;
                        int cc = c + j;
                        if (rr < 0) rr = -rr;
                        if (rr >= this->rows_) rr = rr - 2 * abs(i);
                        if (cc < 0) cc = -cc;
                        if (cc >= this->cols_) cc = cc - 2 * abs(j);

                        sum += kernel[ii][jj] * mat_[rr][cc];
                    }
                }
                res.at(r,c,sum);
            }
        }

        return res;
    }


    IGRAY erosion(const vector<vector<double> >& pattern) {

      int pn = pattern.size();
      int pm = pattern[0].size();

      IGRAY res(this->rows_, this->cols_);

      for(int r=0; r<this->rows_; ++r) {
        for(int c=0; c<this->cols_; ++c) {
          double new_val = 1;
          for(int k=-pn/2; k<=pn/2; ++k) {
            for(int l=-pm/2; l<=pm/2; ++l) {
              int rr = r + k;
              int cc = c + l;
              if (!in_bounds(rr,cc) || (this->mat_[rr][cc] != 1)){
                  new_val = 0;
              }
            }
          }
          res.at(r,c,new_val);
        }
      }
      return res;
    }


    IGRAY threshold (double threshold, double max_value, THRESHOLD_TYPE type = THRESHOLD_TYPE::THRESH_BINARY) {

        IGRAY res(this->rows_, this->cols_);        

        for (int r = 0; r < this->rows_; ++r)
        {
            for (int c = 0; c < this->cols_; ++c)
            {
                if (type == THRESHOLD_TYPE::THRESH_BINARY)
                {
                    if (this->mat_[r][c] > threshold)
                    {
                        res.at(r,c,max_value);
                    }
                    else {
                        res.at(r,c,0);
                    }
                }
                else if (type == THRESHOLD_TYPE::THRESH_BINARY_INV)  
                {
                    if (this->mat_[r][c] > threshold)
                    {
                        res.at(r,c,0);
                    }
                    else {
                        res.at(r,c,max_value);
                    }
                }
            }
        }

        return res;
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


#endif // COUNT_THE_CIRCLES_HPP