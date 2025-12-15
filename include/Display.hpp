#pragma once
#include <opencv2/opencv.hpp>
#include <string>

class Display {
private:
    std::string windowName;

public:
    Display(std::string name);
    void show(const cv::Mat& frame);
    bool checkExitKey(); // Ritorna true se l'utente preme ESC

    void addTrackbar(const std::string& trackbarName, int* value, int maxVal);
};