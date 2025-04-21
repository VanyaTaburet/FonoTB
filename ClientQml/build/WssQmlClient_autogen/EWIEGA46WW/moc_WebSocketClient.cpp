/****************************************************************************
** Meta object code from reading C++ file 'WebSocketClient.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../WebSocketClient.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'WebSocketClient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WebSocketClient_t {
    QByteArrayData data[26];
    char stringdata0[304];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WebSocketClient_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WebSocketClient_t qt_meta_stringdata_WebSocketClient = {
    {
QT_MOC_LITERAL(0, 0, 15), // "WebSocketClient"
QT_MOC_LITERAL(1, 16, 9), // "connected"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 12), // "disconnected"
QT_MOC_LITERAL(4, 40, 15), // "messageReceived"
QT_MOC_LITERAL(5, 56, 7), // "message"
QT_MOC_LITERAL(6, 64, 13), // "tracksUpdated"
QT_MOC_LITERAL(7, 78, 18), // "std::vector<Track>"
QT_MOC_LITERAL(8, 97, 6), // "tracks"
QT_MOC_LITERAL(9, 104, 17), // "trackUsersUpdated"
QT_MOC_LITERAL(10, 122, 7), // "trackId"
QT_MOC_LITERAL(11, 130, 5), // "users"
QT_MOC_LITERAL(12, 136, 11), // "messageSent"
QT_MOC_LITERAL(13, 148, 11), // "onConnected"
QT_MOC_LITERAL(14, 160, 14), // "onDisconnected"
QT_MOC_LITERAL(15, 175, 21), // "onTextMessageReceived"
QT_MOC_LITERAL(16, 197, 14), // "onBytesWritten"
QT_MOC_LITERAL(17, 212, 5), // "bytes"
QT_MOC_LITERAL(18, 218, 15), // "connectToServer"
QT_MOC_LITERAL(19, 234, 3), // "url"
QT_MOC_LITERAL(20, 238, 14), // "addUserToTrack"
QT_MOC_LITERAL(21, 253, 10), // "removeUser"
QT_MOC_LITERAL(22, 264, 15), // "sendJsonMessage"
QT_MOC_LITERAL(23, 280, 4), // "type"
QT_MOC_LITERAL(24, 285, 4), // "name"
QT_MOC_LITERAL(25, 290, 13) // "getTrackUsers"

    },
    "WebSocketClient\0connected\0\0disconnected\0"
    "messageReceived\0message\0tracksUpdated\0"
    "std::vector<Track>\0tracks\0trackUsersUpdated\0"
    "trackId\0users\0messageSent\0onConnected\0"
    "onDisconnected\0onTextMessageReceived\0"
    "onBytesWritten\0bytes\0connectToServer\0"
    "url\0addUserToTrack\0removeUser\0"
    "sendJsonMessage\0type\0name\0getTrackUsers"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WebSocketClient[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   89,    2, 0x06 /* Public */,
       3,    0,   90,    2, 0x06 /* Public */,
       4,    1,   91,    2, 0x06 /* Public */,
       6,    1,   94,    2, 0x06 /* Public */,
       9,    2,   97,    2, 0x06 /* Public */,
      12,    0,  102,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      13,    0,  103,    2, 0x08 /* Private */,
      14,    0,  104,    2, 0x08 /* Private */,
      15,    1,  105,    2, 0x08 /* Private */,
      16,    1,  108,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
      18,    1,  111,    2, 0x02 /* Public */,
      20,    1,  114,    2, 0x02 /* Public */,
      21,    0,  117,    2, 0x02 /* Public */,
      22,    2,  118,    2, 0x02 /* Public */,
      25,    0,  123,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, QMetaType::QString, QMetaType::QStringList,   10,   11,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::LongLong,   17,

 // methods: parameters
    QMetaType::Void, QMetaType::QString,   19,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   23,   24,
    QMetaType::Void,

       0        // eod
};

void WebSocketClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WebSocketClient *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->connected(); break;
        case 1: _t->disconnected(); break;
        case 2: _t->messageReceived((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->tracksUpdated((*reinterpret_cast< const std::vector<Track>(*)>(_a[1]))); break;
        case 4: _t->trackUsersUpdated((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QStringList(*)>(_a[2]))); break;
        case 5: _t->messageSent(); break;
        case 6: _t->onConnected(); break;
        case 7: _t->onDisconnected(); break;
        case 8: _t->onTextMessageReceived((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 9: _t->onBytesWritten((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 10: _t->connectToServer((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 11: _t->addUserToTrack((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 12: _t->removeUser(); break;
        case 13: _t->sendJsonMessage((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 14: _t->getTrackUsers(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (WebSocketClient::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WebSocketClient::connected)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (WebSocketClient::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WebSocketClient::disconnected)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (WebSocketClient::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WebSocketClient::messageReceived)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (WebSocketClient::*)(const std::vector<Track> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WebSocketClient::tracksUpdated)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (WebSocketClient::*)(const QString & , const QStringList & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WebSocketClient::trackUsersUpdated)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (WebSocketClient::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WebSocketClient::messageSent)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject WebSocketClient::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_WebSocketClient.data,
    qt_meta_data_WebSocketClient,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *WebSocketClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WebSocketClient::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WebSocketClient.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int WebSocketClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void WebSocketClient::connected()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void WebSocketClient::disconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void WebSocketClient::messageReceived(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void WebSocketClient::tracksUpdated(const std::vector<Track> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void WebSocketClient::trackUsersUpdated(const QString & _t1, const QStringList & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void WebSocketClient::messageSent()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
