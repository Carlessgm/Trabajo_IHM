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
    void cargarPartidas(const QDate &fechaInicial, const QDate &fechaFinal, const int &tipo, const QString &persona); // Carga las partidas según el rango de fechas
    void aplicarFiltro(); // Aplica el filtro según las fechas seleccionadas
    void crearGraficoBarras(QList<QPair<int, int>> ganadas, QList<QPair<int,int>> perdidas, int personas_dist); //Genera los gráficos de barras de las partidas

};

#endif // PANTALLAPARTIDAS_H
