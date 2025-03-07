#include <iostream>
#include <opencv2/opencv.hpp>
#include "lab2.h"
using namespace std;
using namespace cv;

image_channels_bgr break_channels(Mat source){

    /*
     * Create a function that will copy the R, G and B channels of a color,
     * RGB image (CV_8UC3 type) into three matrices of type CV_8UC1 (grayscale images).
     * Return the three matrices in an image_channels_bgr structure
     *
     * Inputs:
     *  source: the source image(BGR)
     * Variables:
     *  rows: number of rows of the source matrix
     *  cols: number of cols of the source matrix
     *  B, G, R: Matrices that will store each a color channel
     *  bgr_channels: structure of type image_channels_bgr that will return three channels
     */

    int rows = source.rows, cols = source.cols;
    Mat B(rows, cols, CV_8UC3), G(rows, cols, CV_8UC3), R(rows, cols, CV_8UC3);
    image_channels_bgr bgr_channels;

    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            
            B.at<Vec3b>(i,j)[1] = 0;
            B.at<Vec3b>(i,j)[2] = 0;
            
            G.at<Vec3b>(i,j)[0] = 0;
            G.at<Vec3b>(i,j)[2] = 0;

            
            R.at<Vec3b>(i,j)[1] = 0;
            R.at<Vec3b>(i,j)[0] = 0;

            B.at<Vec3b>(i,j)[0] = source.at<Vec3b>(i,j)[0];
            G.at<Vec3b>(i,j)[1] = source.at<Vec3b>(i,j)[1];
            R.at<Vec3b>(i,j)[2] = source.at<Vec3b>(i,j)[2];
        }
    }

    bgr_channels.B = B;
    bgr_channels.G = G;
    bgr_channels.R = R;

    return bgr_channels;

}

void display_channels(image_channels_bgr bgr_channels){
    /*
     * Display each channel in a different window
     * Do not put here the waitKey() try to use only one at the end of the lab
     * Input:
     *  bgr_channels: structure of type image_channels_bgr that will store B, G, R channels
     *
     */
    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****

}

Mat bgr_2_grayscale(Mat source){
    /*
    * Create a function that will convert a color RGB image (CV_8UC3 type) to a grayscale image (CV_8UC1),
    * and return the result image
    * Inputs: source: the source matrix(BGR)
    * Variables:
    *  rows: number of rows of the source matrix
    *  cols: number of cols of the source matrix
    *  grayscale_image: The grayscale image that you will obtain and return
    */
    Mat grayscale_image(source.rows, source.cols, CV_8UC1);

    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    for (size_t i = 0; i < source.rows; i++)
    {
        for (size_t j = 0; j < source.cols; j++)
        {
            Vec3b pixel = source.at<Vec3b>(i, j);
            grayscale_image.at<uchar>(i,j) = (pixel[0] + pixel[1] + pixel[2])/3;
        }
        
    }
    

    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****

    return grayscale_image;

}

Mat grayscale_2_binary(Mat source, int threshold){
    /*
    * Create a function for converting from grayscale to black and white (binary), using (2.2).
    * Test the operation on multiple images, and using multiple thresholds.
    * Inputs:
    *    source: grayscale image
    *    threshold: the threshold you are going to use to perform the binarization
    *  Variables:
    *    rows: number of rows of the source matrix
    *    cols: number of cols of the source matrix
    *    binary: the resulted binarized image
    */

    Mat binary = source.clone();

    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
    
    for(int i=0; i<source.rows; i++) {
        for(int j=0; j<source.cols; j++) {
            if(source.at<uchar>(i,j) < threshold) {
                binary.at<uchar>(i,j) = 0;
            }
            else {
                binary.at<uchar>(i,j) = 255;
            }
        }
    }

    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****
    return binary;
}

image_channels_hsv bgr_2_hsv(image_channels_bgr bgr_channels){
    /*
    * Create a function that will compute the H, S and V values from the R, G, B channels of
    * an image, using the equations from 2.6. Store each value (H, S, V) in a CV_8UC1 matrix that will be
    * stored in an image_channels_hsv struct.
    * Inputs:
    *    bgr_channels: structure that stores the B, G, R channels of an image
    * Variables:
    *    rows: number of rows of the source matrix
    *    cols: number of cols of the source matrix
    *    H, S, V: matrices that will store the values of the 3 different channels (Pay attention to the type of elements
    *       that are stored in these matrices.
    *    hsv_channels: structure that will store the H, S, V channels
    */

    int rows = bgr_channels.B.rows;
    int cols = bgr_channels.B.cols;
    Mat H = Mat::zeros(rows, cols, CV_8UC1);
    Mat S = Mat::zeros(rows, cols, CV_8UC1);
    Mat V = Mat::zeros(rows, cols, CV_8UC1);
    
    image_channels_hsv hsv_channels;

    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            float r = bgr_channels.R.at<Vec3b>(i,j)[2] / 255.0f;
            float g = bgr_channels.G.at<Vec3b>(i,j)[1] / 255.0f;
            float b = bgr_channels.B.at<Vec3b>(i,j)[0] / 255.0f;

            float M = std::max(std::max(r, g), b);
            float m = std::min(std::min(r, g), b);
            
            V.at<uchar>(i, j) = static_cast<uchar>(M * 255);
            S.at<uchar>(i,j) = static_cast<uchar>((M == 0 ? 0 : (M - m) / M) * 255);

            float h;
            if (M-m == 0) h = 0;    
            else if (M == r) h = 60.0f * (g - b) / (M-m);
            else if (M == g) h = 120.0f + 60.0f * (b - r) / (M-m);
            else h = 240.0f + 60.0f * (r - g) / (M-m);

            if (h < 0) h += 360.0f;
            H.at<uchar>(i,j) = static_cast<uchar>(h * 255.0f / 360.0f);
        }
        
    }
    

    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****

    hsv_channels.H = H;
    hsv_channels.S = S;
    hsv_channels.V = V;

    return hsv_channels;
}

void display_hsv_channels(image_channels_hsv hsv_channels){

    /*
    * Display the three channels
    * Inputs:
    *    hsv_channels: structure that stores the H, S, V channels of an image.
    *      In order to display them don't forget to normalize them accordingly
    *  Variables:
    *    rows: number of rows of the source matrix
    *    cols: number of cols of the source matrix
    *    H_norm, S_norm, V_norm: Normalized matrices.
    */

    int rows, cols;
    Mat H_norm, S_norm, V_norm;

    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****

}

bool IsInside(Mat img, int i, int j){
    /*
    * Implement a function called isInside(img, i, j) which checks if the position indicated by
    * the pair (i,j) (row, column) is inside the image img.
    */

    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    if (i < 0 || j < 0) return false;
    if (i >= img.rows || j >= img.cols) return false;

    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****
    return true;
}