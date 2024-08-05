#ifndef INFOWIN_H
#define INFOWIN_H

#ifdef _WIN32 // Класс для сбора всей информации о комьютере в среде Windows
#include "infoPlatform.h"
//#include <QScreen> // Для определения монитора

class InfoWin : public InfoPlatform
{
    Q_OBJECT
public:
    explicit InfoWin(QObject *parent = nullptr);          // Конструктор
    ~InfoWin() = default;

    void DecodeSMBIOS(SMBIOS *SMTable) override; // Функция для получения информации об оперативной памяти из SMBIOS для Windows

    QString GetOsVersionNameQSysInfo() override; // Получить версию ОС с использованием QSysInfo
    QString GetComputerName_() override;         // Получить имя компьютера
    QString GetUserName_() override;             // Получить имя пользователя
    const char *GetOsBitWidth() override;        // Разрядность ОС
    //Информация о процессоре
    //thisCPU GetCPU();                 // Информация о процессоре
    QString GetCPUName() override;               // Получить имя процессора (Здесь можно оптимизировать, считать все данные сразу в одной функции)
    QString GetCPUType() override;               // Получить тип архитектуры процессора
    DWORD GetCPUFrequency() override;            // Получить частоту процессора
    DWORD GetCPUNumberCore() override;           // Получить кол-во ядер
    //Информация о материнской плате
    QString GetBoardManufacturer() override;     // Получить производителя мат. платы (Здесь можно оптимизировать, считать все данные сразу в одной функции)
    QString GetBoardName() override;             // Получить название мат.платы.
    //Информация о ОЗУ
    DWORD GetMemorySize() override;              // Общий объём оперативной памяти.
    // //Информация о Видеокарте
    QString GetGPUName() override;               // Получить модель видеокарты
    DWORD GetGPUMemSize() override;              // Получить объём видеопамяти видеокарты
    //Информация о жёстких дисках
    void GetHardDriveInfo() override;            // Получить информацию о физических дисках
    //Информация о дисководе
    bool GetCDROM() override;


    // //Информация о мониторах
    // //void GetMonitor() override;                  // Получить информацию о мониторе
    // struct infoMonitors;                // Структура Информации о конкретном мониторе
    // std::vector<infoMonitors> vecMonitors; // Информация обо всех плашках мониторах

    //ОЗУ
    // WORD TotalRAMSlots;                     // Общее кол-во разъёмов для памяти
    // std::vector<InfoPlatform::infoMemory> vecMemory;      // Информация обо всех плашках ОЗУ
    //Диск
    // std::vector<InfoPlatform::infoHardDrive> vecDrive;    // Информация обо всех физических дисках
    // //Монитор
    // struct infoMonitors;                    // Структура Информации о конкретном мониторе
    // std::vector<infoMonitors> vecMonitors;  // Информация обо всех плашках мониторах
private:
};


#endif

#endif // INFOWIN_H
