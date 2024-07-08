#include "compInfo.h"
#include "smbios.h" //Описание класса SMBIOS
#include <sysinfoapi.h>
#include <QCoreApplication> //Для запроса PowerShell
#include <QProcess>
#include <QDebug>
//#include <QStorageInfo>

compInfo::compInfo() //Конструктор
{
    compInfo::SMBIOS SMTable; // Класс для содержания необработанной инфы из SMBIOS
    compInfo::DecodeSMBIOS(&SMTable); // Расшифровать информацию из таблицы SMBIOS
    compInfo::GetHardDriveInfo(); //Функцию для чтения информации про жёсткие диски из WMI с помощью PowerShell.
}

void compInfo::GetHardDriveInfo(){ //Функцию для чтения информации про жёсткие диски из WMI с помощью PowerShell.
    QProcess process; // Создаем процесс PowerShell

    // Устанавливаем команду для выполнения скрипта PowerShell
    QStringList arguments;
    arguments << "-Command" << "Get-WmiObject Win32_DiskDrive; Exit 0;"; //<< "-NoProfile" << "exit"
    process.start("powershell", arguments); // Запускаем процесс

    //if(!process.waitForReadyRead(30000)){ // Ждём пока данные будут доступны для чтения (waitForFinished зависает намертво)
    //if(!process.waitForFinished(-1)){
    if(!process.waitForFinished(30000)){
        process.kill(); // Завершаем процесс
        return; // Выходим из функции
    }
    QString queryResult = process.readAllStandardOutput();    // Если всё хорошо, считываем данные из запроса.
    // Destroyed while process ("powershell") is still running.
    process.kill(); // Завершаем процесс (// waitForFinished зависает намертво)

    //Обрабатываем данные
    WORD diskCount = queryResult.count("Model      :"); // Кол-во вхождений подстроки в строку
    for(WORD i = 0; i < diskCount; ++i){  // Проходим по всем дискам
        compInfo::infoHardDrive newStruct; // Создаём структуру для хранения данных
        int index = queryResult.indexOf("Model      :", 0, Qt::CaseInsensitive); // Ищем подстроку Model
        queryResult.remove(0, index + 13); // Удаляем лишние данные (Получаем начало названия диска)
        index = queryResult.indexOf("\r", 0, Qt::CaseInsensitive); // Ищем конец названия
        newStruct.Name = queryResult.left(index); // Сохраняем имя диска
        queryResult.remove(0, index + 15); // Удаляем лишние данные (Получаем начало размера диска)
        index = queryResult.indexOf("\r", 0, Qt::CaseInsensitive); // Ищем конец размера диска
        QString tempStr = queryResult.left(index); // Определяем размер диска в отдельную строку
        long long tempLong = tempStr.toLongLong(); // Конвертируем байты а численный тип
        newStruct.Size = tempLong / (1024 * 1024 * 1024); // Конвертируем байты в гигабайты и сохраняем значение
        compInfo::vecDrive.push_back(newStruct); // Сохраняем структуру в векторе
    }
};

void compInfo::DecodeSMBIOS(compInfo::SMBIOS *SMTable){     //Функция для декодирования данных из таблицы SMBIOS
    // ОЗУ
    WORD slotsNum = SMTable->vecMemory.size();                                                  // Кол-во разъёмов для памяти, найденных в SMBIOS
    compInfo::TotalRAMSlots = slotsNum;                                                         // Сохраняем инфу о общем кол-ве разъёмов для памяти
    for(UINT i = 0; i < slotsNum; ++i){                                                         // Перебераем все плашки ОЗУ
        if(SMTable->vecMemory.at(i).Size){                                                      // Если плашка памяти установлена
            compInfo::infoMemory newStruct;                                                     // Создаём новую структуру с обработанными данными про конкретную плашку ОЗУ
            newStruct.Size = SMTable->vecMemory.at(i).Size;                                     // Сохраняем Объём плашки в МБ.
            newStruct.FormFactor = SMTable->GetFormFactor(SMTable->vecMemory.at(i).FormFactor); // Сохраняем Форм фактор плашки
            newStruct.DeviceLocator = SMTable->vecMemory.at(i).DeviceLocator;                   // В каокм слоте стоит плашка
            newStruct.MemoryType = SMTable->GetMemoryType(SMTable->vecMemory.at(i).MemoryType); // Сохраняем тип памяти
            newStruct.Speed = SMTable->vecMemory.at(i).Speed;                                   // Сохраняем скорость
            newStruct.Manufacturer = SMTable->vecMemory.at(i).Manufacturer;                     // Сохраняем производителя
            compInfo::vecMemory.push_back(newStruct);                                           // Добавляем инфу об установленной плашке памяти
        }                                                                                       // Кол-во элементов вектора обозначает кол-во установленных плашек ОЗУ
    }
};

QString compInfo::GetOsVersionNameQSysInfo(){//Версия ОС
    return QSysInfo::prettyProductName();
}
// const char *compInfo::GetOsVersionName(){ //Версия ОС
//     if (IsWindows10OrGreater())
//         return "Windows 10";
//     if (IsWindows8Point1OrGreater())
//         return "Windows 8.1";
//     if (IsWindows8OrGreater())
//         return "Windows 8";
//     if (IsWindows7SP1OrGreater())
//         return "Windows 7 SP1";
//     if (IsWindows7OrGreater())
//         return "Windows 7";
//     if (IsWindowsVistaSP2OrGreater())
//         return "Windows Vista SP2";
//     if (IsWindowsVistaSP1OrGreater())
//         return "Windows Vista SP1";
//     if (IsWindowsVistaOrGreater())
//         return "Windows Vista";
//     if (IsWindowsXPSP3OrGreater())
//         return "Windows XP SP3";
//     if (IsWindowsXPSP2OrGreater())
//         return "Windows XP SP2";
//     if (IsWindowsXPSP1OrGreater())
//         return "Windows XP SP1";
//     if (IsWindowsXPOrGreater())
//         return "Windows XP";
//     if (IsWindowsServer())
//         return "Windows Server"; //Потом исправить
//     return "Unknown";
// };

QString compInfo::GetComputerName_(){ //Получить имя компьютера
    char buffer[MAX_COMPUTERNAME_LENGTH + 1] = ""; //Буфер для вывода имени компьютера
    DWORD size = sizeof(buffer);                   //Размер этого буфера
    if (GetComputerNameA(buffer, &size))             //Если функция отработала корректно
        return buffer;                              //Возвращаем имя компьютера
    return "undefine";
};

QString compInfo::GetUserName_(){ //Получить имя пользователя
    char buffer[MAX_COMPUTERNAME_LENGTH + 1] = ""; //Буфер для вывода имени компьютера
    DWORD size = sizeof(buffer);                   //Размер этого буфера
    if (GetUserNameA(buffer, &size))             //Если функция отработала корректно
        return buffer;
    return "undefine";
};

const char *compInfo::GetOsBitWidth(){ //Получить разрядность винды
//    #if defined(__LP64__) || defined(_M_IA64) //(Кросс-платформа)
//        return "x64";
//    #endif
//    return "x32";
    #if defined(_WIN64) //Это только для винды
        return "x64";
    #elif defined(_WIN32)
        return "x32";
    #endif
};

QString compInfo::GetCPUName(){ //Получить имя процессора
    char cpuName[256]; //Имя процессора
    HKEY hKey;
    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
        // Чтение имени процессора из реестра
            DWORD dwBufferSize = sizeof(cpuName);
            RegQueryValueExA(hKey, "ProcessorNameString", NULL, NULL, (LPBYTE)&cpuName, &dwBufferSize);
            RegCloseKey(hKey); // Закрываем ключ реестра
            return cpuName;
    }
    return "undefine";
};

QString compInfo::GetCPUType(){ //Получить тип архитектуры процессора
    char cpuType[256];
    HKEY hKey;
    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
        // Чтение имени процессора из реестра
            DWORD dwBufferSize = sizeof(cpuType);
            RegQueryValueExA(hKey, "Identifier", NULL, NULL, (LPBYTE)&cpuType, &dwBufferSize);
            RegCloseKey(hKey); // Закрываем ключ реестра
            return cpuType;
    }
    return "undefine";
};

DWORD compInfo::GetCPUFrequency(){ //Получить частоту процессора
    DWORD dwMHz = 0; //Частота процессора
    HKEY hKey;
    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
        // Чтение частоты процессора из реестра
        DWORD dwBufferSize = sizeof(dwMHz);
        RegQueryValueExA(hKey, "~MHz", NULL, NULL, (LPBYTE)&dwMHz, &dwBufferSize);
        RegCloseKey(hKey); // Закрываем ключ реестра
        return dwMHz;
    }
    return 0;
};

DWORD compInfo::GetCPUNumberCore(){ //Получить кол-во ядер процессора
    SYSTEM_INFO sysInfo; // Получение информации о системе
    GetSystemInfo(&sysInfo);
    return sysInfo.dwNumberOfProcessors; //Кол-во ядер процессора
};

QString compInfo::GetBoardManufacturer(){ //Получить производителя мат.платы
    char MBManufacturer[256];
    HKEY hKey;
    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\BIOS", 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
            DWORD dwBufferSize = sizeof(MBManufacturer);
            RegQueryValueExA(hKey, "BaseBoardManufacturer", NULL, NULL, (LPBYTE)&MBManufacturer, &dwBufferSize);
            RegCloseKey(hKey); // Закрываем ключ реестра
            return MBManufacturer;
    }
    return "undefine";
};

QString compInfo::GetBoardName(){ //Получить название мат.платы
    char MBName[256];
    HKEY hKey;
    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\BIOS", 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
            DWORD dwBufferSize = sizeof(MBName);
            RegQueryValueExA(hKey, "BaseBoardProduct", NULL, NULL, (LPBYTE)&MBName, &dwBufferSize);
            RegCloseKey(hKey); // Закрываем ключ реестра
            return MBName;
    }
    return "undefine";
};

DWORD compInfo::GetMemorySize(){ //Получить общий объём ОЗУ
    MEMORYSTATUSEX memoryStatus;
    memoryStatus.dwLength = sizeof (memoryStatus);
    GlobalMemoryStatusEx(&memoryStatus);
    return memoryStatus.ullTotalPhys / (1024 * 1024);
};


QString compInfo::GetGPUName(){ // Получить модель видеокарты
    DISPLAY_DEVICE displayDevice;
    displayDevice.cb = sizeof (DISPLAY_DEVICE);

    DWORD deviceIndex = 0;
       // while (EnumDisplayDevices(NULL, deviceIndex, &displayDevice, 0)){
       //     if(displayDevice.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE){
       //         return displayDevice.DeviceString; // Преобразуем Wchar_t в QString
       //         //qDebug() << "Primary Display Adapter: " << displayDevice.DeviceString;
       //     } else{
       //         //qDebug() << "Secondary Display Adapter: " << displayDevice.DeviceString;
       //     }
       //     deviceIndex++;
       // }
    //На разных компах по разному
    while (EnumDisplayDevicesW(NULL, deviceIndex, &displayDevice, 0)){
        if(displayDevice.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE){
            return QString::fromWCharArray(displayDevice.DeviceString); // Преобразуем Wchar_t в QString
            //qDebug() << "Primary Display Adapter: " << displayDevice.DeviceString;
        } else{
            //qDebug() << "Secondary Display Adapter: " << displayDevice.DeviceString;
        }
        deviceIndex++;
    }
    return "Undefined";
};

DWORD compInfo::GetGPUMemSize(){ // Получить объём видеопамяти
    IDXGIFactory* pFactory;
    HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&pFactory);
    if (FAILED(hr)){
        //qDebug() << "Failed to create DXGI factory. Error code: " << hr;
        return 0;
    }

    IDXGIAdapter* pAdapter;
    hr = pFactory->EnumAdapters(0, &pAdapter);
    if(FAILED(hr)){
        //qDebug() << "Failed to enumerate DXGI adapters. Error code: " << hr;
        return 0;
        pFactory->Release();
    }
    DXGI_ADAPTER_DESC adapterDesc;
    hr = pAdapter->GetDesc(&adapterDesc);
    if(FAILED(hr)){
        //qDebug() << "Failed to get DXGI adapter description. Error code: " << hr;
        return 0;
        pAdapter->Release();
        pFactory->Release();
    }
    //qDebug() << "Video Memory: " <<adapterDesc.DedicatedVideoMemory / (1024 * 1024) << "MB";
    return adapterDesc.DedicatedVideoMemory / (1024 * 1024);
    pAdapter->Release();
    pFactory->Release();
};

bool compInfo::GetCDROM(){ // Получить наличие дисковода
    // Проходим по буквам дисков, начиная с 'A' и заканчивая 'Z'
    for (char drive = 'A'; drive <= 'Z'; ++drive) {
        // Формируем строку с именем диска
        std::string rootPath = std::string("\\\\.\\") + drive + ":";

        // Получаем тип дискового устройства
        UINT driveType = GetDriveTypeA(rootPath.c_str());

        // Проверяем, является ли диск CDROM'ом
        if (driveType == DRIVE_CDROM) { // Если нашли CDROM
            return true;
        }
    }
    return false; // Если не нашли CDROM
};

//void compInfo::GetMonitor() { // Получить инфу об мониторе
//    HMONITOR hMonitor = MonitorFromPoint(POINT{0, 0}, MONITOR_DEFAULTTOPRIMARY); // Получаем список мониторов
//    while (hMonitor != NULL) {
//        // Получаем информацию о мониторе
//        MONITORINFO monitorInfo;
//        GetMonitorInfo(hMonitor, &monitorInfo);

//        // Сохраняем параметры монитора
//        compInfo::infoMonitors newStruct; // Создаём структуру для хранения данных
//        newStruct.Name = monitorInfo.cbSize;
////        std::cout << "Monitor name: " << monitorInfo.szDevice << std::endl;
////        std::cout << "Size: " << monitorInfo.rcMonitor.right << " x " << monitorInfo.rcMonitor.bottom << std::endl;
////        std::cout << "Position: " << monitorInfo.rcMonitor.left << ", " << monitorInfo.rcMonitor.top << std::endl;
////        std::cout << "State: " << monitorInfo.dwFlags << std::endl;
////        std::cout << "Type: " << monitorInfo.dmPosition << std::endl;
////        std::cout << "Resolution: " << monitorInfo.dwWidth << " x " << monitorInfo.dwHeight << std::endl;
////        std::cout << "Aspect ratio: " << monitorInfo.dmPelsWidth << " / " << monitorInfo.dmPelsHeight << std::endl;
////        std::cout << "Vertical sync: " << (monitorInfo.dwFlags & VERTRES ? "enabled" : "disabled") << std::endl;
////        std::cout << "Refresh rate: " << monitorInfo.dwRefreshRate << std::endl;

//        // Переходим к следующему монитору
//        //hMonitor = MonitorNext(hMonitor);
//    }
//};
