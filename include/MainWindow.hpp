#pragma once

#include <QMainWindow>
#include <QLabel>
#include <QComboBox>
#include <QVBoxLayout>
#include <QTimer>
#include <opencv2/opencv.hpp>

// Includi le tue classi esistenti
#include "Camera.hpp"
#include "GScaler.hpp"
#include "Canny.hpp"
#include "Treshold.hpp" // Attenzione al typo nel nome file originale se era Treshold vs Threshold
#include "Dither.hpp"
#include "PerformanceMonitor.hpp"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void updateFrame();      // Chiamato dal timer ogni tot millisecondi
    void onFilterChanged(int index); // Chiamato quando cambi selezione

private:
    // UI Elements
    QWidget *centralWidget;
    QVBoxLayout *layout;
    QLabel *videoLabel;      // Qui mostreremo l'immagine
    QComboBox *filterSelector;
    QLabel *statsLabel;

    // Logica Applicativa
    QTimer *timer;
    Camera myCam;
    
    // Istanze dei tuoi processori
    GScaler grayProc;
    Canny cannyProc;
    Threshold thrProc;
    Dither ditherProc;
    PerformanceMonitor perfMon;

    // Stato
    enum FilterType {
        None = 0,
        Grayscale,
        CannyEdge,
        Thresholding,
        Dithering
    };
    
    FilterType currentFilter;

    // Helper per convertire OpenCV Mat -> Qt QImage
    QImage matToQImage(const cv::Mat &mat);
};