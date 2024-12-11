#ifndef PANTALLARANKING_H
#define PANTALLARANKING_H

#include <QWidget>
#include "personatablemodel.h"

namespace Ui {
class PantallaRanking;
}

class PantallaRanking : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaRanking(QWidget *parent = nullptr);
    ~PantallaRanking();

private:
    Ui::PantallaRanking *ui;
    PersonaTableModel *listModelP; // Modelo para mostrar la tabla del ranking
};

#endif // PANTALLARANKING_H
