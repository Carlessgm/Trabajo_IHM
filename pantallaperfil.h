#ifndef PANTALLAPERFIL_H
#define PANTALLAPERFIL_H

#include <QWidget>
#include "ui_pantallaperfil.h"
#include "Player.h"

namespace Ui {
class PantallaPerfil;
}

class PantallaPerfil : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaPerfil(Player *player, QWidget *parent = nullptr);
    ~PantallaPerfil();

private slots:
    void on_btnGuardar_clicked();
    void on_btnCancelar_clicked();
    void on_btnChangeAvatar_clicked();

private:
    Ui::PantallaPerfil *ui;
    Player* m_player;
    QString avatarPath; // donde guardamos ruta si elige una nueva

    bool validarCorreo(const QString &correo);
    bool validarContrasena(const QString &pass);
    bool validarEdad(const QDate &fechaNac);
};
#endif // PANTALLAPERFIL_H
