#include "PantallaRegistro.h"
#include "ui_PantallaRegistro.h"
#include <QFileDialog>
#include <QDate>
#include <QStyle>
#include "connect4.h"

PantallaRegistro::PantallaRegistro(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PantallaRegistro)
{
    ui->setupUi(this);
    bool prueba;
    line_edits[0]= ui->lineEditUsuario;
    line_edits[1]= ui->lineEditCorreo;
    line_edits[2]= ui->lineEditConfirmarCorreo;
    line_edits[3]= ui->lineEditContrasena;
    line_edits[4]= ui->lineEditConfirmarContrasena;
    line_edits[5]= ui->lineEditAvatar;
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &PantallaRegistro::reject);
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &PantallaRegistro::okButtonClicked);
    ui->label->setProperty("aux", true);

    connect(ui->lineEditUsuario, &QLineEdit::editingFinished, this, &PantallaRegistro::validarNombreUsuario);
    connect(ui->lineEditContrasena, &QLineEdit::editingFinished, this, &PantallaRegistro::validarContrasenas);
    connect(ui->lineEditConfirmarContrasena, &QLineEdit::editingFinished, this, &PantallaRegistro::validarContrasenas);
    connect(ui->lineEditCorreo, &QLineEdit::editingFinished, this, &PantallaRegistro::validarEmail);
    connect(ui->lineEditConfirmarCorreo, &QLineEdit::editingFinished, this, &PantallaRegistro::validarEmail);
    connect(ui->dateEditNacimiento, &QDateEdit::editingFinished, this, &PantallaRegistro::validarEdad);

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
    }
}


bool PantallaRegistro::validarFormulario()
{

    for(int i = 0; i <= 4; i++){
        if(line_edits[i]->property("Valido") == false){
            mostrarError("Corrija los errores (marcados en rojo)");
            return false;
        }
        if(line_edits[i]->text().length() == 0){
            mostrarError("Rellene los espacios obligatorios");
            return false;
        }
    }
    // Validar la edad (mayor de 12 años)
    if(!validarEdad()){
        mostrarError("Se tiene que tener una edad mayor a 12 años");
        return false;
    }else{
        return true;
    }
}

void PantallaRegistro::validarEmail()
{
    QString correo = ui->lineEditCorreo->text();
    QString confirmarCorreo = ui->lineEditConfirmarCorreo->text();

    // Validar que las contraseñas coinciden
    if (correo != confirmarCorreo && (confirmarCorreo != "")) {
        ui->lineEditConfirmarCorreo->setProperty("Valido", false);
        qDebug() << ui->lineEditConfirmarCorreo->property("Valido") << "emails distintas";

    }else{

        ui->lineEditConfirmarCorreo->setProperty("Valido", true);
        qDebug() << ui->lineEditConfirmarCorreo->property("Valido") << "emails iguales";
    }

    static QRegularExpression emailRegex("^[a-zA-Z0-9_+&*-]+(?:\\.[a-zA-Z0-9_+&*-]+)*@(?:[a-zA-Z0-9-]+\\.)+[a-zA-Z]{2,7}$");
    if(!emailRegex.match(correo).hasMatch())
    {
        ui->lineEditCorreo->setProperty("Valido", false);
        qDebug() << ui->lineEditCorreo->property("Valido") << "email incorrecto";
    }else{

        ui->lineEditCorreo->setProperty("Valido", true);
        qDebug() << ui->lineEditCorreo->property("Valido") << "email correcta";
    }
    setStyleSheet(valido_estilo);

}

void PantallaRegistro::validarContrasenas()
{
    QString contrasena = ui->lineEditContrasena->text();
    QString confirmarContrasena = ui->lineEditConfirmarContrasena->text();


    static QRegularExpression contrasenaRegex("^(?=.*[A-Z])(?=.*[a-z])(?=.*[0-9])(?=.*[!@#$%&*()\\-+=]).{8,20}$");
    if (!contrasenaRegex.match(contrasena).hasMatch()) {
        ui->lineEditContrasena->setProperty("Valido", false);
        qDebug() << ui->lineEditContrasena->property("Valido") << "contraseña mal";

    }
    else{
        ui->lineEditContrasena->setProperty("Valido", true);
        qDebug() << ui->lineEditContrasena->property("Valido") << "Contraseña correcta";

    }

    // Validar que las contraseñas coinciden
    if (contrasena != confirmarContrasena && (confirmarContrasena != "")) {
        ui->lineEditConfirmarContrasena->setProperty("Valido", false);
        qDebug() << ui->lineEditContrasena->property("Valido") << "Contraseñas distintas";
    }
    else{

        ui->lineEditConfirmarContrasena->setProperty("Valido", true);
        qDebug() << ui->lineEditContrasena->property("Valido") << "Contraseñas iguales";
    }
    setStyleSheet(valido_estilo);
    // Validar que la contraseña cumpla con los requisitos

}

void PantallaRegistro::validarNombreUsuario()
{
    // Validar que el nombre de usuario tenga entre 6 y 15 caracteres y que no contenga espacios
    QString nombreUsuario = ui->lineEditUsuario->text();

    static QRegularExpression nombreUsuarioRegex("^[a-zA-Z0-9_-]{6,15}$");
    if (!nombreUsuarioRegex.match(nombreUsuario).hasMatch()) {
        ui->lineEditUsuario->setProperty("Valido", false);

    }else{
        ui->lineEditUsuario->setProperty("Valido", true);
    }
    setStyleSheet(valido_estilo);
}

bool PantallaRegistro::validarEdad()
{
    QDate fechaNacimiento = ui->dateEditNacimiento->date();
    QDate fechaActual = QDate::currentDate();

    // Calcular la edad exacta
    int edad = fechaActual.year() - fechaNacimiento.year();

    if (fechaActual.month() < fechaNacimiento.month() ||
        (fechaActual.month() == fechaNacimiento.month() && fechaActual.day() < fechaNacimiento.day())) {
        edad--;
    }

    qDebug() << "Edad calculada: " << edad;

    if (edad < 12) {
        ui->dateEditNacimiento->setStyleSheet("background-color: red;"); // Indicar error visualmente
        return false;
    }

    ui->dateEditNacimiento->setStyleSheet(""); // Restablecer estilo si es válido
    return true;
}

void PantallaRegistro::mostrarError(const QString &mensaje)
{
    QMessageBox::warning(this, "Los errores son: \n", mensaje);
}
