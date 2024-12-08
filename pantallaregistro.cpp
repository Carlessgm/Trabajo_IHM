#include "PantallaRegistro.h"
#include "ui_PantallaRegistro.h"
#include <QFileDialog>
#include <QDate>
#include "connect4.h"

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
    if (validarFormulario()) {
        QString nickname = ui->lineEditUsuario->text();
        QString email = ui->lineEditCorreo->text();
        QString password = ui->lineEditContrasena->text();
        QDate birthdate = ui->dateEditNacimiento->date();
        QString avatarPath = ui->lineEditAvatar->text();

        Connect4& connect4 = Connect4::getInstance();

        // Verificar si el nombre de usuario ya existe
        if (connect4.existsNickName(nickname)) {
            mostrarError("El nombre de usuario ya está en uso. Por favor, elige otro.");
            return;
        }
        // Verificar si el correo ya está registrado
        if (connect4.existsEmail(email)) {
            mostrarError("El correo electrónico ya está registrado. Por favor, utiliza otro.");
            return;
        }
        // Registrar el jugador
        Player* newPlayer = connect4.registerPlayer(nickname, email, password, birthdate);

        if (newPlayer) {
            if (!avatarPath.isEmpty()) {
                // Guardar avatar si se necesita lógica adicional
                qDebug() << "Avatar seleccionado: " << avatarPath;
            }

            accept();  // Cierra la ventana
            QMessageBox::information(this, "Registro Exitoso", "¡Te has registrado correctamente!");
        } else {
            mostrarError("Ocurrió un error al registrar al usuario. Inténtalo de nuevo.");
        }
    } else {
        mostrarError("Por favor, asegúrate de que todos los campos sean válidos.");
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
