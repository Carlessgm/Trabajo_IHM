#ifndef PANTALLAREGISTRO_H
#define PANTALLAREGISTRO_H

#include <QDialog>
#include <QMessageBox>
#include <QRegularExpression>
#include <QDate>

namespace Ui {
class PantallaRegistro;
}

class PantallaRegistro : public QDialog
{
    Q_OBJECT

public:
    explicit PantallaRegistro(QWidget *parent = nullptr);
    ~PantallaRegistro();

private slots:
    void on_botonSeleccionarAvatar_clicked();  // Para seleccionar el avatar
    void okButtonClicked();

private:
    Ui::PantallaRegistro *ui;

    bool validarFormulario();  // Validar los campos del formulario
    bool validarEmail(QString &tipo_error);  // Validar correo electrónico
    bool validarContrasenas(QString &tipo_error);  // Validar que las contraseñas coincidan
    void validarNombreUsuario(); // Validar nombre de usuario
    bool validarEdad();  // Validar la edad
    void mostrarError(const QString &mensaje);  // Mostrar mensajes de error
};

#endif // PANTALLAREGISTRO_H
