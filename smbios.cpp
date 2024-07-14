#ifdef _WIN32 // Класс для сбора всей информации о комьютере в среде Windows

#include "smbios.h"
#include <QDebug>       //Для отладки


//void ReadSMBIOS(); // Определяем функцию для чтения SMBIOS
WORD BYTEtoWORD(BYTE **ptrByte); // Определяем функцию для конвертации из двух BYTE в один WORD
DWORD BYTEtoDWORD(BYTE **ptrByte); // Определяем функцию для конвертации из четырёх BYTE в один DWORD
QWORD BYTEtoQWORD(BYTE **ptrByte); // Определяем функцию для конвертации из восьми BYTE в один QWORD
QString BYTEtoSTRING(BYTE **ptrStr); // Определяем функцию для конвертации из нескольких BYTE в одну строку

compInfo::SMBIOS::SMBIOS() //Конструктор
{
    compInfo::SMBIOS::ReadSMBIOS(); //Функция чтения таблицы SMBIOS
};


//WORD BYTEtoWORD(BYTE *ptrByte){ //конвертации из двух BYTE в один WORD
//    return ((WORD)*(ptrByte + 1) << 8) | *ptrByte; //Без перехода к следующему байту
//}
WORD BYTEtoWORD(BYTE **ptrByte){                    // Конвертации из двух BYTE в один WORD
    BYTE *temp = *ptrByte;
    WORD res = ((WORD)*(temp + 1) << 8) | *temp;    // Превращаем BYTE в WORD
    *ptrByte += 2;                                  // Перемещаем указатель байтов для перехода на слд. параметр таблицы SMBIOS
    return res;
};

DWORD BYTEtoDWORD(BYTE **ptrByte){ //Конвертация из четырёх BYTE в один DWORD
//    BYTE *temp = *ptrByte;
//    WORD tempW1 = ((WORD)*(temp + 1) << 8) | *temp;         // Создаём два временных WORD
//    WORD tempW2 = ((WORD)*(temp + 3) << 8) | *(temp + 2);
//    *ptrByte += 4;                                          //Перемещаем указатель
//    return ((DWORD) tempW2 << 16) | tempW1;

    BYTE *temp = *ptrByte + 2;
    return ((DWORD) BYTEtoWORD(&temp) << 16) | BYTEtoWORD(ptrByte);
};

QWORD BYTEtoQWORD(BYTE **ptrByte){ //конвертации из восьми BYTE в один QWORD
    BYTE* temp = *ptrByte + 4;
    return ((QWORD)BYTEtoDWORD(&temp) << 32) | BYTEtoDWORD(ptrByte);
};

QString BYTEtoSTRING(BYTE **ptrStr){ // Конвертации из нескольких BYTE в одну строку
    QString res;
    while(**ptrStr){
        res += (char)**ptrStr;
        ++(*ptrStr);
    }
    ++(*ptrStr);
    return res;
};

void compInfo::SMBIOS::ReadSMBIOS(){ //Чтение таблицы из БИОСа
    struct RawSMBIOSData //Структура для чтения SMBIOS
    {
        BYTE    Used20CallingMethod;
        BYTE    SMBIOSMajorVersion;
        BYTE    SMBIOSMinorVersion;
        BYTE    DmiRevision;
        DWORD   Length; //Сколько байтов в таблица
        BYTE    SMBIOSTableData[]; //Массив всех байтов
    };

    enum SpecVersion //Расшифровка версий таблицы биоса из hex
    {
        SMBIOS_2_0 = 0x0200,
        SMBIOS_2_1 = 0x0201,
        SMBIOS_2_2 = 0x0202,
        SMBIOS_2_3 = 0x0203,
        SMBIOS_2_4 = 0x0204,
        SMBIOS_2_5 = 0x0205,
        SMBIOS_2_6 = 0x0206,
        SMBIOS_2_7 = 0x0207,
        SMBIOS_2_8 = 0x0208,
        SMBIOS_3_0 = 0x0300,
        SMBIOS_3_1 = 0x0301,
        SMBIOS_3_2 = 0x0302,
        SMBIOS_3_3 = 0x0303,
        SMBIOS_3_4 = 0x0304,
        SMBIOS_3_5 = 0x0305,
        SMBIOS_3_6 = 0x0306,
        SMBIOS_3_7 = 0x0307
    };

    DWORD error = ERROR_SUCCESS;
    DWORD smBiosDataSize = 0;
    RawSMBIOSData* smBiosData = NULL; // Ссылка на структуру
    DWORD bytesWritten = 0;

    // Размер запроса данных SMBIOS.
    smBiosDataSize = GetSystemFirmwareTable('RSMB', 0, NULL, 0);

    // Выделите память для данных SMBIOS
    smBiosData = (RawSMBIOSData*) HeapAlloc(GetProcessHeap(), 0, smBiosDataSize);
    if (!smBiosData) {
        error = ERROR_OUTOFMEMORY;
        qDebug() << "Ошибка таблицы или выделения памяти для неё";
    }

    // Получение таблицы SMBIOS
    bytesWritten = GetSystemFirmwareTable('RSMB', 0, smBiosData, smBiosDataSize);

    if (bytesWritten != smBiosDataSize) { //Проверка на запись всех байтов
        error = ERROR_INVALID_DATA;
        //return smBiosData;
        qDebug() << "Записались не всё байты";
    }
    else{
        //qDebug() << "Всё чётко";
    }
    // Получаем версию SMBIOS
    int version = smBiosData->SMBIOSMajorVersion << 8 | smBiosData->SMBIOSMinorVersion;

    // Далее нужен код для обработки данных SMBIOS и освобождение памяти под меткой выхода
    BYTE *ptrByte = smBiosData->SMBIOSTableData;        // Указатель на первый байт таблицы
    BYTE *ptrStr = smBiosData->SMBIOSTableData;         // Указатель на строки в структурах таблицы SMBIOS
    while(*ptrStr != TYPE_END_OF_TABLE){                // Обработка каждого байта в таблице SMBIOS
        ptrByte = ptrStr;                               // Переход на следующую структуру
        switch (*ptrByte) {                             // Ищем в байтах структуры
            case TYPE_MEMORY_DEVICE:{                   // Парсим инфу об ОЗУ
                compInfo::SMBIOS::SMInfoMemory thisMemory; // Создаём новую структуру с необработанными данными про конкретную плашку ОЗУ
                //compInfo::infoMemory newStruct;
                //newStruct.Size = BYTEtoWORD(&ptrByte);
                ++ptrByte;                              // Подготовка к считыванию данных
                ptrStr = ptrByte + *ptrByte - 1; ptrByte += 3; // Ставим оба указателя на свои места
                if(version >= SMBIOS_2_0){              // Версия 2.0
                    thisMemory.PhysicalArrayHandle = BYTEtoWORD(&ptrByte); // Делаем из двух BYTE один WORD. И переходим на след. параметр
                    thisMemory.ErrorInformationHandle = BYTEtoWORD(&ptrByte);
                    thisMemory.TotalWidth = BYTEtoWORD(&ptrByte);
                    thisMemory.DataWidth = BYTEtoWORD(&ptrByte);
                    thisMemory.Size = BYTEtoWORD(&ptrByte);
                    thisMemory.FormFactor = *ptrByte++; // Присваеваем значение и переходим к следующему байту
                    thisMemory.DeviceSet = *ptrByte++;
                    thisMemory.DeviceLocator = BYTEtoSTRING(&ptrStr); ptrByte++; // Здесь начинается первая строка
                    thisMemory.BankLocator = BYTEtoSTRING(&ptrStr); ptrByte++;
                    thisMemory.MemoryType = *ptrByte++;
                    thisMemory.TypeDetail = BYTEtoWORD(&ptrByte);
                } else {vecMemory.push_back(thisMemory); break;} // Сохраняем данные и выходим из case
                if(version >= SMBIOS_2_3){              // Версия 2.3
                    thisMemory.Speed = BYTEtoWORD(&ptrByte);
                    thisMemory.Manufacturer = BYTEtoSTRING(&ptrStr); ptrByte++;
                    thisMemory.SerialNumber = BYTEtoSTRING(&ptrStr); ptrByte++;
                    thisMemory.AssetTagNumber = BYTEtoSTRING(&ptrStr); ptrByte++;
                    thisMemory.PartNumber = BYTEtoSTRING(&ptrStr); ptrByte++;
                } else {vecMemory.push_back(thisMemory); break;} // Сохраняем данные и выходим из case
                if(version >= SMBIOS_2_6){              // Версия 2.6
                    thisMemory.Attributes = *ptrByte++;
                } else {vecMemory.push_back(thisMemory); break;} // Сохраняем данные и выходим из case
                if(version >= SMBIOS_2_7){              // Версия 2.7
                    thisMemory.ExtendedSize = BYTEtoDWORD(&ptrByte);
                    thisMemory.ConfiguredMemorySpeed = BYTEtoWORD(&ptrByte);
                } else {vecMemory.push_back(thisMemory); break;} // Сохраняем данные и выходим из case
                if(version >= SMBIOS_2_8){              // Версия 2.8
                    thisMemory.MinimumVoltage = BYTEtoWORD(&ptrByte);
                    thisMemory.MaximumVoltage = BYTEtoWORD(&ptrByte);
                    thisMemory.ConfiguredVoltage = BYTEtoWORD(&ptrByte);
                } else {vecMemory.push_back(thisMemory); break;} // Сохраняем данные и выходим из case
                if(version >= SMBIOS_3_2){              // Версия 3.2
                    thisMemory.MemoryTechnology = *ptrByte++;
                    thisMemory.MemoryOperatingModeCapability = BYTEtoWORD(&ptrByte);
                    thisMemory.FirmwareVersion = BYTEtoSTRING(&ptrStr);ptrByte++;
                    thisMemory.ModuleManufacturerID = BYTEtoWORD(&ptrByte);
                    thisMemory.ModuleProductID = BYTEtoWORD(&ptrByte);
                    thisMemory.MemorySubsystemControllerManufacturerID = BYTEtoWORD(&ptrByte);
                    thisMemory.MemorySubsystemControllerProductID = BYTEtoWORD(&ptrByte);
                    thisMemory.NonVolatileSize = BYTEtoQWORD(&ptrByte);
                    thisMemory.VolatileSize = BYTEtoQWORD(&ptrByte);
                    thisMemory.CacheSize = BYTEtoQWORD(&ptrByte);
                    thisMemory.LogicalSize = BYTEtoQWORD(&ptrByte);
                } else {vecMemory.push_back(thisMemory); break;} // Сохраняем данные и выходим из case
                if(version >= SMBIOS_3_3){              // Версия 3.3
                    thisMemory.ExtendedSpeed = BYTEtoDWORD(&ptrByte);
                    thisMemory.ExtendedConfiguredMemorySpeed = BYTEtoDWORD(&ptrByte);
                } else {vecMemory.push_back(thisMemory); break;} // Сохраняем данные и выходим из case
                if(version >= SMBIOS_3_7){              // Версия 3.7
                    thisMemory.PMIC0ManufacturerID = BYTEtoWORD(&ptrByte);
                    thisMemory.PMIC0RevisionNumber = BYTEtoWORD(&ptrByte);
                    thisMemory.RCDManufacturerID = BYTEtoWORD(&ptrByte);
                    thisMemory.RCDRevisionNumber = BYTEtoWORD(&ptrByte);
                } else {vecMemory.push_back(thisMemory); break;} // Сохраняем данные и выходим из case
            }
            //case TYPE_END_OF_TABLE: break;              // Конец таблицы SMBIOS
            default:{                                   // Обработка ненужных нам типов.
                ptrByte++;                              // Ставим указатель на бит, определяющий длинну конкретного типа в таблице.
                ptrStr = ptrByte + *ptrByte - 1;       // Переходим к строковым типам.
                bool endString = false;                 // Переменная для определения конца строк
                while(*ptrStr != 0 || !endString){     // Пока не будет найден конец всех строк (Цикл в цикле. Нужана оптимизация)
                    if(!*ptrStr)
                        endString = true;
                    else
                        endString = false;
                    ptrStr++;                          // Переход на следующий бит
                }
                ptrStr++;                              // Переход на следующий бит
            }
        }
    }
}


 //Функции декодирования
QString compInfo::SMBIOS::GetFormFactor(BYTE FormFactor){ // Получить форм фактор
    switch (FormFactor) {
        case 1: return "Other";
        case 2: return "Unknown";
        case 3: return "SIMM";
        case 4: return "SIP";
        case 5: return "Chip";
        case 6: return "DIP";
        case 7: return "ZIP";
        case 8: return "Proprietary Card";
        case 9: return "DIMM";
        case 10: return "TSOP";
        case 11: return "Row of chips";
        case 12: return "RIMM";
        case 13: return "SODIMM";
        case 14: return "SRIMM";
        case 15: return "FB-DIMM";
        case 16: return "Die";
        default: return "Undefined";
    }
};

QString compInfo::SMBIOS::GetMemoryType(BYTE MemoryType){ // Получить тип памяти
    switch (MemoryType){
    case 1: return "Other";
    case 2: return "Unknown";
    case 3: return "DRAM";
    case 4: return "EDRAM";
    case 5: return "VRAM";
    case 6: return "SRAM";
    case 7: return "RAM";
    case 8: return "ROM";
    case 9: return "FLASH";
    case 10: return "EEPROM";
    case 11: return "FEPROM";
    case 12: return "EPROM";
    case 13: return "CDRAM";
    case 14: return "3DRAM";
    case 15: return "SDRAM";
    case 16: return "SGRAM";
    case 17: return "RDRAM";
    case 18: return "DDR";
    case 19: return "DDR2";
    case 20: return "DDR2 FB-DIMM";
    case 21: return "Reserved";
    case 22: return "Reserved";
    case 23: return "Reserved";
    case 24: return "DDR3";
    case 25: return "FBD2";
    case 26: return "DDR4";
    case 27: return "LPDDR";
    case 28: return "LPDDR2";
    case 29: return "LPDDR3";
    case 30: return "LPDDR4";
    case 31: return "Logical non-volatile device";
    case 32: return "HBM (High Bandwidth Memory)";
    case 33: return "HBM2 (High Bandwidth Memory Generation 2";
    case 34: return "DDR5";
    case 35: return "LPDDR5";
    case 36: return "HBM3 (High Bandwidth Memory Generation 3";
    default: return "Undefined";
    }
};

#endif
