#include "pantallapartidas.h"
#include "ui_pantallapartidas.h"
#include "connect4.h"

PantallaPartidas::PantallaPartidas(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaPartidas)
    , tableModel(new PartidaTableModel(this)) // Crear el modelo
{
    ui->setupUi(this);

    // Configurar la tabla para usar el modelo
    ui->tableView->setModel(tableModel);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->verticalHeader()->setDefaultSectionSize(50);

    // Configurar opciones en el comboBox existente
    ui->comboBox->addItem("Todas las partidas");
    ui->comboBox->addItem("Partidas ganadas");
    ui->comboBox->addItem("Partidas perdidas");

    // Conectar señales para los filtros
    connect(ui->dateEdit_inicial, &QDateEdit::dateChanged, this, &PantallaPartidas::aplicarFiltro);
    connect(ui->dateEdit_final, &QDateEdit::dateChanged, this, &PantallaPartidas::aplicarFiltro);
    connect(ui->comboBox, &QComboBox::currentTextChanged, this, &PantallaPartidas::aplicarFiltro);

    // Inicializar las fechas con valores predeterminados
    ui->dateEdit_inicial->setDate(QDate(2000, 1, 1));
    ui->dateEdit_final->setDate(QDate::currentDate());

    // Cargar partidas con el filtro inicial
    aplicarFiltro();
}

PantallaPartidas::~PantallaPartidas()
{
    delete ui;
}

void PantallaPartidas::cargarPartidas(const QDate &fechaInicial, const QDate &fechaFinal, const QString &tipo)
{
    QList<Partida*> partidas;
    // Obtener instancia de Connect4
    Connect4 *connect4 = nullptr;
    try {
        connect4 = &Connect4::getInstance();
    } catch (const std::exception &e) {
        qCritical() << "Excepción al obtener la instancia de Connect4:" << e.what();
        tableModel->setPartidas(partidas);
        return;
    }
    if (!connect4) {
        qCritical() << "Connect4::getInstance() devolvió un puntero nulo.";
        tableModel->setPartidas(partidas);
        return;
    }
    // Obtener todos los jugadores
    QList<Player*> jugadores = connect4->getRanking();
    for (Player* jugador : jugadores) {
        if (!jugador) continue; // Evitar punteros nulos
        // Obtener rondas para cada jugador
        QList<Round*> rounds;
        try {
            rounds = connect4->getRoundsForPlayer(jugador);
        } catch (const std::exception &e) {
            qCritical() << "Excepción al obtener las rondas para el jugador:" << jugador->getNickName() << " - " << e.what();
            continue;
        } catch (...) {
            qCritical() << "Error desconocido al obtener las rondas para el jugador:" << jugador->getNickName();
            continue;
        }
        for (Round* round : rounds) {
            if (!round) {
                qWarning() << "Ronda nula encontrada. Saltando.";
                continue;
            }
            if (round->getTimestamp().date() < fechaInicial || round->getTimestamp().date() > fechaFinal) {
                continue;
            }
            Player *winner = round->getWinner();
            Player *loser = round->getLoser();
            if (!winner || !loser) {
                qWarning() << "Datos incompletos en la ronda: ganador o perdedor nulo.";
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
    }
    // Aplicar filtro
    QList<Partida*> partidasFiltradas;
    for (Partida* partida : partidas) {
        if (tipo == "Todas las partidas") {
            partidasFiltradas.append(partida);
        }
    }
    // Actualizar el modelo con las partidas filtradas
    tableModel->setPartidas(partidasFiltradas);
}


void PantallaPartidas::aplicarFiltro()
{
    QDate fechaInicial = ui->dateEdit_inicial->date();
    QDate fechaFinal = ui->dateEdit_final->date();
    QString tipo = ui->comboBox->currentText();

    cargarPartidas(fechaInicial, fechaFinal, tipo);
}
