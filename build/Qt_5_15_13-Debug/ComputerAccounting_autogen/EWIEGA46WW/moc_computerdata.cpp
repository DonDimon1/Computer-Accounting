/****************************************************************************
** Meta object code from reading C++ file 'computerdata.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.13)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../computerdata.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'computerdata.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.13. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_computerData_t {
    QByteArrayData data[10];
    char stringdata0[174];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_computerData_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_computerData_t qt_meta_stringdata_computerData = {
    {
QT_MOC_LITERAL(0, 0, 12), // "computerData"
QT_MOC_LITERAL(1, 13, 16), // "sendUpdateSignal"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 7), // "tabName"
QT_MOC_LITERAL(4, 39, 26), // "on_pushButton_Save_clicked"
QT_MOC_LITERAL(5, 66, 33), // "on_pushButton_SaveAndExit_cli..."
QT_MOC_LITERAL(6, 100, 29), // "on_pushButton_Refresh_clicked"
QT_MOC_LITERAL(7, 130, 29), // "on_CustomContextMenuRequested"
QT_MOC_LITERAL(8, 160, 3), // "pos"
QT_MOC_LITERAL(9, 164, 9) // "insertRow"

    },
    "computerData\0sendUpdateSignal\0\0tabName\0"
    "on_pushButton_Save_clicked\0"
    "on_pushButton_SaveAndExit_clicked\0"
    "on_pushButton_Refresh_clicked\0"
    "on_CustomContextMenuRequested\0pos\0"
    "insertRow"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_computerData[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,
       1,    0,   52,    2, 0x26 /* Public | MethodCloned */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   53,    2, 0x08 /* Private */,
       5,    0,   54,    2, 0x08 /* Private */,
       6,    0,   55,    2, 0x08 /* Private */,
       7,    1,   56,    2, 0x08 /* Private */,
       9,    0,   59,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,    8,
    QMetaType::Void,

       0        // eod
};

void computerData::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<computerData *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->sendUpdateSignal((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->sendUpdateSignal(); break;
        case 2: _t->on_pushButton_Save_clicked(); break;
        case 3: _t->on_pushButton_SaveAndExit_clicked(); break;
        case 4: _t->on_pushButton_Refresh_clicked(); break;
        case 5: _t->on_CustomContextMenuRequested((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 6: _t->insertRow(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (computerData::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&computerData::sendUpdateSignal)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject computerData::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_computerData.data,
    qt_meta_data_computerData,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *computerData::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *computerData::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_computerData.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int computerData::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void computerData::sendUpdateSignal(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
