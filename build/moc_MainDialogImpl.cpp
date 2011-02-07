/****************************************************************************
** Meta object code from reading C++ file 'MainDialogImpl.h'
**
** Created: Tue 1. Feb 20:18:54 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/MainDialogImpl.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainDialogImpl.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainDialogImpl[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x08,
      42,   15,   15,   15, 0x08,
      68,   15,   15,   15, 0x08,
      97,   15,   15,   15, 0x08,
     127,   15,   15,   15, 0x08,
     156,   15,   15,   15, 0x08,
     166,   15,   15,   15, 0x08,
     173,   15,   15,   15, 0x08,
     180,   15,   15,   15, 0x08,
     189,   15,   15,   15, 0x08,
     206,   15,   15,   15, 0x08,
     216,  214,   15,   15, 0x08,
     253,  214,   15,   15, 0x08,
     299,  292,   15,   15, 0x08,
     336,  214,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainDialogImpl[] = {
    "MainDialogImpl\0\0on_actionOpen_triggered()\0"
    "on_actionSave_triggered()\0"
    "on_actionSave_as_triggered()\0"
    "on_actionSettings_triggered()\0"
    "on_actionActions_triggered()\0newFile()\0"
    "open()\0save()\0saveAs()\0openRecentFile()\0"
    "about()\0,\0VerClicked(VerItem*,Qt::MouseButton)\0"
    "EdgeClicked(EdgeItem*,Qt::MouseButton)\0"
    "point,\0AreaClicked(QPointF,Qt::MouseButton)\0"
    "VersConnected(VerItem*,VerItem*)\0"
};

const QMetaObject MainDialogImpl::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainDialogImpl,
      qt_meta_data_MainDialogImpl, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainDialogImpl::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainDialogImpl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainDialogImpl::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainDialogImpl))
        return static_cast<void*>(const_cast< MainDialogImpl*>(this));
    if (!strcmp(_clname, "Ui::MainDialog"))
        return static_cast< Ui::MainDialog*>(const_cast< MainDialogImpl*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainDialogImpl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_actionOpen_triggered(); break;
        case 1: on_actionSave_triggered(); break;
        case 2: on_actionSave_as_triggered(); break;
        case 3: on_actionSettings_triggered(); break;
        case 4: on_actionActions_triggered(); break;
        case 5: newFile(); break;
        case 6: open(); break;
        case 7: save(); break;
        case 8: saveAs(); break;
        case 9: openRecentFile(); break;
        case 10: about(); break;
        case 11: VerClicked((*reinterpret_cast< VerItem*(*)>(_a[1])),(*reinterpret_cast< Qt::MouseButton(*)>(_a[2]))); break;
        case 12: EdgeClicked((*reinterpret_cast< EdgeItem*(*)>(_a[1])),(*reinterpret_cast< Qt::MouseButton(*)>(_a[2]))); break;
        case 13: AreaClicked((*reinterpret_cast< QPointF(*)>(_a[1])),(*reinterpret_cast< Qt::MouseButton(*)>(_a[2]))); break;
        case 14: VersConnected((*reinterpret_cast< VerItem*(*)>(_a[1])),(*reinterpret_cast< VerItem*(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 15;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
