#ifndef PANTALLAPARTIDAS_H
#define PANTALLAPARTIDAS_H

#include <QWidget>
#include "partidatablemodel.h" // Modelo para manejar las partidas

namespace Ui {
class PantallaPartidas;
}

class PantallaPartidas : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaPartidas(QWidget *parent = nullptr);
    ~PantallaPartidas();

private:
    Ui::PantallaPartidas *ui;
    PartidaTableModel *tableModel; // Modelo para mostrar la tabla de partidas

    void cargarPartidas(); // Método para cargar las partidas
};

#endif // PANTALLAPARTIDAS_H
