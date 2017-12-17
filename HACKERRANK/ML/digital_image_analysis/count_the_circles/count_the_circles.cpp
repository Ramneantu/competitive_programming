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
    /**
     * TEST: read image just wroten, and show with opencv.
     */
    {
        Mat img = read_IRGB_to_opencv(output_file);
        show_img(img);
    }
#endif


#ifdef USE_OPENCV
    /**
     * TEST: display grayscale image with opencv.
     */
    {
        Mat gray_opencv = IGRAY_to_opencv(gray);
        show_img(gray_opencv);
    }
#endif

    


    return 0;
}
