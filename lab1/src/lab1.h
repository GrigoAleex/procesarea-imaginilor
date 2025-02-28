//
// Created by Mihnea Jurca on 1/24/25.
//
#ifndef LAB1_H
#define LAB1_H

#include <opencv2/opencv.hpp>

cv::Mat negative_image(cv::Mat image);
cv::Mat add_scalar(cv::Mat image, int factor);
cv::Mat mul_scalar(cv::Mat image, float factor);
cv::Mat draw_squares(int rows, int cols);

#endif // LAB1_H