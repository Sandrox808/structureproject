#include <QApplication>
#include "MainWindow.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow w;
    w.setWindowTitle("Raspberry Pi 5 - Smart Cam Filter");
    w.resize(1024, 768);
    w.show();

    return app.exec(); // Avvia l'event loop di Qt
}