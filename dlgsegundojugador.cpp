#include "dlgsegundojugador.h"

DlgSegundoJugador::DlgSegundoJugador(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Login Segundo Jugador");

    QVBoxLayout* layout = new QVBoxLayout(this);

    leNick = new QLineEdit(this);
    lePass = new QLineEdit(this);
    lePass->setEchoMode(QLineEdit::Password);

    QPushButton* btnLogin = new QPushButton("Iniciar Sesión (2º Jugador)", this);

    layout->addWidget(new QLabel("Nickname:"));
    layout->addWidget(leNick);
    layout->addWidget(new QLabel("Contraseña:"));
    layout->addWidget(lePass);
    layout->addWidget(btnLogin);

    connect(btnLogin, &QPushButton::clicked, this, &DlgSegundoJugador::on_btnLogin_clicked);
}

void DlgSegundoJugador::on_btnLogin_clicked()
{
    QString nick = leNick->text();
    QString pass = lePass->text();

    Connect4& game = Connect4::getInstance();
    Player* p = game.loginPlayer(nick, pass);
    if (p) {
        m_loggedPlayer = p;
        accept();  // cierra el diálogo con estado "Accepted"
    } else {
        QMessageBox::warning(this, "Error", "Nickname o contraseña inválidos para el 2º jugador.");
    }
}
