// Общий интерфейс
#ifndef INFOPLATFORM_H
#define INFOPLATFORM_H

#include "smbios.h" // Подключаем класс чтения таблиц SMBIOS
#include <QObject>
#include <QApplication>


class InfoPlatform : public QObject
{
    Q_OBJECT
public:
    explicit InfoPlatform(QObject *parent = nullptr);
    virtual ~InfoPlatform() = default;

    virtual void DecodeSMBIOS(SMBIOS *SMTable) = 0; // Декодируем таблицу SMBIOS

    virtual QString GetOsVersionNameQSysInfo() = 0; // Получить версию ОС с использованием QSysInfo
    virtual QString GetComputerName_()= 0;          // Получить имя компьютера
    virtual QString GetUserName_() = 0;             // Получить имя пользователя
    virtual const char *GetOsBitWidth() = 0;        // Разрядность ОС
    //Информация о процессоре
    virtual QString GetCPUName() = 0;               // Получить имя процессора (Здесь можно оптимизировать, считать все данные сразу в одной функции)
    virtual QString GetCPUType() = 0;               // Получить тип архитектуры процессора
    virtual DWORD GetCPUFrequency() = 0;            // Получить частоту процессора
    virtual DWORD GetCPUNumberCore() = 0;           // Получить кол-во ядер
    //Информация о материнской плате
    virtual QString GetBoardManufacturer() = 0;     // Получить производителя мат. платы (Здесь можно оптимизировать, считать все данные сразу в одной функции)
    virtual QString GetBoardName() = 0;             // Получить название мат.платы.
    //Информация о ОЗУ
    virtual DWORD GetMemorySize() = 0;              // Общий объём оперативной памяти.
    //Информация о Видеокарте
    virtual QString GetGPUName() = 0;               // Получить модель видеокарты
    virtual DWORD GetGPUMemSize() = 0;              // Получить объём видеопамяти видеокарты
    //Информация о жёстких дисках
    virtual void GetHardDriveInfo() = 0;            // Получить информацию о физических дисках
    //Информация о дисководе
    virtual bool GetCDROM() = 0;
    //Информация о мониторах
    //void GetMonitor();                            // Получить информацию о мониторе

    //ОЗУ
    WORD TotalRAMSlots{};                       // Общее кол-во разъёмов для памяти
    struct infoMemory;                          // Структура информации о конкретной плашки памяти.
    std::vector<infoMemory> vecMemory{};        // Информация обо всех плашках ОЗУ
    //Disk
    struct infoHardDrive;                       // Структура информации о конкретном жёстком диске(или ссд).
    std::vector<infoHardDrive> vecDrive{};      // Информация обо всех физических дисках
    //Monitor
    struct infoMonitors;                        // Структура Информации о конкретном мониторе
    //std::vector<infoMonitors> vecMonitors;    // Информация обо всех плашках мониторах

    //Геттеры
//    virtual WORD GetTotalRAMSlots() = 0;
//    virtual std::vector<infoMemory> GetInfoMemoryVec() = 0;
//    virtual std::vector<infoHardDrive> GetInfoHardDriveVec() = 0;
signals:
    void sendUpdateMySqlTableModelSignal(QString model, QString field, QString dataStr = ""); // Отправка сигнала для обновления таблиц MySqlTableModel на форме computerdata

};

struct InfoPlatform::infoMemory {
    WORD Size;              // Объём памяти
    QString FormFactor;     // Форм фактор
    QString DeviceLocator;  // В Каком слоте на мат.плате
    QString MemoryType;     // Тип модуля памяти
    WORD Speed;             // Скорость
    QString Manufacturer;   // Производитель
};

struct InfoPlatform::infoHardDrive{ // Структура информации о конкретном жёстком диске(или ссд).
    QString Name;           // Название жёсткого диска
    double Size;            // Объём жёсткого диска
};

struct InfoPlatform::infoMonitors {
    QString Name;           // Название монитора
    QString Size;           // Размер
    QString Type;           // Тип
    QString Resolution;     // Разрешение
    QString AspectRatio;    // Соотношение сторон
    QString RefreshRate;    // Частота обновления экрана
};
#endif // INFOPLATFORM_H
