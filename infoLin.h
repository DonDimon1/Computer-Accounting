#ifndef INFOLIN_H
#define INFOLIN_H

#ifdef __linux__ // Класс для сбора всей информации о комьютере в среде Linux
#include <QApplication>
#include <unistd.h> // Для определения имени пк

class InfoLin
{
public:
    InfoLin(); // Конструктор
    QString GetOsVersionNameQSysInfo(); // Получить версию ОС с использованием QSysInfo
    QString GetComputerName_();         // Получить имя компьютера
    QString GetUserName_();             // Получить имя пользователя
    const char *GetOsBitWidth();        // Разрядность ОС
};

#endif

#endif // INFOLIN_H
