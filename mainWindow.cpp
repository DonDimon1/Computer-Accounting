#include "mainWindow.h"
#include "./ui_mainWindow.h"
#include "infoLin.h"
//#include <windows.h> // winAPI
#include <QStandardItemModel> //Для модели
#include <QtSql>


class MainWindow::MySqlTableModel : public QSqlTableModel { // Переопределяем для виртуальных колонок
public:
    MySqlTableModel(QObject *parent = nullptr, QSqlDatabase db = QSqlDatabase()) :
        QSqlTableModel(parent, db) {}
    // Переопределяем метод columnCount для корректного подсчёта колонок модели. (Чтобы колонка не пропадала при обновлении таблицы.)
    int columnCount(const QModelIndex &parent = QModelIndex()) const override { // Кол-во столбцов
        return QSqlTableModel::columnCount(parent) + 1; // +1 для дополнительного столбца
    }
    // Переопределяем метод data() для возврата значения виртуального столбца
    // Тут какая то фигня. Походу код выполняется каждый раз когда я взаимодействую со строкой. Значит и запрос выполняется что нагружает БД
    // Мб выгднее просто сохранить значения виртуальных колонок куда нибудь?
    QVariant data(const QModelIndex &item, int role = Qt::DisplayRole) const override // Переопределяем
    {
        if (!item.isValid()) { return QVariant(); }
        if (item.column() == 5 && role==Qt::DisplayRole) {  // Пока что хардкод (Без роли появляется чекбокс)
            // handle column separately
            UINT ID = QSqlTableModel::data(this->index(item.row(), 0), Qt::DisplayRole).toUInt(); // Хардкод колонки ID (Хз как по другому)
            QSqlQuery localQuery(MainWindow::db); // Локальный запрос
            localQuery.prepare("SELECT ComputerName FROM BasicInf WHERE ID = :id ORDER BY id DESC LIMIT 1"); // Выборка по ID задом наперёд с лимитом в 1 строку
            localQuery.bindValue(":id", ID); // Вставляем в запрос ID текущей строки
            if(!localQuery.exec()) { // Запрашиваем
                qDebug() << "При запросе имени компа для виртуальной колонки Name произошла ошибка";
                return "Ошибка";
            }
            if(localQuery.next()) // Если есть результат запроса
                return localQuery.value("ComputerName").toString();
            localQuery.clear(); // Очищаем запрос
            return "";
        }
        return QSqlQueryModel::data(item, role); // Если не виртуальная колонка
    }
    // Переопределяем метод flags для того чтобы ячейка была compInfo активная а не серая
    Qt::ItemFlags flags(const QModelIndex &index) const override {
        if(!index.isValid()) {return Qt::NoItemFlags;}
        if(index.column() == 5)  // Пока что хардкод
            return Qt::ItemIsSelectable | Qt::ItemIsEnabled; // Разрешаем выбор и включение
        return QSqlTableModel::flags(index);
    }
};

MainWindow::MainWindow(QWidget *parent) //Конструктор
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->showMaximized(); //Начальное окно на весь экран

    // Подключение к БД
    qDebug() << "Drivers list: " << QSqlDatabase::drivers();
    db = QSqlDatabase::addDatabase("QMYSQL", "mydb");   //Создания объекта соединения
    //db.setDatabaseName("./testDB.db");
    db.setHostName("localhost");//127.0.0.1
    db.setDatabaseName("ComputerAccounting");
    db.setUserName("root");
    //db.setPassword("EAZzae1234");
    db.setPassword("");

    if(!db.open())                                      //Проверка подключения к БД
        qDebug() << "Не удалось подключиться к БД: " << db.databaseName();

    query = new QSqlQuery(db);                          // Инициализация запроса
    if(!MainWindow::creationTablesDB()) {               // Создаём все нужные таблицы в базе данных
        return;}

    // Запрос проверки подключения к таблице MainTab
    if(!query->exec("SELECT * FROM MainTab"))
        qDebug() << "Не удалось подключиться к таблице: MainTab";

    model = new MainWindow::MySqlTableModel(this, db);  // Инициализация модель
    model->setTable("MainTab");                         // Устанавливает таблицу базы данных, с которой работает модель.
    model->select();                                    // Заполняет модель данными из таблицы, которая была задана через setTable()

    ui->tableViewMainTab->setEditTriggers(QAbstractItemView::NoEditTriggers); // Запрещаем пользователю редактировать таблицу tableViewMainTab
    ui->tableViewMainTab->setModel(model);              // Добавляем представлению таблицы нашу модель (помещаем модель в таблицу).
    //ui->tableViewMainTab->resizeColumnsToContents();  // Устанавливаем размер колонок под размер контента
    query->clear();                                     // Очищаем запрос

    //Узнаём крайний использованный id. Создаём запрос с сортировкой по ключу в обратном порядке и ограничиваем на 1у запись
    query->prepare("SELECT ID FROM MainTab ORDER BY ID DESC LIMIT 1"); // Подготавливаем запрос
    if(!query->exec())
        qDebug() << "Ошибка в запросе последнего ID";
    if(query->next())                                   // Если есть результат запроса
        computerCount = query->value(0).toUInt();       // Извлекаем значение последнего ключа из запроса
    query->clear();                                     // Очищаем запрос

    // Выводим имя в строке
    model->insertColumn(model->columnCount());          // Добавляем новую колонку для отображения имени компа
    model->setHeaderData(model->columnCount() - 1, Qt::Horizontal, QObject::tr("Name"), Qt::DisplayRole); // Имя новой колонки

    //####################//
//    InfoLin comp; //Объект класса compInfo
//    qDebug() << "Запущена Windows:" << comp.GetOsVersionNameQSysInfo(); //Инфа о версии ОС
//    qDebug() << "Имя компьютера:" << comp.GetComputerName_(); //Получить имя компа
//    qDebug() << "Имя пользователя:" << comp.GetUserName_(); //Получить имя пользователя
//    qDebug() << "Разрядность ОС:" << comp.GetOsBitWidth(); //Получить разрядность ОС

//    QSqlTableModel *mod = new QSqlTableModel(this, db);
//    mod->setTable("BasicInf");
//    mod->setEditStrategy(QSqlTableModel::OnManualSubmit);
//    mod->select();
//    mod->insertRow(0);

//    int row = 0;
//    int col = 2;
//    QVariant newValue = "new_value";
//    QModelIndex ind = mod->index(row, col);
//    if(!ind.isValid())
//        qDebug() << "Invalid index";

//    if(!mod->setData(ind, newValue))
//        qDebug() << "Failed to set data:" << mod->lastError().text();
//    ui->tableViewMainTab->setModel(mod);


    // //Процессор
    // qDebug() << "Имя процессора:" << comp.GetCPUName();
    // qDebug() << "Архитектура процессора:" << comp.GetCPUType();
    // qDebug() << "Частота процессора:" << comp.GetCPUFrequency();
    // qDebug() << "Кол-во ядер:" << comp.GetCPUNumberCore();

    // //Материнская плата
    // qDebug() << "Производитель материнской платы:" << comp.GetBoardManufacturer();
    // qDebug() << "Наименование материнской платы:" << comp.GetBoardName();

    // //ОЗУ
    // qDebug() << "Общее кол-во памяти ОЗУ:" << comp.GetMemorySize() << "МБ";

    // //qDebug() << system("wmic path win32_physicalmedia get SerialNumber"); //Серийник hdd
    // //getWmiQueryResult(L"SELECT SerialNumber FROM Win32_PhysicalMedia", L"SerialNumber");

    // //Видеокарта
    // qDebug() << "Модель видеокарты: " << comp.GetGPUName();
    // qDebug() << "Объём видеопамяти: " << comp.GetGPUMemSize() << "МБ";

    // //Дисковод
    // qDebug() << "Наличие дисковода: " << comp.GetCDROM();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Add_clicked()    // Обработка добавления новой строки в базу
{
    model->insertRow(model->rowCount());        // Создаём строку в конце таблицы.
}

void MainWindow::on_pushButton_Delete_clicked() { // Обработка удаления строки из базы
    // Узнаём ID текущей строки, чтобы удалить связанные с этой строкой строки других таблиц
    UINT ID = model->data(model->index(activeRow, model->fieldIndex("ID"))).toUInt(); // Узнаём ID выбранной строки
    // Подготавливаем модель
    QSqlTableModel cleansingModel(this, MainWindow::db);    // Модель очистки таблиц
    cleansingModel.setEditStrategy(QSqlTableModel::OnManualSubmit); // // Стратегия редактирования при которой изменения сохр. в бд только при вызове submitAll()
    QString filterID = "ID = " + QString::number(ID);       // Собираем строку фильтра
    const int countTables = 4;
    QString allTables[countTables] = {"BasicInf", "Hardware", "repair", "movements"};
    for(int i = 0; i < countTables; ++i){                   // Проходим по всем таблицам
        cleansingModel.setTable(allTables[i]);              // Выбираем для очистки таблицу
        cleansingModel.setFilter(filterID);                 // Сортируем модель по ID
        cleansingModel.select();                            // Выполняем запрос
        cleansingModel.removeRows(0, cleansingModel.rowCount()); // Удаляем строки
        if(!cleansingModel.submitAll()) {                   // Применяем изменения к БД
            qDebug() << "Ошибка удаления иформации из таблицы " << allTables[i] << " c ID = " << ID;
        }
        cleansingModel.clear();                             // Очищаем модель
    }
    // Удаляем строку из основной таблицы MainTab
    model->removeRow(activeRow);                            // Удаляем текущую активную строку
    model->select();                                        // Обновляем таблицу
}

void MainWindow::on_tableViewMainTab_clicked(const QModelIndex &index) //Обработка активной строки
{
    activeRow = index.row(); //При нажатии на строку происходит обновление активной строки.
}

void MainWindow::on_tableViewMainTab_doubleClicked(const QModelIndex &index) // Обработка двойного нажатия (Открываем новую вкладку с существующим компом)
{
    QModelIndex newIndex = index.sibling(index.row(), 0);               // Новый индекс указывает на ту же строку но колонка указывает на ID
    UINT ID = model->data(newIndex).toUInt();                           // Считываем значение ID  в этой строке
    computerData *myNewTab1 = new computerData(ui->tabWidget_Main, ID); // Создаём экземпляр класса вкладки. (Передаём ID по которому будем искать информацию и предка)
    // Подключаем сигнал окна computerData к слоту обновления таблиц в MainWindow
    connect(myNewTab1, &computerData::sendUpdateSignal, this, &MainWindow::upDateTable);
    ui->tabWidget_Main->addTab(myNewTab1,"Имя новой вкладки");          // Добавляем новую вкладку в виджет вкладок tabWidget_Main
    ui->tabWidget_Main->setCurrentWidget(myNewTab1);                    // Автоматически открывается новая вкладка.
    // Устанавливаем имя вкладки (Либо так, либо сделать ui public)
    QSqlQuery localQuery(MainWindow::db);
    localQuery.prepare("SELECT ComputerName FROM BasicInf WHERE ID = :id ORDER BY id DESC LIMIT 1"); // Выборка по ID задом наперёд с лимитом в 1 строку
    localQuery.bindValue(":id", ID);                                    // Вставляем в запрос нужную нам строку
    if(!localQuery.exec())                                              // Запрашиваем
        return;
    if(localQuery.next())                                               // Если есть результат запроса
        ui->tabWidget_Main->setTabText(ui->tabWidget_Main->count() - 1, localQuery.value("ComputerName").toString());
    localQuery.clear();
}

void MainWindow::on_pushButton_Create_clicked() //Создание новой вкладки с информацией о новом компьютере
{
    computerData *myNewTab1 = new computerData(ui->tabWidget_Main);     // Создаём экземпляр класса вкладки, указываем предка.
    // Подключаем сигнал окна computerData к слоту обновления таблиц в MainWindow
    connect(myNewTab1, &computerData::sendUpdateSignal, this, &MainWindow::upDateTable);
    ui->tabWidget_Main->addTab(myNewTab1,"Новая вкладка");              // Добавляем новую вкладку в виджет вкладок tabWidget_Main
    ui->tabWidget_Main->setCurrentWidget(myNewTab1);                    // Автоматически открывается новая вкладка.
}

void MainWindow::upDateTable(QString tabName) { // Слот для обновления основной таблицы tableViewMainTab
    model->select(); // Обновляем данные из БД и аввтоматически обновляет отображение в QTableView
    ui->tabWidget_Main->setTabText(ui->tabWidget_Main->currentIndex(), tabName); // Обновляем надпись бара вкладки
}

void MainWindow::on_tabWidget_Main_tabCloseRequested(int index) { // Закрытие вкладки на крестик в баре вкладки
    if(index)                                                           // Если вкладка не первая (домашняя)
        ui->tabWidget_Main->removeTab(index);                           // То удаляем её
}

bool MainWindow::creationTablesDB() { // Создание таблиц для работы с БД
//    query->prepare("DROP TABLE BasicInf;");
//    query->exec();
//    query->clear();
//    query->prepare("DROP TABLE Hardware;");
//    query->exec();
//    query->clear();
//    query->prepare("DROP TABLE Repair;");
//    query->exec();
//    query->clear();
//    query->prepare("DROP TABLE Movements;");
//    query->exec();
//    query->clear();
    // Подготовкак запроса создания таблицы MainTab
    query->prepare("CREATE TABLE IF NOT EXISTS MainTab ("
                   "ID INT PRIMARY KEY,"
                   "LastChange DATETIME,"
                   "YearOfRelease YEAR,"
                   "SerialNumber VARCHAR(50),"
                   "Warranty VARCHAR(50))"
                   "CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;"); // Для отображения русских букв
    if(!query->exec()) { // Запрашиваем
        qDebug() << "Не удалось создать таблицу: MainTab";
        return false;
    }
    query->clear();
    // Подготовка запроса создания таблицы BasicInf
    query->prepare("CREATE TABLE IF NOT EXISTS BasicInf("
                   "ID INT,"
                   "LastChange DATETIME,"
                   "ComputerName VARCHAR(100),"
                   "OS VARCHAR(100),"
                   "bitWidth VARCHAR(3),"
                   "NumberOIT VARCHAR(7),"
                   "Department VARCHAR(100),"
                   "User VARCHAR(100),"
                   "Antivirus VARCHAR(100),"
                   "Status VARCHAR(30),"
                   "BiosPassword VARCHAR(30),"
                   "Comments TEXT)"
                   "CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;"); // Для отображения русских букв
    if(!query->exec()) { // Запрашиваем
        qDebug() << "Не удалось создать таблицу: BasicInf";
        return false;
    }
    query->clear();
    // Подготовка запроса создания таблицы Hardware
    query->prepare("CREATE TABLE IF NOT EXISTS Hardware("
                   "ID INT,"
                   "LastChange DATETIME,"
                   "CPU VARCHAR(100),"
                   "CPUManufacturer VARCHAR(100),"
                   "CPUFrequency INT,"
                   "NumberCPUCores INT,"
                   "Motherboard VARCHAR(100),"
                   "MotherboardManufacturer VARCHAR(100),"
                   "Videocard TEXT,"
                   "videoMemory INT,"
                   "TypeVideoAdapter VARCHAR(50),"
                   "RAM TEXT,"
                   "RAMCapacity INT,"
                   "typeDDR VARCHAR(50),"
                   "TotalRAMSlots INT,"
                   "CurrentRAMSlots INT,"
                   "HDDSDD TEXT,"
                   "ROMcapacity INT,"
                   "NumberOfPhysicalDisks INT,"
                   "Monitor TEXT,"
                   "PrinterScaner TEXT,"
                   "diskDrive VARCHAR(4),"
                   "PowerSupply TEXT)"
                   "CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;"); // Для отображения русских букв
    if(!query->exec()) { // Запрашиваем
        qDebug() << "Не удалось создать таблицу: Hardware";
        return false;
    }
    query->clear();
    // Подготовка запроса создания таблицы Repair
    query->prepare("CREATE TABLE IF NOT EXISTS Repair("
                   "ID INT,"
                   "LastChange DATETIME,"
                   "RepairDate DATETIME,"
                   "RepairDescription TEXT,"
                   "Specialist VARCHAR(100))"
                   "CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;"); // Для отображения русских букв
    if(!query->exec()) { // Запрашиваем
        qDebug() << "Не удалось создать таблицу: Repair";
        return false;
    }
    query->clear();
    // Подготовка запроса создания таблицы Movements
    query->prepare("CREATE TABLE IF NOT EXISTS Movements("
                   "ID INT,"
                   "LastChange DATETIME,"
                   "MovementDate DATETIME,"
                   "OldOwner VARCHAR(100),"
                   "NewOwner VARCHAR(100),"
                   "OldDepartment VARCHAR(100),"
                   "NewDepartment VARCHAR(100),"
                   "Notes TEXT)"
                   "CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;"); // Для отображения русских букв
    if(!query->exec()) { // Запрашиваем
        qDebug() << "Не удалось создать таблицу: Movements";
        return false;
    }
    query->clear();
    return true;
}

