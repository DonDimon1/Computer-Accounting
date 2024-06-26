#ifndef SMBIOS_H
#define SMBIOS_H

// Класс для парсинга таблицы SMBIOS компьютера.
#include "compInfo.h"

class compInfo::SMBIOS
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
struct compInfo::SMBIOS::SMInfoMemory{      // Определение структуры ОЗУ
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



#endif // SMBIOS_H
