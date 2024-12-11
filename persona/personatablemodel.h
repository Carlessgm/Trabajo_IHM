// personatablemodel.h -> Modelo de datos personalizados "QAbstractTableModel" para mostrar lista de objetos Persona en una QTableView

#ifndef PERSONATABLEMODEL_H
#define PERSONATABLEMODEL_H

#include <QAbstractTableModel>
#include "persona.h"

class PersonaTableModel : public QAbstractTableModel {
    Q_OBJECT

public:
    explicit PersonaTableModel(QObject *parent = nullptr);

    // Lista de personas que se mostrarán en la tabla
    void setPersonas(const QList<Persona*>& personas);

    // Devuelve el número de filas y columnas de la tableView
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    // Proporciona los datos que se muestran en cada celda
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    // Define los encabezados de las columnas
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

private:
    QList<Persona*> personas;
};

#endif // PERSONATABLEMODEL_H
