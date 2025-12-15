#pragma once
#include <opencv2/opencv.hpp>
#include <chrono>
#include <string>

class PerformanceMonitor {
private:
    // Alias per non scrivere std::chrono::... ogni volta
    using Clock = std::chrono::high_resolution_clock;
    using TimePoint = std::chrono::time_point<Clock>;

    // Variabili per il calcolo FPS
    TimePoint lastFpsTime;
    int frameCounter;
    double currentFps;

    // Variabili per il tempo di processing
    TimePoint processStart;
    double processTimeMs;

public:
    PerformanceMonitor();

    // Chiama questo prima di iniziare l'elaborazione pesante
    void startTimer();

    // Chiama questo appena finita l'elaborazione
    void stopTimer();

    // Chiama questo per calcolare gli FPS (una volta a giro)
    void tick();

    // Disegna le statistiche direttamente sull'immagine
    void drawStats(cv::Mat& frame);
};