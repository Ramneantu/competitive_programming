#include "common_opencv.hpp"

using namespace std;


vector<pair<int,int> > neighbors {{0,-1}, {-1,-1}, {-1,0}, {-1,1}, {0,1}, {1,1}, {1,0}, {1,-1}};


inline bool in_bounds(int i, int j, int n, int m) {
    return i >= 0 && i<n && j >= 0 && j < m;
}

int intensity_at(int i, int j, Mat gray) {
    Scalar intensity = gray.at<uchar>(i,j);
    int val = intensity.val[0];
    return val;
}


void dfs(vector<vector<int> >& mat, int i, int j, int& label, Mat gray) {

    if (mat[i][j] == -1 && intensity_at(i,j,gray) >= 255) {
        mat[i][j] = label;
    }
    else 
        return;

    for (auto n : neighbors) {
        if (in_bounds(i+n.first, j+n.second, mat.size(), mat[0].size())) {
            dfs (mat, i+n.first, j+n.second, label, gray);
        }
    }
}

bool is_circle (int i, int j, vector<vector<int> >& viz, vector<vector<int> >& seg) {
    viz[i][j] = 1;

    for (auto n : neighbors) {
        if (!in_bounds(i+n.first, j+n.second, viz.size(), viz[0].size())) {
            return false;
        }
        if (viz[i+n.first][j+n.second] == 0 && seg[i+n.first][j+n.second] != -1) {
            bool res = is_circle(i+n.first, j+n.second, viz, seg);
            if (res == false)
                return false;
        }
    }
    return true;
}


int main (int argc, char** argv) {

    /**
     * Read image
     */
    cout << "Read image ..." << endl;
    Mat img = imread(argv[1]);
    show_img(img);
    

    /**
     * Convert to gray
     */
    cout << "Convert to gray ..." << endl;
    Mat gray;
    cvtColor(img, gray, CV_RGB2GRAY);
    show_img(gray);

    /**
     * Gaussian blur
     */
    #if 0
    int ksize = 9;
    double sigma = 2;
    cout << "Gaussian blur ..." << endl;
    GaussianBlur(gray, gray, Size(ksize, ksize), sigma, sigma);
    show_img(gray);    
    #endif

    /**
     * Erosion
     */
    Mat erosion_gray;
    cout << "Threshold ..." << endl;
    threshold( gray, erosion_gray, 230, 255, THRESH_BINARY_INV);
    show_img(erosion_gray);

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


    /**
     * Floodfill connected components
     */

    // get background label
    Scalar intensity = erosion_gray.at<uchar>(20, 30);
    int bg_val = intensity.val[0];
    cout << "Intensity = " << bg_val << endl << endl;

    vector<vector<int> > seg(erosion_gray.rows, vector<int>(erosion_gray.cols, -1));
    int label = 1;
    for (int r=0; r<erosion_gray.rows; ++r) {
        for (int c = 0; c < erosion_gray.cols; ++c) {
            if (seg[r][c] == -1 && intensity_at(r,c,erosion_gray) >= 255) { // not labeled
                dfs(seg, r, c, label, erosion_gray);
                label++;
            }
        }
    }
    cout << "#componens after floodfill: " << label-1 << endl;

    int n_circles = 0;
    vector<std::vector<int> > viz(erosion_gray.rows, vector<int>(erosion_gray.cols, 0));
    for (int r=0; r<erosion_gray.rows; ++r) {
        for (int c=0; c<erosion_gray.cols; ++c) {
            if (seg[r][c] != -1 && viz[r][c] == 0) {
                n_circles += is_circle(r,c,viz,seg);
            }
        }
    }
    cout << "#circles: " << n_circles << endl;

    for (int r=0; r<erosion_gray.rows; ++r) {
        for (int c=0; c<erosion_gray.cols; ++c) {
            if (seg[r][c] != -1) {
                erosion_gray.at<uchar>(r,c) = seg[r][c] * 20;
            }
        }
    }
    show_img (erosion_gray);


exit(0);



    /**
     * apply Laplace kernel
     */
    {
        cout << "Laplace kernel ..." << endl;
        
        Mat abs_dst, dst;
        int scale = 1;
        int delta = 0;
        int ddepth = CV_16S;
        int kernel_size = 3;

        Laplacian( gray, dst, ddepth, kernel_size, scale, delta, BORDER_DEFAULT );
        convertScaleAbs( dst, abs_dst );

        show_img( abs_dst );
    }


    /**
     * Sobel kernel
     */
    cout << "Sobel kernel ..." << endl;
    Mat grad;
    int scale = 1;
    int delta = 0;
    int ddepth = CV_16S;

    /// Generate grad_x and grad_y
     Mat grad_x, grad_y;
     Mat abs_grad_x, abs_grad_y;

     /// Gradient X
     Sobel( gray, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT );
     convertScaleAbs( grad_x, abs_grad_x );

     /// Gradient Y
     Sobel( gray, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT );
     convertScaleAbs( grad_y, abs_grad_y );

     /// Total Gradient (approximate)
    addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad );

    show_img( grad );



    exit (0);

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
