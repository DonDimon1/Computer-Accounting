#ifndef INFOWIN_H
#define INFOWIN_H

#ifdef _WIN32 // Класс для сбора всей информации о комьютере в среде Windows

#include <QApplication>
#include <windows.h>        // WinAPI
#include <dxgi.h>           // DirectX API
#include <versionhelpers.h> // Для определения версии ОС

//#include <QScreen> // Для определения монитора


typedef unsigned __int64 QWORD; // У меня почему то не определён QWORD. (Возможно старая версия SDK)

class InfoWin
{
public:
//    struct thisCPU{     //Данные о процессоре
//        char cpuName[256]; //Имя процессора
//        DWORD dwMHz; //Частота процессора
//        unsigned long numCore; //Кол-во ядер
//    };
    InfoWin();                         // Конструктор
    class SMBIOS;                       // Вложенный класс, в нём парсим таблицу SMBIOS.
    void DecodeSMBIOS(InfoWin::SMBIOS *SMTable); // Декодируем таблицу SMBIOS

    //const char *GetOsVersionName();     // Получить версию ОС
    QString GetOsVersionNameQSysInfo(); // Получить версию ОС с использованием QSysInfo
    QString GetComputerName_();         // Получить имя компьютера
    QString GetUserName_();             // Получить имя пользователя
    const char *GetOsBitWidth();        // Разрядность ОС
    //Информация о процессоре
    //thisCPU GetCPU();                 // Информация о процессоре
    QString GetCPUName();               // Получить имя процессора (Здесь можно оптимизировать, считать все данные сразу в одной функции)
    QString GetCPUType();               // Получить тип архитектуры процессора
    DWORD GetCPUFrequency();            // Получить частоту процессора
    DWORD GetCPUNumberCore();           // Получить кол-во ядер
    //Информация о материнской плате
    QString GetBoardManufacturer();     // Получить производителя мат. платы (Здесь можно оптимизировать, считать все данные сразу в одной функции)
    QString GetBoardName();             // Получить название мат.платы.
    //Информация о ОЗУ
    DWORD GetMemorySize();              // Общий объём оперативной памяти.
    WORD TotalRAMSlots;                 // Общее кол-во разъёмов для памяти
    struct infoMemory;                  // Структура информации о конкретной плашки памяти.
    std::vector<infoMemory> vecMemory;  // Информация обо всех плашках ОЗУ
    //Информация о Видеокарте
    QString GetGPUName();               // Получить модель видеокарты
    DWORD GetGPUMemSize();              // Получить объём видеопамяти видеокарты
    //Информация о жёстких дисках
    void GetHardDriveInfo();            // Получить информацию о физических дисках
    struct infoHardDrive;               // Структура информации о конкретном жёстком диске(или ссд).
    std::vector<infoHardDrive> vecDrive;// Информация обо всех физических дисках
    //Информация о дисководе
    bool GetCDROM();
    //Информация о мониторах
    //void GetMonitor();                  // Получить информацию о мониторе
    struct infoMonitors;                // Структура Информации о конкретном мониторе
    std::vector<infoMonitors> vecMonitors; // Информация обо всех плашках мониторах
private:
};

struct InfoWin::infoMemory {
    WORD Size;              // Объём памяти
    QString FormFactor;     // Форм фактор
    QString DeviceLocator;  // В Каком слоте на мат.плате
    QString MemoryType;     // Тип модуля памяти
    WORD Speed;             // Скорость
    QString Manufacturer;   // Производитель
};

struct InfoWin::infoHardDrive{ // Структура информации о конкретном жёстком диске(или ссд).
    QString Name;           // Название жёсткого диска
    double Size;            // Объём жёсткого диска
};

struct InfoWin::infoMonitors {
    QString Name;           // Название монитора
    QString Size;           // Размер
    QString Type;           // Тип
    QString Resolution;     // Разрешение
    QString AspectRatio;    // Соотношение сторон
    QString RefreshRate;    // Частота обновления экрана
};

#endif

#endif // INFOWIN_H
