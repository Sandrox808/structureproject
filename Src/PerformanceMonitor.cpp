#include "PerformanceMonitor.hpp"

using namespace std::chrono;

PerformanceMonitor::PerformanceMonitor() {
    lastFpsTime = Clock::now();
    frameCounter = 0;
    currentFps = 0.0;
    processTimeMs = 0.0;
}

void PerformanceMonitor::startTimer() {
    processStart = Clock::now();
}

void PerformanceMonitor::stopTimer() {
    auto end = Clock::now();
    // Calcola la differenza in millisecondi
    processTimeMs = duration_cast<duration<double, std::milli>>(end - processStart).count();
}

void PerformanceMonitor::tick() {
    frameCounter++;
    auto now = Clock::now();
    
    // Se è passato almeno 1 secondo, aggiorna il valore FPS visualizzato
    if (duration_cast<seconds>(now - lastFpsTime).count() >= 1) {
        currentFps = frameCounter;
        frameCounter = 0;
        lastFpsTime = now;
    }
}

void PerformanceMonitor::drawStats(cv::Mat& frame) {
    if (frame.empty()) return;

    std::string fpsText = "FPS: " + std::to_string((int)currentFps);
    std::string timeText = "CPU: " + std::to_string((int)processTimeMs) + " ms";

    // Disegna un rettangolo nero semitrasparente (sfondo) per leggere meglio il testo
    // (Opzionale: qui facciamo un rettangolo pieno semplice)
    //cv::rectangle(frame, cv::Point(0, 0), cv::Point(200, 70), cv::Scalar(0, 0, 0), cv::FILLED);

    // Scrivi il testo (Bianco)
    cv::putText(frame, fpsText, cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(203, 192, 255), 2);
    cv::putText(frame, timeText, cv::Point(10, 60), cv::FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(203, 192, 255), 2);
}

