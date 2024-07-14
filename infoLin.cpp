#ifdef __linux__

#include "infoLin.h"

InfoLin::InfoLin(){} // Конструктор

QString InfoLin::GetOsVersionNameQSysInfo(){ //Версия ОС
    return QSysInfo::prettyProductName();
}

QString InfoLin::GetComputerName_(){ //Получить имя компьютера
    char hostname[HOST_NAME_MAX];
    if(gethostname(hostname, HOST_NAME_MAX))
        return QString::fromUtf8(hostname);
    return "undefine";
};

QString InfoLin::GetUserName_(){ //Получить имя пользователя
    char username[LOGIN_NAME_MAX];
    if(getlogin_r(username, LOGIN_NAME_MAX))
        return QString::fromUtf8(username);
    return "undefine";
};

const char *InfoLin::GetOsBitWidth(){ //Получить разрядность винды
    #if defined(__LP64__) || defined(_M_IA64) //(Кросс-платформа)
        return "x64";
    #endif
        return "x32";
};

#endif
