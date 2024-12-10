#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "pantallainicio.h"
#include "pantallajuego.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , currentWidget(nullptr)
{
    ui->setupUi(this);

    // Crear acciones para la barra de herramientas
    QAction *timeAction = new QAction("Mostrar Pantalla Inicio", this);
    QAction *dateAction = new QAction("Mostrar Pantalla Juego", this);

    // Agregar acciones a la barra de herramientas
    ui->toolBar->addAction(timeAction);
    ui->toolBar->addAction(dateAction);

    // Conectar acciones con slots
    connect(timeAction, &QAction::triggered, this, &MainWindow::showPantallaInicio);
    connect(dateAction, &QAction::triggered, this, &MainWindow::showPantallaJuego);

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
