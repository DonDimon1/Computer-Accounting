#ifndef MYPROCESSMANAGER_H
#define MYPROCESSMANAGER_H

#include <QObject>
#include <QProcess>
#include <QMap>
#include <QString>
#include <QPointer>

class MyProcessManager : public QObject {
    Q_OBJECT
public:
    explicit MyProcessManager(QObject *parent = nullptr);
    ~MyProcessManager();

    void startProcess(const QString &processName, const QString &command);                              // Старт процесса
    void cleanUpProcess(const QString &processName);                                                    // Удаление процесса

signals:
    //void processFinished(const QString &processName, int exitCode, QProcess::ExitStatus exitStatus);
    void processFinished(const QString &processName, const QString &output);                            // Сигнал посылающий результат работы процесса
    void processError(const QString &processName, QProcess::ProcessError &error);                       // Сигнал посылающий вывод ошибки процесса

private slots:
    void onProcessFinished(int exitCode, QProcess::ExitStatus exitStatus);                              // Слот, ожидающий окончания процесса
    void onProcessError(QProcess::ProcessError error);                                                  // Слот, ожидающий ошибки процесса
    //void onReadyReadStandardOutput();                                                                   // Слот, ожидающий чтения результата процесса
    //void onReadyReadStandardError();                                                                    // Слот, лжидающий чтения ошибки процесса

private:
    QMap<QString, QPointer<QProcess>> m_processes;                                                      // Мапа процессов (Имя процесса, умного указателя на процесс).
};

#endif // MYPROCESSMANAGER_H




