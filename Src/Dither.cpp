#include "Dither.hpp"

Dither::Dither() {}
Dither::~Dither() {}

void Dither::applyFloydSteinberg(const cv::Mat& input, cv::Mat& output, int scaleFactor) {
    if (input.empty()) return;

    cv::Mat gray;
    // 1. Convertiamo in grigio
    if (input.channels() == 3) {
        cv::cvtColor(input, gray, cv::COLOR_BGR2GRAY);
    } else {
        gray = input.clone();
    }

    // 2. (Opzionale) Ridimensioniamo per effetto "Retro"
    // Se scaleFactor > 1, rimpiccioliamo l'immagine.
    // Il dithering su 1080p sembra solo rumore, su 320x240 è artistico.
    if (scaleFactor > 1) {
        cv::resize(gray, gray, cv::Size(gray.cols / scaleFactor, gray.rows / scaleFactor));
    }

    // 3. Prepariamo l'immagine di lavoro
    // Usiamo CV_16S (Short con segno) perché l'errore può rendere i pixel temporaneamente
    // negativi o > 255, e uchar (0-255) farebbe overflow rovinando tutto.
    cv::Mat workingMat;
    gray.convertTo(workingMat, CV_16S);

    // 4. Algoritmo Floyd-Steinberg
    // Iteriamo su tutti i pixel tranne l'ultima riga e colonna (per non uscire dai bordi)
    for (int y = 0; y < workingMat.rows - 1; y++) {
        for (int x = 1; x < workingMat.cols - 1; x++) {
            
            // Leggiamo il pixel attuale
            short oldPixel = workingMat.at<short>(y, x);
            
            // Quantizziamo: Se > 128 diventa 255 (Bianco), altrimenti 0 (Nero)
            short newPixel = (oldPixel > 128) ? 255 : 0;
            
            // Scriviamo il risultato finale
            workingMat.at<short>(y, x) = newPixel;

            // Calcoliamo l'errore
            short quantError = oldPixel - newPixel;

            // Diffondiamo l'errore ai vicini secondo la matrice Floyd-Steinberg:
            //       X   7
            //   3   5   1
            // (/16)
            
            workingMat.at<short>(y, x + 1)     += quantError * 7 / 16;
            workingMat.at<short>(y + 1, x - 1) += quantError * 3 / 16;
            workingMat.at<short>(y + 1, x)     += quantError * 5 / 16;
            workingMat.at<short>(y + 1, x + 1) += quantError * 1 / 16;
        }
    }

    // 5. Convertiamo il risultato finale in uchar (0-255) per la visualizzazione
    workingMat.convertTo(output, CV_8U);

    // 6. Se avevamo ridimensionato, ingrandiamo di nuovo per riempire lo schermo
    if (scaleFactor > 1) {
        cv::resize(output, output, cv::Size(input.cols, input.rows), 0, 0, cv::INTER_NEAREST);
    }
}