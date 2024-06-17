#ifndef COMPUTERDATA_H
#define COMPUTERDATA_H

//Окно карточки приложения. Открывается в новой вкладке основного окна
#include <QWidget>
#include <QStandardItemModel> //Для модели
#include "mainWindow.h" // Считывание параметров компьютера
#include "compInfo.h" // Считывание параметров компьютера
#include <QSqlQuery>    //Для работы с SQL
#include <QMenu> // Для контекстного меню

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
    void readPCCharacteristics(UINT ID = 0); // Считываем характеристики ПК
    void modelsHeaders(); // Функция для задания заголовков моделям
    class MySqlTableModel : public QSqlTableModel { // Переопределение QSqlTableModel для запрета редактирования колонки с датой
        // Q_OBJECT // Функции метаобъекта не поддерживаются для вложенных классов
    public:
        MySqlTableModel(QObject *parent = nullptr, QSqlDatabase db = QSqlDatabase()) : QSqlTableModel(parent, db) {}; // Конструктор
        Qt::ItemFlags flags(const QModelIndex &index) const override; // Переопределяем условие редактирования в MySqlTableModel
    };

signals:
    void sendUpdateSignal(QString tabName = "Новая вкладка"); // Отправка сигнала для обновления таблицы tableViewMainTab на форме mainWindow

private slots:
    void on_pushButton_Save_clicked(); 
    void on_pushButton_SaveAndExit_clicked();
    void on_pushButton_Refresh_clicked();

    void on_CustomContextMenuRequested(const QPoint &pos); // Кастомный слот для контекстного меню = QPoint(NULL, NULL)
    void insertRow(); // Вставить новую строку с помощью контекстного меню

private:
    Ui::computerData *ui;
    UINT ID = 0; //id компьютера в БД со стандартным значением
    QMenu *contextMenu; // Контекстное меню для таблиц
    //Модели для таблиц
    MySqlTableModel *basicInfModel;
    MySqlTableModel *hardware;
    MySqlTableModel *repair;
    MySqlTableModel *movements;
    //Действия контекстного меню
    QAction *deleteAction;
    QAction *insertAction;
};

#endif // COMPUTERDATA_H
