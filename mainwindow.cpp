#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "pantallainicio.h"
#include "pantallajuego.h"
#include "pantallaranking.h"
#include <qdir.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , currentWidget(nullptr)
{
    ui->setupUi(this);

    // Crear acciones para la barra de herramientas
    QAction *loginAction = new QAction("Mostrar Pantalla Inicio", this);
    QAction *gameAction = new QAction("Mostrar Pantalla Juego", this);
    QAction *rankingAction = new QAction("Mostrar Ranking", this);

    // Agregar acciones a la barra de herramientas
    ui->toolBar->addAction(loginAction);
    ui->toolBar->addAction(gameAction);
    ui->toolBar->addAction(rankingAction);

    // Conectar acciones con slots
    connect(loginAction, &QAction::triggered, this, &MainWindow::showPantallaInicio);
    connect(gameAction, &QAction::triggered, this, &MainWindow::showPantallaJuego);
    connect(rankingAction, &QAction::triggered, this, &MainWindow::showPantallaRanking);


    // Mostrar inicialmente el TimeWidget
    showPantallaInicio();
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showPantallaInicio() {
    if (currentWidget) {
        delete currentWidget;
    }
    currentWidget = new PantallaInicio(this);
    setCentralWidget(currentWidget);

}

void MainWindow::showPantallaJuego() {
    if (currentWidget) {
        delete currentWidget;
    }
    currentWidget = new PantallaJuego(this);
    setCentralWidget(currentWidget);
}

void MainWindow::showPantallaRanking() {
    if (currentWidget) {
        delete currentWidget;
    }
    currentWidget = new PantallaRanking(this);
    setCentralWidget(currentWidget);
}
