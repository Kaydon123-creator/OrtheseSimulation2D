cmake_minimum_required(VERSION 4.0)
project(test2400)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(test2400
        affichage.cpp
        affichage.h
        MiniDesign.cpp
        Scene.h
        Scene.cpp
        Point.h
        Point.cpp
        Nuage.h
        Nuage.cpp
        Display.h
        DisplayTexture.cpp
        DisplayID.cpp
        SurfaceStrategy.h
        SurfaceStrategyC1.cpp
        SurfaceStrategyC2.cpp
)
