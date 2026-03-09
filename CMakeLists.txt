cmake_minimum_required(VERSION 3.10)
project(StructuredProject LANGUAGES CXX)

# =========================
# C++ standard
# =========================
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ========================= 
# Impostazioni Qt (Automatiche)
# =========================
# Fondamentale per la compilazione dei file che usano Q_OBJECT, file .ui e risorse .qrc
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# =========================
# OpenCV
# =========================
set(OpenCV_DIR "/usr/local/lib/cmake/opencv4"
    CACHE PATH "Path to OpenCVConfig.cmake")

find_package(OpenCV REQUIRED)

# =========================
# Qt
# =========================



# =========================
# Sorgenti
# =========================
set(SOURCES
    Src/main.cpp
    Src/Camera.cpp
    Src/Display.cpp
    Src/GScaler.cpp
    Src/PerformanceMonitor.cpp
    Src/Canny.cpp
    Src/Treshold.cpp
    Src/Dither.cpp
)

# =========================
# Target
# =========================
add_executable(CamApp ${SOURCES})

# Include del progetto + OpenCV
target_include_directories(CamApp PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${OpenCV_INCLUDE_DIRS}
)

# Link OpenCV
target_link_libraries(CamApp PRIVATE
    ${OpenCV_LIBS}
)

