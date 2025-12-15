#include "Treshold.hpp"

//Costruttore 
Threshold::Threshold() {}

//Distruttore
Threshold::~Threshold() {}

void Threshold::Thresholdit(const cv::Mat& input, cv::Mat& output, int threshValue, int type) {
    if (input.empty()) return;

    // Convertiamo in scala di grigi se non lo è già, perché threshold lavora su 1 canale
    cv::Mat gray;
    if (input.channels() == 3) {
        cv::cvtColor(input, gray, cv::COLOR_BGR2GRAY);
    } else {
        gray = input;
    }

    // Applica la funzione di OpenCV
    // type: OpenCV usa enum (0, 1, 2...), passiamo direttamente l'int del cursore
    cv::threshold(gray, output, threshValue, 255, type);
}