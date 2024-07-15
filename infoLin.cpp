#ifdef __linux__

#include "infoLin.h"

InfoLin::InfoLin(){} // Конструктор

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

const char *InfoLin::GetOsBitWidth(){ //Получить разрядность винды
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

#endif
