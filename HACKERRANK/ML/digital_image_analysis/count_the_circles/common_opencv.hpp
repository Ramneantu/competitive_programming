#ifndef COMMON_OPENCV_HPP
#define COMMON_OPENCV_HPP

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

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.hpp>

#include "count_the_circles.hpp"

using namespace cv;
using namespace std;


void show_img(const Mat& img) {
    imshow("window", img);
    waitKey(0);
}


Mat IGRAY_to_opencv(IGRAY& gray) {

	Mat img(gray.rows(), gray.cols(), CV_8U);

	for (int r = 0; r < gray.rows(); ++r) {
		for (int c = 0; c < gray.cols(); ++c) {
			img.at<uchar>(Point(r,c)) = gray.at(r,c);
		}
	}
	return img;
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

#endif // COMMON_OPENCV_HPP