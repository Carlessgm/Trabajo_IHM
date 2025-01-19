#include "pantallapartidas.h"
#include "ui_pantallapartidas.h"
#include "connect4.h"

PantallaPartidas::PantallaPartidas(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaPartidas)
{
    ui->setupUi(this);

    // Crear el modelo para manejar las partidas
    tableModel = new PartidaTableModel(this);

    // Configurar la tabla para usar el modelo
    ui->tableView->setModel(tableModel);
    ui->tableView->horizontalHeader()->setStretchLastSection(true); // Ajustar columnas al ancho disponible
    ui->tableView->verticalHeader()->setDefaultSectionSize(50);     // Altura de filas suficiente para los avatares

    // Cargar las partidas desde la base de datos
    cargarPartidas();
}

PantallaPartidas::~PantallaPartidas() {
    delete ui;
}

void PantallaPartidas::cargarPartidas() {
  /*  QList<Partida*> partidas;

    QList<Round*> rounds = Connect4::getInstance().getRoundsForPlayer(nullptr);
    if (rounds.isEmpty()) {
        qWarning() << "No se encontraron rondas en la base de datos.";
        return;
    }

    for (Round *round : rounds) {
        if (!round) {
            qWarning() << "Se encontró una ronda nula.";
            continue;
        }

        Player *winner = round->getWinner();
        Player *loser = round->getLoser();
        if (!winner || !loser) {
            qWarning() << "Datos incompletos: ganador o perdedor es nulo.";
            continue;
        }

        partidas.append(new Partida(
            round->getTimestamp().toString("yyyy-MM-dd"),
            winner->getNickName(),
            winner->getAvatar(),
            loser->getNickName(),
            loser->getAvatar()
            ));
    }

    tableModel->setPartidas(partidas);*/
}

