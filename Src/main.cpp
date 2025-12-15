#include "Camera.hpp"
#include "Display.hpp"
#include "GScaler.hpp"
#include "PerformanceMonitor.hpp"
#include "Canny.hpp"
#include "Treshold.hpp"
#include "Dither.hpp"

#include <iostream>

int main() {
    
    Camera myCam;
    GScaler grayproc;
    PerformanceMonitor p;
    Canny canny;
    Threshold thr; 
    Dither d; 
    

    // Queste variabili verranno modificate automaticamente dai cursori
    int threshold_value = 127; // Valore iniziale
    int threshold_type = 0;    // 0 = Binary
    int max_type_val = 4;      // OpenCV supporta 5 tipi (0-4)

    //Display LeScreen("Raspberry Pi 5 Feed");

    // --- SETUP UI ---
    // Colleghiamo le variabili ai cursori passando il loro indirizzo (&)
    //LeScreen.addTrackbar("Valore (0-255)", &threshold_value, 255);
    //LeScreen.addTrackbar("Tipo (0-4)", &threshold_type, max_type_val);

    Display myScreen("Floyd-Steinberg Dithering");

    int pixel_scale = 1; 
     myScreen.addTrackbar("Pixel Scale", &pixel_scale, 8);


    Display Screen2("Originale");
    Display Screen3("Mix&Match");

    // Avvio Camera
    if (!myCam.start()) {
        return -1;
    }

    cv::Mat frame; 
    cv::Mat grayFrame;
    cv::Mat displayFrame;
    cv::Mat frameframe;

    std::cout << "Avvio streaming. Premi ESC per uscire." << std::endl;

    // Loop
    while (true) {
        
        if (!myCam.getFrame(frame)) {
            std::cerr << "Frame perso o camera disconnessa." << std::endl;
            break;
        }
        
        p.startTimer();
        
        // Grayscaling
        //usare *grayFrame* se si utilizza il resize sotto
        //grayproc.toGrayscale(frame, displayFrame); 
        //cv::resize(grayFrame, displayFrame, cv::Size(960, 540));

        //Canny 
        canny.applyCanny(frame,frameframe);


        //Threshold
        //thr.Thresholdit(frameframe, grayFrame, threshold_value, threshold_type);


        //Dither
        int currentScale = (pixel_scale < 1) ? 1 : pixel_scale; 
         d.applyFloydSteinberg(frame, displayFrame, currentScale);

        


        p.stopTimer();
        p.tick();
        p.drawStats(displayFrame);

        myScreen.show(displayFrame);
        Screen2.show(frame);
        //LeScreen.show(grayFrame);
        Screen3.show(frameframe);

        if (myScreen.checkExitKey()) {
            break;
        }
    }

    return 0;
}