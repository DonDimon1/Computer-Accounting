#ifndef INFOLIN_H
#define INFOLIN_H

#ifdef __linux__ // Класс для сбора всей информации о комьютере в среде Linux
#include "infoPlatform.h"

class InfoLin : public InfoPlatform
{
    Q_OBJECT
public:
    explicit InfoLin(QObject *parent = nullptr); // Конструктор
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
    //Информация о Видеокарте
    QString GetGPUName() override;                  // Получить модель видеокарты
    DWORD GetGPUMemSize() override;                 // Получить объём видеопамяти видеокарты
    //Информация о жёстких дисках
    void GetHardDriveInfo() override;               // Получить информацию о физических дисках
    //Информация о дисководе
    bool GetCDROM() override;


    // Обработка процессов QProcess
    void ProcessingDataCPUName(const QString &output); // Обработка результата процесса ProcessGetGPUName
    //ОЗУ
    //WORD TotalRAMSlots;                                 // Общее кол-во разъёмов для памяти
    //std::vector<InfoPlatform::infoMemory> vecMemory;    // Информация обо всех плашках ОЗУ
    //Дису
    //std::vector<infoHardDrive> vecDrive;                // Информация обо всех физических дисках
    // //Monitor
    // std::vector<infoMonitors> vecMonitors;           // Информация обо всех плашках мониторах

private slots:
    //void readProcessOutput();
    //void processGetGPUNameFinished(int exitCode, QProcess::ExitStatus exitStatus);
public slots:
    void distributionSignals(const QString &processName, const QString &output) override;               // Основной слот для распределения сигналов по корректным методам
    void distributionErrors(const QString &processName, const QProcess::ProcessError &error) override;  // Основной слот для обработки ошибок процессов
private:
    QProcess *process;
};

#endif

#endif // INFOLIN_H
