#ifndef CONNECT4_H
#define CONNECT4_H

#include <QString>
#include <QDir>
#include "Player.h"
#include "Round.h"

class Connect4 {
public:
    static Connect4& getInstance();

    // Métodos de negocio
    Player* registerPlayer(const QString &nickName, const QString& email,
                           const QString &password, const QDate& birthdate, int points);
    Player* registerPlayer(const QString& nickName, const QString& email,
                           const QString& password, const QDate& birthdate, int points, const QImage& avatar);

    Round* registerRound(const QDateTime& timestamp, Player* winner, Player* loser);
    Player* loginPlayer(const QString& nickName, const QString& password);
    Player* getPlayer(const QString& nickname);
    bool existsNickName(const QString& nickname);
    QList<Player*> getRanking();
    QList<Round*> getRoundsForPlayer(Player* player);

    void clearAllData();

private:
    Connect4(); // Constructor privado para Singleton
    ~Connect4();

    void initializeDatabase();

    Connect4(const Connect4&) = delete;
    Connect4& operator=(const Connect4&) = delete;

    QString databaseFilePath = "data.db"; // Nombre del archivo de base de datos
};

#endif // CONNECT4_H
