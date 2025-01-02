#ifndef PANTALLAPARTIDAS_H
#define PANTALLAPARTIDAS_H

#include <QWidget>

namespace Ui {
class PantallaPartidas;
}

class PantallaPartidas : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaPartidas(QWidget *parent = nullptr);
    ~PantallaPartidas();

private slots:
    void mostrarPartidas(int index);

private:
    Ui::PantallaPartidas *ui;

    void cargarPartidasRealizadas();
    void cargarPartidasGanadas();
    void cargarPartidasPerdidas();
};

#endif // PANTALLAPARTIDAS_H
