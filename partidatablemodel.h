#ifndef PARTIDATABLEMODEL_H
#define PARTIDATABLEMODEL_H

#include <QAbstractTableModel>
#include <QImage>
#include <QList>

// Clase para representar una partida
class Partida {
public:
    QString fecha;
    QString ganador;
    QImage ganadorAvatar;
    QString perdedor;
    QImage perdedorAvatar;

    Partida(QString f, QString g, const QImage &ga, QString p, const QImage &pa)
        : fecha(f), ganador(g), ganadorAvatar(ga), perdedor(p), perdedorAvatar(pa) {}
};

// Modelo personalizado para manejar las partidas
class PartidaTableModel : public QAbstractTableModel {
    Q_OBJECT

public:
    explicit PartidaTableModel(QObject *parent = nullptr);
    void setPartidas(const QList<Partida*> &partidas);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

private:
    QList<Partida*> m_partidas; // Lista de partidas
};

#endif // PARTIDATABLEMODEL_H
