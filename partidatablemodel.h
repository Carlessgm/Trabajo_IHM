#ifndef PARTIDATABLEMODEL_H
#define PARTIDATABLEMODEL_H

#include <QAbstractTableModel>
#include <QList>
#include <QImage>

// Clase que representa una partida individual
class Partida {
public:
    QString fecha;               // Fecha de la partida
    QString ganador;             // Nombre del jugador ganador
    QImage ganadorAvatar;        // Avatar del jugador ganador
    QString perdedor;            // Nombre del jugador perdedor
    QImage perdedorAvatar;       // Avatar del jugador perdedor

    Partida(const QString &fecha,
            const QString &ganador,
            const QImage &ganadorAvatar,
            const QString &perdedor,
            const QImage &perdedorAvatar)
        : fecha(fecha),
        ganador(ganador),
        ganadorAvatar(ganadorAvatar),
        perdedor(perdedor),
        perdedorAvatar(perdedorAvatar) {}
};

// Modelo para manejar las partidas en una tabla
class PartidaTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit PartidaTableModel(QObject *parent = nullptr);
    ~PartidaTableModel(); // Liberar memoria al destruir el modelo

    // Métodos obligatorios de QAbstractTableModel
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Método para actualizar las partidas en el modelo
    void setPartidas(const QList<Partida*> &partidas);

private:
    QList<Partida*> m_partidas; // Lista de punteros a las partidas
};

#endif // PARTIDATABLEMODEL_H
