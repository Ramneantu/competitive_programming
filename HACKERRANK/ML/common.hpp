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


/**
* Typedefs
*/
typedef std::vector<std::vector<std::vector<double> > > IRGB;
typedef std::vector<std::vector<double> > IGRAY;
typedef std::vector<std::vector<int> > IBIN;


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
