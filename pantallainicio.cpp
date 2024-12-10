#include "pantallainicio.h"
#include "ui_pantallainicio.h"
#include "pantallajuego.h"
#include "pantallaregistro.h"
#include "connect4.h"
#include <QMessageBox>

PantallaInicio::PantallaInicio(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PantallaInicio)
{
    ui->setupUi(this);

    // Conectar el botón de inicio de sesión
    connect(ui->botonIniciarSesion, &QPushButton::clicked, this, &PantallaInicio::onbotonIniciarSesion_clicked);

    // Conectar el botón de registro (puedes dejarlo vacío por ahora)
    connect(ui->botonRegistrar, &QPushButton::clicked, this, &PantallaInicio::onbotonRegistrar_clicked);
}

PantallaInicio::~PantallaInicio()
{
    delete ui;
}

void PantallaInicio::onbotonRegistrar_clicked()
{
    //QMessageBox::information(this, "Registro", "Función de registro en desarrollo.");
    // Abrimos la ventana de registro
    PantallaRegistro *pr = new PantallaRegistro(this);
    pr->show();
}

void PantallaInicio::onbotonIniciarSesion_clicked()
{
    QString usuario = ui->lineUsuario->text();
    QString contrasena = ui->lineContrasena->text();

    if (usuario.isEmpty() || contrasena.isEmpty()) {
        QMessageBox::warning(this, "Error", "Por favor, complete todos los campos.");
        return;
    }

    // Llamar a la función de login del juego
    Connect4& game = Connect4::getInstance();
    Player* player = game.loginPlayer(usuario, contrasena);

    if (player) {
        QMessageBox::information(this, "Inicio de sesión exitoso", "Bienvenido, " + player->getNickName() + "!");
        qDebug() << "Jugador logueado: " << player->getNickName();
        delete player; // Si player fue retornado desde DAO, elimina para evitar fugas
        // Abrimos la ventana de juego
        /*PantallaJuego *w = new PantallaJuego(this);
        w->show();
        // Cerramos la ventana de Inicio
        this->close();*/
    } else {
        QMessageBox::warning(this, "Error", "Usuario o contraseña incorrectos.");
    }
}
