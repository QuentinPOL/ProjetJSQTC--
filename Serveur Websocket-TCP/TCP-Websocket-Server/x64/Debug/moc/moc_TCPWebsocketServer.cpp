/****************************************************************************
** Meta object code from reading C++ file 'TCPWebsocketServer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../TCPWebsocketServer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TCPWebsocketServer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TCPWebsocketServer_t {
    QByteArrayData data[13];
    char stringdata0[188];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TCPWebsocketServer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TCPWebsocketServer_t qt_meta_stringdata_TCPWebsocketServer = {
    {
QT_MOC_LITERAL(0, 0, 18), // "TCPWebsocketServer"
QT_MOC_LITERAL(1, 19, 21), // "onServerNewConnection"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 20), // "onClientDisconnected"
QT_MOC_LITERAL(4, 63, 17), // "onClientReadyRead"
QT_MOC_LITERAL(5, 81, 20), // "onWebClientReadyRead"
QT_MOC_LITERAL(6, 102, 7), // "message"
QT_MOC_LITERAL(7, 110, 26), // "onSendMessageButtonClicked"
QT_MOC_LITERAL(8, 137, 11), // "QTcpSocket*"
QT_MOC_LITERAL(9, 149, 3), // "obj"
QT_MOC_LITERAL(10, 153, 11), // "QWebSocket*"
QT_MOC_LITERAL(11, 165, 6), // "objWeb"
QT_MOC_LITERAL(12, 172, 15) // "messageReceived"

    },
    "TCPWebsocketServer\0onServerNewConnection\0"
    "\0onClientDisconnected\0onClientReadyRead\0"
    "onWebClientReadyRead\0message\0"
    "onSendMessageButtonClicked\0QTcpSocket*\0"
    "obj\0QWebSocket*\0objWeb\0messageReceived"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TCPWebsocketServer[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x0a /* Public */,
       3,    0,   40,    2, 0x0a /* Public */,
       4,    0,   41,    2, 0x0a /* Public */,
       5,    1,   42,    2, 0x0a /* Public */,
       7,    3,   45,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, 0x80000000 | 8, 0x80000000 | 10, QMetaType::QString,    9,   11,   12,

       0        // eod
};

void TCPWebsocketServer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TCPWebsocketServer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onServerNewConnection(); break;
        case 1: _t->onClientDisconnected(); break;
        case 2: _t->onClientReadyRead(); break;
        case 3: _t->onWebClientReadyRead((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->onSendMessageButtonClicked((*reinterpret_cast< QTcpSocket*(*)>(_a[1])),(*reinterpret_cast< QWebSocket*(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QTcpSocket* >(); break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWebSocket* >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject TCPWebsocketServer::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_TCPWebsocketServer.data,
    qt_meta_data_TCPWebsocketServer,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TCPWebsocketServer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TCPWebsocketServer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TCPWebsocketServer.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int TCPWebsocketServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
