#include "cerrarsesion.h"

Cerrarsesion::Cerrarsesion(QWidget *parent, Player* User1, Player* User2)

    : QDialog(parent)
{

    qDebug() << User1 << " " << User2;
    setWindowTitle("Usuario a cerrar de sesión");

    QVBoxLayout* layout = new QVBoxLayout(this);


    QPushButton* btn_user1 = new QPushButton(User1->getNickName(), this);
    QPushButton* btn_user2 = new QPushButton(User2->getNickName(), this);

    layout->addWidget(new QLabel("Que usuario quieres logout:"));
    layout->addWidget(btn_user1);
    layout->addWidget(btn_user2);

    connect(btn_user1, &QPushButton::clicked, this, [=]() mutable{
        QMessageBox::information(this, "Cerrar Sesión", "La sesión de "+ User1->getNickName()+" se ha cerrado con éxito.");
        User1 = nullptr;
    });
    // 1) Dejar el puntero a null
    connect(btn_user2, &QPushButton::clicked, this, [=]() mutable{
        QMessageBox::information(this, "Cerrar Sesión", "La sesión de "+ User2->getNickName()+" se ha cerrado con éxito.");
        User2 = nullptr;
    });

}

