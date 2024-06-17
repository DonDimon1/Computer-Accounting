#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//Основное окно приложения
#include <QMainWindow>
#include <QSqlDatabase> //Доступ к базе данных через соединение
#include <QSqlQuery>    //Для работы с SQL
#include <QDebug>       //Для отладки
#include <QSqlTableModel> //Для отображения таблицы БД в виджите tableView
#include <QSqlQueryModel> //Для отображения данных из БД в режиме только чтения
#include "computerdata.h" //Для своей вкладки в tabWidget_Main

typedef unsigned int UINT; // Почему то само не определяется

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    inline static QSqlDatabase db; //Объект класса QSqlDatabase
    //inline static QSqlQuery *query; //Объект класса QSqlQuery (Мы не создаём новую БД каждый раз, а работаем с уже открытой во всей программе)
    inline static UINT computerCount = 0; // Кол-во записей о комьютерах
    bool creationTablesDB(); // Создание таблиц для работы с БД

private slots:
    void on_pushButton_Add_clicked();

    void on_pushButton_Delete_clicked();

    void on_tableViewMainTab_clicked(const QModelIndex &index);

    void on_pushButton_Create_clicked();

    void on_tableViewMainTab_doubleClicked(const QModelIndex &index);

    void upDateTable(QString tabName); // Слот для обновления основной таблицы tableViewMainTab //computerData *myNewTab1

    void on_tabWidget_Main_tabCloseRequested(int index);

private:
    Ui::MainWindow *ui;
    //QSqlDatabase db; //Объект класса QSqlDatabase
    QSqlQuery *query; //Объект класса QSqlQuery
    QSqlTableModel *model; //Для считывания данных из БД в режиме редактирования
    //QSqlQueryModel *model; //Для считывания данных из БД в режиме только чтения

    int activeRow; //Номер активной строки
};
#endif // MAINWINDOW_H
