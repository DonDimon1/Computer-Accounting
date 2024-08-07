#include "myProcessManager.h"
#include <QDebug>

MyProcessManager::MyProcessManager(QObject *parent) : QObject(parent) {}

MyProcessManager::~MyProcessManager() {
    // Очищаем все процессы при уничтожении объекта ProcessManager
    for (auto &process : m_processes) {
        if (process) {
            process->kill();
            process->waitForFinished();
            //process->deleteLater();
            delete process;
            process = nullptr;
        }
    }
    m_processes.clear();
}

//void MyProcessManager::startProcess(const QString &processName, const QString &command) {
void MyProcessManager::startProcess(const QString &processName, const QString &command, const QStringList &arguments) {

    if (m_processes.contains(processName)) {
        qWarning() << "Process" << processName << "is already running.";
        return;
    }

    QPointer<QProcess> process = new QProcess(this);
    m_processes[processName] = process;

    //connect(process, &QProcess::finished, this, &MyProcessManager::onProcessFinished);
    connect(process, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(onProcessFinished(int,QProcess::ExitStatus)));
    connect(process, QOverload<QProcess::ProcessError>::of(&QProcess::errorOccurred), this, &MyProcessManager::onProcessError);
//    connect(process, &QProcess::readyReadStandardOutput, this, &MyProcessManager::onReadyReadStandardOutput);
//    connect(process, &QProcess::readyReadStandardError, this, &MyProcessManager::onReadyReadStandardError);

    //process->start(command);
    process->start(command, arguments);
    //process->start("lshw", QStringList() << "-c" << "video");
    //process->start("lshw", {"-c", "video"});

    qCritical() << "MyProcessManager::startProcess" << "Процесс " << processName << "Стартовал";
}

void MyProcessManager::cleanUpProcess(const QString &processName) {
    if (m_processes.contains(processName)) {
        QPointer<QProcess> process = m_processes[processName];
        if (process) {

            qCritical() << "MyProcessManager::cleanUpProcess" << "Процесс " << process << "удаляется";

            process->kill();
            process->waitForFinished();
            process->deleteLater();
            process = nullptr;

            qCritical() << "MyProcessManager::cleanUpProcess" << "Процесс удалён";
        }
        m_processes.remove(processName);
    }
}

void MyProcessManager::onProcessFinished(int exitCode, QProcess::ExitStatus exitStatus) {
    QProcess *process = qobject_cast<QProcess*>(sender());            
    QString processName;
    for (auto it = m_processes.begin(); it != m_processes.end(); ++it) {
        if (it.value() == process) {
            processName = it.key();
            qCritical() << "MyProcessManager::onProcessFinished" << "Процесс " << process << "Корректно завершён";
            break;
        }
    }

    if (!processName.isEmpty()) {
        QString output = process->readAllStandardOutput();

        qCritical() << "MyProcessManager::onProcessFinished" << "Вызов сигнала processFinished";

        emit processFinished(processName, output);
        cleanUpProcess(processName);
    }
}

void MyProcessManager::onProcessError(QProcess::ProcessError error) {
    QProcess *process = qobject_cast<QProcess*>(sender());

    qCritical() << "MyProcessManager::onProcessError" << "Процесс " << process << "Завершён ошибкой";
    QString processName;
    for (auto it = m_processes.begin(); it != m_processes.end(); ++it) {
        if (it.value() == process) {
            processName = it.key();
            break;
        }
    }

    if (!processName.isEmpty()) {
        emit processError(processName, error);
        cleanUpProcess(processName);
    }
}

//void MyProcessManager::onReadyReadStandardOutput() {
//    QProcess *process = qobject_cast<QProcess*>(sender());
//    QString processName;
//    for (auto it = m_processes.begin(); it != m_processes.end(); ++it) {
//        if (it.value() == process) {
//            processName = it.key();
//            break;
//        }
//    }

//    if (!processName.isEmpty()) {
//        QString output = process->readAllStandardOutput();
//        qDebug() << "Process" << processName << "output:" << output;
//        // Добавьте здесь код для обработки вывода конкретного процесса
//    }
//}

//void MyProcessManager::onReadyReadStandardError() {
//    QProcess *process = qobject_cast<QProcess*>(sender());
//    QString processName;
//    for (auto it = m_processes.begin(); it != m_processes.end(); ++it) {
//        if (it.value() == process) {
//            processName = it.key();
//            break;
//        }
//    }

//    if (!processName.isEmpty()) {
//        QString errorOutput = process->readAllStandardError();
//        qDebug() << "Process" << processName << "error output:" << errorOutput;
//        // Добавьте здесь код для обработки вывода ошибок конкретного процесса
//    }
//}


