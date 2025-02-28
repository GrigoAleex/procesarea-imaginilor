#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
 * Create a negative image
 * Hint:
 *  Checkout clone() method provided by OpenCV
 * Args:
 *  image: input grayscale image
 * Return:
 *  negative: negative of the input image
 */
Mat negative_image(Mat image){
    Mat negative = image.clone();

    for(int i=0; i<image.rows; i++){
        for(int j=0; j<image.cols; j++){
            negative.at<uchar>(i,j) = 255 - image.at<uchar>(i,j);
        }
    }

    return negative;
}

/*
 * Add a scalar to the entire image
 * Hint:
 *  Values may overshoot
 *  Checkout clone() method provided by OpenCV
 * Args:
 *  image: input grayscale image
 *  factor: value to add to each pixel of the image
 * Variables:
 *  rows: number of rows of the image
 *  cols: number of columns of the image
 * Return:
 *  result: transformed matrix
 */
Mat add_scalar(Mat image, int factor){
    Mat result = image.clone();

    for(int i=0; i<image.rows; i++){
        for(int j=0; j<image.cols; j++){
            int value = image.at<uchar>(i,j) + factor;
            value = std::min(255, std::max(0, value));
            result.at<uchar>(i,j) = value;
        }
    }

    return result;
}

/*
 * Multiply a scalar to the entire image
 * Hint:
 *  Values may overshoot
 *  Checkout clone() method provided by OpenCV
 * Args:
 *  image: input grayscale image
 *  factor: value to multiply to each pixel of the image
 * Variables:
 *  rows: number of rows of the image
 *  cols: number of columns of the image
 * Return:
 *  result: transformed matrix
 */
Mat mul_scalar(Mat image, float factor){
    Mat result = image.clone();

    for(int i=0; i<image.rows; i++){
        for(int j=0; j<image.cols; j++){
            int value = image.at<uchar>(i,j) * factor;
            value = std::min(255, std::max(0, value));
            result.at<uchar>(i,j) = value;
        }
    }

    return result;  
}

/*
 * Initialize a Mat object in order to create a square divided in four sub-squares which you are
 * going to color from top to bottom, left to right as: white, red, green, yellow
 * Hint:
 *  The channels are BGR not RGB
 *  value 0 means black 255 value means white (0 intensity to full intensity)
 *  You can initialize the image with White at the beginning
 * Args:
 *  rows: number of rows of the image 
 *  cols: number of cols of the image
 * Variables:
 *  red: vector representing red color
 *  green: vector representing green color
 *  yellow: vector representing yellow color
 * Return:
 *  result: final matrix
*/
Mat draw_squares(int rows, int cols){    
    Mat result = Mat::zeros(rows, cols, CV_8UC3);

    for(int i=0; i<rows/2; i++){
        for(int j=0; j<cols/2; j++){
            result.at<Vec3b>(i,j) = Vec3b(255, 255, 255);
        }
    }

    for(int i=0; i<rows/2; i++){
        for(int j=cols/2; j<cols; j++){
            result.at<Vec3b>(i,j) = Vec3b(0, 0, 255);
        }
    }
    
    for(int i=rows/2; i<rows; i++){
        for(int j=0; j<cols/2; j++){
            result.at<Vec3b>(i,j) = Vec3b(0, 255, 0);
        }
    }

    for(int i=rows/2; i<rows; i++){
        for(int j=cols/2; j<cols; j++){
            result.at<Vec3b>(i,j) = Vec3b(0, 255, 255);
        }
    }
    
    return result;
}
