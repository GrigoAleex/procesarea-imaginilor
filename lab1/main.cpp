#include <iostream>
#include <opencv2/opencv.hpp>
#include "src/lab1.h"

using namespace std;
using namespace cv;

int main(){
    Mat image = imread("images/kids.bmp", IMREAD_GRAYSCALE);
    imshow("Original Image", image);
    waitKey(0);

    Mat result = negative_image(image);
    imshow("Negative Image", result);
    waitKey(0);

    Mat result2 = add_scalar(image, 100);
    imshow("Add Scalar", result2);
    waitKey(0);

    Mat result3 = mul_scalar(image, 0.5);
    imshow("Mul Scalar", result3);
    waitKey(0);
    
    Mat result4 = draw_squares(256, 256);
    imshow("Draw Squares", result4);
    waitKey(0);

    return 0;
}