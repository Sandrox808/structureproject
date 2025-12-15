#pragma once
#include <opencv2/opencv.hpp>

class Canny {
public:
    Canny(); //Costruttore

    ~Canny(); //Distruttore
    
    // --- NUOVO METODO CANNY ---
    // Prende l'immagine originale a colori (input)
    // Restituisce l'immagine con i bordi rilevati (output)
    void applyCanny(const cv::Mat& input, cv::Mat& output);
};