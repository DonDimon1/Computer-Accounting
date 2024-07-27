#ifdef __linux__

#include "infoLin.h"
#include <sys/utsname.h> // Для определения имени пк TODO сделать всё через boost
#include <unistd.h>     // Для определения имени пользователя
#include <fstream>      // Для парсинга иныормации о процессоре
#include <string>
#include <QSysInfo>     // Для определения архитектуры процессора
#include <sstream>      // Из std::string в DWORD
//
 #include <QDebug>
// Для DecodeSMBIOS
#include <QFile>        //Какие то из них не нужны
#include <QTextStream>
#include <QVector>
#include <QByteArray>
//


InfoLin::InfoLin(){                     // Конструктор
    SMBIOS SMTable;                     // Класс для содержания необработанной инфы из SMBIOS
    //InfoLin::DecodeSMBIOS(&SMTable);    // Расшифровать информацию из таблицы SMBIOS
}

void InfoLin::DecodeSMBIOS(SMBIOS *SMTable){     //Функция для декодирования данных из таблицы SMBIOS
    // ОЗУ
    // WORD slotsNum = SMTable->vecMemory.size();                                                  // Кол-во разъёмов для памяти, найденных в SMBIOS
    // InfoLin::TotalRAMSlots = slotsNum;                                                         // Сохраняем инфу о общем кол-ве разъёмов для памяти
    // for(UINT i = 0; i < slotsNum; ++i){                                                         // Перебераем все плашки ОЗУ
    //     if(SMTable->vecMemory.at(i).Size){                                                      // Если плашка памяти установлена
    //         InfoPlatform::infoMemory newStruct;                                                     // Создаём новую структуру с обработанными данными про конкретную плашку ОЗУ
    //         newStruct.Size = SMTable->vecMemory.at(i).Size;                                     // Сохраняем Объём плашки в МБ.
    //         newStruct.FormFactor = SMTable->GetFormFactor(SMTable->vecMemory.at(i).FormFactor); // Сохраняем Форм фактор плашки
    //         newStruct.DeviceLocator = SMTable->vecMemory.at(i).DeviceLocator;                   // В каокм слоте стоит плашка
    //         newStruct.MemoryType = SMTable->GetMemoryType(SMTable->vecMemory.at(i).MemoryType); // Сохраняем тип памяти
    //         newStruct.Speed = SMTable->vecMemory.at(i).Speed;                                   // Сохраняем скорость
    //         newStruct.Manufacturer = SMTable->vecMemory.at(i).Manufacturer;                     // Сохраняем производителя
    //         InfoLin::vecMemory.push_back(newStruct);                                           // Добавляем инфу об установленной плашке памяти
    //     }                                                                                       // Кол-во элементов вектора обозначает кол-во установленных плашек ОЗУ
    // }
};

QString InfoLin::GetOsVersionNameQSysInfo(){ //Версия ОС
    return QSysInfo::prettyProductName();
}

QString InfoLin::GetComputerName_(){ //Получить имя компьютера
    struct utsname system_info;
    uname(&system_info);
    if(system_info.nodename)
        return QString::fromUtf8(system_info.nodename);
    return "undefine";
};

QString InfoLin::GetUserName_(){ //Получить имя пользователя
    char username[100];
    if(getlogin_r(username, sizeof(username)));
        return QString::fromUtf8(username);
    return "undefine";
};

const char *InfoLin::GetOsBitWidth(){ //Получить разрядность
    #if defined(__LP64__) || defined(_M_IA64) //(Кросс-платформа)
        return "x64";
    #endif
        return "x32";
};

QString InfoLin::GetCPUName(){ //Получить имя процессора
    std::ifstream file("/proc/cpuinfo"); // Открываем файл с инфой о проце
    if(!file.is_open()){                 // Если не открылся
        return "Unable to open /proc/cpuinfo";
    }

    std::string line;
    while (std::getline(file, line)) {
        // Найти строку, содержащую "model name"
        if (line.find("model name") != std::string::npos) {
            // Найти позицию двоеточия
            std::size_t colonPos = line.find(':');
            if (colonPos != std::string::npos) {
                // Вернуть подстроку после двоеточия с удалением пробелов
                std::string modelName = line.substr(colonPos + 2);
                file.close();
                return QString::fromStdString(modelName);
            }
        }
    }
    file.close();
    return "undefine";
};

QString InfoLin::GetCPUType(){ //Получить тип архитектуры процессора
    QString arch = QSysInfo::currentCpuArchitecture();
    if(arch.size() != 0)
        return arch;
    return "undefine";
};

DWORD InfoLin::GetCPUFrequency(){ //Получить частоту процессора
    std::ifstream file("/proc/cpuinfo"); // Открываем файл с инфой о проце
    if(!file.is_open()){                 // Если не открылся
        return 0;
    }

    std::string line;
    while (std::getline(file, line)) {
        // Найти строку, содержащую "cpu MHz"
        if (line.find("cpu MHz") != std::string::npos) {
            // Найти позицию двоеточия
            std::size_t colonPos = line.find(':');
            if (colonPos != std::string::npos) {
                // Вернуть подстроку после двоеточия с удалением пробелов
                std::string modelName = line.substr(colonPos + 2);
                file.close();
                std::stringstream ss(modelName);
                DWORD result;
                ss >> result;
                return result;
            }
        }
    }
    return 0;
};

DWORD InfoLin::GetCPUNumberCore(){ //Получить кол-во ядер процессора
    std::ifstream file("/proc/cpuinfo"); // Открываем файл с инфой о проце
    if(!file.is_open()){                 // Если не открылся
        return 0;
    }

    std::string line;
    DWORD result = 0;
    while (std::getline(file, line)) {
        // Найти строку, содержащую "processor"             //Возможно лучше считывать строку, содержащую "cpu cores"
        if (line.find("processor") != std::string::npos)
            result += 1;
    }
    file.close();
    return result;
};

QString InfoLin::GetBoardManufacturer(){ //Получить производителя мат.платы
    std::ifstream file("/sys/class/dmi/id/board_vendor"); // Открываем файл с инфой о производителе мат.платы
    if(!file.is_open()){                 // Если не открылся
        return "Unable to open /sys/class/dmi/id/board_vendor";
    }

    std::string vendor;
    std::getline(file, vendor);
    file.close();
    return QString::fromStdString(vendor);
};

QString InfoLin::GetBoardName(){ //Получить название мат.платы
    std::ifstream file("/sys/class/dmi/id/board_name"); // Открываем файл с инфой о названии мат.платы
    if(!file.is_open()){                 // Если не открылся
        return "Unable to open /sys/class/dmi/id/board_name";
    }

    std::string name;
    std::getline(file, name);
    file.close();
    return QString::fromStdString(name);
};

DWORD InfoLin::GetMemorySize(){ //Получить общий объём ОЗУ
    std::ifstream file("/proc/meminfo");
    if (!file.is_open()) {
        return 0;
    }

    std::string totalMemory;
    std::string line;
    while (std::getline(file, line)) {
        if (line.find("MemTotal:") != std::string::npos) {
            size_t pos = line.find(":");
            totalMemory = line.substr(pos + 1);

            file.close();
            std::stringstream ss(totalMemory);
            DWORD result;
            ss >> result;
            return result / 1024; // Переводим Кб в Мб.
        }
    }

    file.close();
    return 0;
};

// // Временно!
// QString BYTEtoSTRING(BYTE **ptrStr){ // Конвертации из нескольких BYTE в одну строку
//     QString res;
//     while(**ptrStr){
//         res += (char)**ptrStr;
//         ++(*ptrStr);
//     }
//     ++(*ptrStr);
//     return res;
// };

void InfoLin::DecodeSMBIOS_2(){
    // // Получаем версию SMBIOS
    // const char* pathEPS = "/sys/firmware/dmi/tables/smbios_entry_point";
    // std::ifstream fileEPS(pathEPS, std::ios::binary);

    // if (!fileEPS.is_open()) {
    //     qCritical() << "Нет прав для открытия файла " << pathEPS << ". Запустите программу с правами администратора (root).";
    //     return;
    // }

    // // Получаем размер файла
    // fileEPS.seekg(0, std::ios::end);
    // std::streampos fileEpsSize = fileEPS.tellg();
    // fileEPS.seekg(0, std::ios::beg);

    // // Считываем содержимое файла в буфер
    // std::vector<BYTE> bufferEPS(fileEpsSize);
    // if (!fileEPS.read(reinterpret_cast<char*>(bufferEPS.data()), fileEpsSize)) {
    //     qCritical() << "Ошибка при чтении файла " << pathEPS;
    //     return;
    // }
    // fileEPS.close();

    // BYTE majorVersionIndex{};
    // if(GetOsBitWidth() == "x32") // Место данных разное, в зависимости от разрядности.
    //     majorVersionIndex = 5;
    // else
    //     majorVersionIndex = 6;
    // float version = bufferEPS.at(majorVersionIndex);
    // char fractionalPart = bufferEPS.at(majorVersionIndex + 2);
    // version += (fractionalPart / 10.0f);    // Получаем версию таблицы SMBIOS
    // qCritical() << version;
    /////////////////////////////
    // Получаем версию SMBIOS
    float version{};
    QFile smbiosEntryPointFile("/sys/firmware/dmi/tables/smbios_entry_point");
    if (!smbiosEntryPointFile.open(QIODevice::ReadOnly)) {        // Попытка открыть файл
        qCritical() << "Нет прав для открытия файла /sys/firmware/dmi/tables/smbios_entry_point. Запустите программу с правами администратора (root).";
        return;
    }
    QByteArray bufferEPS = smbiosEntryPointFile.readAll();        // Считываем информацию из файла
    smbiosEntryPointFile.close();                                 // Закрываем файл

    const BYTE *verByte = reinterpret_cast<const BYTE*>(bufferEPS.data()); // Указатель на первый байт таблицы

    // qCritical() << "Первые 10 байтов:";
    // for (int i = 0; i < qMin(20, bufferEPS.size()); ++i) {
    //     qCritical() << QString::number(verByte[i], 16).rightJustified(2, '0');
    // }

    //Узнаем версию таблицы SMBIOS
    GetOsBitWidth() == "x32" ? verByte += 5 : verByte += 6; // Место данных разное, в зависимости от разрядности.
    version = *verByte;                     // Сохраняем целую часть
    ++verByte;                              // Переходим на место дробной части числа версии
    char fractionalPart = *verByte;         // Сохраняем дробную часть
    version += (fractionalPart / 10.0f);    // Получаем версию таблицы SMBIOS

    //qCritical() << version;


////////////////////////////////////////////
    // Получаем данные из таблицы SMBIOS
    QFile smbiosFile("/sys/firmware/dmi/tables/DMI");   // Путь к данным из таблицы SMBIOS в Linux
    if (!smbiosFile.open(QIODevice::ReadOnly)) {        // Попытка открыть файл
        qCritical() << "Нет прав для открытия файла /sys/firmware/dmi/tables/DMI. Запустите программу с правами администратора (root).";
        return;
    }

    QByteArray buffer = smbiosFile.readAll();           // Считываем информацию из файла
    smbiosFile.close();                                 // Закрываем файл

    BYTE *ptrByte = reinterpret_cast<BYTE*>(buffer.data()); // Указатель на первый байт таблицы
    BYTE *ptrStr = ptrByte;                       // Указатель на строки в структурах таблицы SMBIOS

    // qCritical() << "Файл успешно прочитан. Размер:" << buffer.size() << "байт";
    // qCritical() << "Первые 10 байтов:";
    // for (int i = 0; i < qMin(20, buffer.size()); ++i) {
    //     qCritical() << QString::number(ptrByte[i], 16).rightJustified(2, '0');
    // }

    // Простое парсирование: нахождение таблиц памяти

    while (*ptrStr != 127) { // Обработка каждого байта в таблице SMBIOS
        ptrByte = ptrStr;             // Переход на следующую структуру
        //BYTE length = *ptrByte + 1; // Узнаём длину структуры без строк
        switch (*ptrByte) {
        case 17: {
            InfoPlatform::infoMemory module;
            ++ptrByte;                                      // Подготовка к считыванию данных
            ptrStr = ptrByte + *ptrByte - 1; ptrByte += 3;  // Ставим оба указателя на свои места
            if(version >= 2.0){              // Версия 2.0
                ptrByte += 2; //PhysicalArrayHandle // Делаем из двух BYTE один WORD. И переходим на след. параметр
                ptrByte += 2; // ErrorInformationHandle
                ptrByte += 2; // TotalWidth
                ptrByte += 2; // DataWidth
                ptrByte += 2; // Size
                ptrByte += 2; // FormFactor // Присваеваем значение и переходим к следующему байту
                ptrByte += 2; // DeviceSet
                //QString temp = BYTEtoSTRING(&ptrStr); ptrByte++; // Здесь начинается первая строка
                //temp = BYTEtoSTRING(&ptrStr); ptrByte++;
                ptrByte++;    // MemoryType
                ptrByte += 2; // TypeDetail
            } else {InfoLin::vecMemory.push_back(module); break;} // Сохраняем данные и выходим из case
            break;}
        case 127: {return;}
        default:                // Обработка ненужных нам типов.
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
            // ptrByte += length;   // Переходим к строковым типам.
            // while (ptrByte < buffer.size() && buffer[ptrByte] == 0) { // Пока не будет найден конец всех строк (Цикл в цикле. Нужана оптимизация)
            //     ptrByte++;
            // }
            break;
        }
    }

    // while (offset < smbiosData.size()) {
    //     quint8 type = static_cast<quint8>(smbiosData[offset]);
    //     quint8 length = static_cast<quint8>(smbiosData[offset + 1]);
    //     quint16 handle = *reinterpret_cast<quint16*>(smbiosData.data() + offset + 2);

    //     if (type == 17) { // 17 - Тип записи для Memory Device
    //         InfoLin::infoMemory module;
    //         module.Size = static_cast<int>(smbiosData[offset + 12]) * 1024; // Size in KB
    //         qCritical() << module.Size;
    //         module.FormFactor = QString::number(static_cast<int>(smbiosData[offset + 21]));
    //         module.MemoryType = QString::number(static_cast<int>(smbiosData[offset + 22]));

    //         // Пример получения строки производителя (строковые индексы начинаются с 1)
    //         int manufacturerIdx = static_cast<int>(smbiosData[offset + 17]);
    //         int partNumberIdx = static_cast<int>(smbiosData[offset + 20]);
    //         int serialNumberIdx = static_cast<int>(smbiosData[offset + 18]);
    //         int assetTagIdx = static_cast<int>(smbiosData[offset + 19]);

    //         // Поиск строковых данных
    //         int stringStart = offset + length;
    //         int stringOffset = stringStart;
    //         int currentStringIdx = 1;

    //         // while (stringOffset < smbiosData.size() && smbiosData[stringOffset] != 0) {
    //         //     if (currentStringIdx == manufacturerIdx) {
    //         //         module.manufacturer = QString::fromUtf8(smbiosData.data() + stringOffset);
    //         //     } else if (currentStringIdx == partNumberIdx) {
    //         //         module.partNumber = QString::fromUtf8(smbiosData.data() + stringOffset);
    //         //     } else if (currentStringIdx == serialNumberIdx) {
    //         //         module.serialNumber = QString::fromUtf8(smbiosData.data() + stringOffset);
    //         //     } else if (currentStringIdx == assetTagIdx) {
    //         //         module.assetTag = QString::fromUtf8(smbiosData.data() + stringOffset);
    //         //     }
    //         //     stringOffset += strlen(smbiosData.data() + stringOffset) + 1;
    //         //     currentStringIdx++;
    //         // }
    //         InfoLin::vecMemory.push_back(module);
    //     }

    //     offset += length;
    //     while (offset < smbiosData.size() && smbiosData[offset] == 0) {
    //         offset++;
    //     }
    // }

    // // // Вывод информации о всех найденных модулях RAM
    // // for (const auto &module : ramModules) {
    // //     module.print();
    // // }
};


#endif
