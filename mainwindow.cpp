#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "pantallainicio.h"
#include "pantallajuego.h"
#include "pantallaranking.h"
#include "pantallapartidas.h"
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
    QAction *partidasAction = new QAction("Partidas Jugadas", this);

    // Agregar acciones a la barra de herramientas
    ui->toolBar->addAction(loginAction);
    ui->toolBar->addAction(gameAction);
    ui->toolBar->addAction(rankingAction);
    ui->toolBar->addAction(partidasAction);

    // Deshabilitar botón de "Mostrar Pantalla Juego" inicialmente
    gameAction->setEnabled(false);

    // Conectar acciones con slots
    connect(loginAction, &QAction::triggered, this, &MainWindow::showPantallaInicio);
    connect(gameAction, &QAction::triggered, this, &MainWindow::showPantallaJuego);
    connect(rankingAction, &QAction::triggered, this, &MainWindow::showPantallaRanking);
    connect(partidasAction, &QAction::triggered, this, &MainWindow::showPantallaPartidas);

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
    auto *pantallaInicio = new PantallaInicio(this);
    currentWidget = pantallaInicio;
    setCentralWidget(currentWidget);

    // Conectar señal de inicio de sesión exitoso para habilitar el botón y cambiar la pantalla
    connect(pantallaInicio, &PantallaInicio::loginSuccessful, this, [this]() {
        ui->toolBar->actions()[1]->setEnabled(true); // Habilitar "Mostrar Pantalla Juego"
        showPantallaJuego();
    });
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

void MainWindow::showPantallaPartidas() {
    if (currentWidget) {
        delete currentWidget;
    }
    currentWidget = new PantallaPartidas(this);
    setCentralWidget(currentWidget);
}
