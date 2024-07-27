/********************************************************************************
** Form generated from reading UI file 'mainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_6;
    QTabWidget *tabWidget_Main;
    QWidget *tab_Home;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_Create;
    QPushButton *pushButton_Add;
    QPushButton *pushButton_Delete;
    QHBoxLayout *horizontalLayout_2;
    QTableView *tableViewMainTab;
    QTabWidget *tabWidget_Bottom;
    QWidget *tab;
    QVBoxLayout *verticalLayout_2;
    QTableView *tableViewBottom_1;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_3;
    QTableView *tableViewBottom_2;
    QWidget *tab_3;
    QVBoxLayout *verticalLayout_4;
    QTableView *tableViewBottom_3;
    QWidget *tab_4;
    QVBoxLayout *verticalLayout_5;
    QTableView *tableViewBottom_4;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1063, 629);
        MainWindow->setAutoFillBackground(false);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setEnabled(true);
        verticalLayout_6 = new QVBoxLayout(centralwidget);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        tabWidget_Main = new QTabWidget(centralwidget);
        tabWidget_Main->setObjectName(QString::fromUtf8("tabWidget_Main"));
        tabWidget_Main->setTabsClosable(true);
        tabWidget_Main->setMovable(true);
        tab_Home = new QWidget();
        tab_Home->setObjectName(QString::fromUtf8("tab_Home"));
        verticalLayout = new QVBoxLayout(tab_Home);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        pushButton_Create = new QPushButton(tab_Home);
        pushButton_Create->setObjectName(QString::fromUtf8("pushButton_Create"));
        pushButton_Create->setMaximumSize(QSize(100, 100));

        horizontalLayout_3->addWidget(pushButton_Create);

        pushButton_Add = new QPushButton(tab_Home);
        pushButton_Add->setObjectName(QString::fromUtf8("pushButton_Add"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_Add->sizePolicy().hasHeightForWidth());
        pushButton_Add->setSizePolicy(sizePolicy);
        pushButton_Add->setMaximumSize(QSize(100, 100));
        pushButton_Add->setLayoutDirection(Qt::LeftToRight);

        horizontalLayout_3->addWidget(pushButton_Add);

        pushButton_Delete = new QPushButton(tab_Home);
        pushButton_Delete->setObjectName(QString::fromUtf8("pushButton_Delete"));
        sizePolicy.setHeightForWidth(pushButton_Delete->sizePolicy().hasHeightForWidth());
        pushButton_Delete->setSizePolicy(sizePolicy);
        pushButton_Delete->setMaximumSize(QSize(100, 100));

        horizontalLayout_3->addWidget(pushButton_Delete);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        tableViewMainTab = new QTableView(tab_Home);
        tableViewMainTab->setObjectName(QString::fromUtf8("tableViewMainTab"));
        tableViewMainTab->setEnabled(true);
        tableViewMainTab->setSortingEnabled(true);

        horizontalLayout_2->addWidget(tableViewMainTab);


        verticalLayout->addLayout(horizontalLayout_2);

        tabWidget_Bottom = new QTabWidget(tab_Home);
        tabWidget_Bottom->setObjectName(QString::fromUtf8("tabWidget_Bottom"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tabWidget_Bottom->sizePolicy().hasHeightForWidth());
        tabWidget_Bottom->setSizePolicy(sizePolicy1);
        tabWidget_Bottom->setMinimumSize(QSize(0, 100));
        QFont font;
        font.setPointSize(8);
        font.setBold(false);
        font.setUnderline(false);
        font.setWeight(50);
        tabWidget_Bottom->setFont(font);
        tabWidget_Bottom->setTabletTracking(false);
        tabWidget_Bottom->setContextMenuPolicy(Qt::DefaultContextMenu);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        tab->setFont(font);
        verticalLayout_2 = new QVBoxLayout(tab);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        tableViewBottom_1 = new QTableView(tab);
        tableViewBottom_1->setObjectName(QString::fromUtf8("tableViewBottom_1"));

        verticalLayout_2->addWidget(tableViewBottom_1);

        tabWidget_Bottom->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        verticalLayout_3 = new QVBoxLayout(tab_2);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        tableViewBottom_2 = new QTableView(tab_2);
        tableViewBottom_2->setObjectName(QString::fromUtf8("tableViewBottom_2"));

        verticalLayout_3->addWidget(tableViewBottom_2);

        tabWidget_Bottom->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        verticalLayout_4 = new QVBoxLayout(tab_3);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        tableViewBottom_3 = new QTableView(tab_3);
        tableViewBottom_3->setObjectName(QString::fromUtf8("tableViewBottom_3"));

        verticalLayout_4->addWidget(tableViewBottom_3);

        tabWidget_Bottom->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        verticalLayout_5 = new QVBoxLayout(tab_4);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        tableViewBottom_4 = new QTableView(tab_4);
        tableViewBottom_4->setObjectName(QString::fromUtf8("tableViewBottom_4"));

        verticalLayout_5->addWidget(tableViewBottom_4);

        tabWidget_Bottom->addTab(tab_4, QString());

        verticalLayout->addWidget(tabWidget_Bottom);

        tabWidget_Main->addTab(tab_Home, QString());

        verticalLayout_6->addWidget(tabWidget_Main);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1063, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget_Main->setCurrentIndex(0);
        tabWidget_Bottom->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton_Create->setText(QCoreApplication::translate("MainWindow", "Create", nullptr));
        pushButton_Add->setText(QCoreApplication::translate("MainWindow", "Add", nullptr));
        pushButton_Delete->setText(QCoreApplication::translate("MainWindow", "Delete", nullptr));
#if QT_CONFIG(tooltip)
        tabWidget_Bottom->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p><br/></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        tab->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p><br/></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        tabWidget_Bottom->setTabText(tabWidget_Bottom->indexOf(tab), QCoreApplication::translate("MainWindow", "\320\236\321\201\320\275\320\276\320\262\320\275\320\260\321\217 \320\270\320\275\321\204\320\276\321\200\320\274\320\260\321\206\320\270\321\217", nullptr));
        tabWidget_Bottom->setTabText(tabWidget_Bottom->indexOf(tab_2), QCoreApplication::translate("MainWindow", "\320\226\320\265\320\273\320\265\320\267\320\276 \320\270 \320\277\320\265\321\200\320\270\321\204\320\265\321\200\320\270\321\217", nullptr));
        tabWidget_Bottom->setTabText(tabWidget_Bottom->indexOf(tab_3), QCoreApplication::translate("MainWindow", "\320\240\320\265\320\274\320\276\320\275\321\202 \320\270 \320\276\320\261\321\201\320\273\321\203\320\266\320\270\320\262\320\260\320\275\320\270\320\265", nullptr));
        tabWidget_Bottom->setTabText(tabWidget_Bottom->indexOf(tab_4), QCoreApplication::translate("MainWindow", "\320\237\320\265\321\200\320\265\320\274\320\265\321\211\320\265\320\275\320\270\321\217", nullptr));
        tabWidget_Main->setTabText(tabWidget_Main->indexOf(tab_Home), QCoreApplication::translate("MainWindow", "\320\235\320\260\321\207\320\260\320\273\321\214\320\275\320\260\321\217 \321\201\321\202\321\200\320\260\320\275\320\270\321\206\320\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
