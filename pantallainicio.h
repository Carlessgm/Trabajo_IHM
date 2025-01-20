#ifndef PANTALLAINICIO_H
#define PANTALLAINICIO_H

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

signals:
    void loginSuccessful();

private:
    Ui::PantallaInicio *ui;
    QWidget *currentWidget; // Puntero al widget actual
};

#endif // PANTALLAINICIO_H
