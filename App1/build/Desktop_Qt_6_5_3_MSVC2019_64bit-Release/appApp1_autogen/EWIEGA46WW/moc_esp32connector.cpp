/****************************************************************************
** Meta object code from reading C++ file 'esp32connector.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../esp32connector.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'esp32connector.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSconnectorENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSconnectorENDCLASS = QtMocHelpers::stringData(
    "connector",
    "initializeSocket",
    "",
    "connectToRoom",
    "tryToConnect",
    "writeDataToRoom",
    "data",
    "readDataFromRoom",
    "sendCmd",
    "cmd",
    "handleResponseFromRoom",
    "rep",
    "heartBeat"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSconnectorENDCLASS_t {
    uint offsetsAndSizes[26];
    char stringdata0[10];
    char stringdata1[17];
    char stringdata2[1];
    char stringdata3[14];
    char stringdata4[13];
    char stringdata5[16];
    char stringdata6[5];
    char stringdata7[17];
    char stringdata8[8];
    char stringdata9[4];
    char stringdata10[23];
    char stringdata11[4];
    char stringdata12[10];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSconnectorENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSconnectorENDCLASS_t qt_meta_stringdata_CLASSconnectorENDCLASS = {
    {
        QT_MOC_LITERAL(0, 9),  // "connector"
        QT_MOC_LITERAL(10, 16),  // "initializeSocket"
        QT_MOC_LITERAL(27, 0),  // ""
        QT_MOC_LITERAL(28, 13),  // "connectToRoom"
        QT_MOC_LITERAL(42, 12),  // "tryToConnect"
        QT_MOC_LITERAL(55, 15),  // "writeDataToRoom"
        QT_MOC_LITERAL(71, 4),  // "data"
        QT_MOC_LITERAL(76, 16),  // "readDataFromRoom"
        QT_MOC_LITERAL(93, 7),  // "sendCmd"
        QT_MOC_LITERAL(101, 3),  // "cmd"
        QT_MOC_LITERAL(105, 22),  // "handleResponseFromRoom"
        QT_MOC_LITERAL(128, 3),  // "rep"
        QT_MOC_LITERAL(132, 9)   // "heartBeat"
    },
    "connector",
    "initializeSocket",
    "",
    "connectToRoom",
    "tryToConnect",
    "writeDataToRoom",
    "data",
    "readDataFromRoom",
    "sendCmd",
    "cmd",
    "handleResponseFromRoom",
    "rep",
    "heartBeat"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSconnectorENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   62,    2, 0x0a,    1 /* Public */,
       3,    0,   63,    2, 0x0a,    2 /* Public */,
       4,    0,   64,    2, 0x0a,    3 /* Public */,
       5,    1,   65,    2, 0x0a,    4 /* Public */,
       7,    0,   68,    2, 0x0a,    6 /* Public */,
       8,    1,   69,    2, 0x0a,    7 /* Public */,
      10,    1,   72,    2, 0x0a,    9 /* Public */,
      12,    0,   75,    2, 0x0a,   11 /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Bool, QMetaType::QString,    6,
    QMetaType::QString,
    QMetaType::QString, QMetaType::QString,    9,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject connector::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSconnectorENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSconnectorENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSconnectorENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<connector, std::true_type>,
        // method 'initializeSocket'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'connectToRoom'
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'tryToConnect'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'writeDataToRoom'
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'readDataFromRoom'
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'sendCmd'
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'handleResponseFromRoom'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'heartBeat'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void connector::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<connector *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->initializeSocket(); break;
        case 1: { bool _r = _t->connectToRoom();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 2: _t->tryToConnect(); break;
        case 3: { bool _r = _t->writeDataToRoom((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 4: { QString _r = _t->readDataFromRoom();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 5: { QString _r = _t->sendCmd((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 6: _t->handleResponseFromRoom((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 7: _t->heartBeat(); break;
        default: ;
        }
    }
}

const QMetaObject *connector::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *connector::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSconnectorENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int connector::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 8;
    }
    return _id;
}
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSesp32ConnectorENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSesp32ConnectorENDCLASS = QtMocHelpers::stringData(
    "esp32Connector",
    "sendCmd",
    "",
    "cmd",
    "runningStatusChanged",
    "timeStartChanged",
    "timeEndChanged",
    "timeRemainningChanged",
    "roomBtnClick",
    "startEnd",
    "getRoomInfor",
    "infor",
    "runningStatus",
    "timeStart",
    "timeEnd",
    "timeRemainning"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSesp32ConnectorENDCLASS_t {
    uint offsetsAndSizes[32];
    char stringdata0[15];
    char stringdata1[8];
    char stringdata2[1];
    char stringdata3[4];
    char stringdata4[21];
    char stringdata5[17];
    char stringdata6[15];
    char stringdata7[22];
    char stringdata8[13];
    char stringdata9[9];
    char stringdata10[13];
    char stringdata11[6];
    char stringdata12[14];
    char stringdata13[10];
    char stringdata14[8];
    char stringdata15[15];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSesp32ConnectorENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSesp32ConnectorENDCLASS_t qt_meta_stringdata_CLASSesp32ConnectorENDCLASS = {
    {
        QT_MOC_LITERAL(0, 14),  // "esp32Connector"
        QT_MOC_LITERAL(15, 7),  // "sendCmd"
        QT_MOC_LITERAL(23, 0),  // ""
        QT_MOC_LITERAL(24, 3),  // "cmd"
        QT_MOC_LITERAL(28, 20),  // "runningStatusChanged"
        QT_MOC_LITERAL(49, 16),  // "timeStartChanged"
        QT_MOC_LITERAL(66, 14),  // "timeEndChanged"
        QT_MOC_LITERAL(81, 21),  // "timeRemainningChanged"
        QT_MOC_LITERAL(103, 12),  // "roomBtnClick"
        QT_MOC_LITERAL(116, 8),  // "startEnd"
        QT_MOC_LITERAL(125, 12),  // "getRoomInfor"
        QT_MOC_LITERAL(138, 5),  // "infor"
        QT_MOC_LITERAL(144, 13),  // "runningStatus"
        QT_MOC_LITERAL(158, 9),  // "timeStart"
        QT_MOC_LITERAL(168, 7),  // "timeEnd"
        QT_MOC_LITERAL(176, 14)   // "timeRemainning"
    },
    "esp32Connector",
    "sendCmd",
    "",
    "cmd",
    "runningStatusChanged",
    "timeStartChanged",
    "timeEndChanged",
    "timeRemainningChanged",
    "roomBtnClick",
    "startEnd",
    "getRoomInfor",
    "infor",
    "runningStatus",
    "timeStart",
    "timeEnd",
    "timeRemainning"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSesp32ConnectorENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       4,   74, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   62,    2, 0x06,    5 /* Public */,
       4,    0,   65,    2, 0x06,    7 /* Public */,
       5,    0,   66,    2, 0x06,    8 /* Public */,
       6,    0,   67,    2, 0x06,    9 /* Public */,
       7,    0,   68,    2, 0x06,   10 /* Public */,

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
       8,    0,   69,    2, 0x02,   11 /* Public */,
       9,    0,   70,    2, 0x02,   12 /* Public */,
      10,    1,   71,    2, 0x02,   13 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::QString, QMetaType::QString,   11,

 // properties: name, type, flags
      12, QMetaType::QString, 0x00015903, uint(1), 0,
      13, QMetaType::QString, 0x00015903, uint(2), 0,
      14, QMetaType::QString, 0x00015903, uint(3), 0,
      15, QMetaType::QString, 0x00015903, uint(4), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject esp32Connector::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSesp32ConnectorENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSesp32ConnectorENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSesp32ConnectorENDCLASS_t,
        // property 'runningStatus'
        QtPrivate::TypeAndForceComplete<QString, std::true_type>,
        // property 'timeStart'
        QtPrivate::TypeAndForceComplete<QString, std::true_type>,
        // property 'timeEnd'
        QtPrivate::TypeAndForceComplete<QString, std::true_type>,
        // property 'timeRemainning'
        QtPrivate::TypeAndForceComplete<QString, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<esp32Connector, std::true_type>,
        // method 'sendCmd'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'runningStatusChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'timeStartChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'timeEndChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'timeRemainningChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'roomBtnClick'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'startEnd'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'getRoomInfor'
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>
    >,
    nullptr
} };

void esp32Connector::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<esp32Connector *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->sendCmd((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->runningStatusChanged(); break;
        case 2: _t->timeStartChanged(); break;
        case 3: _t->timeEndChanged(); break;
        case 4: _t->timeRemainningChanged(); break;
        case 5: _t->roomBtnClick(); break;
        case 6: _t->startEnd(); break;
        case 7: { QString _r = _t->getRoomInfor((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (esp32Connector::*)(QString );
            if (_t _q_method = &esp32Connector::sendCmd; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (esp32Connector::*)();
            if (_t _q_method = &esp32Connector::runningStatusChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (esp32Connector::*)();
            if (_t _q_method = &esp32Connector::timeStartChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (esp32Connector::*)();
            if (_t _q_method = &esp32Connector::timeEndChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (esp32Connector::*)();
            if (_t _q_method = &esp32Connector::timeRemainningChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
    }else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<esp32Connector *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->runningStatus(); break;
        case 1: *reinterpret_cast< QString*>(_v) = _t->timeStart(); break;
        case 2: *reinterpret_cast< QString*>(_v) = _t->timeEnd(); break;
        case 3: *reinterpret_cast< QString*>(_v) = _t->timeRemainning(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<esp32Connector *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setRunningStatus(*reinterpret_cast< QString*>(_v)); break;
        case 1: _t->setTimeStart(*reinterpret_cast< QString*>(_v)); break;
        case 2: _t->setTimeEnd(*reinterpret_cast< QString*>(_v)); break;
        case 3: _t->setTimeRemainning(*reinterpret_cast< QString*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
}

const QMetaObject *esp32Connector::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *esp32Connector::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSesp32ConnectorENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int esp32Connector::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 8;
    }else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void esp32Connector::sendCmd(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void esp32Connector::runningStatusChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void esp32Connector::timeStartChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void esp32Connector::timeEndChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void esp32Connector::timeRemainningChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
QT_WARNING_POP
