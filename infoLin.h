#ifndef INFOLIN_H
#define INFOLIN_H

#ifdef __linux__ // Класс для сбора всей информации о комьютере в среде Linux
#include <QApplication>
#include <sys/utsname.h> // Для определения имени пк TODO сделать всё через boost
#include <unistd.h>     // Для определения имени пользователя
#include <fstream>      // Для парсинга иныормации о процессоре
#include <string>
#include <QSysInfo>     // Для определения архитектуры процессора
#include <sstream>      // Из std::string в DWORD

// Псевдонимы
using BYTE = unsigned char;         // 1 байт (8 бит)
using WORD = unsigned short;        // 2 байта (16 бит)
using DWORD = unsigned long;        // 4 байта (32 бита)
using QWORD = unsigned long long;   // 8 байт (64 бита)

class InfoLin
{
public:
    InfoLin(); // Конструктор
    QString GetOsVersionNameQSysInfo(); // Получить версию ОС с использованием QSysInfo
    QString GetComputerName_();         // Получить имя компьютера
    QString GetUserName_();             // Получить имя пользователя
    const char *GetOsBitWidth();        // Разрядность ОС
    //Информация о процессоре
    QString GetCPUName();               // Получить имя процессора
    QString GetCPUType();               // Получить тип архитектуры процессора
    DWORD GetCPUFrequency();            // Получить частоту процессора. DWORD потому что у infoWin тоже DWORD. Для единообразия
    DWORD GetCPUNumberCore();           // Получить кол-во ядер
    //Информация о материнской плате
    QString GetBoardManufacturer();     // Получить производителя мат. платы
    QString GetBoardName();             // Получить название мат.платы.
    //Информация о ОЗУ
    DWORD GetMemorySize();              // Общий объём оперативной памяти.
    WORD TotalRAMSlots;                 // Общее кол-во разъёмов для памяти
    struct infoMemory;                  // Структура информации о конкретной плашки памяти.
    std::vector<infoMemory> vecMemory;  // Информация обо всех плашках ОЗУ
    void DecodeSMBIOS();                // Функция для получения информации об оперативной памяти из SMBIOS для Linux
};

struct InfoLin::infoMemory {
    WORD Size;              // Объём памяти
    QString FormFactor;     // Форм фактор
    QString DeviceLocator;  // В Каком слоте на мат.плате
    QString MemoryType;     // Тип модуля памяти
    WORD Speed;             // Скорость
    QString Manufacturer;   // Производитель
};

#endif

#endif // INFOLIN_H
