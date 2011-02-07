/****************************************************************************
** Meta object code from reading C++ file 'dialogimpl.h'
**
** Created: Fri Jan 14 13:58:47 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/dialogimpl.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dialogimpl.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DialogImpl[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,   12,   11,   11, 0x08,
      51,   12,   11,   11, 0x08,
      97,   90,   11,   11, 0x08,
     134,   12,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_DialogImpl[] = {
    "DialogImpl\0\0,\0VerClicked(VerItem*,Qt::MouseButton)\0"
    "EdgeClicked(EdgeItem*,Qt::MouseButton)\0"
    "point,\0AreaClicked(QPointF,Qt::MouseButton)\0"
    "VersConnected(VerItem*,VerItem*)\0"
};

const QMetaObject DialogImpl::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DialogImpl,
      qt_meta_data_DialogImpl, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DialogImpl::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DialogImpl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DialogImpl::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DialogImpl))
        return static_cast<void*>(const_cast< DialogImpl*>(this));
    if (!strcmp(_clname, "Ui::Dialog"))
        return static_cast< Ui::Dialog*>(const_cast< DialogImpl*>(this));
    return QDialog::qt_metacast(_clname);
}

int DialogImpl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: VerClicked((*reinterpret_cast< VerItem*(*)>(_a[1])),(*reinterpret_cast< Qt::MouseButton(*)>(_a[2]))); break;
        case 1: EdgeClicked((*reinterpret_cast< EdgeItem*(*)>(_a[1])),(*reinterpret_cast< Qt::MouseButton(*)>(_a[2]))); break;
        case 2: AreaClicked((*reinterpret_cast< QPointF(*)>(_a[1])),(*reinterpret_cast< Qt::MouseButton(*)>(_a[2]))); break;
        case 3: VersConnected((*reinterpret_cast< VerItem*(*)>(_a[1])),(*reinterpret_cast< VerItem*(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
