// persona.cpp -> Modela a cada jugador en el ranking proporcionando su información
#include "persona.h"

// Inicializa los atributos de un usuario
Persona::Persona(const QString& nickname, int puntos, const QImage& avatar)
    : nickname(nickname), puntos(puntos), avatar(avatar) {}

// Devuelvo el nickname del jugador
QString Persona::getNickname() const {
    return nickname;
}

// Devuelve el número de puntos del jugador
int Persona::getPuntos() const {
    return puntos;
}

// Devuelve el avatar del jugador en formato QPixmap
QImage Persona::getAvatar() const {
    return avatar;
}
