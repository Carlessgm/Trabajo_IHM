#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QColorDialog>
#include <QTimer>
#include "connect4.h"

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

private slots:
    void showPantallaInicio();
    void showPantallaJuego();
    void showPantallaRanking();
    void showPantallaPartidas();
    void showPantallaJuegoDosJugadores();
    void showPantallaPerfil();
    void toggleDarkMode();
    void showPantallaRecuperarClave();
    void logout();

private:
    Ui::MainWindow *ui;
    QWidget *currentWidget; // Puntero al widget actual
    Player *currentUser;  // Guardamos el usuario actualmente logueado
    bool isDarkMode = false;
};
#endif // MAINWINDOW_H
