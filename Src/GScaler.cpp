#include "GScaler.hpp"

GScaler::GScaler() {
    // Costruttore
}

GScaler::~GScaler() {
    // Distruttore 
}

void GScaler::toGrayscale(const cv::Mat& input, cv::Mat& output) {
    // Controllo di sicurezza: se l'input è vuoto, non facciamo nulla
    if (input.empty()) return;

    // Conversione da BGR (Colori) a GRAY (Scala di grigi)
    cv::cvtColor(input, output, cv::COLOR_BGR2GRAY);
}