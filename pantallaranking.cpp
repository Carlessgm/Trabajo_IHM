#include "pantallaranking.h"
#include "ui_pantallaranking.h"
#include "connect4.h"

PantallaRanking::PantallaRanking(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaRanking)
{
    ui->setupUi(this);

    listModelP = new PersonaTableModel(this);

    // Obtener el ranking de jugadores de Connect4
    QList<Persona*> personas;
    auto players = Connect4::getInstance().getRanking();

    // Recorrer la lista de jugadores y convertirlos en objetos Persona
    for (int i = 0; i < players.size(); i++) {
        Player* player = players[i]; // Obtenemos al jugador actual (Ordenados por puntuación por el getRanking())
        personas.append(new Persona(player->getNickName(), player->getPoints(), player->getAvatar()));
    }

    listModelP->setPersonas(personas);

    ui->tableView->setModel(listModelP);
    ui->tableView->horizontalHeader()->setStretchLastSection(true); // Ajustar columnas
}

PantallaRanking::~PantallaRanking() {
    delete ui;
}
