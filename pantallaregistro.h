#ifndef PANTALLAREGISTRO_H
#define PANTALLAREGISTRO_H

#include <QDialog>
#include <QMessageBox>
#include <QRegularExpression>
#include <QDate>
#include <qlineedit.h>

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
    QString valido_estilo = "";
    bool validarFormulario();  // Validar los campos del formulario
    void validarEmail();  // Validar correo electrónico
    void validarContrasenas();  // Validar que las contraseñas coincidan
    void validarNombreUsuario(); // Validar nombre de usuario
    bool validarEdad();  // Validar la edad
    QLineEdit *line_edits[8];
    void mostrarError(const QString &mensaje);  // Mostrar mensajes de error
    bool see_password = false;
};

#endif // PANTALLAREGISTRO_H
