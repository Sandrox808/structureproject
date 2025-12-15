#include "Camera.hpp"
#include <iostream>

// Costruttore pipeline
Camera::Camera() {
    
    // Full HD a 60fps 
    pipeline = "libcamerasrc ! video/x-raw, format=NV12, width= 640, height=480, framerate=120/1 ! "
           "videoconvert ! video/x-raw, format=BGR ! "
           "appsink drop=true";
}

// Distruttore
Camera::~Camera() {
    stop();
}

bool Camera::start() {
    std::cout << "Tentativo di apertura camera..." << std::endl;
    cap.open(pipeline, cv::CAP_GSTREAMER);
    
    if (!cap.isOpened()) {
        std::cerr << "Errore: Impossibile aprire la pipeline GStreamer!" << std::endl;
        return false;
    }
    return true;
}

bool Camera::getFrame(cv::Mat& frame) {
    if (!cap.isOpened()) return false;
    
    cap >> frame; // Legge il frame
    return !frame.empty();
}

void Camera::stop() {
    if (cap.isOpened()) {
        cap.release();
        std::cout << "Camera chiusa." << std::endl;
    }
}