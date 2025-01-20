#ifndef DLGSEGUNDOJUGADOR_H
#define DLGSEGUNDOJUGADOR_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include "connect4.h"  // Para usar Connect4 & Player

class DlgSegundoJugador : public QDialog
{
    Q_OBJECT
public:
    explicit DlgSegundoJugador(QWidget *parent = nullptr);
    Player* getLoggedPlayer() const { return m_loggedPlayer; }

private slots:
    void on_btnLogin_clicked();

private:
    QLineEdit* leNick;
    QLineEdit* lePass;
    Player* m_loggedPlayer = nullptr;
};

#endif // DLGSEGUNDOJUGADOR_H

