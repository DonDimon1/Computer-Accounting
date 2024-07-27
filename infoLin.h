#ifndef INFOLIN_H
#define INFOLIN_H

#ifdef __linux__ // Класс для сбора всей информации о комьютере в среде Linux
#include "infoPlatform.h"

class InfoLin : public InfoPlatform
{
public:
    InfoLin(); // Конструктор
    ~InfoLin() = default;

    void DecodeSMBIOS(SMBIOS *SMTable) override;    // Функция для получения информации об оперативной памяти из SMBIOS для Linux

    QString GetOsVersionNameQSysInfo() override;    // Получить версию ОС с использованием QSysInfo
    QString GetComputerName_() override;            // Получить имя компьютера
    QString GetUserName_() override;                // Получить имя пользователя
    const char *GetOsBitWidth() override;           // Разрядность ОС
    //Информация о процессоре
    QString GetCPUName() override;                  // Получить имя процессора
    QString GetCPUType() override;                  // Получить тип архитектуры процессора
    DWORD GetCPUFrequency() override;               // Получить частоту процессора. DWORD потому что у infoWin тоже DWORD. Для единообразия
    DWORD GetCPUNumberCore() override;              // Получить кол-во ядер
    //Информация о материнской плате
    QString GetBoardManufacturer() override;        // Получить производителя мат. платы
    QString GetBoardName() override;                // Получить название мат.платы.
    //Информация о ОЗУ
    DWORD GetMemorySize() override;                 // Общий объём оперативной памяти.
    //WORD TotalRAMSlots;                           // Общее кол-во разъёмов для памяти
    // struct InfoPlatform::infoMemory g;           // Структура информации о конкретной плашки памяти.
    // std::vector<infoMemory> vecMemory;           // Информация обо всех плашках ОЗУ

    // Временно!
    void DecodeSMBIOS_2();

    //ОЗУ
     WORD TotalRAMSlots;                                // Общее кол-во разъёмов для памяти
    // struct infoMemory;                               // Структура информации о конкретной плашки памяти.
     std::vector<InfoPlatform::infoMemory> vecMemory;   // Информация обо всех плашках ОЗУ
    // //DiskInfoLin
    // struct infoHardDrive;                            // Структура информации о конкретном жёстком диске(или ссд).
    // std::vector<infoHardDrive> vecDrive;             // Информация обо всех физических дисках
    // //Monitor
    // struct infoMonitors;                             // Структура Информации о конкретном мониторе
    // std::vector<infoMonitors> vecMonitors;           // Информация обо всех плашках мониторах
};


#endif

#endif // INFOLIN_H
