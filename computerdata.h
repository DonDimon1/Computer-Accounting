#ifndef COMPUTERDATA_H
#define COMPUTERDATA_H

//Окно карточки приложения. Открывается в новой вкладке основного окна
#include <QWidget>
#include <QStandardItemModel> //Для модели
#include "mainWindow.h" // Считывание параметров компьютера
#include "compInfo.h" // Считывание параметров компьютера
#include <QSqlQuery>    //Для работы с SQL

namespace Ui {
class computerData;
}

class computerData : public QWidget
{
    Q_OBJECT

public:
    //explicit computerData(QWidget *parent = nullptr);
    explicit computerData(QWidget *parent = nullptr, UINT ID = 0); // Конструктор открытия комьютера
    ~computerData();
    void existingPC(); // Функция помощника конструктора для существующего в базе компьютера
    void defunctPC(); // Функция помощника конструктора для НЕ существующего в базе компьютера
    void modelsHeaders(); // Функция для задания заголовков моделям

signals:
    void sendUpdateSignal(QString tabName = "Новая вкладка"); // Отправка сигнала для обновления таблицы tableViewMainTab на форме mainWindow

private slots:
    void on_pushButton_Save_clicked(); 

private:
    Ui::computerData *ui;
    class MySqlTableModel;  // Переопределение QStandardItemModel для запрета редактирования колонки с датой
    UINT ID = 0; //id компьютера в БД со стандартным значением
    //Модели для таблиц
    MySqlTableModel *basicInfModel;
    MySqlTableModel *hardware;
    MySqlTableModel *repair;
    MySqlTableModel *movements;
};

#endif // COMPUTERDATA_H
