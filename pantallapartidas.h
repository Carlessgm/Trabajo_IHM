#ifndef PANTALLAPARTIDAS_H
#define PANTALLAPARTIDAS_H

#include <QWidget>
#include <QDate>
#include "partidatablemodel.h"

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
    PartidaTableModel *tableModel; // Modelo para manejar las partidas en la tabla

    // Métodos
    void cargarPartidas(const QDate &fechaInicial, const QDate &fechaFinal, const QString &tipo); // Carga las partidas según el rango de fechas
    void aplicarFiltro(); // Aplica el filtro según las fechas seleccionadas
};

#endif // PANTALLAPARTIDAS_H
