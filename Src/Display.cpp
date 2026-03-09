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

bool Display::startShmStream(int width, int height, double fps, std::string socketPath) {
    // Pipeline GStreamer:
    // 1. appsrc: prende i dati da OpenCV
    // 2. videoconvert: converte i colori (importante!)
    // 3. video/x-raw,format=RGB: Convertiamo BGR (OpenCV) in RGB (standard per Qt)
    // 4. shmsink: scrive in memoria condivisa
    std::string pipeline = 
        "appsrc ! "
        "queue ! "
        "videoconvert ! "
        "video/x-raw,format=RGB ! " 
        "shmsink socket-path=" + socketPath + " "
        "shm-size=20000000 wait-for-connection=false";

    // 0 = fourcc (non serve con appsrc), true = isColor
    streamer.open(pipeline, cv::CAP_GSTREAMER, 0, fps, cv::Size(width, height), true);

    if (!streamer.isOpened()) {
        std::cerr << "[Display] Errore: Impossibile avviare GStreamer shmsink!" << std::endl;
        isStreamActive = false;
        return false;
    }

    std::cout << "[Display] Streaming attivo su: " << socketPath << std::endl;
    isStreamActive = true;
    return true;
}