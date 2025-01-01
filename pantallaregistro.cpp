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
    QString error;
    bool prueba;
    ui->lineEditUsuario->setProperty("Valido", true);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &PantallaRegistro::reject);
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &PantallaRegistro::okButtonClicked);

    connect(ui->lineEditUsuario, &QLineEdit::editingFinished, this, &PantallaRegistro::validarNombreUsuario);
}

PantallaRegistro::~PantallaRegistro()
{
    delete ui;
}

void PantallaRegistro::on_botonSeleccionarAvatar_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Seleccionar Avatar"), "", tr("Imágenes (*.png *.jpg *.jpeg *.bmp)"));
    if (!filePath.isEmpty()) {
        if (QFile::exists(filePath)) {
            ui->lineEditAvatar->setText(filePath);  // Mostrar ruta en el QLineEdit
        } else {
            mostrarError("El archivo seleccionado no existe. Por favor, selecciona una ruta válida.");
        }
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
        /*if (connect4.existsEmail(email)) {
            mostrarError("El correo electrónico ya está registrado. Por favor, utiliza otro.");
            return;
        }*/
        // Cargamos la imagen desde la ruta que se indica
        QImage avatarImage;
        if (!avatarPath.isEmpty() && avatarImage.load(avatarPath)) {
            qDebug() << "Avatar cargado correctamente desde la ruta: " << avatarPath;
        } else {
            avatarImage = QImage();  // Crear una imagen vacía en caso de error.
            qDebug() << "No se pudo cargar la imagen desde la ruta: " << avatarPath;
        }

        // Registrar el jugador
        Player* newPlayer = connect4.registerPlayer(nickname, email, password, birthdate, 0, avatarImage);

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
    if (false) {
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
    if (!validarEmail(error_mail)) {
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
        errores += 1;
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

bool PantallaRegistro::validarEmail(QString &tipo_error)
{
    QString correo = ui->lineEditCorreo->text();
    QString confirmarCorreo = ui->lineEditConfirmarCorreo->text();

    // Validar que las contraseñas coinciden
    if (correo != confirmarCorreo) {
        tipo_error = "Los emails no coinciden. \n";
        return false;
    }

    static QRegularExpression emailRegex("^[a-zA-Z0-9_+&*-]+(?:\\.[a-zA-Z0-9_+&*-]+)*@(?:[a-zA-Z0-9-]+\\.)+[a-zA-Z]{2,7}$");
    if(!emailRegex.match(correo).hasMatch())
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

void PantallaRegistro::validarNombreUsuario()
{
    // Validar que el nombre de usuario tenga entre 6 y 15 caracteres y que no contenga espacios
    QString nombreUsuario = ui->lineEditUsuario->text();

    static QRegularExpression nombreUsuarioRegex("^[a-zA-Z0-9_-]{6,15}$");
    if (!nombreUsuarioRegex.match(nombreUsuario).hasMatch()) {
        //tipo_error = "El nombre de usuario debe tener entre 6 y 15 caracteres, y no debe contener espacios. \n";
        qDebug() << "He estado aqui";
        ui->lineEditUsuario->setStyleSheet("QLineEdit#lineEditUsuario{ border-color: #ff0000; background-color: #ff0000};");
        qDebug() << ui->lineEditUsuario->property("Valido");
    }

    // Verificar que el nombre de usuario no esté en uso (esto se simula aquí, pero debería ser una consulta a la base de datos)
    if (nombreUsuario == "pgarcia") {  // Simulación de nombre de usuario ya en uso
        //ipo_error = "Este nombre de usuario ya está en uso. Elige otro. \n";
        ui->lineEditUsuario->setStyleSheet("QLineEdit#lineEditUsuario{ border-color: #ff0000; background-color: #ff0000};");
    }
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
