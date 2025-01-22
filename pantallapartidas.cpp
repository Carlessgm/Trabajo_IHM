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

    ui->comboBox_personas->addItem("Todos");
    QList<Player *> jugadores = Connect4::getInstance().getRanking();
    for(int i = 0; i < jugadores.length(); i++){
        ui->comboBox_personas->addItem(jugadores[i]->getNickName());
    }
    // Conectar señales para los filtros
    connect(ui->dateEdit_inicial, &QDateEdit::dateChanged, this, &PantallaPartidas::aplicarFiltro);
    connect(ui->dateEdit_final, &QDateEdit::dateChanged, this, &PantallaPartidas::aplicarFiltro);
    connect(ui->comboBox, &QComboBox::currentTextChanged, this, &PantallaPartidas::aplicarFiltro);
    connect(ui->comboBox_personas, &QComboBox::currentTextChanged, this, &PantallaPartidas::aplicarFiltro);

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

void PantallaPartidas::cargarPartidas(const QDate &fechaInicial, const QDate &fechaFinal, const int &tipo, const QString &persona)
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
    if(persona == "Todos"){
        QList<QDateTime> tiempos;
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
                if ((round->getTimestamp().date() < fechaInicial || round->getTimestamp().date() > fechaFinal) || tiempos.contains(round->getTimestamp())) {
                    continue;
                }
                tiempos.append(round->getTimestamp());
                Player *winner = round->getWinner();
                Player *loser = round->getLoser();
                if (!winner || !loser) {
                    qWarning() << "Datos incompletos en la ronda: ganador o perdedor nulo.";
                    continue;
                }
                Partida * partida_nueva = new Partida(
                    round->getTimestamp().toString("yyyy-MM-dd hh:mm:ss"),
                    winner->getNickName(),
                    winner->getAvatar(),
                    loser->getNickName(),
                    loser->getAvatar()
                    );
                partidas.append(partida_nueva);


            }
        }
    }else{
        Player *jugador_sel = Connect4::getInstance().getPlayer(persona);
        QList<Round*> rounds;
        rounds = Connect4::getInstance().getRoundsForPlayer(jugador_sel);
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
                round->getTimestamp().toString("yyyy-MM-dd hh:mm:ss"),
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
        switch (tipo) {
        case 0:
            partidasFiltradas.append(partida);
            break;
        case 1:
            if(partida->ganador == persona){
                partidasFiltradas.append(partida);
            }
            break;
        case 2:
            if(partida->perdedor == persona){
                partidasFiltradas.append(partida);
            }
            break;
        default:
            break;
        }

    }
    // Actualizar el modelo con las partidas filtradas
    tableModel->setPartidas(partidasFiltradas);
}


void PantallaPartidas::aplicarFiltro()
{
    if(ui->comboBox_personas->currentIndex() == 0){
        ui->comboBox->setCurrentIndex(0);
    }
    QDate fechaInicial = ui->dateEdit_inicial->date();
    QDate fechaFinal = ui->dateEdit_final->date();
    int tipo = ui->comboBox->currentIndex();
    QString persona = ui->comboBox_personas->currentText();

    cargarPartidas(fechaInicial, fechaFinal, tipo, persona);
}
