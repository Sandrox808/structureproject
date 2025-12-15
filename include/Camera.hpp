#pragma once // Evita importazioni duplicate
#include <opencv2/opencv.hpp>
#include <string>

class Camera {
private:
    cv::VideoCapture cap;
    std::string pipeline;

public:
    Camera();  // Costruttore
    ~Camera(); // Distruttore (pulisce la memoria)

    bool start(); // Apre la connessione
    bool getFrame(cv::Mat& frame); // Mette la foto nella variabile 'frame'
    void stop(); // Chiude tutto
};

