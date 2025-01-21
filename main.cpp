#include "mainwindow.h"
#include "connect4.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Usar la biblioteca Connec4Lib
    Connect4& game = Connect4::getInstance();

    // Registra algunos jugadores de ejemplo
    Player* player = game.registerPlayer("Player1", "player1@example.com", "Password123!", QDate(1990, 1, 1), 100);
    Player* player2 = game.registerPlayer("Player2", "player2@example.com", "Password123!", QDate(1990, 1, 1), 150);
    Player* player3 = game.registerPlayer("Player3", "player3@example.com", "Password123!", QDate(1990, 1, 1), 50);
    if (player && player2 && player3) {
        qDebug() << "Jugador registrado:" << player->getNickName();
        qDebug() << "Jugador registrado:" << player2->getNickName();
        qDebug() << "Jugador registrado:" << player3->getNickName();
    }

    MainWindow w;
    QFile file(":/estilos/estilos.qss"); // Asegúrate de que el archivo esté en el recurso
    // Intenta cargar la hoja de estilo desde los recursos
    if (file.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(file.readAll());
        w.setStyleSheet(styleSheet);
        qDebug() << "StyleSheet set";
        file.close();
    }else{
        qDebug() << "el fichero no se ha podido abrir";
    }
    w.show();
    return a.exec();
}
