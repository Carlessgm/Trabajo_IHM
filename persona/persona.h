// Persona.h -> Representa la información de un usuario en el ranking
#ifndef PERSONA_H
#define PERSONA_H

#include <QString>
#include <QImage>

class Persona {
public:
    // Define la estructura de un usuario
    Persona(const QString& nickname, int puntos, const QImage& avatar);

    // Métodos para leer atributos del usuario
    QString getNickname() const;
    int getPuntos() const;
    QImage getAvatar() const;

private:
    // Atributos de cada usuario
    QString nickname;
    int puntos;
    QImage avatar; // Usaremos un QImage para el avatar
};

#endif // PERSONA_H
