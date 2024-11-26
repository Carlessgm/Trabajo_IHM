#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QColorDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override; // Detectar movimiento del ratón

private:
    Ui::MainWindow *ui;
    int rows;
    int cols;
    int cellSize;

    QVector<QVector<int>> tablero; // 0: vacío, 1: jugador 1, 2: jugador 2
    int currentPlayer;
    int highlightedColumn; // Columna actualmente resaltada (-1 si ninguna está resaltada)

    bool dropDisc(int column, int &row);
    bool checkWin(int row, int col);
    void updateHighlightedColumn(int mouseX); // Actualizar la columna resaltada
};
#endif // MAINWINDOW_H
