//https://stackoverflow.com/questions/25127302/how-to-add-tabs-dynamically-in-a-qt
#include "computerdata.h"
#include "ui_computerdata.h"

class computerData::MySqlTableModel : public QSqlTableModel { // Для запрета редактирования колонки с датой нужно переопределить класс QSqlTableModel
public:
    MySqlTableModel(QObject *parent = nullptr, QSqlDatabase db = QSqlDatabase()) :
        QSqlTableModel(parent, db) {}

    Qt::ItemFlags flags(const QModelIndex &index) const override { // Переопределяем условие редактирования
        Qt::ItemFlags flags = QSqlTableModel::flags(index);
        QString columnName = headerData(index.column(), Qt::Horizontal).toString(); // Узнаём название текущей колонки
        // Проверяем, является ли текущая колонка "lastchange"
        if (columnName == "Дата заполнения карточки") // Замените "yourColumnNameIndex" на соответствующую функцию, которая возвращает индекс колонки по ее названию
        {
            //flags &= ~Qt::ItemIsEditable;ItemIsEnabled
            flags &= ~Qt::ItemIsEnabled;
        }
        return flags;
    }
};

computerData::computerData(QWidget *parent, UINT ID) : // Конструктор открытия уже существующего комьютера
    QWidget(parent),
    ui(new Ui::computerData)
{
    ui->setupUi(this);
    // Создаём модели
    basicInfModel = new MySqlTableModel(this, MainWindow::db); // Подключение к БД
    basicInfModel->setTable("basicInf"); // Устанавливает таблицу базы данных, с которой работает модель.
    basicInfModel->setEditStrategy(QSqlTableModel::OnManualSubmit); // Стратегия редактирования при которой изменения сохр. в бд только при вызове submitAll()

    hardware = new MySqlTableModel(this, MainWindow::db);
    hardware->setTable("hardware");
    hardware->setEditStrategy(QSqlTableModel::OnManualSubmit);

    repair = new MySqlTableModel(this, MainWindow::db);
    repair->setTable("repair");
    repair->setEditStrategy(QSqlTableModel::OnManualSubmit);

    movements = new MySqlTableModel(this, MainWindow::db);
    movements->setTable("movements");
    movements->setEditStrategy(QSqlTableModel::OnManualSubmit);

    computerData::modelsHeaders();// Создаём моделям заголовки
    //connect(ui->pushButton_Save, &QPushButton::clicked, this, &computerData::sendUpdateSignal); // Конект для обновления mainWindow (Автоматически на нажатие сохранить)
    //connect(this, &computerData::sendUpdateSignal, &MainWindow::upDateTable; // Конект для обновления mainWindow
    computerData::ID = ID; // Если ID == 0 то, компа нет в базе, иначе есть
    if(computerData::ID){ // Если мы открываем уже существующий в базе компьютер
        computerData::existingPC(); // Вызов функции помощника конструктора для существующего в базе компьютера
    } else{ // Если мы открываем ещё НЕ существующий в базе компьютер
        computerData::defunctPC(); // Вызов функции помощника конструктора для НЕсуществующего в базе компьютера
    }
}

void computerData::existingPC() { // Функция помощника конструктора для существующего в базе компьютера
    // Здесь мы достаём информацию из БД о существующем компе используюя индекс в таблице.
    QSqlQuery *query = new QSqlQuery(MainWindow::db);             // Инициализация запроса
    // Запрос в таблицу MainTab
    query->prepare("SELECT * FROM MainTab WHERE ID = :ID"); // Подготавливаем запрос
    query->bindValue(":ID", ID); // Вставляем в запрос нужную нам строку
    if(!query->exec()) { // Запрашиваем
        qDebug() << "Не удалось подключиться к таблице: MainTab";
        return;
    }
    if(query->next()){ // Обрабатываем результат запроса и присваиваем полям значения
        ui->label_ThisID->setText(query->value("ID").toString()); // Присваиваем полю label_ID на форме computerdata значение ID
        ui->dateTimeEdit_LastChange->setDateTime(query->value("LastChange").toDateTime());
        ui->dateEdit_YearOfRelease->setDate(QDate(query->value("YearOfRelease").toInt(),1,1));
        ui->lineEdit_SerialNumber->setText(query->value("SerialNumber").toString());
        ui->lineEdit_Warranty->setText(query->value("Warranty").toString());
    }
    query->clear(); // Очищаем запрос

    // Считываем таблицу basicInf
    QString filterID = "ID = " + QString::number(ID); // Собираем строку фильтра
    basicInfModel->setFilter(filterID); // Сортируем модель по ID
    basicInfModel->select(); // Заполняет модель данными из таблицы, которая была задана через setTable()
    ui->tableViewBottom_1->setModel(basicInfModel); // Устанавливаем модель
    ui->tableViewBottom_1->setColumnHidden(basicInfModel->fieldIndex("ID"), true); // Скрываем колонку с ID

    // Считываем таблицу hardware
    hardware->setFilter(filterID);
    hardware->select();
    ui->tableViewBottom_2->setModel(hardware);
    ui->tableViewBottom_2->setColumnHidden(hardware->fieldIndex("ID"), true);

    // Считываем таблицу repair
    repair->setFilter(filterID);
    repair->select();
    ui->tableViewBottom_3->setModel(repair);
    ui->tableViewBottom_3->setColumnHidden(repair->fieldIndex("ID"), true);

    // Считываем таблицу movements
    movements->setFilter(filterID);
    movements->select();
    ui->tableViewBottom_4->setModel(movements);
    ui->tableViewBottom_4->setColumnHidden(movements->fieldIndex("ID"), true);

    // Устанавливаем текущее имя компьютера
    ui->label_ThisName->setText(basicInfModel->data(basicInfModel->index(basicInfModel->rowCount() - 1, basicInfModel->fieldIndex("ComputerName"))).toString());
}

void computerData::defunctPC() { // Функция помощник конструктора для НЕ существующего в базе компьютера
    // Здесь мы добавляем первую информацию о компьютере в карточку компьютера. Пользователь может её изменять.
    compInfo comp; //Объект класса compInfo для определения всех характеристик компьютера
    // Определяем данные для таблицы Основная информация
    basicInfModel->setFilter("ID = 0"); // Сортируем модель по несуществующей строке
    basicInfModel->select(); // Заполняет модель данными из таблицы, которая была задана через setTable()
    // Установка стандартных значений
    basicInfModel->insertRow(0); // Вставить новую строку в конец таблицы
    basicInfModel->setData(basicInfModel->index(0, basicInfModel->fieldIndex("ComputerName")), comp.GetComputerName_()); // Получаем имя компьютера
    basicInfModel->setData(basicInfModel->index(0, basicInfModel->fieldIndex("OS")), comp.GetOsVersionName()); // Получаем ОС компьютера
    basicInfModel->setData(basicInfModel->index(0, basicInfModel->fieldIndex("bitWidth")), comp.GetOsBitWidth()); // Получаем разрядность ОС
    basicInfModel->setData(basicInfModel->index(0, basicInfModel->fieldIndex("User")), comp.GetUserName_()); // Получаем разрядность ОС

    ui->tableViewBottom_1->setModel(basicInfModel); // Устанавливаем модель
    ui->tableViewBottom_1->setColumnHidden(basicInfModel->fieldIndex("ID"), true); // Скрываем колонку с ID

    // Определяем данные для таблицы Железо и периферия
    hardware->setFilter("ID = 0"); // Сортируем модель по несуществующей строке
    hardware->select(); // Заполняет модель данными из таблицы, которая была задана через setTable()
    // Установка стандартных значений
    hardware->insertRow(0); // Вставить новую строку в конец таблицы
    hardware->setData(hardware->index(0, hardware->fieldIndex("CPU")), comp.GetCPUName()); // Получаем CPU
    hardware->setData(hardware->index(0, hardware->fieldIndex("CPUFrequency")), (int)comp.GetCPUFrequency()); // Получаем частоту CPU
    hardware->setData(hardware->index(0, hardware->fieldIndex("NumberCPUCores")), (int)comp.GetCPUNumberCore()); // Получаем кол-во ядер
    hardware->setData(hardware->index(0, hardware->fieldIndex("Motherboard")), comp.GetBoardName()); // Получаем Мат.Плату
    hardware->setData(hardware->index(0, hardware->fieldIndex("MotherboardManufacturer")), comp.GetBoardManufacturer()); // Получаем производителя Мат.Платы
    hardware->setData(hardware->index(0, hardware->fieldIndex("Videocard")), comp.GetGPUName()); // Получаем видеокарту
    hardware->setData(hardware->index(0, hardware->fieldIndex("videoMemory")), (int)comp.GetGPUMemSize()); // Получаем видеопамять
    QString RAMStr = ""; // Строка с параметрами ОЗУ
    QString typeDDRStr = ""; // Строка с типом ddr
    WORD numRAM = comp.vecMemory.size(); // Кол-во плашек памяти
    for(UINT i = 0; i < numRAM; ++i){ // Проходим по всем плашкам
        RAMStr += QString::number(i + 1) + ") " + comp.vecMemory[i].Manufacturer + " "; // Создаём строку вывода
        RAMStr += QString::number(comp.vecMemory[i].Size) + " Мб, ";
        if(!typeDDRStr.contains("DDR")) // Записываем тип DDR памяти
            typeDDRStr = comp.vecMemory[i].MemoryType;
    };
    hardware->setData(hardware->index(0, hardware->fieldIndex("RAM")), RAMStr); // Получаем ОЗУ
    hardware->setData(hardware->index(0, hardware->fieldIndex("RAMCapacity")), (int)comp.GetMemorySize()); // Получаем общее количество ОЗУ
    hardware->setData(hardware->index(0, hardware->fieldIndex("typeDDR")), typeDDRStr); // Получаем тип DDR
    hardware->setData(hardware->index(0, hardware->fieldIndex("TotalRAMSlots")), (int)comp.TotalRAMSlots); // Получаем Общее кол-во слотов
    hardware->setData(hardware->index(0, hardware->fieldIndex("CurrentRAMSlots")), (int)numRAM); // Получаем Общее кол-во слотов
    QString driveStr = ""; // Строка с дисками
    WORD numDrive = comp.vecDrive.size(); // Кол-во дисков
    WORD totalCapacityDrive = 0; // Общий объём всех дисков
    for (UINT i = 0; i < numDrive; ++i) { // Проходим по всем дискам
        driveStr += QString::number(i + 1) + ") " + comp.vecDrive[i].Name + " "; // Создаём строку вывода
        driveStr += QString::number(comp.vecDrive[i].Size) + " Гб, ";
        totalCapacityDrive += comp.vecDrive[i].Size;                        // Общий объём всех дисков
    }
    hardware->setData(hardware->index(0, hardware->fieldIndex("HDDSDD")), driveStr); // Получаем HDD & SSD
    hardware->setData(hardware->index(0, hardware->fieldIndex("ROMcapacity")), (int)totalCapacityDrive); // Получаем общий объём дисков QString::number(totalCapacityDrive) + " Гб"
    hardware->setData(hardware->index(0, hardware->fieldIndex("NumberOfPhysicalDisks")), (int)numDrive); // Получаем кол-во дисков
    QString cdROM = "Нет"; // Строка CDROM
    if(comp.GetCDROM())
        cdROM = "Есть"; // Обработка наличия CDROM
    hardware->setData(hardware->index(0, hardware->fieldIndex("diskDrive")), cdROM); // Получить наличие дисковода cdROM.toLatin1()

    ui->tableViewBottom_2->setModel(hardware); // Устанавливаем второй таблице модель Hardware
    ui->tableViewBottom_2->setColumnHidden(hardware->fieldIndex("ID"), true); // Скрываем колонку с ID

    // Определяем данные для таблицы Ремонт и обслуживание
    repair->setFilter("ID = 0"); // Сортируем модель по несуществующей строке
    repair->select(); // Заполняет модель данными из таблицы, которая была задана через setTable()
    repair->insertRow(0); // Вставить новую строку в конец таблицы

    ui->tableViewBottom_3->setModel(repair); // Устанавливаем 3ей таблице модель repair
    ui->tableViewBottom_3->setColumnHidden(repair->fieldIndex("ID"), true); // Скрываем колонку с ID

    // Определяем данные для таблицы Перемещения
    movements->setFilter("ID = 0"); // Сортируем модель по несуществующей строке
    movements->select(); // Заполняет модель данными из таблицы, которая была задана через setTable()
    movements->insertRow(0); // Вставить новую строку в конец таблицы

    ui->tableViewBottom_4->setModel(movements); // Устанавливаем 4ой таблице модель movements
    ui->tableViewBottom_4->setColumnHidden(movements->fieldIndex("ID"), true); // Скрываем колонку с ID
}

computerData::~computerData() // Деструктор
{
    delete ui;
}

void computerData::on_pushButton_Save_clicked() // Сохраняем данные в БД
{
    QSqlQuery *query = new QSqlQuery(MainWindow::db); // Инициализация запроса сохранения в БД
    // Таблица MainTab
    if(computerData::ID){ // Если компьютер уже существует
        query->prepare("UPDATE MainTab SET LastChange = CURRENT_TIMESTAMP, YearOfRelease = :YearOfRelease, SerialNumber = :SerialNumber,"
                       "Warranty = :Warranty WHERE ID = :ID"); // Подготавливаем запрос
        query->bindValue(":ID", computerData::ID); // Заполняем значение поля ID
    }
    else { // Если компьютер новый
        computerData::ID = ++MainWindow::computerCount; // Присваиваем новому компьютеру ID
        query->prepare("INSERT INTO MainTab (ID, LastChange, YearOfRelease, SerialNumber, Warranty ) "
                       "VALUES(:ID, CURRENT_TIMESTAMP, :YearOfRelease, :SerialNumber, :Warranty)"); // Подготавливаем запрос
        query->bindValue(":ID", computerData::ID); // Заполняем значение поля ID
        ui->label_ThisID->setText(QString::number(computerData::ID)); // Показываем новый ID на форме
    }

    query->bindValue(":YearOfRelease", ui->dateEdit_YearOfRelease->text());
    query->bindValue(":SerialNumber", ui->lineEdit_SerialNumber->text());
    query->bindValue(":Warranty", ui->lineEdit_Warranty->text());
    if(!query->exec()) { // Запрашиваем
        qDebug() << "При сохранении данных формы не удалось подключиться к таблице: MainTab";
        return;
    }
    query->clear(); // Очищаем запрос

    // Сохраняем информацию в таблице basicInf(basicInfModel->rowCount())
    basicInfModel->setData(basicInfModel->index(basicInfModel->rowCount() - 1, basicInfModel->fieldIndex("ID")), computerData::ID); // Сохраняем ID
    basicInfModel->setData(basicInfModel->index(basicInfModel->rowCount() - 1, basicInfModel->fieldIndex("LastChange")), QDateTime::currentDateTime()); // Дата последнего изменения таблицы basicInf
    basicInfModel->submitAll(); // Сохраняем изменения в basicInf
    QString filterID = "ID = " + QString::number(computerData::ID); // Собираем строку фильтра
    basicInfModel->setFilter(filterID); // Сортируем модель по новому ID

    // Сохраняем информацию в таблице hardware
    hardware->setData(hardware->index(hardware->rowCount() - 1, hardware->fieldIndex("ID")), computerData::ID);
    hardware->setData(hardware->index(hardware->rowCount() - 1, hardware->fieldIndex("LastChange")), QDateTime::currentDateTime());
    hardware->submitAll();
    hardware->setFilter(filterID);

    // Сохраняем информацию в таблице repair
    repair->setData(repair->index(repair->rowCount() - 1, repair->fieldIndex("ID")), computerData::ID);
    repair->setData(repair->index(repair->rowCount() - 1, repair->fieldIndex("LastChange")), QDateTime::currentDateTime());
    repair->submitAll();
    repair->setFilter(filterID);

    // Сохраняем информацию в таблице movements
    movements->setData(movements->index(movements->rowCount() - 1, movements->fieldIndex("ID")), computerData::ID);
    movements->setData(movements->index(movements->rowCount() - 1, movements->fieldIndex("LastChange")), QDateTime::currentDateTime());
    movements->submitAll();
    movements->setFilter(filterID);

    // Действия не касающиеся БД (Если будут много вынесу в отдельную функцию)
    // Устанавливаем текущее имя компьютера
    ui->label_ThisName->setText(basicInfModel->data(basicInfModel->index(basicInfModel->rowCount() - 1, basicInfModel->fieldIndex("ComputerName"))).toString());
    this->sendUpdateSignal(ui->label_ThisName->text());
}

void computerData::modelsHeaders() { // Функция для задания заголовков моделям
    // Установка заголовков таблицы basicInf
    basicInfModel->setHeaderData(basicInfModel->fieldIndex("LastChange"), Qt::Horizontal, "Дата заполнения карточки"); // Меняем заголовки на русский
    basicInfModel->setHeaderData(basicInfModel->fieldIndex("ComputerName"), Qt::Horizontal, "Имя компьютера");
    basicInfModel->setHeaderData(basicInfModel->fieldIndex("OS"), Qt::Horizontal, "ОС");
    basicInfModel->setHeaderData(basicInfModel->fieldIndex("bitWidth"), Qt::Horizontal, "Разрядность ОС");
    basicInfModel->setHeaderData(basicInfModel->fieldIndex("NumberOIT"), Qt::Horizontal, "Номер ОИТ");
    basicInfModel->setHeaderData(basicInfModel->fieldIndex("Department"), Qt::Horizontal, "Отдел");
    basicInfModel->setHeaderData(basicInfModel->fieldIndex("User"), Qt::Horizontal, "Пользователь");
    basicInfModel->setHeaderData(basicInfModel->fieldIndex("Antivirus"), Qt::Horizontal, "Антивирус");
    basicInfModel->setHeaderData(basicInfModel->fieldIndex("Status"), Qt::Horizontal, "Статус эксплуатации");
    basicInfModel->setHeaderData(basicInfModel->fieldIndex("BiosPassword"), Qt::Horizontal, "Пароль БИОС");
    basicInfModel->setHeaderData(basicInfModel->fieldIndex("Comments"), Qt::Horizontal, "Доп. Коментарии");

    // Установка заголовков таблицы hardware
    hardware->setHeaderData(hardware->fieldIndex("LastChange"), Qt::Horizontal, "Дата заполнения карточки");
    hardware->setHeaderData(hardware->fieldIndex("CPU"), Qt::Horizontal, "CPU");
    hardware->setHeaderData(hardware->fieldIndex("CPUManufacturer"), Qt::Horizontal, "CPU Производитель");
    hardware->setHeaderData(hardware->fieldIndex("CPUFrequency"), Qt::Horizontal, "CPU Частота");
    hardware->setHeaderData(hardware->fieldIndex("NumberCPUCores"), Qt::Horizontal, "CPU Кол-во ядер");
    hardware->setHeaderData(hardware->fieldIndex("Motherboard"), Qt::Horizontal, "Мат.Плата");
    hardware->setHeaderData(hardware->fieldIndex("MotherboardManufacturer"), Qt::Horizontal, "Производитель Мат.Платы");
    hardware->setHeaderData(hardware->fieldIndex("Videocard"), Qt::Horizontal, "Видеокарта");
    hardware->setHeaderData(hardware->fieldIndex("videoMemory"), Qt::Horizontal, "Видеопамять");
    hardware->setHeaderData(hardware->fieldIndex("TypeVideoAdapter"), Qt::Horizontal, "Тип видеоадаптера");
    hardware->setHeaderData(hardware->fieldIndex("RAM"), Qt::Horizontal, "ОЗУ");
    hardware->setHeaderData(hardware->fieldIndex("RAMCapacity"), Qt::Horizontal, "ОЗУ Общее кол-во памяти");
    hardware->setHeaderData(hardware->fieldIndex("typeDDR"), Qt::Horizontal, "ОЗУ Тип DDR");
    hardware->setHeaderData(hardware->fieldIndex("TotalRAMSlots"), Qt::Horizontal, "ОЗУ Общее кол-во слотов");
    hardware->setHeaderData(hardware->fieldIndex("CurrentRAMSlots"), Qt::Horizontal, "ОЗУ Использовано слотов");
    hardware->setHeaderData(hardware->fieldIndex("HDDSDD"), Qt::Horizontal, "HDD & SSD");
    hardware->setHeaderData(hardware->fieldIndex("ROMcapacity"), Qt::Horizontal, "Общее объём памяти");
    hardware->setHeaderData(hardware->fieldIndex("NumberOfPhysicalDisks"), Qt::Horizontal, "Кол-во дисков");
    hardware->setHeaderData(hardware->fieldIndex("Monitor"), Qt::Horizontal, "Монитор");
    hardware->setHeaderData(hardware->fieldIndex("PrinterScaner"), Qt::Horizontal, "Принтер");
    hardware->setHeaderData(hardware->fieldIndex("diskDrive"), Qt::Horizontal, "Наличие дисковода");
    hardware->setHeaderData(hardware->fieldIndex("PowerSupply"), Qt::Horizontal, "Блок питания");

    // Установка заголовков таблицы repair
    repair->setHeaderData(repair->fieldIndex("LastChange"), Qt::Horizontal, "Дата заполнения карточки");
    repair->setHeaderData(repair->fieldIndex("RepairDate"), Qt::Horizontal, "Дата выполнения ремонта");
    repair->setHeaderData(repair->fieldIndex("RepairDescription"), Qt::Horizontal, "Описание ремонта");
    repair->setHeaderData(repair->fieldIndex("Specialist"), Qt::Horizontal, "Специалист");

    // Установка заголовков таблицы movements
    movements->setHeaderData(movements->fieldIndex("LastChange"), Qt::Horizontal, "Дата заполнения карточки");
    movements->setHeaderData(movements->fieldIndex("MovementDate"), Qt::Horizontal, "Дата перемещения");
    movements->setHeaderData(movements->fieldIndex("OldOwner"), Qt::Horizontal, "Прошлый пользователь");
    movements->setHeaderData(movements->fieldIndex("NewOwner"), Qt::Horizontal, "Новый пользователь");
    movements->setHeaderData(movements->fieldIndex("OldDepartment"), Qt::Horizontal, "Прошлый отдел");
    movements->setHeaderData(movements->fieldIndex("NewDepartment"), Qt::Horizontal, "Новый отдел");
    movements->setHeaderData(movements->fieldIndex("Notes"), Qt::Horizontal, "Заметки");
};


