#include "MainWindow.hpp"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), currentFilter(FilterType::None) {
    // 1. Setup UI
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    layout = new QVBoxLayout(centralWidget);

    // Selettore Filtri
    filterSelector = new QComboBox(this);
    filterSelector->addItem("Originale", FilterType::None);
    filterSelector->addItem("Grayscale", FilterType::Grayscale);
    filterSelector->addItem("Canny Edge", FilterType::CannyEdge);
    filterSelector->addItem("Threshold", FilterType::Thresholding);
    filterSelector->addItem("Dithering", FilterType::Dithering);
    layout->addWidget(new QLabel("Seleziona Filtro:"));
    layout->addWidget(filterSelector);

    // Label Video
    videoLabel = new QLabel(this);
    videoLabel->setAlignment(Qt::AlignCenter);
    videoLabel->setMinimumSize(640, 480);
    layout->addWidget(videoLabel);

    // Stats Label
    statsLabel = new QLabel("FPS: 0", this);
    layout->addWidget(statsLabel);

    // 2. Setup Camera
    if (!myCam.start()) {
        qCritical() << "Errore: Impossibile avviare la camera!";
        videoLabel->setText("Errore Camera");
    }

    // 3. Connessioni Segnali
    connect(filterSelector, QOverload<int>::of(&QComboBox::currentIndexChanged), 
            this, &MainWindow::onFilterChanged);

    // 4. Timer per il loop (es. 30ms ~ 33 FPS)
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateFrame);
    timer->start(30); 
}

MainWindow::~MainWindow() {
    // Il distruttore di myCam gestirà la chiusura della camera
}

void MainWindow::onFilterChanged(int index) {
    // La QComboBox contiene i dati enum impostati nell'addItem
    currentFilter = static_cast<FilterType>(filterSelector->currentData().toInt());
}

void MainWindow::updateFrame() {
    cv::Mat frame;
    if (!myCam.getFrame(frame)) return;

    perfMon.startTimer();

    cv::Mat processedFrame;
    
    // Logica di selezione filtro
    switch (currentFilter) {
        case FilterType::None:
            processedFrame = frame.clone();
            break;

        case FilterType::Grayscale:
            // Assumo che toGrayscale prenda (input, output)
            grayProc.toGrayscale(frame, processedFrame); 
            break;

        case FilterType::CannyEdge:
            cannyProc.applyCanny(frame, processedFrame);
            break;

        case FilterType::Thresholding:
            // Nota: per Threshold serve grayscale prima solitamente, 
            // dipende dalla tua implementazione interna.
            // Uso valori default per semplicità qui.
            thrProc.Thresholdit(frame, processedFrame, 127, 0); 
            break;

        case FilterType::Dithering:
            ditherProc.applyFloydSteinberg(frame, processedFrame, 1);
            break;
    }

    perfMon.stopTimer();
    perfMon.tick();

    // Aggiorna Stats UI
    // Nota: perfMon.drawStats disegna su Mat, ma qui usiamo una Label Qt per pulizia
    // Se vuoi disegnare sull'immagine, fallo prima di convertire in QImage.
    statsLabel->setText(QString("Processing Time: %1 ms").arg(perfMon.getLastTime()));

    // Converti e mostra
    if (!processedFrame.empty()) {
        QImage qimg = matToQImage(processedFrame);
        videoLabel->setPixmap(QPixmap::fromImage(qimg).scaled(
            videoLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
}

QImage MainWindow::matToQImage(const cv::Mat &mat) {
    if (mat.empty()) return QImage();

    // OpenCV usa BGR, Qt usa RGB. Dobbiamo convertire o scambiare i canali.
    if (mat.type() == CV_8UC3) {
        // Immagine a colori
        cv::Mat rgbMat;
        cv::cvtColor(mat, rgbMat, cv::COLOR_BGR2RGB);
        return QImage(rgbMat.data, rgbMat.cols, rgbMat.rows, rgbMat.step, QImage::Format_RGB888).copy();
    } 
    else if (mat.type() == CV_8UC1) {
        // Grayscale
        return QImage(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_Grayscale8).copy();
    }
    
    return QImage();
}