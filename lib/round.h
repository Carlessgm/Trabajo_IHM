#ifndef ROUND_H
#define ROUND_H

#include <QDateTime>
#include "Player.h"

class Connect4; // Declaración adelantada

class Round {
private:
    // Constructor privado: solo accesible desde Connect4
    Round(const QDateTime& timestamp, Player* winner, Player* loser);

    friend class Connect4; // Permite a Connect4 acceder al constructor
    friend class  Connect4DAO;

public:
    QDateTime getTimestamp() const;
    Player* getWinner() const;
    Player* getLoser() const;

private:
    QDateTime timestamp;
    Player* winner;
    Player* loser;
};

#endif // ROUND_H

