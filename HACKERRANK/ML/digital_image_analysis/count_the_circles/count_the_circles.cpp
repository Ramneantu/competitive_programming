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
#include <stack>
#include <climits>
using namespace std;

#define DEBUG 1
#define DBG(code) { if (DEBUG) { do { code }while(0); } }

//#define USE_OPENCV 1

/**
 * Kernels
 */
vector<vector<double> > laplace3x3
                            {
                                {-1, 0, 1},
                                {-2, 0, 2},
                                {-1, 0, 1}
                            };


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


inline bool in_bounds(int i, int j, int n, int m) {
    return i >= 0 && i<n && j >= 0 && j < m;
}


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

        int h, w;
        cin >> h >> w;

        init (h,w);

        for (int r = 0; r < h; r++) {
            for (int c = 0; c < w; c++) {
                string tok;
                cin >> tok;
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





/**
 * Grayscale image class
 */
class IGRAY {
private:
    size_t rows_;
    size_t cols_;
    vector<vector<double> > mat_;


public:

    enum class THRESHOLD_TYPE : int
    {
        THRESH_BINARY = 0,
        THRESH_BINARY_INV,
        THRESH_BINARY_BACKGROUND,
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



    IGRAY erode(const vector<vector<double> >& pattern) {

      int pn = pattern.size();
      int pm = pattern[0].size();

      IGRAY res(this->rows_, this->cols_);

      for(int r=0; r<this->rows_; ++r) {
        for(int c=0; c<this->cols_; ++c) {
          double new_val = 255;
          for(int k=-pn/2; k<=pn/2; ++k) {
            for(int l=-pm/2; l<=pm/2; ++l) {
              int rr = r + k;
              int cc = c + l;
              if (!in_bounds(rr,cc) || (this->mat_[rr][cc] != 255)){
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
                else if (type == THRESHOLD_TYPE::THRESH_BINARY_BACKGROUND) {
                    if (this->mat_[r][c] == threshold) {
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


vector<pair<int,int> > neighbors {{0,-1}, {-1,-1}, {-1,0}, {-1,1}, {0,1}, {1,1}, {1,0}, {1,-1}};


vector<vector<double> > get_cross (int h2, int w2) {
    int h = 2*h2 + 1;
    int w = 2*w2 + 1;
    vector<vector<double> > res (h, vector<double>(w,0));

    for (int r = 0; r < h; ++r) {
        res[r][w2] = 1;
    }

    for (int c = 0; c < w; ++c) {
        res[h2][c] = 1;
    }
    return res;
}


vector<vector<double> > get_ellipse (int h2, int w2) {
    int h = 2*h2 + 1;
    int w = 2*w2 + 1;
    vector<vector<double> > res (h, vector<double>(w,0));

    for (int c = 0; c < w; ++c) {
        res[h2][c] = 1;
    }

    for (int r=0; r<h2; ++r) {
        for (int c = w2-r; c < w2+r; ++c) {
            res[r][c] = 1;
        }
    }

    return res;
}


void print_bin_mat(vector<vector<double> >& mat) {
    for (int i = 0; i<mat.size(); ++i) {
        for (int j = 0; j<mat[0].size(); ++j) {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
}


#ifdef USE_OPENCV
    #include <opencv2/core/core.hpp>
    #include <opencv2/highgui/highgui.hpp>
    #include <opencv/cv.hpp>

    using namespace cv;

    void show_img(const Mat& img, string win = "window") {
        imshow(win, img);
        waitKey(0);
    }

    Mat IGRAY_to_opencv(IGRAY& gray) {

        Mat img(gray.rows(), gray.cols(), CV_8UC1);

        for (int r = 0; r < gray.rows(); ++r) {
            for (int c = 0; c < gray.cols(); ++c) {
                img.at<uchar>(r,c) = uchar(abs(gray.at(r,c)) > 255 ? 255 : abs(gray.at(r,c)));
            }
        }
        return img;
    }

    void show_img (IGRAY& img, string win = "window") {
        show_img (IGRAY_to_opencv(img));
    }


    Mat IRGB_to_opencv(IRGB& img) {

        Mat image(img.rows(), img.cols(), CV_8UC3, Scalar(0,0,0));

        for (int r = 0; r < img.rows(); ++r) {
            for (int c = 0; c < img.cols(); ++c) {
                auto rgb = img.at(r,c);
                image.at<Vec3b>(Point(r,c))[0] = rgb[0];
                image.at<Vec3b>(Point(r,c))[1] = rgb[1];
                image.at<Vec3b>(Point(r,c))[2] = rgb[2];
            }
        }
        return image;   
    }

    void show_img (IRGB& img, string win = "window") {
        show_img (IRGB_to_opencv(img));
    }


    Mat read_IRGB_to_opencv (string filename) {

        ifstream fin(filename);

        int h, w;
        fin >> h >> w;
        IRGB img;

        img.read(filename);

        fin.close();

        return IRGB_to_opencv(img);
    }
#endif // USE_OPENCV



IGRAY copy_img (IGRAY& img) {
    IGRAY new_img (img.rows(), img.cols());

    for (int r=0; r<img.rows(); ++r) {
        for (int c = 0; c < img.cols(); ++c) {
            new_img.at(r,c,img.at(r,c));
        }
    }
    return new_img;
}


void watershed_maxima(IGRAY& img, IGRAY& gray) {

    vector<vector<int> > viz(img.rows(), vector<int>(img.cols(), 0));
    //queue<pair<pair<int,int>,double> > Q;
    priority_queue<pair<double, pair<int,int> >, vector<pair<double, pair<int,int> > >, greater<pair<double, pair<int,int> > > > pq;

    vector<vector<double> > dist(img.rows(), vector<double>(img.cols(), INT_MAX));

    for (int r = 0; r < img.rows(); ++r) {
        for (int c = 0; c < img.cols(); ++c) {
            if (img.at(r,c) == 0) {
                viz[r][c] = 1;
                for (auto n : neighbors) {
                    int nr = r+n.first;
                    int nc = c+n.second;

                    if (in_bounds(nr,nc,img.rows(), img.cols())) {
                        if (img.at(nr,nc) == 255) {
                            //Q.push({{r,c},0});
                            pq.push({0,{r,c}});
                            dist[r][c] = 0;
                            break;
                        }
                    }
                }
            }
        }
    }

    while(!pq.empty()){
        auto e = pq.top();
        pq.pop();
        double d = e.first;
        int i = e.second.first;
        int j = e.second.second;
        if(d == dist[i][j]){

            for (auto n : neighbors) {
                int ni = i+n.first;
                int nj = j+n.second;
                if (in_bounds(ni,nj,gray.rows(), gray.cols()) && img.at(ni,nj) == 255) {

                    double w = sqrt((i-ni)*(i-ni) + (j-nj)*(j-nj));

                    if (dist[i][j] + w < dist[ni][nj]) {
                        dist[ni][nj] = dist[i][j] + w;
                        gray.at(ni,nj, (1 * int(dist[ni][nj])) % 256);
                        pq.push({dist[ni][nj], {ni, nj}});
                    }
                }
            }
        }
    }
}

inline double l2(double x, double y, double q, double r) {
    return sqrt((x-q)*(x-q) + (y-r)*(y-r));
}

typedef pair<double,double> DD;

inline double l2 (DD a, DD b) {
    return l2 (a.first, a.second, b.first, b.second);
}


inline DD merge (DD a, DD b) {
    DD m;
    m.first = (a.first + b.first) * 0.5;
    m.second = (a.second + b.second) * 0.5;

    return m;
}


void draw_maxi(IGRAY& gray, map<pair<double,double>, bool>& maxi) {
    for (auto r : maxi) {
        int i = r.first.first;
        int j = r.first.second;
        gray.at(i,j,255);

    }
}


int find_n_circles(IGRAY& img, int ksize) {

    IGRAY gray (img.rows(), img.cols());
    for (int r = 0; r < img.rows(); ++r) {
        for (int c = 0; c < img.cols(); ++c) {
            gray.at(r,c,img.at(r,c));
        }
    }

    watershed_maxima(img, gray);

    int kh2 = ksize / 2;
    int kw2 = ksize / 2;

    map<pair<double,double>, bool> maxi;

    IGRAY dilated_gray (gray.rows(), gray.cols());

    /**
     * Find local maximas by comparing dilated img with the original img.
     */
    for (int r = 0; r<gray.rows(); ++r) {
        for (int c = 0; c < gray.cols(); ++c) {

            if (gray.at(r,c) > 0) {
                double maxim = gray.at(r,c);
                for (int i = -kh2; i<=kh2; ++i) {
                    for (int j = -kw2; j<=kw2; ++j) {
                        int rr = r + i;
                        int cc = c + j;
                        if (in_bounds(rr,cc,gray.rows(), gray.cols())) {
                            if (maxim < gray.at(rr,cc)) {
                                maxim = gray.at(rr,cc);
                            }
                        }
                        else {
                            maxim = INT_MAX;
                        }
                    }
                }
                dilated_gray.at(r,c,maxim);
            }
        }
    }

    // local maximas are pixels in dilated img which are equal to ones in img
    for (int r = 0; r<gray.rows(); ++r) {
        for (int c = 0; c < gray.cols(); ++c) {
            if (gray.at(r,c) > 0) {
                if (gray.at(r,c) == dilated_gray.at(r,c)) {
                    maxi[{r,c}] = true;
                }
            }
        }
    }

    vector<pair<double,double> > res;
    while (true) {
        bool merged = false;

        for (auto k : maxi) {
            for (auto l : maxi) {
                if (k.first != l.first) {
                    double d = l2 (k.first, l.first);

                    if (d < 30) {
                        merged = true;
                        auto m = merge (k.first, l.first);

                        maxi.erase(l.first);
                        maxi.erase(k.first);
                        maxi[m] = true;
                        break;
                    }
                }
            }
            if (merged)
                break;
        }

        if(!merged)
            break;
    }
    return maxi.size();
}


int main(int argc, char** argv) {


    /**
     * Read image
     */
    IRGB img;
    img.read();

    /**
     * Convert to grayscale
     */
    IGRAY gray = rgb2gray(img);


    /**
     * Threshold
     */
    double bg = gray.at(10,10);
    IGRAY erosion_gray = gray.threshold(bg, 255, IGRAY::THRESHOLD_TYPE::THRESH_BINARY_BACKGROUND);

    cout << find_n_circles(erosion_gray, 15) << endl;

    return 0;
}
