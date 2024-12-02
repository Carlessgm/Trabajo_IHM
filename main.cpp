#include "pantallainicio.h"
#include "connect4.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Usar la biblioteca Connec4Lib
    Connect4& game = Connect4::getInstance();

    Player* player = game.registerPlayer("Player1", "player1@example.com", "Password123!", QDate(1990, 1, 1), 100);
    if (player) {
        qDebug() << "Jugador registrado:" << player->getNickName();
    }

    PantallaInicio p;
    p.show();
    return a.exec();
}
