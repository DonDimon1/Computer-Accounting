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
#include <QFile>
#include <QByteArray>
// Для определения модели Видеокарты
#include <QProcess>
#include <QStringList>
// Для определения CDROM
#include <QDir>


InfoLin::InfoLin(){                     // Конструктор
    SMBIOS SMTable;                     // Класс для содержания необработанной инфы из SMBIOS
    InfoLin::DecodeSMBIOS(&SMTable);    // Расшифровать информацию из таблицы SMBIOS
    InfoLin::GetHardDriveInfo();        // Функцию для чтения информации про жёсткие диски
}

void InfoLin::DecodeSMBIOS(SMBIOS *SMTable){     //Функция для декодирования данных из таблицы SMBIOS
    // ОЗУ
    WORD slotsNum = SMTable->vecMemory.size();                                                  // Кол-во разъёмов для памяти, найденных в SMBIOS
    InfoLin::TotalRAMSlots = slotsNum;                                                          // Сохраняем инфу о общем кол-ве разъёмов для памяти
    for(UINT i = 0; i < slotsNum; ++i){                                                         // Перебераем все плашки ОЗУ
        if(SMTable->vecMemory.at(i).Size){                                                      // Если плашка памяти установлена
            InfoPlatform::infoMemory newStruct;                                                 // Создаём новую структуру с обработанными данными про конкретную плашку ОЗУ
            newStruct.Size = SMTable->vecMemory.at(i).Size;                                     // Сохраняем Объём плашки в МБ.
            newStruct.FormFactor = SMTable->GetFormFactor(SMTable->vecMemory.at(i).FormFactor); // Сохраняем Форм фактор плашки
            newStruct.DeviceLocator = SMTable->vecMemory.at(i).DeviceLocator;                   // В каокм слоте стоит плашка
            newStruct.MemoryType = SMTable->GetMemoryType(SMTable->vecMemory.at(i).MemoryType); // Сохраняем тип памяти
            newStruct.Speed = SMTable->vecMemory.at(i).Speed;                                   // Сохраняем скорость
            newStruct.Manufacturer = SMTable->vecMemory.at(i).Manufacturer;                     // Сохраняем производителя
            InfoLin::vecMemory.push_back(newStruct);                                            // Добавляем инфу об установленной плашке памяти
        }                                                                                       // Кол-во элементов вектора обозначает кол-во установленных плашек ОЗУ
    }
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

QString InfoLin::GetGPUName() { // Получить модель видеокарты
    //QString cmd = "sh -c \"lspci | grep -E \"VGA|3D\"\"";
    //QString cmd = "lspci | grep -E \"VGA|3D\"";
    QString cmd = "lshw -c video";
    QProcess process;
    process.start(cmd);
    process.waitForFinished();          // TODO: вызыв консоли тормозит программу. Либо обойтись без вызова, либо закинуть это в отдельный поток
    process.waitForReadyRead();
    QString output = process.readAllStandardOutput(); // Вывод консольной команды

    if(output.isEmpty()){
        qCritical() << "Не удалось получить модель видеокарты. Попробуйте запустить программу с правами суперпользователя (root), либо обновите пакет lshw.";
        qCritical() << process.readAllStandardError();
        process.close();
        return "undefine";
    }
    process.close();

    QStringList stringList = output.split('\n', Qt::SkipEmptyParts); // Разделяем строку на несколько строк для удобства
    const std::vector<QString> search = {"product:", "vendor:", "version:"};
    std::vector<QString> vecValue; //{QString product, QString vendor, QString version};

    int keyWordIndex = 0;
    for(const QString &line : stringList){ // Поиск по всем строкам
        if(line.contains(search.at(keyWordIndex))){     // Если ключевое слово найдено
            //foundValue = line.trimmed(); // Сохраняем значение (Модель отдельно)
            QString foundValue = line.trimmed();
            foundValue.remove(search.at(keyWordIndex)); // Удаляем ключевое слово из строки
            vecValue.push_back(foundValue);             // Сохраняем строку
            if(++keyWordIndex >= search.size())         // Проверка на наличие строк
                break;
        }
    }
    return vecValue.at(1) + " " + vecValue.at(0) + " version:" + vecValue.at(2); // Выводим значения в нужном порядке
}

DWORD InfoLin::GetGPUMemSize() {              // Получить объём видеопамяти видеокарты
    // TODO: Пока не реализовано
    return 0;
}

void InfoLin::GetHardDriveInfo() { // Получить информацию о физических дисках
    // TODO: вызыв консоли тормозит программу. Либо обойтись без вызова, либо закинуть это в отдельный поток
    //hdparm -I /dev/sda
    //ls -lF /dev/disk/by-id/
    QProcess process;
    process.start("lsblk -o NAME,SIZE,TYPE --noheadings");  // Получаем список всех дисков
    process.waitForFinished();
    process.waitForReadyRead();
    QString output = process.readAllStandardOutput();

    if(output.isEmpty()){
        qCritical() << "Не удалось получить информацию о количестве физических дисков с помощью lsblk.";
        return;
    }

    QStringList stringList = output.split("\n", Qt::SkipEmptyParts);                            // Разбиваем список на строки

    for (const QString &line : stringList) {                                                    // Обработка каждой строки вывода lsblk
        QStringList fields = line.split(QRegExp("\\s+"), Qt::SkipEmptyParts);                   // Разделяем каждую строку на подстроки (их 3)
        if (fields.at(2) == "disk" && fields.at(0).contains("sd")) { //fields.size() >= 3       // Если в 3 подстроке есть слово disk и первая подстрока содержит символы sd
            InfoPlatform::infoHardDrive newStruct;                                              // Создаём новую структуру для записи характеристик
            std::vector<QString> vecValue;                                                      // Вектор в который будем сохранять результаты парсинга
            QString deviceName = fields[0];                                                     // Сохраняем временное имя
            QString deviceSize = fields[1];                                                     // Сохраняем размер диска
            deviceSize.remove("G");                                                             // Подготавливаем строку к переходу к типо DWORD
            deviceSize.replace(",",".");
            newStruct.Size = deviceSize.toDouble();                                             // Преобразуем в DWORD

            // Получаем информацию о диске с помощью hdparm
            QString hdparmOutput = "hdparm -I /dev/" + deviceName;                              // Вызываем новый процесс для определения всех характеристик текущего диска
            QProcess subProcess;
            subProcess.start(hdparmOutput);
            subProcess.waitForFinished();
            subProcess.waitForReadyRead();
            QString diskOutput = subProcess.readAllStandardOutput();                            // Считываем характеристики

            if(diskOutput.isEmpty()){
                qCritical() << "Не удалось получить информацию о диске " + deviceName + " с помощью hdparm.";
                continue;
            }

            QStringList diskFields = diskOutput.split("\n", Qt::SkipEmptyParts);                // Разбиваем их для удобности по строкам
            const QString keyWord = "Model Number:";                                            // Ключевое слово для поиска наименования модели
            for(const QString &diskLine : diskFields){                                          // Проходим по всем строкам
                if(diskLine.contains(keyWord)){                                                 // Если строка содержит ключевое слово
                    QString temp = diskLine.trimmed();                                          // Удаляем лишние пробелы
                    temp.remove(keyWord);                                                       // Удаляем само ключевое слово из строки
                    newStruct.Name = temp.trimmed();
                    qCritical() << newStruct.Name;                                              // Сохраняем результат
                    break;
                }
            }
            InfoLin::vecDrive.push_back(newStruct);
        }
    }
}

bool InfoLin::GetCDROM() {  // Информация о дисководе
    QDir devDir("/dev");
    QStringList srDevices = devDir.entryList(QStringList() << "sr*", QDir::System);
    if(!srDevices.isEmpty())
        return true; // Если нашли CDROM
    else
        return false; // Если не нашли CDROM
}
#endif
