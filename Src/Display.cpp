#include "Display.hpp"

Display::Display(std::string name) : windowName(name) {
    // Possiamo creare la finestra subito o lasciar fare a imshow
    cv::namedWindow(windowName, cv::WINDOW_AUTOSIZE);
}

void Display::show(const cv::Mat& frame) {
    if (!frame.empty()) {
        cv::imshow(windowName, frame);
    }
}

bool Display::checkExitKey() {
    // waitKey(1) è obbligatorio per aggiornare la GUI di OpenCV
    char key = (char)cv::waitKey(1);
    return (key == 27); // 27 è il codice ASCII di ESC

    
}

void Display::addTrackbar(const std::string& trackbarName, int* value, int maxVal) {
    // Creiamo il cursore e lo attacchiamo a QUESTA finestra (windowName)
    // Passiamo 'value' che è l'indirizzo di memoria della variabile nel main
    cv::createTrackbar(trackbarName, windowName, value, maxVal);

}