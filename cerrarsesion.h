#ifndef CERRARSESION_H
#define CERRARSESION_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include "connect4.h"  // Para usar Connect4 & Player
class Cerrarsesion : public QDialog
{
public:
    explicit Cerrarsesion(QWidget *parent = nullptr, Player* User1 = nullptr, Player* User2 = nullptr);

signals:
    //void usuario_logout(Player* user);

};
#endif // CERRARSESION_H
