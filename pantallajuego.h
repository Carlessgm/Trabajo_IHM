#ifndef PANTALLAJUEGO_H
#define PANTALLAJUEGO_H

#include <QWidget>
#include <QPainter>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QColorDialog>
#include <QTimer>

namespace Ui {
class PantallaJuego;
}

class PantallaJuego : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaJuego(QWidget *parent = nullptr);
    ~PantallaJuego();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override; // Detectar movimiento del ratón

private:
    Ui::PantallaJuego *ui;
    int rows;
    int cols;
    int cellSize;

    QVector<QVector<int>> tablero; // 0: vacío, 1: jugador 1, 2: jugador 2
    int currentPlayer;
    int highlightedColumn; // Columna actualmente resaltada (-1 si ninguna está resaltada)
    bool playAgainstCPU;

    QTimer *cpuTimer;       // Temporizador para el movimiento de la CPU

    bool dropDisc(int column, int &row);
    bool checkWin(int row, int col);
    void updateHighlightedColumn(int mouseX); // Actualizar la columna resaltada
    void cpuMove();             // Realizar movimiento de la CPU
};

#endif // PANTALLAJUEGO_H
