/********************************************************************************
** Form generated from reading UI file 'pantallajuego.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PANTALLAJUEGO_H
#define UI_PANTALLAJUEGO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PantallaJuego
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;

    void setupUi(QWidget *PantallaJuego)
    {
        if (PantallaJuego->objectName().isEmpty())
            PantallaJuego->setObjectName("PantallaJuego");
        PantallaJuego->resize(581, 390);
        verticalLayout = new QVBoxLayout(PantallaJuego);
        verticalLayout->setObjectName("verticalLayout");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");

        verticalLayout->addLayout(gridLayout);


        retranslateUi(PantallaJuego);

        QMetaObject::connectSlotsByName(PantallaJuego);
    } // setupUi

    void retranslateUi(QWidget *PantallaJuego)
    {
        PantallaJuego->setWindowTitle(QCoreApplication::translate("PantallaJuego", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PantallaJuego: public Ui_PantallaJuego {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PANTALLAJUEGO_H
