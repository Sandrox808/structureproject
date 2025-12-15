#include "Canny.hpp"

//Costruttore
Canny::Canny(){}

//Distruttore
Canny::~Canny(){}


// Implementazione Canny Edge Detector
void Canny::applyCanny(const cv::Mat& input, cv::Mat& output) {
    if (input.empty()) return;

    // Variabili temporanee necessarie per i passaggi intermedi
    cv::Mat gray, detected_edges;

    // 1. Converti in Scala di Grigi
    cv::cvtColor(input, gray, cv::COLOR_BGR2GRAY);

    // 2. Riduci il rumore (Noise Reduction)
    // Il tutorial suggerisce un kernel 3x3.
    // Usiamo 'blur' (box filter) o 'GaussianBlur' (più pesante ma migliore).
    // Qui uso blur come nel tutorial base.
    cv::blur(gray, detected_edges, cv::Size(3,3));

    // 3. Applica Canny
    // Parametri fissi come richiesto:
    // lowThreshold = 50
    // highThreshold = 150 (Di solito si usa un rapporto 1:3 rispetto alla bassa)
    // kernel_size = 3
    cv::Canny(detected_edges, output, 50, 150, 3);
}