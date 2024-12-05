#include "PantallaRegistro.h"
#include "ui_PantallaRegistro.h"
#include <QFileDialog>
#include <QDate>

PantallaRegistro::PantallaRegistro(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PantallaRegistro)
{
    ui->setupUi(this);

    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &PantallaRegistro::reject);
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &PantallaRegistro::okButtonClicked);
}

PantallaRegistro::~PantallaRegistro()
{
    delete ui;
}

void PantallaRegistro::on_botonSeleccionarAvatar_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Seleccionar Avatar"), "", tr("Imágenes (*.png *.jpg *.jpeg *.bmp)"));
    if (!filePath.isEmpty()) {
        ui->lineEditAvatar->setText(filePath);
    }
}

void PantallaRegistro::okButtonClicked()
{
    // Validar el formulario antes de continuar
    if (validarFormulario()) {
        // Aquí puedes realizar el registro del usuario, guardarlo en base de datos, etc.
        accept();  // Cierra la ventana y acepta el registro
        QMessageBox::information(this, "Registro Exitoso", "¡Te has registrado correctamente!");
    } else {
        mostrarError("Por favor, asegúrate de que todos los campos sean válidos.");
        return;
    }
}

bool PantallaRegistro::validarFormulario()
{
    int errores = 0;
    QString error_usuario = "";
    QString error_contrasena = "";
    QString error_mail = "";
    QString error_fecha = "";
    QString error_avatar = "";

    // Validar el nombre de usuario
    if (!validarNombreUsuario(ui->lineEditUsuario->text(), error_usuario)) {
        ui->lineEditUsuario->setText("");
        errores += 1;
    }

    // Validar las contraseñas
    if (!validarContrasenas(error_contrasena)) {
        ui->lineEditContrasena->setText("");
        ui->lineEditConfirmarContrasena->setText("");
        errores += 1;
    }

    // Validar el correo electrónico
    if (!validarEmail(ui->lineEditCorreo->text(),error_mail)) {
        ui->lineEditCorreo->clear();
        ui->lineEditConfirmarCorreo->clear();
        errores += 1;
    }

    // Validar la edad (mayor de 12 años)
    if (!validarEdad()) {
        error_fecha = "Debes ser mayor de 12 años para registrarte.";
        errores += 1;
    }

    // Validar si la ruta del avatar es válida (si se proporciona una)
    if (!ui->lineEditAvatar->text().isEmpty() && !QFile::exists(ui->lineEditAvatar->text())) {
        error_avatar = "La ruta del avatar no es válida.";
        return false;
    }

    if(errores == 0)
    {
        return true;
    }
    else
    {
        QString mensaje_final = error_usuario + error_contrasena + error_mail + error_fecha + error_avatar;
        mostrarError(mensaje_final);
        return false;
    }

}

bool PantallaRegistro::validarEmail(const QString &email, QString &tipo_error)
{
    QString correo = ui->lineEditCorreo->text();
    QString confirmarCorreo = ui->lineEditConfirmarCorreo->text();

    // Validar que las contraseñas coinciden
    if (correo != confirmarCorreo) {
        tipo_error = "Los emails no coinciden. \n";
        return false;
    }

    static QRegularExpression emailRegex("^[a-zA-Z0-9_+&*-]+(?:\\.[a-zA-Z0-9_+&*-]+)*@(?:[a-zA-Z0-9-]+\\.)+[a-zA-Z]{2,7}$");
    if(!emailRegex.match(email).hasMatch())
    {
        tipo_error = "Introduzca un correo electrónico válido \n";
        return false;
    }

    return true;
}

bool PantallaRegistro::validarContrasenas(QString &tipo_error)
{
    QString contrasena = ui->lineEditContrasena->text();
    QString confirmarContrasena = ui->lineEditConfirmarContrasena->text();

    // Validar que las contraseñas coinciden
    if (contrasena != confirmarContrasena) {
        tipo_error = "Las contraseñas no coinciden. \n";
        return false;
    }

    // Validar que la contraseña cumpla con los requisitos
    static QRegularExpression contrasenaRegex("^(?=.*[A-Z])(?=.*[a-z])(?=.*[0-9])(?=.*[!@#$%&*()\\-+=]).{8,20}$");
    if (!contrasenaRegex.match(contrasena).hasMatch()) {
        tipo_error = "La contraseña debe tener entre 8 y 20 caracteres, "
                     "incluyendo al menos una letra mayúscula, una minúscula, "
                     "un número y un carácter especial. \n";
        return false;
    }

    return true;
}

bool PantallaRegistro::validarNombreUsuario(const QString &nombreUsuario, QString &tipo_error)
{
    // Validar que el nombre de usuario tenga entre 6 y 15 caracteres y que no contenga espacios
    static QRegularExpression nombreUsuarioRegex("^[a-zA-Z0-9_-]{6,15}$");
    if (!nombreUsuarioRegex.match(nombreUsuario).hasMatch()) {
        tipo_error = "El nombre de usuario debe tener entre 6 y 15 caracteres, y no debe contener espacios. \n";
        return false;
    }

    // Verificar que el nombre de usuario no esté en uso (esto se simula aquí, pero debería ser una consulta a la base de datos)
    if (nombreUsuario == "pgarcia") {  // Simulación de nombre de usuario ya en uso
       tipo_error = "Este nombre de usuario ya está en uso. Elige otro. \n";
        return false;
    }

    return true;
}

bool PantallaRegistro::validarEdad()
{
    QDate fechaNacimiento = ui->dateEditNacimiento->date();
    int edad = fechaNacimiento.daysTo(QDate::currentDate()) / 365;

    if (edad <= 12) {
        return false;
    }

    return true;
}

void PantallaRegistro::mostrarError(const QString &mensaje)
{
    QMessageBox::warning(this, "Los errores son: \n", mensaje);
}
