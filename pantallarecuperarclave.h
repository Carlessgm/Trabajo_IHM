#ifndef PANTALLARECUPERARCLAVE_H
#define PANTALLARECUPERARCLAVE_H

#include <QWidget>

namespace Ui {
class PantallaRecuperarClave;
}

class PantallaRecuperarClave : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaRecuperarClave(QWidget *parent = nullptr);
    ~PantallaRecuperarClave();

private slots:
    void on_btnEnviarCodigo_clicked();
    void on_btnValidarCodigo_clicked();

private:
    Ui::PantallaRecuperarClave *ui;
    int lastCode;
};

#endif // PANTALLARECUPERARCLAVE_H

