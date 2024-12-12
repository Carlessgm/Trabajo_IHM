/********************************************************************************
** Form generated from reading UI file 'pantallainicio.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PANTALLAINICIO_H
#define UI_PANTALLAINICIO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PantallaInicio
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *labelTitulo;
    QLineEdit *lineUsuario;
    QLineEdit *lineContrasena;
    QPushButton *botonIniciarSesion;
    QPushButton *botonRegistrar;

    void setupUi(QWidget *PantallaInicio)
    {
        if (PantallaInicio->objectName().isEmpty())
            PantallaInicio->setObjectName("PantallaInicio");
        PantallaInicio->resize(400, 300);
        verticalLayout = new QVBoxLayout(PantallaInicio);
        verticalLayout->setObjectName("verticalLayout");
        labelTitulo = new QLabel(PantallaInicio);
        labelTitulo->setObjectName("labelTitulo");
        labelTitulo->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(labelTitulo);

        lineUsuario = new QLineEdit(PantallaInicio);
        lineUsuario->setObjectName("lineUsuario");

        verticalLayout->addWidget(lineUsuario);

        lineContrasena = new QLineEdit(PantallaInicio);
        lineContrasena->setObjectName("lineContrasena");
        lineContrasena->setInputMethodHints(Qt::InputMethodHint::ImhNoAutoUppercase|Qt::InputMethodHint::ImhNoPredictiveText|Qt::InputMethodHint::ImhSensitiveData);
        lineContrasena->setEchoMode(QLineEdit::EchoMode::Password);

        verticalLayout->addWidget(lineContrasena);

        botonIniciarSesion = new QPushButton(PantallaInicio);
        botonIniciarSesion->setObjectName("botonIniciarSesion");

        verticalLayout->addWidget(botonIniciarSesion);

        botonRegistrar = new QPushButton(PantallaInicio);
        botonRegistrar->setObjectName("botonRegistrar");

        verticalLayout->addWidget(botonRegistrar);


        retranslateUi(PantallaInicio);

        QMetaObject::connectSlotsByName(PantallaInicio);
    } // setupUi

    void retranslateUi(QWidget *PantallaInicio)
    {
        PantallaInicio->setWindowTitle(QCoreApplication::translate("PantallaInicio", "Inicio de Sesi\303\263n", nullptr));
        labelTitulo->setText(QCoreApplication::translate("PantallaInicio", "Iniciar Sesi\303\263n", nullptr));
        lineUsuario->setPlaceholderText(QCoreApplication::translate("PantallaInicio", "Usuario", nullptr));
        lineContrasena->setPlaceholderText(QCoreApplication::translate("PantallaInicio", "Contrase\303\261a", nullptr));
        botonIniciarSesion->setText(QCoreApplication::translate("PantallaInicio", "Iniciar Sesi\303\263n", nullptr));
        botonRegistrar->setText(QCoreApplication::translate("PantallaInicio", "Registrarse", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PantallaInicio: public Ui_PantallaInicio {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PANTALLAINICIO_H
