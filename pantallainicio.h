#ifndef PANTALLAINICIO_H
#define PANTALLAINICIO_H

#include "Player.h"
#include <QWidget>
#include <qpushbutton.h>

namespace Ui {
class PantallaInicio;
}

class PantallaInicio : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaInicio(QWidget *parent = nullptr);
    ~PantallaInicio();

private slots:
    void onbotonIniciarSesion_clicked();
    void onbotonRegistrar_clicked();
    void on_botonOlvideContrasena_clicked();
signals:
    void loginSuccessful(Player* user);
    void forgotPasswordRequested();

private:
    Ui::PantallaInicio *ui;
    QWidget *currentWidget; // Puntero al widget actual
};

#endif // PANTALLAINICIO_H
