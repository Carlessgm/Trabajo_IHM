#ifndef CONNECT4DAO_H
#define CONNECT4DAO_H

#include <QSqlDatabase>
#include <QList>
#include <QMap>
#include "Player.h"
#include "Round.h"

class Connect4DAO {
public:
    static Connect4DAO& getInstance();

    bool initializeDatabase(const QString& dbName);
    bool addPlayer(const Player& player);
    Player* getPlayer(const QString& nickName);
    bool addRound(const Round& round);
    QList<Round*> getRoundsForPlayer(const QString& nickName);
    QList<Player*> getRanking();
    void clearAllData();

private:
    Connect4DAO() {}
    ~Connect4DAO();

    Connect4DAO(const Connect4DAO&) = delete;
    Connect4DAO& operator=(const Connect4DAO&) = delete;

    QSqlDatabase db;
};

#endif // CONNECT4DAO_H


