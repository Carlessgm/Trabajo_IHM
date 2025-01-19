#include "partidatablemodel.h"
#include <QPixmap>

PartidaTableModel::PartidaTableModel(QObject *parent)
    : QAbstractTableModel(parent) {}

void PartidaTableModel::setPartidas(const QList<Partida*> &partidas) {
    beginResetModel();
    m_partidas = partidas;
    endResetModel();
}

int PartidaTableModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid()) return 0;
    return m_partidas.size();
}

int PartidaTableModel::columnCount(const QModelIndex &parent) const {
    if (parent.isValid()) return 0;
    return 3; // Fecha, Ganador, Perdedor
}

QVariant PartidaTableModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) return QVariant();

    Partida *partida = m_partidas.at(index.row());
    if (!partida) return QVariant();

    if (role == Qt::DisplayRole) {
        switch (index.column()) {
        case 0: return partida->fecha;
        case 1: return partida->ganador;
        case 2: return partida->perdedor;
        }
    } else if (role == Qt::DecorationRole) {
        if (index.column() == 1) {
            return QPixmap::fromImage(partida->ganadorAvatar).scaled(32, 32, Qt::KeepAspectRatio);
        } else if (index.column() == 2) {
            return QPixmap::fromImage(partida->perdedorAvatar).scaled(32, 32, Qt::KeepAspectRatio);
        }
    }

    return QVariant();
}

QVariant PartidaTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case 0: return "Fecha";
        case 1: return "Ganador";
        case 2: return "Perdedor";
        }
    }
    return QVariant();
}
