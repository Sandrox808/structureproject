#pragma once
#include <opencv2/opencv.hpp>

class Dither {
public:
    Dither();
    ~Dither();

    // Applica l'algoritmo Floyd-Steinberg
    // scaleFactor: (Opzionale) Riduce l'immagine prima di applicare l'effetto
    // per renderlo più visibile (stile GameBoy). 1 = risoluzione originale.
    void applyFloydSteinberg(const cv::Mat& input, cv::Mat& output, int scaleFactor = 1);
};