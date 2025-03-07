#include <iostream>
#include <opencv2/opencv.hpp>
#include "./src/lab2.h"

using namespace std;
using namespace cv;

int main(){
    Mat image = imread("images/flowers_24bits.bmp", IMREAD_COLOR);
    imshow("Original", image);
    

    image_channels_bgr bgr_channels = break_channels(image);
    imshow("Blue", bgr_channels.B);
    imshow("Green", bgr_channels.G);
    imshow("Red", bgr_channels.R);

    Mat gray_image = bgr_2_grayscale(image);
    imshow("Gray", gray_image);

    srand(time(0));  // Initialize random seed
    int threshold = rand() % 256;
    Mat binary_image = grayscale_2_binary(gray_image, threshold);
    imshow("Binary (t=" + to_string(threshold) + ")", binary_image);

    image_channels_hsv hsv_image = bgr_2_hsv(bgr_channels);
    imshow("Hue", hsv_image.H);
    imshow("Saturation", hsv_image.S);
    imshow("Value", hsv_image.V);

    waitKey(0);
    return 0;
}