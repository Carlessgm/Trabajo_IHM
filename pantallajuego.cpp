#include "pantallajuego.h"
#include "ui_pantallajuego.h"

#include <QMessageBox>
#include <QMouseEvent>
#include <cstdlib>
#include <ctime>

PantallaJuego::PantallaJuego(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaJuego)
    , rows(7)
    , cols(8)
    , currentPlayer(1)
    , highlightedColumn(-1)
    , playAgainstCPU(true)  // por defecto, vs CPU
    , p1(nullptr)
    , p2(nullptr)
    , twoPlayersMode(false)
{
    ui->setupUi(this);
    tablero.resize(rows, QVector<int>(cols, 0));

    setMinimumSize(cols * 40, rows * 40);
    setMouseTracking(true);

    // Semilla random
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Temporizador para CPU
    cpuTimer = new QTimer(this);
    cpuTimer->setSingleShot(true);
    connect(cpuTimer, &QTimer::timeout, this, &PantallaJuego::cpuMove);
}

// Constructor para 2 jugadores humanos
PantallaJuego::PantallaJuego(Player* jugador1, Player* jugador2, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaJuego)
    , rows(7)
    , cols(8)
    , currentPlayer(1)
    , highlightedColumn(-1)
    , playAgainstCPU(false) // 2 jugadores => false
    , p1(jugador1)
    , p2(jugador2)
    , twoPlayersMode(true)
{
    ui->setupUi(this);
    tablero.resize(rows, QVector<int>(cols, 0));

    setMinimumSize(cols * 40, rows * 40);
    setMouseTracking(true);

    // CPU no se utiliza
    cpuTimer = nullptr;  // o new QTimer(this), si prefieres, pero no se usará.

    // Semilla random para cualquier cosa, por si la quisieras
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
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

    // Ajustar cellSize
    if ((width / cols) < (height / rows)) {
        cellSize = width / cols;
    } else {
        cellSize = height / rows;
    }

    int x0 = (width - (cols * cellSize)) / 2;
    int y0 = (height - (rows * cellSize)) / 2;

    // Fondo del tablero (azul oscuro)
    painter.setBrush(Qt::darkBlue);
    painter.drawRect(x0, y0, cols * cellSize, rows * cellSize);

    // Fichas
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            QRect circleRect(x0 + (c * cellSize + 5),
                             y0 + (r * cellSize + 5),
                             cellSize - 10,
                             cellSize - 10);
            if (tablero[r][c] == 0) {
                painter.setBrush(Qt::white);
            } else if (tablero[r][c] == 1) {
                painter.setBrush(Qt::red);
            } else {
                painter.setBrush(Qt::yellow);
            }
            painter.drawEllipse(circleRect);
        }
    }

    // Círculo "fantasma" para la columna resaltada
    if (highlightedColumn != -1) {
        // Buscar la fila más baja disponible
        int dropRow = -1;
        for (int r = rows - 1; r >= 0; r--) {
            if (tablero[r][highlightedColumn] == 0) {
                dropRow = r;
                break;
            }
        }
        if (dropRow != -1) {
            QRect ghostRect(
                x0 + (highlightedColumn * cellSize + 5),
                y0 + (dropRow * cellSize + 5),
                cellSize - 10,
                cellSize - 10
            );
            painter.setBrush(QColor(200, 200, 255, 128));
            painter.drawEllipse(ghostRect);
        }
    }
}

void PantallaJuego::mousePressEvent(QMouseEvent *event)
{
    // Si es vs CPU y es turno de CPU, ignorar clicks
    if (playAgainstCPU && currentPlayer == 2) {
        return;
    }

    if (event->button() == Qt::LeftButton) {
        int mouseX = event->pos().x();

        QRect geom = geometry();
        int width = geom.width();
        int x0 = (width - (cols * cellSize)) / 2;
        int column = (mouseX - x0) / cellSize;

        if (column >= 0 && column < cols) {
            int row;
            if (dropDisc(column, row)) {
                update(); // Redibujar

                // Comprobar si alguien ganó
                if (checkWin(row, column)) {
                    // Quién ha ganado...
                    QString winnerName = (currentPlayer == 1) ? "Jugador 1" : "Jugador 2";
                    if (twoPlayersMode && p1 && p2) {
                        winnerName = (currentPlayer == 1) ? p1->getNickName() : p2->getNickName();
                    }

                    QMessageBox::information(this, "Victoria",
                                             QString("¡%1 ha ganado!").arg(winnerName));

                    // Registrar la partida si es 2 jugadores...
                    if (twoPlayersMode && p1 && p2) {
                        Player* winnerP = (currentPlayer == 1) ? p1 : p2;
                        Player* loserP  = (currentPlayer == 1) ? p2 : p1;
                        winnerP->addPoints(10);
                        Connect4::getInstance().registerRound(QDateTime::currentDateTime(), winnerP, loserP);
                    }

                    // --- Preguntamos al usuario ---
                    QMessageBox::StandardButton reply = QMessageBox::question(
                        this,
                        "Partida terminada",
                        "¿Quieres jugar otra partida?",
                        QMessageBox::Yes | QMessageBox::No
                        );
                    if (reply == QMessageBox::Yes) {
                        // Reiniciar el tablero y alternar el turno
                        resetBoard(true);
                    } else {
                        // Cerrar la ventana si no quiere seguir
                        close();
                    }
                    return;
                }

                // Cambiar de jugador
                currentPlayer = (currentPlayer == 1) ? 2 : 1;

                // Si es vs CPU y ahora es turno de CPU
                if (playAgainstCPU && currentPlayer == 2) {
                    cpuTimer->start(500); // Jugada de CPU en 0.5 s
                }
            } else {
                QMessageBox::warning(this, "Columna Llena",
                                     "La columna está llena. Elige otra.");
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
    int x0 = (width - (cols * cellSize)) / 2;

    int col = (mouseX - x0) / cellSize;
    if (col >= 0 && col < cols) {
        if (col != highlightedColumn) {
            highlightedColumn = col;
            update();
        }
    } else {
        // Fuera del tablero
        if (highlightedColumn != -1) {
            highlightedColumn = -1;
            update();
        }
    }
}

bool PantallaJuego::dropDisc(int column, int &row)
{
    for (row = rows - 1; row >= 0; row--) {
        if (tablero[row][column] == 0) {
            tablero[row][column] = currentPlayer;
            return true;
        }
    }
    return false;
}

bool PantallaJuego::checkWin(int row, int col)
{
    int player = tablero[row][col];
    if (player == 0) return false;

    // Direcciones: horizontal, vertical, diag /, diag
    QVector<QPair<int,int>> directions = {
        {0,1}, {1,0}, {1,1}, {1,-1}
    };

    for (auto dir : directions) {
        int count = 1;

        // hacia un lado
        int rr = row + dir.first;
        int cc = col + dir.second;
        while (rr >= 0 && rr < rows && cc >= 0 && cc < cols
               && tablero[rr][cc] == player)
        {
            count++;
            rr += dir.first;
            cc += dir.second;
        }
        // hacia el otro lado
        rr = row - dir.first;
        cc = col - dir.second;
        while (rr >= 0 && rr < rows && cc >= 0 && cc < cols
               && tablero[rr][cc] == player)
        {
            count++;
            rr -= dir.first;
            cc -= dir.second;
        }

        if (count >= 4) return true;
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
        QMessageBox::information(this, "Victoria", "¡La CPU ha ganado!");

        QMessageBox::StandardButton reply = QMessageBox::question(
            this,
            "Partida terminada",
            "¿Quieres jugar otra partida?",
            QMessageBox::Yes | QMessageBox::No
            );
        if (reply == QMessageBox::Yes) {
            // Re-iniciar
            resetBoard(false); // Modo CPU: no hace falta alternar, siempre inicia Jugador 1
        } else {
            close();
        }
        return;
    }


    currentPlayer = 1; // vuelve al jugador humano
}

void PantallaJuego::resetBoard(bool alternateTurn)
{
    // Poner todas las celdas a 0
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            tablero[r][c] = 0;
        }
    }
    // Alternar quién empieza si es modo 2 jugadores
    if (twoPlayersMode && alternateTurn) {
        currentPlayer = (currentPlayer == 1) ? 2 : 1;
    } else {
        // Modo CPU o no alternar: vuelve siempre a jugador 1
        currentPlayer = 1;
    }
    // Forzar repintado
    update();
}
