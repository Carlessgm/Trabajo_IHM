#include "pantallapartidas.h"
#include "ui_pantallapartidas.h"
#include "connect4.h"

#include <QtCore>
#include <QtGui>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts>
#include <QtWidgets>


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

    ui->tableView->setColumnWidth(0, 150); // Columna "Fecha"
    ui->tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch); // Columna "Ganador"
    ui->tableView->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch); // Columna "Perdedor"

    // Configurar opciones en el comboBox
    ui->comboBox->addItem("Todas las partidas");
    ui->comboBox->addItem("Partidas ganadas");
    ui->comboBox->addItem("Partidas perdidas");
    ui->comboBox->addItem("Cantidad partidas");
    ui->comboBox->addItem("Victoria/perdidas ratio");

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
    QList<QString> jugadores_dist;

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
    //Un jugador en concreto
    }else{

        Player *jugador_sel = Connect4::getInstance().getPlayer(persona);
        QList<Round*> rounds;
        rounds = Connect4::getInstance().getRoundsForPlayer(jugador_sel);
        jugadores_dist.append(jugador_sel->getNickName());
        for (Round* round : rounds) {
            if (!round) {
                qWarning() << "Ronda nula encontrada. Saltando.";
                continue;
            }
            if (round->getTimestamp().date() < fechaInicial || round->getTimestamp().date() > fechaFinal) {
                continue;
            }

            if(!jugadores_dist.contains(round->getLoser()->getNickName())){
                jugadores_dist.append(round->getLoser()->getNickName());
            }
            if(!jugadores_dist.contains(round->getWinner()->getNickName())){
                jugadores_dist.append(round->getWinner()->getNickName());
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
    QList<int> fechas_gan, fechas_per;
    int dia = ui->dateEdit_final->date().day() - ui->dateEdit_inicial->date().day();
    int mes = ui->dateEdit_final->date().month() - ui->dateEdit_inicial->date().month();
    int year = ui->dateEdit_final->date().year() - ui->dateEdit_inicial->date().year();
    int cant_ganadas = 0, cant_perdidas = 0, pers_dist = 0;
    QList<QPair<int, int>> ganadas, perdidas, personas_distintas;
        switch (tipo) {
        case 0:
            for (Partida* partida : partidas) {
            partidasFiltradas.append(partida);
            }
            break;

        case 1:
            for (Partida* partida : partidas) {
                if(partida->ganador == persona){
                   partidasFiltradas.append(partida);
                }
            }
            break;
        case 2:
            for (Partida* partida : partidas) {
                if(partida->perdedor == persona){
                    partidasFiltradas.append(partida);
                }
            }
            break;
        case 3:
            break;
        case 4:

            if(mes < 1 && year < 1){
                QPair<int, int> aux_pair;
                int dia_ant = 0;
                for(Partida* partida :partidas){
                    QString aux = partida->fecha.remove(0,8);
                    int dia_ini = aux.chopped(9).toInt();
                    if(partidas.first() == partida){
                        dia_ant = dia_ini;
                    }
                    qDebug() << dia_ini << " " << dia_ant;
                    if(dia_ini != dia_ant){

                        aux_pair.first = dia_ant;
                        aux_pair.second = cant_ganadas;
                        ganadas.append(aux_pair);
                        aux_pair.second = cant_perdidas;
                        perdidas.append(aux_pair);
                        cant_ganadas = 0;
                        cant_perdidas = 0;
                        aux_pair.first = dia_ini;
                    }
                    if(partida->ganador == persona){
                        cant_ganadas++;
                    }
                    if(partida->perdedor == persona){
                        cant_perdidas++;
                    }
                    dia_ant = dia_ini;
                }
                aux_pair.second = (cant_ganadas);
                ganadas.append(aux_pair);
                aux_pair.second = (cant_perdidas);
                perdidas.append(aux_pair);
            }


            if(mes > 1 && year < 1){
                    QPair<int, int> aux_pair;
                    int dia_ant = 0;
                    for(Partida* partida :partidas){
                        QString aux = partida->fecha.remove(0,5);
                        int dia_ini = aux.chopped(12).toInt();
                        if(partidas.first() == partida){
                            dia_ant = dia_ini;
                        }
                        qDebug() << dia_ini << " " << dia_ant;
                        if(dia_ini != dia_ant){

                            aux_pair.first = dia_ant;
                            aux_pair.second = cant_ganadas;
                            ganadas.append(aux_pair);
                            aux_pair.second = cant_perdidas;
                            perdidas.append(aux_pair);
                            cant_ganadas = 0;
                            cant_perdidas = 0;
                            aux_pair.first = dia_ini;
                        }
                        if(partida->ganador == persona){
                            cant_ganadas++;
                        }
                        if(partida->perdedor == persona){
                            cant_perdidas++;
                        }
                        dia_ant = dia_ini;
                    }
                    aux_pair.second = (cant_ganadas);
                    ganadas.append(aux_pair);
                    aux_pair.second = (cant_perdidas);
                    perdidas.append(aux_pair);
            }

            if(year > 1){

                QPair<int, int> aux_pair;
                int dia_ant = 0;
                for(Partida* partida :partidas){
                    QString aux = partida->fecha;
                    int dia_ini = aux.chopped(15).toInt();
                    if(partidas.first() == partida){
                        dia_ant = dia_ini;
                        aux_pair.first = dia_ant;
                    }
                    qDebug() << dia_ini << " " << dia_ant;
                    if(dia_ini != dia_ant){

                        aux_pair.first = dia_ant;
                        aux_pair.second = cant_ganadas;
                        ganadas.append(aux_pair);
                        aux_pair.second = cant_perdidas;
                        perdidas.append(aux_pair);
                        cant_ganadas = 0;
                        cant_perdidas = 0;
                        aux_pair.first = dia_ini;
                    }
                    if(partida->ganador == persona){
                        cant_ganadas++;
                    }
                    if(partida->perdedor == persona){
                        cant_perdidas++;
                    }
                    dia_ant = dia_ini;
                }
                aux_pair.second = (cant_ganadas);
                ganadas.append(aux_pair);
                aux_pair.second = (cant_perdidas);
                perdidas.append(aux_pair);
            }

            qDebug() << ganadas;
            qDebug() << perdidas;
            break;
        default:
            break;
        }

    if(!ui->layout_aux->isEmpty()){
        QLayoutItem *child;
        while ((child = ui->layout_aux->takeAt(0)) != nullptr) {
            if (child->widget()) {
                child->widget()->deleteLater();
            }
            delete child;
        }
    }
    // Actualizar el modelo con las partidas filtradas
    if(tipo <= 2){
        tableModel->setPartidas(partidasFiltradas);
        ui->tableView->show();
    }
    if(tipo == 4){
        ui->tableView->hide();
        crearGraficoBarras(ganadas, perdidas, pers_dist);
    }
    if(tipo == 3){

    }
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

void PantallaPartidas::crearGraficoBarras(QList<QPair<int, int>> cantidad_gan, QList<QPair<int, int>> cantidad_per, int personas_dist)
{
    // Crear un conjunto de datos de ejemplo
    QBarSet *setGanadas = new QBarSet("Ganadas");
    QBarSet *setPerdidas = new QBarSet("Perdidas");

    QList<QPair<int, int>> aux_cantidad_gan = cantidad_gan;
    int dias = ui->dateEdit_final->date().day() - ui->dateEdit_inicial->date().day();
    int meses = ui->dateEdit_final->date().month() - ui->dateEdit_inicial->date().month();
    int year = ui->dateEdit_final->date().year() - ui->dateEdit_inicial->date().year();

    // Añadir datos
    if(meses < 1){
        for(int i = 1; i <= ui->dateEdit_final->date().day(); i++){
            if(!aux_cantidad_gan.empty()){
                if(aux_cantidad_gan.first().first == i){
                    *setGanadas << aux_cantidad_gan.first().second;
                    aux_cantidad_gan.pop_front();
                }else{
                    *setGanadas << 0;
                }
            }
        }
        for(int i = 1; i <= ui->dateEdit_final->date().day(); i++){
            if(!cantidad_per.empty()){
                if(cantidad_per.first().first == i){
                    *setPerdidas << cantidad_per.first().second;
                    cantidad_per.pop_front();
                }else{
                    *setPerdidas << 0;
                }
            }
        }
    }
    if(meses > 1 && year < 1){
        for(int i = 1; i <= ui->dateEdit_final->date().month(); i++){
            if(!aux_cantidad_gan.empty()){
                if(aux_cantidad_gan.first().first == i){
                    *setGanadas << aux_cantidad_gan.first().second;
                    aux_cantidad_gan.pop_front();
                }else{
                    *setGanadas << 0;
                }
            }
        }
        for(int i = 1; i <= ui->dateEdit_final->date().month(); i++){
            if(!cantidad_per.empty()){
                if(cantidad_per.first().first == i){
                    *setPerdidas << cantidad_per.first().second;
                    cantidad_per.pop_front();
                }else{
                    *setPerdidas << 0;
                }
            }

        }
    }
    if(year > 1){
        for(int i = 1; i <= ui->dateEdit_final->date().year(); i++){
            if(!aux_cantidad_gan.empty()){
                if(aux_cantidad_gan.first().first == i){
                    *setGanadas << aux_cantidad_gan.first().second;
                    aux_cantidad_gan.pop_front();
                }else{
                    *setGanadas << 0;
                }
            }
        }
        for(int i = 1; i <= ui->dateEdit_final->date().year(); i++){
            if(!cantidad_per.empty()){
                if(cantidad_per.first().first == i){
                    *setPerdidas << cantidad_per.first().second;
                    cantidad_per.pop_front();
                }else{
                    *setPerdidas << 0;
                }
            }
        }
    }

    // Crear la serie de barras
    QBarSeries *series_per = new QBarSeries();
    QStackedBarSeries *series = new QStackedBarSeries();
    series->append(setGanadas);
    series->append(setPerdidas);

    // Crear el gráfico
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Cantidad de ganadas resepecto perdidas");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    // Añadir categorías en el eje X
    QValueAxis *axisX = new QValueAxis();
    if(meses < 1){
        axisX->setRange(ui->dateEdit_inicial->date().day(), ui->dateEdit_final->date().day());
    }
    if(meses > 1 && year < 1){
        axisX->setRange(ui->dateEdit_inicial->date().month(),ui->dateEdit_final->date().month());
    }
    if(year > 1){
        axisX->setRange(ui->dateEdit_inicial->date().year(), ui->dateEdit_final->date().year());
    }

    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    // Configurar el eje Y
    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, 20);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    // Crear la vista del gráfico
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Agregar el gráfico al layout de la interfaz

    ui->layout_aux->addWidget(chartView);
}
