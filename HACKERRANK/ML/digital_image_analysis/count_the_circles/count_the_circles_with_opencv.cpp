#include "common_opencv.hpp"

int main (int argc, char** argv) {


    Mat img = imread(argv[1]);
    //show_img(img);
    Mat gray;
    cvtColor(img, gray, CV_RGB2GRAY);
    //show_img(gray);
    GaussianBlur(gray, gray, Size(9, 9), 2, 2);
    show_img(gray);


    Mat grad;
    int scale = 1;
    int delta = 0;
    int ddepth = CV_16S;

    /// Generate grad_x and grad_y
     Mat grad_x, grad_y;
     Mat abs_grad_x, abs_grad_y;

     /// Gradient X
     //Scharr( src_gray, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT );
     Sobel( gray, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT );
     //convertScaleAbs( grad_x, abs_grad_x );

     /// Gradient Y
     //Scharr( src_gray, grad_y, ddepth, 0, 1, scale, delta, BORDER_DEFAULT );
     Sobel( gray, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT );
     //convertScaleAbs( grad_y, abs_grad_y );

     /// Total Gradient (approximate)
    addWeighted( grad_x, 0.5, grad_y, 0.5, 0, grad );

     show_img( grad );

 //threshold( grad, gray, 15, 255,cv::THRESH_BINARY);

 //show_img( grad );


#if 0
     /// Establish the number of bins
 int histSize = 256;

 /// Set the ranges ( for B,G,R) )
 float range[] = { 0, 256 } ;
 const float* histRange = { range };

 bool uniform = true; bool accumulate = false;

 Mat g_hist;
  calcHist( &grad, 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate );

  // Draw the histograms for B, G and R
int hist_w = 512; int hist_h = 400;
int bin_w = cvRound( (double) hist_w/histSize );

Mat histImage( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );

/// Normalize the result to [ 0, histImage.rows ]
normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );

/// Draw for each channel
for( int i = 1; i < histSize; i++ )
{
    line( histImage, Point( bin_w*(i-1), hist_h - cvRound(g_hist.at<float>(i-1)) ) ,
                     Point( bin_w*(i), hist_h - cvRound(g_hist.at<float>(i)) ),
                     Scalar( 255, 0, 0), 2, 8, 0  );
}

show_img(histImage);
#endif



    /// Apply the Hough Transform to find the circles
    std::vector<Vec3f> circles;
    HoughCircles(gray, circles, CV_HOUGH_GRADIENT, 2, 20, 50, 100, 0, 250);

    for( std::size_t i = 0; i < circles.size(); i++ )
    {
        Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        int radius = cvRound(circles[i][2]);
        // circle center
        circle(img, center, 3, Scalar(0,0,0), -1, 8, 0 );
        // circle outline
        circle(img, center, radius, Scalar(0,0,0), 3, 8, 0 );
     }
     show_img(img);


    cout << circles.size();

    return 0;
}
