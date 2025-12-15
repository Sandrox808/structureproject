#pragma once
#include <opencv2/opencv.hpp>

class GScaler {
public:
    GScaler();
    ~GScaler();

    //Conversione in scala di grigi
    void toGrayscale(const cv::Mat& input, cv::Mat& output);
};