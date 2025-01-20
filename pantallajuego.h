#ifndef PANTALLAJUEGO_H
#define PANTALLAJUEGO_H

#include <QWidget>
#include <QPainter>
#include <QTimer>
#include "connect4.h"   // Para usar Player*

namespace Ui {
class PantallaJuego;
}

class PantallaJuego : public QWidget
{
    Q_OBJECT

public:
    // Constructor tradicional (vs CPU)
    explicit PantallaJuego(QWidget *parent = nullptr);

    // Constructor nuevo (2 jugadores)
    explicit PantallaJuego(Player* jugador1, Player* jugador2, QWidget *parent = nullptr);

    ~PantallaJuego();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    Ui::PantallaJuego *ui;
    int rows;
    int cols;
    int cellSize;

    QVector<QVector<int>> tablero; // 0: vacío, 1: jugador 1, 2: jugador 2
    int currentPlayer;
    int highlightedColumn;
    bool playAgainstCPU;

    // Para CPU
    QTimer *cpuTimer;

    // Para 2 jugadores:
    Player* p1;
    Player* p2;
    bool twoPlayersMode;

    bool dropDisc(int column, int &row);
    bool checkWin(int row, int col);
    void updateHighlightedColumn(int mouseX);
    void cpuMove();

    // Reiniciar partida
    void resetBoard(bool alternateTurn);
};

#endif // PANTALLAJUEGO_H
