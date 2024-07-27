/********************************************************************************
** Form generated from reading UI file 'computerdata.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMPUTERDATA_H
#define UI_COMPUTERDATA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_computerData
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QFormLayout *formLayout;
    QLabel *label_ID;
    QLabel *label_ThisID;
    QLabel *label_LastChange;
    QDateTimeEdit *dateTimeEdit_LastChange;
    QLabel *label_Name;
    QLabel *label_ThisName;
    QLabel *label_YearOfRelease;
    QDateEdit *dateEdit_YearOfRelease;
    QLabel *label_SerialNumber;
    QLineEdit *lineEdit_SerialNumber;
    QLabel *label_Warranty;
    QLineEdit *lineEdit_Warranty;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_SaveAndExit;
    QPushButton *pushButton_Save;
    QPushButton *pushButton_Refresh;
    QSpacerItem *horizontalSpacer;
    QTabWidget *tabWidget_Bottom;
    QWidget *tab_1;
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

    void setupUi(QWidget *computerData)
    {
        if (computerData->objectName().isEmpty())
            computerData->setObjectName(QString::fromUtf8("computerData"));
        computerData->resize(1002, 632);
        verticalLayout = new QVBoxLayout(computerData);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label_ID = new QLabel(computerData);
        label_ID->setObjectName(QString::fromUtf8("label_ID"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_ID);

        label_ThisID = new QLabel(computerData);
        label_ThisID->setObjectName(QString::fromUtf8("label_ThisID"));

        formLayout->setWidget(1, QFormLayout::FieldRole, label_ThisID);

        label_LastChange = new QLabel(computerData);
        label_LastChange->setObjectName(QString::fromUtf8("label_LastChange"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_LastChange);

        dateTimeEdit_LastChange = new QDateTimeEdit(computerData);
        dateTimeEdit_LastChange->setObjectName(QString::fromUtf8("dateTimeEdit_LastChange"));
        dateTimeEdit_LastChange->setReadOnly(true);

        formLayout->setWidget(2, QFormLayout::FieldRole, dateTimeEdit_LastChange);

        label_Name = new QLabel(computerData);
        label_Name->setObjectName(QString::fromUtf8("label_Name"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_Name);

        label_ThisName = new QLabel(computerData);
        label_ThisName->setObjectName(QString::fromUtf8("label_ThisName"));

        formLayout->setWidget(3, QFormLayout::FieldRole, label_ThisName);

        label_YearOfRelease = new QLabel(computerData);
        label_YearOfRelease->setObjectName(QString::fromUtf8("label_YearOfRelease"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_YearOfRelease);

        dateEdit_YearOfRelease = new QDateEdit(computerData);
        dateEdit_YearOfRelease->setObjectName(QString::fromUtf8("dateEdit_YearOfRelease"));
        dateEdit_YearOfRelease->setCalendarPopup(false);

        formLayout->setWidget(4, QFormLayout::FieldRole, dateEdit_YearOfRelease);

        label_SerialNumber = new QLabel(computerData);
        label_SerialNumber->setObjectName(QString::fromUtf8("label_SerialNumber"));

        formLayout->setWidget(5, QFormLayout::LabelRole, label_SerialNumber);

        lineEdit_SerialNumber = new QLineEdit(computerData);
        lineEdit_SerialNumber->setObjectName(QString::fromUtf8("lineEdit_SerialNumber"));

        formLayout->setWidget(5, QFormLayout::FieldRole, lineEdit_SerialNumber);

        label_Warranty = new QLabel(computerData);
        label_Warranty->setObjectName(QString::fromUtf8("label_Warranty"));

        formLayout->setWidget(6, QFormLayout::LabelRole, label_Warranty);

        lineEdit_Warranty = new QLineEdit(computerData);
        lineEdit_Warranty->setObjectName(QString::fromUtf8("lineEdit_Warranty"));

        formLayout->setWidget(6, QFormLayout::FieldRole, lineEdit_Warranty);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        pushButton_SaveAndExit = new QPushButton(computerData);
        pushButton_SaveAndExit->setObjectName(QString::fromUtf8("pushButton_SaveAndExit"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_SaveAndExit->sizePolicy().hasHeightForWidth());
        pushButton_SaveAndExit->setSizePolicy(sizePolicy);
        pushButton_SaveAndExit->setMinimumSize(QSize(107, 23));

        horizontalLayout_2->addWidget(pushButton_SaveAndExit);

        pushButton_Save = new QPushButton(computerData);
        pushButton_Save->setObjectName(QString::fromUtf8("pushButton_Save"));
        pushButton_Save->setMaximumSize(QSize(107, 23));

        horizontalLayout_2->addWidget(pushButton_Save);


        formLayout->setLayout(0, QFormLayout::LabelRole, horizontalLayout_2);

        pushButton_Refresh = new QPushButton(computerData);
        pushButton_Refresh->setObjectName(QString::fromUtf8("pushButton_Refresh"));
        pushButton_Refresh->setMaximumSize(QSize(170, 16777215));

        formLayout->setWidget(0, QFormLayout::FieldRole, pushButton_Refresh);


        horizontalLayout->addLayout(formLayout);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        tabWidget_Bottom = new QTabWidget(computerData);
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
        tab_1 = new QWidget();
        tab_1->setObjectName(QString::fromUtf8("tab_1"));
        tab_1->setFont(font);
        verticalLayout_2 = new QVBoxLayout(tab_1);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        tableViewBottom_1 = new QTableView(tab_1);
        tableViewBottom_1->setObjectName(QString::fromUtf8("tableViewBottom_1"));

        verticalLayout_2->addWidget(tableViewBottom_1);

        tabWidget_Bottom->addTab(tab_1, QString());
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


        retranslateUi(computerData);

        tabWidget_Bottom->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(computerData);
    } // setupUi

    void retranslateUi(QWidget *computerData)
    {
        computerData->setWindowTitle(QCoreApplication::translate("computerData", "Form", nullptr));
        label_ID->setText(QCoreApplication::translate("computerData", "\320\243\320\275\320\270\320\272\320\260\320\273\321\214\320\275\321\213\320\271 \320\275\320\276\320\274\320\265\321\200 ID:", nullptr));
        label_ThisID->setText(QCoreApplication::translate("computerData", "TextLabel", nullptr));
        label_LastChange->setText(QCoreApplication::translate("computerData", "\320\224\320\260\321\202\320\260 \320\277\320\276\321\201\320\273\320\265\320\264\320\275\320\265\320\263\320\276 \320\270\320\267\320\274\320\265\320\275\320\265\320\275\320\270\321\217:", nullptr));
        label_Name->setText(QCoreApplication::translate("computerData", "\320\242\320\265\320\272\321\203\321\211\320\265\320\265 \320\270\320\274\321\217 \320\272\320\276\320\274\320\277\321\214\321\216\321\202\320\265\321\200\320\260:", nullptr));
        label_ThisName->setText(QCoreApplication::translate("computerData", "TextLabel", nullptr));
        label_YearOfRelease->setText(QCoreApplication::translate("computerData", "\320\223\320\276\320\264 \320\262\321\213\320\277\321\203\321\201\320\272\320\260:", nullptr));
        dateEdit_YearOfRelease->setDisplayFormat(QCoreApplication::translate("computerData", "yyyy", nullptr));
        label_SerialNumber->setText(QCoreApplication::translate("computerData", "\320\241\320\265\321\200\320\270\320\271\320\275\321\213\320\271 \320\275\320\276\320\274\320\265\321\200:", nullptr));
        label_Warranty->setText(QCoreApplication::translate("computerData", "\320\223\320\260\321\200\320\260\320\275\321\202\320\270\321\217:", nullptr));
        pushButton_SaveAndExit->setText(QCoreApplication::translate("computerData", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\270 \320\267\320\260\320\272\321\200\321\213\321\202\321\214", nullptr));
        pushButton_Save->setText(QCoreApplication::translate("computerData", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
        pushButton_Refresh->setText(QCoreApplication::translate("computerData", "\320\236\320\261\320\275\320\276\320\262\320\273\320\265\320\275\320\270\320\265 \321\205\320\260\321\200\320\260\320\272\321\202\320\265\321\200\320\270\321\201\321\202\320\270\320\272 \320\237\320\232", nullptr));
#if QT_CONFIG(tooltip)
        tabWidget_Bottom->setToolTip(QCoreApplication::translate("computerData", "<html><head/><body><p><br/></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        tab_1->setToolTip(QCoreApplication::translate("computerData", "<html><head/><body><p><br/></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        tabWidget_Bottom->setTabText(tabWidget_Bottom->indexOf(tab_1), QCoreApplication::translate("computerData", "\320\236\321\201\320\275\320\276\320\262\320\275\320\260\321\217 \320\270\320\275\321\204\320\276\321\200\320\274\320\260\321\206\320\270\321\217", nullptr));
        tabWidget_Bottom->setTabText(tabWidget_Bottom->indexOf(tab_2), QCoreApplication::translate("computerData", "\320\226\320\265\320\273\320\265\320\267\320\276 \320\270 \320\277\320\265\321\200\320\270\321\204\320\265\321\200\320\270\321\217", nullptr));
        tabWidget_Bottom->setTabText(tabWidget_Bottom->indexOf(tab_3), QCoreApplication::translate("computerData", "\320\240\320\265\320\274\320\276\320\275\321\202 \320\270 \320\276\320\261\321\201\320\273\321\203\320\266\320\270\320\262\320\260\320\275\320\270\320\265", nullptr));
        tabWidget_Bottom->setTabText(tabWidget_Bottom->indexOf(tab_4), QCoreApplication::translate("computerData", "\320\237\320\265\321\200\320\265\320\274\320\265\321\211\320\265\320\275\320\270\321\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class computerData: public Ui_computerData {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMPUTERDATA_H
