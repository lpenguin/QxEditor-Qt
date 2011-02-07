/****************************************************************************
** Meta object code from reading C++ file 'GraphView.h'
**
** Created: Tue 1. Feb 20:18:46 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/GraphView.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GraphView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GraphView[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      13,   11,   10,   10, 0x05,
      50,   11,   10,   10, 0x05,
      89,   11,   10,   10, 0x05,
     126,   11,   10,   10, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_GraphView[] = {
    "GraphView\0\0,\0VerClicked(VerItem*,Qt::MouseButton)\0"
    "EdgeClicked(EdgeItem*,Qt::MouseButton)\0"
    "AreaClicked(QPointF,Qt::MouseButton)\0"
    "VersConnected(VerItem*,VerItem*)\0"
};

const QMetaObject GraphView::staticMetaObject = {
    { &QGraphicsView::staticMetaObject, qt_meta_stringdata_GraphView,
      qt_meta_data_GraphView, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GraphView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GraphView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GraphView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GraphView))
        return static_cast<void*>(const_cast< GraphView*>(this));
    return QGraphicsView::qt_metacast(_clname);
}

int GraphView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void GraphView::VerClicked(VerItem * _t1, Qt::MouseButton _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GraphView::EdgeClicked(EdgeItem * _t1, Qt::MouseButton _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void GraphView::AreaClicked(QPointF _t1, Qt::MouseButton _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void GraphView::VersConnected(VerItem * _t1, VerItem * _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
