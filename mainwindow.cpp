#include "mainwindow.h"
#include "cerrarsesion.h"
#include "pantallaperfil.h"
#include "ui_mainwindow.h"
#include "pantallainicio.h"
#include "pantallajuego.h"
#include "pantallaranking.h"
#include "pantallapartidas.h"
#include "dlgsegundojugador.h"
#include "pantallarecuperarclave.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , currentWidget(nullptr)
    , User2(nullptr)
{
    ui->setupUi(this);

    // Crear acciones para la barra de herramientas
    QAction *loginAction = new QAction("Mostrar Pantalla Inicio", this);
    QAction *gameAction = new QAction("Mostrar Pantalla Juego", this);
    QAction *rankingAction = new QAction("Mostrar Ranking", this);
    QAction *partidasAction = new QAction("Partidas Jugadas", this);
    QAction *editProfileAction = new QAction("Editar Perfil", this);
    QAction *logoutAction = new QAction("Cerrar Sesión", this);
    QAction *darkModeAction = new QAction(QIcon(":/imagenes/moon.png"), "Modo Oscuro", this);


    // *** NUEVA ACCIÓN *** para 2 jugadores:
    //QAction *twoPlayersAction = new QAction("Jugar vs. 2º Jugador", this);
    // Agregar acciones a la barra de herramientas
    ui->toolBar->addAction(loginAction);
    ui->toolBar->addAction(gameAction);
    ui->toolBar->addAction(rankingAction);
    ui->toolBar->addAction(partidasAction);
    ui->toolBar->addAction(editProfileAction);
    ui->toolBar->addAction(darkModeAction);
    ui->toolBar->addAction(logoutAction);


    // Asignamos al boton de cambio modo el nombre darkModeAction para poder cambiar su icono posteriormente
    darkModeAction->setObjectName("darkModeAction");

    // Deshabilitar botón de "Mostrar Pantalla Juego" inicialmente
    gameAction->setEnabled(false);
    editProfileAction->setEnabled(false);
    logoutAction->setEnabled(false);
    //twoPlayersAction->setEnabled(false);

    // Conectar acciones con slots
    connect(loginAction, &QAction::triggered, this, &MainWindow::showPantallaInicio);
    connect(gameAction, &QAction::triggered, this, &MainWindow::showPantallaJuego);
    connect(rankingAction, &QAction::triggered, this, &MainWindow::showPantallaRanking);
    connect(partidasAction, &QAction::triggered, this, &MainWindow::showPantallaPartidas);
    connect(editProfileAction, &QAction::triggered, this, &MainWindow::showPantallaPerfil);
    connect(logoutAction, &QAction::triggered, this, &MainWindow::logout);
    connect(darkModeAction, &QAction::triggered, this, &MainWindow::toggleDarkMode);

    // Conectar la acción de 2 jugadores
    //connect(twoPlayersAction, &QAction::triggered, this, &MainWindow::showPantallaJuegoDosJugadores);

    // Mostrar inicialmente la Pantalla de Inicio
    showPantallaInicio();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// =========================
// Slots de cambio de pantalla
// =========================

void MainWindow::showPantallaInicio()
{
    if (currentWidget) {
        delete currentWidget;
        currentWidget = nullptr;
    }
    auto *pantallaInicio = new PantallaInicio(this);
    currentWidget = pantallaInicio;
    setCentralWidget(currentWidget);

    // Cuando el login sea exitoso, habilitamos los botones de juego
    connect(pantallaInicio, &PantallaInicio::loginSuccessful, this, [this](Player* user) {
        // Guardamos el usuario logueado
        currentUser = user;

        // Habilitar "Mostrar Pantalla Juego"
        ui->toolBar->actions()[1]->setEnabled(true);
        // Habilitar "Jugar vs. 2º Jugador" (está en la posición 4 del toolbar, index 4)
        ui->toolBar->actions()[4]->setEnabled(true);
        ui->toolBar->actions()[6]->setEnabled(true);

        // Cambiar a la pantalla de juego de 1 jugador por defecto
        showPantallaJuego();
    });
    connect(pantallaInicio, &PantallaInicio::forgotPasswordRequested, this, &MainWindow::showPantallaRecuperarClave);

}

void MainWindow::showPantallaJuego()
{
    if (currentWidget) {
        delete currentWidget;
        currentWidget = nullptr;
    }

    // PantallaJuego sin parámetros -> Modo contra CPU
    auto pantallajuego = new PantallaJuego(this, currentUser);
    currentWidget = pantallajuego;
    setCentralWidget(currentWidget);
}

void MainWindow::showPantallaRanking()
{
    if (currentWidget) {
        delete currentWidget;
        currentWidget = nullptr;
    }
    currentWidget = new PantallaRanking(this);
    setCentralWidget(currentWidget);
}

void MainWindow::showPantallaPartidas()
{
    if (currentWidget) {
        delete currentWidget;
        currentWidget = nullptr;
    }
    currentWidget = new PantallaPartidas(this);
    setCentralWidget(currentWidget);
}

// =============
// JUEGO 2 JUGADORES
// =============
void MainWindow::showPantallaJuegoDosJugadores()
{
    // Suponiendo que el primer jugador es el que inició sesión.
    // Por ejemplo, Connect4 guarda el "último que hizo login" o
    // tu PantallaInicio lo puedes tener en una variable global/estática.
    // Aquí solo a modo de ejemplo, pediré un Player "Player1":
    Player* player1 = Connect4::getInstance().getPlayer("Player1");
    // O, si en PantallaInicio guardaste el nick en una variable global, recupéralo.

    if (!player1) {
        // Si no encontramos el "jugador 1", avisa
        // (ajusta la lógica según tu proyecto).
        QMessageBox::warning(this, "Error", "No hay un jugador principal logueado.");
        return;
    }

    // Mostrar el diálogo para el 2º jugador
    DlgSegundoJugador dlg(this);
    if (dlg.exec() == QDialog::Accepted) {
        Player* player2 = dlg.getLoggedPlayer();
        if (!player2) {
            QMessageBox::warning(this, "Error", "No se pudo loguear al 2º jugador.");
            return;
        }

        // Ahora creamos la PantallaJuego en modo 2 jugadores
        if (currentWidget) {
            delete currentWidget;
            currentWidget = nullptr;
        }
        // Ojo, usaremos una nueva sobrecarga de PantallaJuego (ver abajo)
        currentWidget = new PantallaJuego(this);
        setCentralWidget(currentWidget);
    }
}
void MainWindow::showPantallaPerfil()
{
    if (!currentUser) {
        QMessageBox::warning(this, "Error", "No hay usuario logueado.");
        return;
    }
    if (currentWidget) {
        delete currentWidget;
        currentWidget = nullptr;
    }
    currentWidget = new PantallaPerfil(currentUser, this);
    setCentralWidget(currentWidget);
}

void MainWindow::toggleDarkMode()
{
    if (!isDarkMode) {
        // Cargar la hoja de estilo OSCURA
        QFile file(":/estilos/estilos_oscuro.qss");
        if (file.open(QFile::ReadOnly)) {
            QString darkStyle = QLatin1String(file.readAll());
            setStyleSheet(darkStyle);
            file.close();
        }

        // Cambiar ícono de la acción a "sol"
        for (QAction* action : ui->toolBar->actions()) {
            if (action->objectName() == "darkModeAction") {
                action->setIcon(QIcon(":/imagenes/sun.png"));
            }
        }

        isDarkMode = true;
    } else {
        // Regresar a la hoja de estilo CLARA
        QFile file(":/estilos/estilos.qss");
        if (file.open(QFile::ReadOnly)) {
            QString lightStyle = QLatin1String(file.readAll());
            setStyleSheet(lightStyle);
            file.close();
        }

        // Cambiar ícono de la acción a "luna"
        for (QAction* action : ui->toolBar->actions()) {
            if (action->objectName() == "darkModeAction") {
                action->setIcon(QIcon(":/imagenes/moon.png"));
            }
        }

        isDarkMode = false;
    }
}

void MainWindow::showPantallaRecuperarClave()
{
    if (currentWidget) {
        delete currentWidget;
        currentWidget = nullptr;
    }
    auto *pant = new PantallaRecuperarClave(this);
    currentWidget = pant;
    setCentralWidget(currentWidget);
}

void MainWindow::logout()
{
    // Si no hay usuario logueado, avisamos
    if (!currentUser) {
        QMessageBox::information(this, "Cerrar Sesión", "Ningún usuario está logueado actualmente.");
        return;
    }
    qDebug() << User2;
    Cerrarsesion crs(this, currentUser, User2);
    // 2) Deshabilitar las acciones que requieren estar logueado
    //    (Por ejemplo, la acción “Mostrar Pantalla Juego” y “Editar Perfil”)
    if(!currentUser && !User2){
        ui->toolBar->actions()[1]->setEnabled(false); // "Mostrar Pantalla Juego"
        ui->toolBar->actions()[4]->setEnabled(false); // "Editar Perfil" (ajusta si cambia el orden)
        ui->toolBar->actions()[6]->setEnabled(false); // "Cerrar sesión"
    }
    // 3) Mostrar mensaje


    // 4) Volver a la pantalla de inicio
    showPantallaInicio();
}
