/********************************************************************************
** Form generated from reading UI file 'pantallaregistro.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PANTALLAREGISTRO_H
#define UI_PANTALLAREGISTRO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_PantallaRegistro
{
public:
    QGridLayout *gridLayout;
    QLabel *labelConfirmarCorreo;
    QLineEdit *lineEditConfirmarCorreo;
    QLabel *labelAvatar;
    QLineEdit *lineEditCorreo;
    QLabel *labelContrasena;
    QLineEdit *lineEditConfirmarContrasena;
    QLineEdit *lineEditUsuario;
    QLabel *labelTitulo;
    QLabel *labelFechaNacimiento;
    QLabel *labelCorreo;
    QPushButton *botonSeleccionarAvatar;
    QDialogButtonBox *buttonBox;
    QLineEdit *lineEditContrasena;
    QLineEdit *lineEditAvatar;
    QLabel *labelNickname;
    QDateEdit *dateEditNacimiento;
    QLabel *labelConfirmarContrasena;

    void setupUi(QDialog *PantallaRegistro)
    {
        if (PantallaRegistro->objectName().isEmpty())
            PantallaRegistro->setObjectName("PantallaRegistro");
        PantallaRegistro->setWindowModality(Qt::WindowModality::ApplicationModal);
        PantallaRegistro->resize(500, 600);
        gridLayout = new QGridLayout(PantallaRegistro);
        gridLayout->setObjectName("gridLayout");
        labelConfirmarCorreo = new QLabel(PantallaRegistro);
        labelConfirmarCorreo->setObjectName("labelConfirmarCorreo");

        gridLayout->addWidget(labelConfirmarCorreo, 9, 0, 1, 1);

        lineEditConfirmarCorreo = new QLineEdit(PantallaRegistro);
        lineEditConfirmarCorreo->setObjectName("lineEditConfirmarCorreo");

        gridLayout->addWidget(lineEditConfirmarCorreo, 10, 0, 1, 1);

        labelAvatar = new QLabel(PantallaRegistro);
        labelAvatar->setObjectName("labelAvatar");

        gridLayout->addWidget(labelAvatar, 13, 0, 1, 1);

        lineEditCorreo = new QLineEdit(PantallaRegistro);
        lineEditCorreo->setObjectName("lineEditCorreo");

        gridLayout->addWidget(lineEditCorreo, 8, 0, 1, 1);

        labelContrasena = new QLabel(PantallaRegistro);
        labelContrasena->setObjectName("labelContrasena");

        gridLayout->addWidget(labelContrasena, 3, 0, 1, 1);

        lineEditConfirmarContrasena = new QLineEdit(PantallaRegistro);
        lineEditConfirmarContrasena->setObjectName("lineEditConfirmarContrasena");
        lineEditConfirmarContrasena->setEchoMode(QLineEdit::EchoMode::Password);

        gridLayout->addWidget(lineEditConfirmarContrasena, 6, 0, 1, 1);

        lineEditUsuario = new QLineEdit(PantallaRegistro);
        lineEditUsuario->setObjectName("lineEditUsuario");

        gridLayout->addWidget(lineEditUsuario, 2, 0, 1, 1);

        labelTitulo = new QLabel(PantallaRegistro);
        labelTitulo->setObjectName("labelTitulo");
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        labelTitulo->setFont(font);
        labelTitulo->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(labelTitulo, 0, 0, 1, 1);

        labelFechaNacimiento = new QLabel(PantallaRegistro);
        labelFechaNacimiento->setObjectName("labelFechaNacimiento");

        gridLayout->addWidget(labelFechaNacimiento, 11, 0, 1, 1);

        labelCorreo = new QLabel(PantallaRegistro);
        labelCorreo->setObjectName("labelCorreo");

        gridLayout->addWidget(labelCorreo, 7, 0, 1, 1);

        botonSeleccionarAvatar = new QPushButton(PantallaRegistro);
        botonSeleccionarAvatar->setObjectName("botonSeleccionarAvatar");

        gridLayout->addWidget(botonSeleccionarAvatar, 15, 0, 1, 1);

        buttonBox = new QDialogButtonBox(PantallaRegistro);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Orientation::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);

        gridLayout->addWidget(buttonBox, 16, 0, 1, 1);

        lineEditContrasena = new QLineEdit(PantallaRegistro);
        lineEditContrasena->setObjectName("lineEditContrasena");
        lineEditContrasena->setEchoMode(QLineEdit::EchoMode::Password);

        gridLayout->addWidget(lineEditContrasena, 4, 0, 1, 1);

        lineEditAvatar = new QLineEdit(PantallaRegistro);
        lineEditAvatar->setObjectName("lineEditAvatar");

        gridLayout->addWidget(lineEditAvatar, 14, 0, 1, 1);

        labelNickname = new QLabel(PantallaRegistro);
        labelNickname->setObjectName("labelNickname");

        gridLayout->addWidget(labelNickname, 1, 0, 1, 1);

        dateEditNacimiento = new QDateEdit(PantallaRegistro);
        dateEditNacimiento->setObjectName("dateEditNacimiento");
        dateEditNacimiento->setCalendarPopup(true);

        gridLayout->addWidget(dateEditNacimiento, 12, 0, 1, 1);

        labelConfirmarContrasena = new QLabel(PantallaRegistro);
        labelConfirmarContrasena->setObjectName("labelConfirmarContrasena");

        gridLayout->addWidget(labelConfirmarContrasena, 5, 0, 1, 1);


        retranslateUi(PantallaRegistro);
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, PantallaRegistro, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(PantallaRegistro);
    } // setupUi

    void retranslateUi(QDialog *PantallaRegistro)
    {
        PantallaRegistro->setWindowTitle(QCoreApplication::translate("PantallaRegistro", "Registro de Usuario", nullptr));
        labelConfirmarCorreo->setText(QCoreApplication::translate("PantallaRegistro", "Confirmar Correo Electr\303\263nico:", nullptr));
        lineEditConfirmarCorreo->setPlaceholderText(QCoreApplication::translate("PantallaRegistro", "Confirma tu correo electr\303\263nico", nullptr));
        labelAvatar->setText(QCoreApplication::translate("PantallaRegistro", "Avatar (opcional):", nullptr));
        lineEditCorreo->setPlaceholderText(QCoreApplication::translate("PantallaRegistro", "Introduce tu correo electr\303\263nico", nullptr));
        labelContrasena->setText(QCoreApplication::translate("PantallaRegistro", "Contrase\303\261a:", nullptr));
        lineEditConfirmarContrasena->setPlaceholderText(QCoreApplication::translate("PantallaRegistro", "Confirma tu contrase\303\261a", nullptr));
        lineEditUsuario->setPlaceholderText(QCoreApplication::translate("PantallaRegistro", "Introduce tu nombre de usuario", nullptr));
        labelTitulo->setText(QCoreApplication::translate("PantallaRegistro", "Formulario de Registro", nullptr));
        labelFechaNacimiento->setText(QCoreApplication::translate("PantallaRegistro", "Fecha de Nacimiento:", nullptr));
        labelCorreo->setText(QCoreApplication::translate("PantallaRegistro", "Correo Electr\303\263nico:", nullptr));
        botonSeleccionarAvatar->setText(QCoreApplication::translate("PantallaRegistro", "Seleccionar Avatar", nullptr));
        lineEditContrasena->setPlaceholderText(QCoreApplication::translate("PantallaRegistro", "Introduce tu contrase\303\261a", nullptr));
        lineEditAvatar->setPlaceholderText(QCoreApplication::translate("PantallaRegistro", "Introduce la ruta de tu avatar", nullptr));
        labelNickname->setText(QCoreApplication::translate("PantallaRegistro", "Nombre de Usuario:", nullptr));
        labelConfirmarContrasena->setText(QCoreApplication::translate("PantallaRegistro", "Confirmar Contrase\303\261a:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PantallaRegistro: public Ui_PantallaRegistro {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PANTALLAREGISTRO_H
