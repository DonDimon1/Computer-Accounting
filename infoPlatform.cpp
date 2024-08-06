#include "infoPlatform.h"

InfoPlatform::InfoPlatform(QObject *parent) : QObject(parent){
    processManager = new MyProcessManager(this);
    connect(processManager, &MyProcessManager::processFinished, this, &InfoPlatform::distributionSignals);  // Основной слот для распределения сигналов
    connect(processManager, &MyProcessManager::processError, this, &InfoPlatform::distributionErrors);      // Основной слот для обработки ошибок
}

InfoPlatform::~InfoPlatform(){
    delete processManager;
}
