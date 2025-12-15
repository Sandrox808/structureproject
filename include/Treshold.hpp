#pragma once
#include <opencv2/opencv.hpp>

class Threshold {
public:
    //Costruttore
    Threshold();
    //Distruttore
    ~Threshold();

    // Applica il threshold
    // threshValue: valore da 0 a 255
    // type: 0=Binary, 1=Binary Inv, 2=Trunc, 3=ToZero, 4=ToZero Inv
    void Thresholdit(const cv::Mat& input, cv::Mat& output, int threshValue, int type);
};