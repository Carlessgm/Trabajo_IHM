#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QKeyEvent>
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

private:
    Ui::MainWindow *ui;
    int rows;
    int cols;
    int cellSize;

    QVector<QVector<int>> tablero; // 0: vacío, 1: jugador 1, 2: jugador 2
    int currentPlayer;

    bool dropDisc(int column, int &row);
    bool checkWin(int row, int col);

};
#endif // MAINWINDOW_H
