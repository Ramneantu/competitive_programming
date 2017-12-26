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

#define USE_OPENCV 1

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


inline bool in_bounds(int i, int j, int n, int m) {
    return i >= 0 && i<n && j >= 0 && j < m;
}

void dfs(vector<vector<int> >& mat, int i, int j, int& label, IGRAY& gray) {

    stack<pair<int,int> > S;
    S.push({i,j});

    while (!S.empty()) {

        auto e = S.top();
        S.pop();
        int ii = e.first;
        int jj = e.second;

        if (mat[ii][jj] == -1 && gray.at(ii,jj) >= 255) {
            mat[ii][jj] = label;

            gray.at(ii,jj,0);
        }
        else 
            continue;

        for (auto n : neighbors) {
            if (in_bounds(ii+n.first, jj+n.second, mat.size(), mat[0].size())) {
                S.push({ii+n.first, jj+n.second});
            }
        }
    }
}



bool is_circle (int i, int j, vector<vector<int> >& viz, vector<vector<int> >& seg) {
    
    

    stack<pair<int,int> > S;
    S.push({i,j});
    viz[i][j] = 1;

    int min_c = INT_MAX;
    int max_c = INT_MIN;
    int min_r = INT_MAX;
    int max_r = INT_MIN;
    int area = 0;

    while (!S.empty ()) {

        auto e = S.top();
        S.pop();

        int ii = e.first;
        int jj = e.second;


        for (auto n : neighbors) {
            int ni = ii+n.first;
            int nj = jj+n.second;
            if (!in_bounds(ni, nj, viz.size(), viz[0].size())) {
    //            return false;
                continue;
            }

            if (viz[ni][nj] == 0 && seg[ni][nj] != -1) {
                S.push({ni,nj});
                viz[ni][nj] = 1;

                max_c = max(max_c, jj);
                min_c = min(min_c, jj);
                max_r = max(max_r, ii);
                min_r = min(min_r, ii);

                area++;

            }
        }
    }

    double r = min(max_c - min_c, max_r - min_r) / 2;
    double est_area = M_PI*r*r;
    double thresh = 2*M_PI*r * 4;
    /*
    cout << "est area: " << est_area << endl;
    cout << "cur area: " << area << endl;
    cout << "radius: " << r << endl;
    cout << "thresh: " << thresh << endl;
    cout << endl;
    */

    if (fabs(area-est_area) > thresh) {
        return false;
    }
    return true;
}


vector<vector<double> > laplace3x3
                            {
                                {-1, 0, 1},
                                {-2, 0, 2},
                                {-1, 0, 1}
                            };

int ksize = 3;
double sigma = 1;


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

void test_cross (int k) {

    for (int i=1; i<=k; ++i) {
        cout << "for k: " << k << endl;

        auto cr = get_cross(i,i);

        print_bin_mat(cr);

        cout << endl;
    }
}


int get_n_circles (IGRAY img) {

    double bg_val = img.at(10,10);
    //cout << "Intensity = " << bg_val << endl << endl;

    vector<vector<int> > seg(img.rows(), vector<int>(img.cols(), -1));
    int label = 1;
    int cols = img.cols();
    int rows = img.rows();
    for (int r = 0; r<rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (seg[r][c] == -1 && img.at(r,c) >= 255) { // not labeled
                //cout << "dfs " << r << "," << c << endl;
                dfs(seg, r, c, label, img);
                label++;
            }
        }
    }


    int n_circles = 0;
    vector<std::vector<int> > viz(img.rows(), vector<int>(img.cols(), 0));
    for (int r=0; r<img.rows(); ++r) {
        for (int c=0; c<img.cols(); ++c) {
            if (seg[r][c] != -1 && viz[r][c] == 0) {
                n_circles += is_circle(r,c,viz,seg);
            }
        }
    }

    return n_circles;
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


int find_optimal_n_circles (IGRAY img) {

    int k = 1;
    int n_circles = -1;

    //auto cross = get_cross(2,2);

    vector<vector<double> > cross = { 
                                        {0,   0,   0,   1,   0,  0, 0},
                                        {0,   0,   1,   1,   1,  0, 0},
                                        {0,   1,   1,   1,   1,  1, 0},
                                        {1,   1,   1,   1,   1,  1, 1},
                                        {0,   1,   1,   1,   1,  1, 0},
                                        {0,   0,   1,   1,   1,  0, 0},
                                        {0,   0,   0,   1,   0,  0, 0}};


    while (true) {
        //cout << "iteration: " << k << endl;
        show_img(img);
        img = img.erode(cross);
        int cur_n_circles = get_n_circles (img);
        cout << "#circles found: " << cur_n_circles << endl;
        if (cur_n_circles < n_circles) {
            //k--;
            break;
        }
        else {
            n_circles = cur_n_circles;
        }
        k++;
    }
    return n_circles;
}


int main(int argc, char** argv) {


    /**
     * Read image
     */
    IRGB img;
    img.read();


    /**
     * Write image to txt file.
     */
    #if 0
    auto pos = input_file.rfind('.');
    string output_file = input_file.substr(0, pos) + ".out";
    img.write(output_file);
    #endif

    /**
     * Convert to grayscale
     */
    //////cout << "Gray ..." << endl;
    IGRAY gray = rgb2gray(img);
    show_img(gray);

#ifdef USE_OPENCV
    vector<vector<double> > gaussian = gray.gaussian_kernel(ksize,sigma);
    #if 1
    /**
     * TEST: Test sobel against opencv implementation
     */
    //cout << "Sobel ..." << endl;

    for(int g=0; g<3; ++g) {
        gray = gray.convolve(gaussian);
        show_img(gray);
    }

    IGRAY img_sobel_x = gray.convolve(sobel_x);

    IGRAY img_sobel_y = gray.convolve(sobel_y);


    IGRAY img_sobel(gray.rows(), gray.cols());

    for (int r = 0; r < img_sobel.rows(); ++r) {
        for (int c = 0; c < img_sobel.cols(); ++c) {
            //if (img_sobel_x.at(r,c) > 255||img_sobel_y.at(r,c) > 255)
            //    //cout << "OVER 9000" << endl;
            //img_sobel.at(r,c, sqrt(0.5 * img_sobel_x.at(r,c) * img_sobel_x.at(r,c) + 0.5 * img_sobel_y.at(r,c) * img_sobel_y.at(r,c)));
            img_sobel.at(r,c, 0.5 * abs(img_sobel_x.at(r,c)) + 0.5 * abs(img_sobel_y.at(r,c)));
        }
    }
    //show_img(IGRAY_to_opencv(img_sobel), "mine");
    show_img(IGRAY_to_opencv(img_sobel_x), "x");
    show_img(IGRAY_to_opencv(img_sobel_y), "y");
    show_img(IGRAY_to_opencv(img_sobel), "sobel");

    IGRAY img_laplace = gray.convolve(laplace3x3);
    show_img(IGRAY_to_opencv(img_laplace), "laplace");    


    //cout << "DoG ..." << endl;
    IGRAY I1(gray.rows(), gray.cols());
    for (int r = 0; r < I1.rows(); ++r) {
        for (int c = 0; c < I1.cols(); ++c) {
            I1.at(r,c, gray.at(r,c));
        }
    }

    IGRAY I2 = I1.convolve(gaussian);

    for (int k = 1; k<=6; ++k) {
        IGRAY I3(I1.rows(), I1.cols());
        for (int r = 0; r < I1.rows(); ++r) {
            for (int c = 0; c < I1.cols(); ++c) {
                I3.at(r,c, I2.at(r,c) - I1.at(r,c));
            }
        }
        show_img(IGRAY_to_opencv(I3), "DoG");


        for (int r = 0; r < I1.rows(); ++r) {
            for (int c = 0; c < I1.cols(); ++c) {
                I1.at(r,c, I2.at(r,c));
            }
        }


        for (int r = 0; r < I2.rows(); ++r) {
            for (int c = 0; c < I2.cols(); ++c) {
                I2.at(r,c, I3.at(r,c));
            }
        }
    }


    // apply opencv sobel
    {
        #if 1
        Mat gray_opencv = IGRAY_to_opencv(gray);
        Mat grad;
        int scale = 1;
        int delta = 0;
        int ddepth = CV_16S;

        /// Generate grad_x and grad_y
         Mat grad_x, grad_y;
         Mat abs_grad_x, abs_grad_y;

         /// Gradient X
         //Scharr( src_gray, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT );
         Sobel( gray_opencv, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT );
         convertScaleAbs( grad_x, abs_grad_x );

         /// Gradient Y
         //Scharr( src_gray, grad_y, ddepth, 0, 1, scale, delta, BORDER_DEFAULT );
         Sobel( gray_opencv, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT );
         convertScaleAbs( grad_y, abs_grad_y );

         /// Total Gradient (approximate)
        addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad );

        show_img(grad, "sobel opencv");
        #endif
    }
    #endif
#endif



    /**
     * Erosion
     */
    //////cout << "Threshold ..." << endl;

    double bg = gray.at(10,10);
    ////cout << "bg: " << bg << endl;

    IGRAY erosion_gray = gray.threshold(bg, 255, IGRAY::THRESHOLD_TYPE::THRESH_BINARY_BACKGROUND);
    show_img(erosion_gray);

    vector<vector<double> > ellipse = { 
                                        {0,   0,   0,   1,   0,  0, 0},
                                        {0,   0,   1,   1,   1,  0, 0},
                                        {0,   1,   1,   1,   1,  1, 0},
                                        {1,   1,   1,   1,   1,  1, 1},
                                        {0,   1,   1,   1,   1,  1, 0},
                                        {0,   0,   1,   1,   1,  0, 0},
                                        {0,   0,   0,   1,   0,  0, 0}};

    /**
     * Get nr of cicles
     */
    //cout << get_n_circles (erosion_gray) << endl;
    cout << find_optimal_n_circles (erosion_gray) << endl;


    return 0;
}
