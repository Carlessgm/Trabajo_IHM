#include "pantallarecuperarclave.h"
#include "ui_pantallarecuperarclave.h"
#include "connect4.h"
#include <QMessageBox>
#include <QRandomGenerator>

PantallaRecuperarClave::PantallaRecuperarClave(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PantallaRecuperarClave),
    lastCode(-1)
{
    ui->setupUi(this);
    // Deja los lineEdits vacíos, etc.
}

PantallaRecuperarClave::~PantallaRecuperarClave()
{
    delete ui;
}

void PantallaRecuperarClave::on_btnEnviarCodigo_clicked()
{
    QString nick = ui->lineNick->text().trimmed();
    QString mail = ui->lineEmail->text().trimmed();

    // Lógica para verificar Player y correo
    Connect4 &game = Connect4::getInstance();
    Player *p = game.getPlayer(nick);
    if (!p) {
        QMessageBox::warning(this, "Error", "No existe ese usuario.");
        return;
    }
    if (p->getEmail() != mail) {
        QMessageBox::warning(this, "Error", "El correo no coincide.");
        return;
    }

    // Generar código
    int code = QRandomGenerator::global()->bounded(1000, 9999);
    lastCode = code;

    // Simular envío
    QMessageBox::information(this, "Código enviado",
                             QString("Tu código es %1 (simulado)").arg(code));
}

void PantallaRecuperarClave::on_btnValidarCodigo_clicked()
{
    if (lastCode < 0) {
        QMessageBox::warning(this, "Error", "Primero Enviar Código.");
        return;
    }
    int codeIngresado = ui->lineCodigo->text().toInt();
    if (codeIngresado == lastCode) {
        // Mostrar pass
        QString nick = ui->lineNick->text().trimmed();
        Player *p = Connect4::getInstance().getPlayer(nick);
        if (!p) {
            QMessageBox::warning(this, "Error", "No se encontró el usuario (raro).");
            return;
        }
        QString pass = p->getPassword();
        QMessageBox::information(this, "Recuperación",
                                 QString("Tu contraseña es: %1").arg(pass));
    } else {
        QMessageBox::warning(this, "Error", "Código incorrecto.");
    }
}
