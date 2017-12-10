#include <iostream>
#include <fstream>
#include <utility>
#include <map>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <sstream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.hpp>

#define DEBUG 1
#define DBG(code) { if (DEBUG) { do { code }while(0); } }


/**
* Typedefs
*/
typedef std::vector<std::vector<std::vector<double> > > IRGB;
typedef std::vector<std::vector<double> > IGRAY;
typedef std::vector<std::vector<int> > IBIN;



inline std::vector<std::pair<int,int> > get_4_neighbours(int i, int j) {
    return std::vector<std::pair<int,int> > {
        {i,j-1},
        {i-1,j},
        {i,j+1},
        {i+1,j}
    };
}

inline std::vector<std::pair<int,int> > get_8_neighbours(int i, int j) {
    return std::vector<std::pair<int,int> > {
        {i,j-1},
        {i-1,j-1},
        {i-1,j},
        {i-1,j+1},
        {i,j+1},
        {i+1,j+1},
        {i+1,j},
        {i+1,j-1}
    };
}


bool in_bounds(int n, int m, int i, int j) {
  return i >= 0 && i < n && j >= 0 && j < m;
}


IRGB read_rgb() {

    // input file contains BGR values, make sure to read them as RGB
    int r, c;
    std::cin >> r >> c;

    IRGB img;
    img.resize(r, std::vector<std::vector<double> > (c, std::vector<double>()));

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            std::string tok;
            std::cin >> tok;
            std::istringstream iss(tok);
            double v;
            while (iss >> v) {
                img[i][j].push_back(v);
                if (iss.peek() == ',') {
                    iss.ignore();
                }
            }
            std::swap(img[i][j][0], img[i][j][2]);
        }
    }
    return img;
}

IGRAY rgb2gray(const IRGB& img) {

    int r = img.size();
    int c = img[0].size();

    IGRAY gray(r, std::vector<double>(c));

    for (int i=0; i<r; ++i) {
        for (int j=0; j<c; ++j) {
            //gray[i][j] = 0.21 * img[i][j][0] + 0.72 * img[i][j][1] + 0.07 * img[i][j][2];
            gray[i][j] = 0.299 * img[i][j][0] + 0.587 * img[i][j][1] + 0.114 * img[i][j][2];
        }
    }
    return gray;
}



IGRAY bin_threshold(IGRAY& gray, double threshold) {
    IGRAY res(gray.size(), std::vector<double>(gray[0].size()));

    for (int r = 0; r < gray.size(); ++r) {
        for (int c = 0; c < gray[0].size(); ++c) {
            if (gray[r][c] <= threshold) {
                res[r][c] = 1;
            }
            else {
                res[r][c] = 0;
            }
        }
    }
    return res;
}


void plot(const IGRAY& gray, double threshold, int h=-1, int w=-1, bool invert=false) {

    int r = (h == -1 ? gray.size() : h);
    int c = (w == -1 ? gray[0].size() : w);

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (gray[i][j] <= threshold) {
                if (invert) {
                    std::cout << " ";
                }
                else {
                    std::cout << "X";
                }
            }
            else {
                if (invert) {
                    std::cout << "X";
                }
                else {
                    std::cout << " ";
                }
            }
        }
        std::cout << std::endl;
    }
}



void plot(const IGRAY& img) {
    for (int r = 0; r < img.size(); r++) {
        for (int c = 0; c < img[0].size(); c++) {
            std::cout << img[r][c] << " ";
        }
        std::cout << std::endl;
    }
}

void plot(const std::vector<std::vector<int> >& img) {
    for (int r = 0; r < img.size(); r++) {
        for (int c = 0; c < img[0].size(); c++) {
            std::cout << img[r][c] << " ";
        }
        std::cout << std::endl;
    }
}
