#ifndef SMBIOS_H
#define SMBIOS_H

// Псевдонимы
using BYTE = unsigned char;         // 1 байт (8 бит)
using WORD = unsigned short;        // 2 байта (16 бит)
using DWORD = unsigned long;        // 4 байта (32 бита)
using QWORD = unsigned long long;   // 8 байт (64 бита)
using UINT = unsigned int;

// Временно определил _WIN32, на самом деле от ОС не зависит
//#ifdef _WIN32 // Класс для сбора всей информации о комьютере в среде Windows
// Класс для парсинга таблицы SMBIOS компьютера.
#include "infoWin.h"
#include <vector>
#include <QString>

class SMBIOS
{
public:
    SMBIOS();
     struct SMInfoMemory;                   // Структура с необработанной информацией о конкретной плашке памяти.
     std::vector<SMInfoMemory> vecMemory;  // Необработанная информация обо всех плашках ОЗУ
     void ReadSMBIOS(); //Функция чтения таблицы SMBIOS

     //Функции декодирования
     QString GetFormFactor(BYTE FormFactor); // Получить формфактор
     QString GetMemoryType(BYTE MemoryType); // Получить тип памяти
};

const static int TYPE_MEMORY_DEVICE = 17;   // Номер типа ОЗУ в таблице SMBIOS
struct SMBIOS::SMInfoMemory{      // Определение структуры ОЗУ
    // 2.1+
    WORD PhysicalArrayHandle;
    WORD ErrorInformationHandle;
    WORD TotalWidth;
    WORD DataWidth;
    WORD Size;                          // Объём памяти
    BYTE FormFactor;                    // Форм фактор
    BYTE DeviceSet;
    QString DeviceLocator;              // В Каком слоте на мат.плате
    QString BankLocator;
    BYTE MemoryType;                    // Тип модуля памяти
    WORD TypeDetail;
    // 2.3+
    WORD Speed;                         // Скорость
    QString Manufacturer;               // Производитель
    QString SerialNumber;
    QString AssetTagNumber;
    QString PartNumber;
    // 2.6+
    BYTE Attributes;
    // 2.7+
    DWORD ExtendedSize;
    WORD ConfiguredMemorySpeed;
    // 2.8+
    WORD MinimumVoltage;
    WORD MaximumVoltage;
    WORD ConfiguredVoltage;
    // 3.2+
    BYTE MemoryTechnology;
    WORD MemoryOperatingModeCapability;
    QString FirmwareVersion;
    WORD ModuleManufacturerID;
    WORD ModuleProductID;
    WORD MemorySubsystemControllerManufacturerID;
    WORD MemorySubsystemControllerProductID;
    QWORD NonVolatileSize;
    QWORD VolatileSize;
    QWORD CacheSize;
    QWORD LogicalSize;
    // 3.3+
    DWORD ExtendedSpeed;
    DWORD ExtendedConfiguredMemorySpeed;
    // 3.7+
    WORD PMIC0ManufacturerID;
    WORD PMIC0RevisionNumber;
    WORD RCDManufacturerID;
    WORD RCDRevisionNumber;
};

const static int TYPE_END_OF_TABLE = 127;

//#endif

#endif // SMBIOS_H
