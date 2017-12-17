#include "count_the_circles.hpp"

#define USE_OPENCV 1
#ifdef USE_OPENCV
#include "common_opencv.hpp"
#endif

int main(int argc, char** argv) {

    /**
     * Read image
     */
    IRGB img;
    string input_file = argv[1];
    img.read(input_file);


    /**
     * Write image to txt file.
     */
    auto pos = input_file.rfind('.');
    string output_file = input_file.substr(0, pos) + ".out";
    img.write(output_file);


    /**
     * Convert to grayscale
     */
    
    IGRAY gray = rgb2gray(img);


#ifdef USE_OPENCV
    #if 0
    /**
     * TEST: read image just wroten, and show with opencv.
     */
    {
        Mat img = read_IRGB_to_opencv(output_file);
        show_img(img);
    }
    #endif
#endif


#ifdef USE_OPENCV
    #if 0
    /**
     * TEST: display grayscale image with opencv.
     */
    {
        Mat gray_opencv = IGRAY_to_opencv(gray);
        show_img(gray_opencv);
    }
    #endif
#endif


#ifdef USE_OPENCV
    #if 1
    /**
     * TEST: compare own gaussian filter with opencv implementation.
     */
    int ksize = 7;
    double sigma = 2;
    Mat gaussian_x = getGaussianKernel(ksize, sigma);
    Mat gaussian_y = getGaussianKernel(ksize, sigma);
    Mat gaussian_opencv = gaussian_x * gaussian_y.t();

    auto gaussian_mine = gray.gaussian_kernel(ksize,sigma);

    for (int r = 0; r < ksize; ++r) {
        for (int c = 0; c < ksize; ++c) {
            assert(fabs(gaussian_opencv.at<double>(Point(r,c)) - gaussian_mine[r][c]) <= 1e-3);
        }
    }
    #endif
#endif



    return 0;
}
