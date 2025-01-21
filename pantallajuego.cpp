#include "pantallajuego.h"
#include "pantallainicio.h"
#include "connect4.h"
#include "ui_pantallajuego.h"
#include <QMessageBox>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <cstdlib>
#include <ctime>
#include <qevent.h>
#include "dlgsegundojugador.h"

PantallaJuego::PantallaJuego(QWidget *parent, Player* p)
    : QWidget(parent)
    , ui(new Ui::PantallaJuego)
    , rows(7)
    , cols(8)
    , currentPlayer(1)
    , highlightedColumn(-1)
    , playAgainstCPU(false)
    , twoPlayersMode(false)
    , cpuTimer(nullptr)
    , p2(nullptr)
    , p1(p)
    , playing(true)
    // Inicializamos marcadores a 0
    , p1Wins(0)
    , p2Wins(0)
    , totalGames(0)
{
    ui->setupUi(this);

    // Preguntar si CPU o 2 jugadores (ya lo tenías) ...
    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Elegir modo de juego");
    msgBox.setText("¿Contra quien quieres Jugar?\n\n(Elige una opción)");
    msgBox.setIcon(QMessageBox::Question);

    // Agregar botones personalizados
    QPushButton *btnCPU = msgBox.addButton("CPU", QMessageBox::AcceptRole);
    QPushButton *btn1vs1 = msgBox.addButton("1VS1", QMessageBox::RejectRole);


    // Mostrar el QMessageBox y capturar la respuesta
    msgBox.exec();

    // Verificar qué botón fue presionado
    if (msgBox.clickedButton() == btnCPU) {
        playAgainstCPU = true;
        twoPlayersMode = false;
    } else if (msgBox.clickedButton() == btn1vs1) {
        playAgainstCPU = false;
        twoPlayersMode = true;
        if (!p1) {
            QMessageBox::warning(this, "Error", "No se encontró al jugador principal. Cerrando...");
            close();
            return;
        }

        DlgSegundoJugador dlg(this);
        if (dlg.exec() == QDialog::Accepted) {
            p2 = dlg.getLoggedPlayer();
            if (!p2) {
                QMessageBox::warning(this, "Error", "No se pudo loguear el 2º jugador. Cerrando...");
                close();
                return;
            }
        } else {
            close();
            return;
        }
    }

    // Inicializar tablero
    tablero.resize(rows, QVector<int>(cols, 0));
    setMinimumSize(cols*40, rows*40);
    setMouseTracking(true);

    // Semilla random (CPU)
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    if (playAgainstCPU) {
        cpuTimer = new QTimer(this);
        cpuTimer->setSingleShot(true);
        connect(cpuTimer, &QTimer::timeout, this, &PantallaJuego::cpuMove);
    }
}

PantallaJuego::~PantallaJuego()
{
    delete ui;
}

void PantallaJuego::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QRect geom = geometry();
    int width = geom.width();
    int height = geom.height();

    if ((width / cols) < (height / rows)) {
        cellSize = width / cols;
    } else {
        cellSize = height / rows;
    }

    int x0 = (width - (cols * cellSize)) / 2;
    int y0 = (height - (rows * cellSize)) / 2;

    // Fondo
    painter.setBrush(Qt::darkBlue);
    painter.drawRect(x0, y0, cols*cellSize, rows*cellSize);

    // Fichas
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            QRect circleRect(x0 + c*cellSize + 5, y0 + r*cellSize + 5,
                             cellSize - 10, cellSize - 10);
            if (tablero[r][c] == 0)
                painter.setBrush(Qt::white);
            else if (tablero[r][c] == 1)
                painter.setBrush(Qt::red);
            else
                painter.setBrush(Qt::yellow);

            painter.drawEllipse(circleRect);
        }
    }

    // Ficha fantasma
    if (highlightedColumn != -1) {
        int dropRow = -1;
        for (int r = rows - 1; r >= 0; r--) {
            if (tablero[r][highlightedColumn] == 0) {
                dropRow = r;
                break;
            }
        }
        if (dropRow != -1) {
            QRect ghostRect(x0 + highlightedColumn*cellSize + 5,
                            y0 + dropRow*cellSize + 5,
                            cellSize - 10, cellSize - 10);
            painter.setBrush(QColor(200,200,255,128));
            painter.drawEllipse(ghostRect);
        }
    }
}

void PantallaJuego::mousePressEvent(QMouseEvent *event)
{
    if (playAgainstCPU && currentPlayer == 2) {
        return; // ignorar clicks si es turno CPU
    }
    if (event->button() == Qt::LeftButton && playing == true) {
        int mouseX = event->pos().x();
        QRect geom = geometry();
        int width = geom.width();
        int x0 = (width - (cols*cellSize)) / 2;
        int column = (mouseX - x0) / cellSize;

        if (column >= 0 && column < cols) {
            int row;
            if (dropDisc(column, row)) {
                update();
                if (checkWin(row, column)) {
                    // Alguien gana
                    QString winnerName;
                    if (playAgainstCPU) {
                        winnerName = (currentPlayer == 1) ? p1->getNickName() : "CPU";
                    } else {
                        winnerName = (currentPlayer == 1) ? p1->getNickName()
                                                          : p2->getNickName();
                    }

                    // Registrar en BD si es 2 jugadores
                    if (twoPlayersMode && p1 && p2) {
                        Player* winner = (currentPlayer == 1) ? p1 : p2;
                        Player* loser  = (currentPlayer == 1) ? p2 : p1;

                        // Sumar puntos
                        winner->addPoints(10);
                        Connect4::getInstance().registerRound(QDateTime::currentDateTime(),
                                                              winner, loser);
                    }

                    // Actualizar marcadores
                    totalGames++;
                    if (currentPlayer == 1)
                        p1Wins++;
                    else
                        p2Wins++;

                    mostrarMarcadorFinal(winnerName);
                    // Mostrar diálogo final: ¿Jugar otra o salir?
                    // (ver más abajo)
                    /*
                    QDialog finalDialog(this);
                    finalDialog.setWindowTitle("Fin de la Partida");
                    QVBoxLayout* mainLay = new QVBoxLayout(&finalDialog);
                    QLabel* lbl = new QLabel(
                        QString("¡" + winnerName+" ha ganado!"),
                        &finalDialog
                    );
                    mainLay->addWidget(lbl);

                    QHBoxLayout* btnLay = new QHBoxLayout;
                    QPushButton* btnAgain = new QPushButton("Jugar de nuevo", &finalDialog);
                    QPushButton* btnExit = new QPushButton("Salir", &finalDialog);
                    btnLay->addWidget(btnAgain);
                    btnLay->addWidget(btnExit);
                    mainLay->addLayout(btnLay);

                    // Conexiones
                    connect(btnAgain, &QPushButton::clicked, [&]() {
                        finalDialog.accept();
                    });
                    connect(btnExit, &QPushButton::clicked, [&]() {
                        finalDialog.reject();
                    });

                    if (finalDialog.exec() == QDialog::Accepted) {
                        // Jugar de nuevo
                        resetBoard(true);
                    } else {
                        // Salir => antes de cerrar, mostramos el marcador final
                        mostrarMarcadorFinal();
                        //close();
                    }
                    */
                    return;
                }

                // Cambiar turno
                currentPlayer = (currentPlayer == 1) ? 2 : 1;
                if (playAgainstCPU && currentPlayer == 2) {
                    cpuTimer->start(500);
                }
            } else {
                QMessageBox::warning(this, "Columna llena", "Columna llena. Elige otra.");
            }
        }
    }
}

void PantallaJuego::mouseMoveEvent(QMouseEvent *event)
{
    updateHighlightedColumn(event->pos().x());
}

void PantallaJuego::updateHighlightedColumn(int mouseX)
{
    QRect geom = geometry();
    int width = geom.width();
    int x0 = (width - (cols*cellSize)) / 2;

    int col = (mouseX - x0) / cellSize;
    if (col >= 0 && col < cols) {
        if (col != highlightedColumn) {
            highlightedColumn = col;
            update();
        }
    } else {
        if (highlightedColumn != -1) {
            highlightedColumn = -1;
            update();
        }
    }
}

bool PantallaJuego::dropDisc(int column, int &row)
{
    for (row = rows-1; row >= 0; row--) {
        if (tablero[row][column] == 0) {
            tablero[row][column] = currentPlayer;
            return true;
        }
    }
    return false;
}

bool PantallaJuego::checkWin(int row, int col)
{
    int pv = tablero[row][col];
    if (pv == 0) return false;

    QVector<QPair<int,int>> directions = {
        {0,1}, {1,0}, {1,1}, {1,-1}
    };
    for (auto dir : directions) {
        int count = 1;
        // sentido +dir
        int rr = row + dir.first;
        int cc = col + dir.second;
        while (rr>=0 && rr<rows && cc>=0 && cc<cols && tablero[rr][cc] == pv) {
            count++;
            rr += dir.first;
            cc += dir.second;
        }
        // sentido -dir
        rr = row - dir.first;
        cc = col - dir.second;
        while (rr>=0 && rr<rows && cc>=0 && cc<cols && tablero[rr][cc] == pv) {
            count++;
            rr -= dir.first;
            cc -= dir.second;
        }
        if (count >= 4){
            playing = false;
            return true;
        }
    }
    return false;
}

void PantallaJuego::cpuMove()
{
    int column, row;
    do {
        column = std::rand() % cols;
    } while (!dropDisc(column, row));

    update();
    if (checkWin(row, column)) {
        // CPU gana
        // Marcador
        totalGames++;
        p2Wins++; // CPU la consideramos "Jugador 2"
        mostrarMarcadorFinal("CPU");
        //close();
        return;
    }
    currentPlayer = 1;
}

void PantallaJuego::resetBoard(bool alternateTurn)
{
    // Poner todo a 0
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            tablero[r][c] = 0;
        }
    }
    if (twoPlayersMode && alternateTurn) {
        currentPlayer = (currentPlayer == 1) ? 2 : 1;
    } else {
        currentPlayer = 1;
    }
    highlightedColumn = -1;
    playing = true;
    update();
}

// Muestra un diálogo con el "marcador final" (cuántas ganó p1 / p2)
void PantallaJuego::mostrarMarcadorFinal(QString ganador)
{
    // Creamos un QDialog "scoreDialog"
    QDialog scoreDialog(this);
    scoreDialog.setWindowTitle("Marcador de la sesión");

    QVBoxLayout* mainLay = new QVBoxLayout(&scoreDialog);
    QString info;

    // 2 jugadores
    if (twoPlayersMode && p1 && p2) {
        info = QString("El ganador ha sido %6\n"
                       "Partidas jugadas: %1\n"
                       "%2 ha ganado %3 veces\n"
                       "%4 ha ganado %5 veces\n")
                .arg(totalGames)
                .arg(p1->getNickName())
                .arg(p1Wins)
                .arg(p2->getNickName())
                .arg(p2Wins)
                .arg(ganador);
    } else {
        // vs CPU => p1Wins es "tú", p2Wins es "CPU"
        info = QString("El ganador ha sido %5\n"
                       "Partidas jugadas: %1\n"
                       "%4 has ganado: %2\n"
                       "CPU ha ganado: %3\n")
                .arg(totalGames)
                .arg(p1Wins)
                .arg(p2Wins)
                .arg(p1->getNickName())
                .arg(ganador);
    }
    QLabel* lbl = new QLabel(info, &scoreDialog);
    mainLay->addWidget(lbl);

    // Botones
    QHBoxLayout* btnLay = new QHBoxLayout;
    QPushButton* btnReplay = new QPushButton("Volver a jugar", &scoreDialog);
    QPushButton* btnClose = new QPushButton("Cerrar", &scoreDialog);
    btnLay->addWidget(btnReplay);
    btnLay->addWidget(btnClose);
    mainLay->addLayout(btnLay);

    // Conexiones
    connect(btnReplay, &QPushButton::clicked, [&]() {
        // Reiniciamos el tablero
        scoreDialog.accept();
        resetBoard(/*alternateTurn=*/true);
    });
    connect(btnClose, &QPushButton::clicked, [&]() {
        scoreDialog.reject();
    });

    // Mostrar modal
    if (scoreDialog.exec() == QDialog::Rejected) {
        // Si cierra el scoreboard => close total
        //close();
    }
}
