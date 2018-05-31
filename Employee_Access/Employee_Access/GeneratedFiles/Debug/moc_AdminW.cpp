/****************************************************************************
** Meta object code from reading C++ file 'AdminW.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../AdminW.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AdminW.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_AdminW_t {
    QByteArrayData data[7];
    char stringdata0[68];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AdminW_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AdminW_t qt_meta_stringdata_AdminW = {
    {
QT_MOC_LITERAL(0, 0, 6), // "AdminW"
QT_MOC_LITERAL(1, 7, 8), // "add_user"
QT_MOC_LITERAL(2, 16, 0), // ""
QT_MOC_LITERAL(3, 17, 11), // "delete_user"
QT_MOC_LITERAL(4, 29, 10), // "changeinfo"
QT_MOC_LITERAL(5, 40, 16), // "adm_return_login"
QT_MOC_LITERAL(6, 57, 10) // "open_manip"

    },
    "AdminW\0add_user\0\0delete_user\0changeinfo\0"
    "adm_return_login\0open_manip"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AdminW[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x08 /* Private */,
       3,    0,   40,    2, 0x08 /* Private */,
       4,    0,   41,    2, 0x08 /* Private */,
       5,    0,   42,    2, 0x08 /* Private */,
       6,    0,   43,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void AdminW::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AdminW *_t = static_cast<AdminW *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->add_user(); break;
        case 1: _t->delete_user(); break;
        case 2: _t->changeinfo(); break;
        case 3: _t->adm_return_login(); break;
        case 4: _t->open_manip(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject AdminW::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_AdminW.data,
      qt_meta_data_AdminW,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *AdminW::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AdminW::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_AdminW.stringdata0))
        return static_cast<void*>(const_cast< AdminW*>(this));
    return QWidget::qt_metacast(_clname);
}

int AdminW::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
