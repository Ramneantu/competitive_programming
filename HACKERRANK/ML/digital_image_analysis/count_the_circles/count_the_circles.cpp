#include "count_the_circles.hpp"

#define USE_OPENCV 1
    #ifdef USE_OPENCV
    #include "common_opencv.hpp"
#endif


vector<vector<double> > laplace3x3
                            {
                                {-1, 0, 1},
                                {-2, 0, 2},
                                {-1, 0, 1}
                            };

int ksize = 3;
double sigma = 1;

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
    show_img(gray);


    /**
     * Erosion
     */
    cout << "Threshold ..." << endl;
    IGRAY erosion_gray = gray.threshold(230, 255, IGRAY::THRESHOLD_TYPE::THRESH_BINARY_INV);
    show_img(erosion_gray);

#if 0
    cout << "Erosion ..." << endl;
    int erosion_size = 2;
    int erosion_iterations = 5;
    Mat element;
    for (int i=0; i<erosion_iterations; ++i) {
        cout << "iteration: " << i << " / " << erosion_iterations << endl;

        if (i <= erosion_iterations / 3) {
            cout << "Apply CROSS ..." << endl;
            element = getStructuringElement(
                                                MORPH_CROSS, 
                                                Size(2*erosion_size + 1, 2*erosion_size+1),
                                                Point(erosion_size, erosion_size));
        }
        else {
            cout << "Apply ELLIPSE ..." << endl;
            element = getStructuringElement(
                                                MORPH_ELLIPSE, 
                                                Size(2*erosion_size + 1, 2*erosion_size+1),
                                                Point(erosion_size, erosion_size));
        }
        cout << element << endl;

        //show_img(element);
        erode(erosion_gray, erosion_gray, element);
        show_img(erosion_gray);
    }
    cout << "Result after " << erosion_iterations << " erosion iterations" << endl;
    show_img(erosion_gray);
    #endif





    uchar background_val = gray.at(20,30);
    cout << background_val << endl;

    for (int r = 0; r < gray.rows(); ++r) {
        for (int c = 0; c < gray.cols(); ++c) {
            if (abs(gray.at(r,c)-background_val) <= 10) {
                gray.at(r,c,255);
            }
        }
    }
    show_img(IGRAY_to_opencv(gray), "flood");


    auto rgb = img.at(50,70);
    cout << rgb[0] << " " << rgb[1] << " " << rgb[2] << endl;

    for (int r = 0; r < gray.rows(); ++r) {
        for (int c = 0; c < gray.cols(); ++c) {
            auto img_rgb = img.at(r,c);
            if (abs(img_rgb[0]-rgb[0]) <= 10 && abs(img_rgb[1]-rgb[1]) <= 10 && abs(img_rgb[2]-rgb[2]) <= 10) {
                gray.at(r,c,0);
            }
        }
    }
    show_img(IGRAY_to_opencv(gray), "flood2");



#ifdef USE_OPENCV
    #if 1
    /**
     * TEST: compare own gaussian filter with opencv implementation.
     */
    Mat gaussian_x = getGaussianKernel(ksize, sigma);
    Mat gaussian_y = getGaussianKernel(ksize, sigma);
    Mat gaussian_opencv = gaussian_x * gaussian_y.t();

    vector<vector<double> > gaussian = gray.gaussian_kernel(ksize,sigma);
    assert(gaussian.size() == ksize && gaussian[0].size() == ksize);

    for (int r = 0; r < ksize; ++r) {
        for (int c = 0; c < ksize; ++c) {
            assert(fabs(gaussian_opencv.at<double>(Point(r,c)) - gaussian[r][c]) <= 1e-3);
        }
    }
    #endif
#endif



#ifdef USE_OPENCV
    #if 1
    /**
     * Apply gaussian blur. Compare to opencv implementation.
     */
    
    cout << "Gaussian blur ...\n";
    IGRAY gaussian_gray = gray.convolve(gaussian);
    Mat gaussian_gray_opencv = IGRAY_to_opencv(gaussian_gray);
    show_img(gaussian_gray_opencv, "mine");

    {
        Mat src = IGRAY_to_opencv(gray);
        Mat dst = src.clone();
        GaussianBlur(src, dst, Size(ksize, ksize), sigma, sigma);

        Mat diff = dst.clone();
        for (int r = 0; r < gaussian_gray_opencv.rows; ++r) {
            for (int c = 0; c < gaussian_gray_opencv.cols; ++c) {
                diff.at<uchar>(r,c) = uchar(fabs(gaussian_gray_opencv.at<uchar>(r,c)-dst.at<uchar>(r,c)));
            }
        }
        show_img(dst, "opencv");
        show_img(diff, "diff");
    }



    #endif
#endif



#ifdef USE_OPENCV
    #if 1
    /**
     * TEST: Test sobel against opencv implementation
     */
    cout << "Sobel ..." << endl;
    IGRAY img_sobel_x = gaussian_gray.convolve(sobel_x);

    IGRAY img_sobel_y = gaussian_gray.convolve(sobel_y);


    IGRAY img_sobel(gaussian_gray.rows(), gaussian_gray.cols());

    for (int r = 0; r < img_sobel.rows(); ++r) {
        for (int c = 0; c < img_sobel.cols(); ++c) {
            //if (img_sobel_x.at(r,c) > 255||img_sobel_y.at(r,c) > 255)
            //    cout << "OVER 9000" << endl;
            //img_sobel.at(r,c, sqrt(0.5 * img_sobel_x.at(r,c) * img_sobel_x.at(r,c) + 0.5 * img_sobel_y.at(r,c) * img_sobel_y.at(r,c)));
            img_sobel.at(r,c, 0.5 * abs(img_sobel_x.at(r,c)) + 0.5 * abs(img_sobel_y.at(r,c)));
        }
    }
    //show_img(IGRAY_to_opencv(img_sobel), "mine");
    show_img(IGRAY_to_opencv(img_sobel_x), "x");
    show_img(IGRAY_to_opencv(img_sobel_y), "y");
    show_img(IGRAY_to_opencv(img_sobel), "sobel");

    IGRAY img_laplace = gaussian_gray.convolve(laplace3x3);
    show_img(IGRAY_to_opencv(img_laplace), "laplace");    


    cout << "DoG ..." << endl;
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





    return 0;
}
