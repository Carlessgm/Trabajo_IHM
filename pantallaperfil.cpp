#include "pantallaperfil.h"
#include "ui_pantallaperfil.h"
#include <QFileDialog>
#include <QMessageBox>
#include <qregularexpression.h>

PantallaPerfil::PantallaPerfil(Player* player, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaPerfil)
    , m_player(player)
{
    ui->setupUi(this);

    // Rellenar campos con datos actuales
    ui->lineEmail->setText(player->getEmail());
    ui->dateEditBirth->setDate(player->getBirthdate());
    // contraseñas vacías por defecto
    ui->linePassword->setText("");
    ui->linePasswordConfirm->setText("");

    // Si el avatar no es nulo, mostrarlo
    QImage avatar = player->getAvatar();
    if (!avatar.isNull()) {
        ui->labelAvatarPreview->setPixmap(
            QPixmap::fromImage(avatar).scaled(80,80, Qt::KeepAspectRatio));
    }
}

PantallaPerfil::~PantallaPerfil()
{
    delete ui;
}

// Botón Guardar
void PantallaPerfil::on_btnGuardar_clicked()
{
    QString newEmail = ui->lineEmail->text().trimmed();
    QString pass = ui->linePassword->text();
    QString passC = ui->linePasswordConfirm->text();
    QDate birth = ui->dateEditBirth->date();

    // Validaciones
    if (!validarCorreo(newEmail)) {
        QMessageBox::warning(this, "Error", "Correo inválido.");
        return;
    }
    if (!validarEdad(birth)) {
        QMessageBox::warning(this, "Error", "Debes tener al menos 12 años.");
        return;
    }
    if (!pass.isEmpty()) {
        if (pass != passC) {
            QMessageBox::warning(this, "Error", "Las contraseñas no coinciden.");
            return;
        }
        if (!validarContrasena(pass)) {
            QMessageBox::warning(this, "Error",
                                 "La contraseña no cumple los requisitos.");
            return;
        }
    }

    // Aplicar cambios
    m_player->setEmail(newEmail);
    m_player->setBirthdate(birth);
    if (!pass.isEmpty()) {
        m_player->setPassword(pass);
    }
    if (!avatarPath.isEmpty()) {
        QImage newAv;
        newAv.load(avatarPath);
        m_player->setAvatar(newAv);
    }

    QMessageBox::information(this, "Perfil", "Datos guardados correctamente.");
}

// Botón Cancelar
void PantallaPerfil::on_btnCancelar_clicked()
{
    // Volver a la pantalla anterior
    // (suele ser setCentralWidget, así que destruimos esta)
    // Podrías hacer algo como:
    // parentWidget()->layout()->removeWidget(this);
    // delete this;
    // O dejas que MainWindow se encargue al cambiar la pantalla.

    // Por simplicidad:
    // QCoreApplication::postEvent(parentWidget(),
    //     new QCloseEvent()); // o algo similar
    // O sencillamente:
    QMessageBox::information(this, "Perfil", "No se han guardado cambios.");
}

// Cambiar avatar
void PantallaPerfil::on_btnChangeAvatar_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, "Seleccionar Avatar", "",
                                                "Imágenes (*.png *.jpg *.jpeg *.bmp)");
    if (!path.isEmpty()) {
        avatarPath = path;
        QPixmap pix(path);
        if (!pix.isNull()) {
            ui->labelAvatarPreview->setPixmap(pix.scaled(80,80, Qt::KeepAspectRatio));
        }
    }
}

// Validaciones
bool PantallaPerfil::validarCorreo(const QString &correo)
{
    static QRegularExpression emailRegex("^[a-zA-Z0-9_+&*-]+(?:\\.[a-zA-Z0-9_+&*-]+)*@"
                                         "(?:[a-zA-Z0-9-]+\\.)+[a-zA-Z]{2,7}$");
    return emailRegex.match(correo).hasMatch();
}

bool PantallaPerfil::validarContrasena(const QString &pass)
{
    static QRegularExpression passRegex("^(?=.*[A-Z])(?=.*[a-z])(?=.*[0-9])"
                                        "(?=.*[!@#$%&*()\\-+=]).{8,20}$");
    return passRegex.match(pass).hasMatch();
}

bool PantallaPerfil::validarEdad(const QDate &fechaNac)
{
    QDate hoy = QDate::currentDate();
    int edad = hoy.year() - fechaNac.year();
    if ((hoy.month() < fechaNac.month())
        || (hoy.month() == fechaNac.month() && hoy.day() < fechaNac.day())) {
        edad--;
    }
    return (edad >= 12);
}

