#include "pantallapartidas.h"
#include "ui_pantallapartidas.h"

PantallaPartidas::PantallaPartidas(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PantallaPartidas)
{
    ui->setupUi(this);

    // Configurar QComboBox con las opciones
    ui->comboBox->addItem("Partidas Realizadas");
    ui->comboBox->addItem("Partidas Ganadas");
    ui->comboBox->addItem("Partidas Perdidas");

    // Conectar la selección del combo box al método mostrarPartidas
    connect(ui->comboBox, &QComboBox::currentIndexChanged, this, &PantallaPartidas::mostrarPartidas);

    // Configurar QTableWidget
    ui->tableWidget->setColumnCount(3); // Número de columnas
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Fecha" << "Ganador" << "Perdedor");

    // Cargar las partidas iniciales
    cargarPartidasRealizadas();
}

PantallaPartidas::~PantallaPartidas()
{
    delete ui;
}

void PantallaPartidas::mostrarPartidas(int index)
{
    switch (index) {
    case 0: // Partidas Realizadas
        cargarPartidasRealizadas();
        break;
    case 1: // Partidas Ganadas
        cargarPartidasGanadas();
        break;
    case 2: // Partidas Perdidas
        cargarPartidasPerdidas();
        break;
    default:
        break;
    }
}

void PantallaPartidas::cargarPartidasRealizadas()
{
    ui->tableWidget->setRowCount(0); // Limpiar tabla

    // Ejemplo de datos
    ui->tableWidget->insertRow(0);
    ui->tableWidget->setItem(0, 0, new QTableWidgetItem("2025-01-01"));
    ui->tableWidget->setItem(0, 1, new QTableWidgetItem("Juan"));
    ui->tableWidget->setItem(0, 2, new QTableWidgetItem("Pedro"));

    ui->tableWidget->insertRow(1);
    ui->tableWidget->setItem(1, 0, new QTableWidgetItem("2025-01-02"));
    ui->tableWidget->setItem(1, 1, new QTableWidgetItem("Luis"));
    ui->tableWidget->setItem(1, 2, new QTableWidgetItem("Ana"));
}

void PantallaPartidas::cargarPartidasGanadas()
{
    ui->tableWidget->setRowCount(0); // Limpiar tabla

    // Ejemplo de datos
    ui->tableWidget->insertRow(0);
    ui->tableWidget->setItem(0, 0, new QTableWidgetItem("2025-01-03"));
    ui->tableWidget->setItem(0, 1, new QTableWidgetItem("Mario"));
    ui->tableWidget->setItem(0, 2, new QTableWidgetItem("Máquina"));
}

void PantallaPartidas::cargarPartidasPerdidas()
{
    ui->tableWidget->setRowCount(0); // Limpiar tabla

    // Ejemplo de datos
    ui->tableWidget->insertRow(0);
    ui->tableWidget->setItem(0, 0, new QTableWidgetItem("2025-01-04"));
    ui->tableWidget->setItem(0, 1, new QTableWidgetItem("Máquina"));
    ui->tableWidget->setItem(0, 2, new QTableWidgetItem("Pedro"));
}
