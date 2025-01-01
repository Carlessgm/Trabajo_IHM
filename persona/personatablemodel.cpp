// personatablemodel.cpp
#include "personatablemodel.h"
#include <QPixmap>

PersonaTableModel::PersonaTableModel(QObject *parent)
    : QAbstractTableModel(parent) {}

// Asigna una nueva lista de "Persona" al modelo (Datos cambiantes cada vez que se ejecuta)
void PersonaTableModel::setPersonas(const QList<Persona*>& personas) {
    beginResetModel();
    this->personas = personas;
    endResetModel();
}

// Se definen las dimensiones de la tabla (filas y columnas)
int PersonaTableModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return personas.size();
}

int PersonaTableModel::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return 3; // Nickname, Puntos, Avatar
}

// Proporciona los valores que se mostrarán en las celdas
QVariant PersonaTableModel::data(const QModelIndex &index, int role) const {
    // Evitar que se devuelvan datos fuera de las dimensiones
    if (!index.isValid() || index.row() >= personas.size() || index.column() >= 3)
        return QVariant();

    const Persona* persona = personas[index.row()];

    // Establecer la alineación para las celdas que contienen texto
    if (role == Qt::TextAlignmentRole) {
        return Qt::AlignCenter; // Centrar el texto en la celda
    }

    // Mostramos los valores que queremos en las celdas (Texto y Gráficos)
    if (role == Qt::DisplayRole) {
        switch (index.column()) {
        case 1: return persona->getNickname();
        case 2: return persona->getPuntos();
        }
    } else if (role == Qt::DecorationRole && index.column() == 0) {
        // Escalar la imagen para que se ajuste a la celda
        QImage avatar = persona->getAvatar();
        if(!avatar.isNull())
        {
            QSize cellSize(40, 40);
            QImage scaledAvatar = avatar.scaled(cellSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            return QPixmap::fromImage(scaledAvatar); // Devuelve el QPixmap escalado
        }
    }

    return QVariant();
}

// Define los encabezados de las columnas
QVariant PersonaTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
        case 0: return "Avatar";
        case 1: return "Nickname";
        case 2: return "Puntos";
        }
    }

    return QVariant();
}
