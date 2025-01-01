#ifndef PLAYER_H
#define PLAYER_H

#include <QString>
#include <QImage>
#include <QDate>

class Connect4; // Declaración adelantada

class Player {
private:
    // Constructor privado: solo accesible desde Connect4

    Player(const QString& nickName, const QString& email, const QString& password,
           const QDate& birthdate, int points = 0, const QImage& avatar = QImage());

    friend class  Connect4; // Permite a Connect4 acceder al constructor
    friend class  Connect4DAO;
public:
    // Métodos de acceso con persistencia
    QString getNickName() const;
    QString getEmail() const;
    void setEmail(const QString& email);

    QString getPassword() const;
    void setPassword(const QString& password);

    QImage getAvatar() const;
    void setAvatar(const QImage& avatar);

    QDate getBirthdate() const;
    void setBirthdate(const QDate& birthdate);

    int getPoints() const;
    void addPoints(int points);

private:
    QString nickName;
    QString email;
    QString password;
    QImage avatar;
    QDate birthdate;
    int points;

    void updateDatabase(); // Método auxiliar para persistir cambios
};

#endif // PLAYER_H
