cmake_minimum_required(VERSION 3.16)

project(Trabajo_IHM VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Charts)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Charts)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

# Ruta para encontrar el archivo.lib
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)
# Ruta relativa para encontrar los archivos de cabecera
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Trabajo_IHM
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        pantallainicio.h pantallainicio.cpp pantallainicio.ui
        pantallaregistro.h pantallaregistro.cpp pantallaregistro.ui
        pantallajuego.h pantallajuego.cpp pantallajuego.ui
        pantallaranking.h pantallaranking.cpp pantallaranking.ui
        persona/persona.h
        persona/persona.cpp
        persona/personatablemodel.cpp
        persona/personatablemodel.h
        resources.qrc
        pantallapartidas.h pantallapartidas.cpp pantallapartidas.ui
        partidatablemodel.h partidatablemodel.cpp
        dlgsegundojugador.h dlgsegundojugador.cpp
        pantallaperfil.h pantallaperfil.cpp pantallaperfil.ui
        pantallarecuperarclave.h pantallarecuperarclave.cpp pantallarecuperarclave.ui

    )

# Enlace de las bibliotecas
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/persona)
target_link_libraries(Trabajo_IHM PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Charts Connect4Lib)

else()
    if(ANDROID)
        add_library(Trabajo_IHM SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(Trabajo_IHM
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Trabajo_IHM PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Charts)

if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Trabajo_IHM)
endif()
set_target_properties(Trabajo_IHM PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Trabajo_IHM
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Trabajo_IHM)
endif()
