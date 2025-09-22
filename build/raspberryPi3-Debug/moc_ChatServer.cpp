/****************************************************************************
** Meta object code from reading C++ file 'ChatServer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../ChatServer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ChatServer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ChatServer_t {
    QByteArrayData data[77];
    char stringdata0[1017];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ChatServer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ChatServer_t qt_meta_stringdata_ChatServer = {
    {
QT_MOC_LITERAL(0, 0, 10), // "ChatServer"
QT_MOC_LITERAL(1, 11, 17), // "updateChannelConf"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 13), // "radioA_IPAddr"
QT_MOC_LITERAL(4, 44, 13), // "radioB_IPAddr"
QT_MOC_LITERAL(5, 58, 13), // "radioModeTxRx"
QT_MOC_LITERAL(6, 72, 16), // "defaultMainRadio"
QT_MOC_LITERAL(7, 89, 7), // "mainVCS"
QT_MOC_LITERAL(8, 97, 10), // "snmpEnable"
QT_MOC_LITERAL(9, 108, 14), // "schedulerIndex"
QT_MOC_LITERAL(10, 123, 9), // "channelID"
QT_MOC_LITERAL(11, 133, 12), // "webchannelID"
QT_MOC_LITERAL(12, 146, 13), // "newConnection"
QT_MOC_LITERAL(13, 160, 9), // "menuIndex"
QT_MOC_LITERAL(14, 170, 11), // "QWebSocket*"
QT_MOC_LITERAL(15, 182, 9), // "newClient"
QT_MOC_LITERAL(16, 192, 13), // "updateNetwork"
QT_MOC_LITERAL(17, 206, 7), // "uint8_t"
QT_MOC_LITERAL(18, 214, 10), // "dhcpmethod"
QT_MOC_LITERAL(19, 225, 9), // "ipaddress"
QT_MOC_LITERAL(20, 235, 6), // "subnet"
QT_MOC_LITERAL(21, 242, 7), // "gateway"
QT_MOC_LITERAL(22, 250, 6), // "pridns"
QT_MOC_LITERAL(23, 257, 6), // "secdns"
QT_MOC_LITERAL(24, 264, 14), // "phyNetworkName"
QT_MOC_LITERAL(25, 279, 15), // "updateScheduler"
QT_MOC_LITERAL(26, 295, 5), // "value"
QT_MOC_LITERAL(27, 301, 14), // "updateFirmware"
QT_MOC_LITERAL(28, 316, 13), // "toggleGpioOut"
QT_MOC_LITERAL(29, 330, 7), // "gpioNum"
QT_MOC_LITERAL(30, 338, 7), // "gpioVal"
QT_MOC_LITERAL(31, 346, 15), // "updateNTPServer"
QT_MOC_LITERAL(32, 362, 18), // "setcurrentDatetime"
QT_MOC_LITERAL(33, 381, 11), // "setLocation"
QT_MOC_LITERAL(34, 393, 14), // "restartnetwork"
QT_MOC_LITERAL(35, 408, 12), // "resetnetwork"
QT_MOC_LITERAL(36, 421, 7), // "pSender"
QT_MOC_LITERAL(37, 429, 12), // "rebootSystem"
QT_MOC_LITERAL(38, 442, 12), // "onNewMessage"
QT_MOC_LITERAL(39, 455, 7), // "message"
QT_MOC_LITERAL(40, 463, 14), // "getMonitorPage"
QT_MOC_LITERAL(41, 478, 14), // "getNetworkPage"
QT_MOC_LITERAL(42, 493, 13), // "getSystemPage"
QT_MOC_LITERAL(43, 507, 15), // "getSystemPageIP"
QT_MOC_LITERAL(44, 523, 16), // "getSwitchingPage"
QT_MOC_LITERAL(45, 540, 15), // "getCtrlInfoPage"
QT_MOC_LITERAL(46, 556, 8), // "idInRole"
QT_MOC_LITERAL(47, 565, 14), // "toggleRxEnable"
QT_MOC_LITERAL(48, 580, 14), // "toggleTxEnable"
QT_MOC_LITERAL(49, 595, 18), // "onNumClientChanged"
QT_MOC_LITERAL(50, 614, 9), // "clientnum"
QT_MOC_LITERAL(51, 624, 14), // "getChannelList"
QT_MOC_LITERAL(52, 639, 15), // "getCtrlinfoPage"
QT_MOC_LITERAL(53, 655, 16), // "updateNewNetwork"
QT_MOC_LITERAL(54, 672, 14), // "updatePostHost"
QT_MOC_LITERAL(55, 687, 15), // "getStatusSwitch"
QT_MOC_LITERAL(56, 703, 13), // "controlswitch"
QT_MOC_LITERAL(57, 717, 16), // "controlAllswitch"
QT_MOC_LITERAL(58, 734, 12), // "getLabelName"
QT_MOC_LITERAL(59, 747, 12), // "getipnetwork"
QT_MOC_LITERAL(60, 760, 17), // "getupdateFirmware"
QT_MOC_LITERAL(61, 778, 13), // "showonDisplay"
QT_MOC_LITERAL(62, 792, 17), // "requectFromClient"
QT_MOC_LITERAL(63, 810, 11), // "testMessage"
QT_MOC_LITERAL(64, 822, 16), // "receiveRequestWS"
QT_MOC_LITERAL(65, 839, 12), // "updateSystem"
QT_MOC_LITERAL(66, 852, 14), // "updatefireware"
QT_MOC_LITERAL(67, 867, 14), // "uploadfireware"
QT_MOC_LITERAL(68, 882, 12), // "systembackup"
QT_MOC_LITERAL(69, 895, 12), // "downloadFile"
QT_MOC_LITERAL(70, 908, 11), // "reboosystem"
QT_MOC_LITERAL(71, 920, 11), // "monitorPage"
QT_MOC_LITERAL(72, 932, 15), // "onNewConnection"
QT_MOC_LITERAL(73, 948, 14), // "commandProcess"
QT_MOC_LITERAL(74, 963, 14), // "processMessage"
QT_MOC_LITERAL(75, 978, 18), // "socketDisconnected"
QT_MOC_LITERAL(76, 997, 19) // "boardcasttomessaege"

    },
    "ChatServer\0updateChannelConf\0\0"
    "radioA_IPAddr\0radioB_IPAddr\0radioModeTxRx\0"
    "defaultMainRadio\0mainVCS\0snmpEnable\0"
    "schedulerIndex\0channelID\0webchannelID\0"
    "newConnection\0menuIndex\0QWebSocket*\0"
    "newClient\0updateNetwork\0uint8_t\0"
    "dhcpmethod\0ipaddress\0subnet\0gateway\0"
    "pridns\0secdns\0phyNetworkName\0"
    "updateScheduler\0value\0updateFirmware\0"
    "toggleGpioOut\0gpioNum\0gpioVal\0"
    "updateNTPServer\0setcurrentDatetime\0"
    "setLocation\0restartnetwork\0resetnetwork\0"
    "pSender\0rebootSystem\0onNewMessage\0"
    "message\0getMonitorPage\0getNetworkPage\0"
    "getSystemPage\0getSystemPageIP\0"
    "getSwitchingPage\0getCtrlInfoPage\0"
    "idInRole\0toggleRxEnable\0toggleTxEnable\0"
    "onNumClientChanged\0clientnum\0"
    "getChannelList\0getCtrlinfoPage\0"
    "updateNewNetwork\0updatePostHost\0"
    "getStatusSwitch\0controlswitch\0"
    "controlAllswitch\0getLabelName\0"
    "getipnetwork\0getupdateFirmware\0"
    "showonDisplay\0requectFromClient\0"
    "testMessage\0receiveRequestWS\0updateSystem\0"
    "updatefireware\0uploadfireware\0"
    "systembackup\0downloadFile\0reboosystem\0"
    "monitorPage\0onNewConnection\0commandProcess\0"
    "processMessage\0socketDisconnected\0"
    "boardcasttomessaege"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ChatServer[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      49,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      44,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    9,  259,    2, 0x06 /* Public */,
      12,    2,  278,    2, 0x06 /* Public */,
      16,    7,  283,    2, 0x06 /* Public */,
      25,    2,  298,    2, 0x06 /* Public */,
      27,    0,  303,    2, 0x06 /* Public */,
      28,    2,  304,    2, 0x06 /* Public */,
      31,    1,  309,    2, 0x06 /* Public */,
      32,    1,  312,    2, 0x06 /* Public */,
      33,    1,  315,    2, 0x06 /* Public */,
      34,    1,  318,    2, 0x06 /* Public */,
      35,    1,  321,    2, 0x06 /* Public */,
      37,    0,  324,    2, 0x06 /* Public */,
      38,    1,  325,    2, 0x06 /* Public */,
      40,    1,  328,    2, 0x06 /* Public */,
      41,    1,  331,    2, 0x06 /* Public */,
      42,    1,  334,    2, 0x06 /* Public */,
      43,    1,  337,    2, 0x06 /* Public */,
      44,    1,  340,    2, 0x06 /* Public */,
      45,    2,  343,    2, 0x06 /* Public */,
      47,    1,  348,    2, 0x06 /* Public */,
      48,    1,  351,    2, 0x06 /* Public */,
      49,    1,  354,    2, 0x06 /* Public */,
      51,    1,  357,    2, 0x06 /* Public */,
      52,    2,  360,    2, 0x06 /* Public */,
      53,    6,  365,    2, 0x06 /* Public */,
      54,    1,  378,    2, 0x06 /* Public */,
      55,    1,  381,    2, 0x06 /* Public */,
      56,    1,  384,    2, 0x06 /* Public */,
      57,    1,  387,    2, 0x06 /* Public */,
      58,    1,  390,    2, 0x06 /* Public */,
      59,    1,  393,    2, 0x06 /* Public */,
      42,    1,  396,    2, 0x06 /* Public */,
      60,    1,  399,    2, 0x06 /* Public */,
      61,    1,  402,    2, 0x06 /* Public */,
      62,    1,  405,    2, 0x06 /* Public */,
      63,    1,  408,    2, 0x06 /* Public */,
      64,    1,  411,    2, 0x06 /* Public */,
      65,    1,  414,    2, 0x06 /* Public */,
      66,    1,  417,    2, 0x06 /* Public */,
      67,    1,  420,    2, 0x06 /* Public */,
      68,    1,  423,    2, 0x06 /* Public */,
      69,    1,  426,    2, 0x06 /* Public */,
      70,    1,  429,    2, 0x06 /* Public */,
      71,    1,  432,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      72,    0,  435,    2, 0x08 /* Private */,
      73,    2,  436,    2, 0x08 /* Private */,
      74,    1,  441,    2, 0x08 /* Private */,
      75,    0,  444,    2, 0x08 /* Private */,
      76,    1,  445,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool, QMetaType::Int, QMetaType::Int, QMetaType::QString,    3,    4,    5,    6,    7,    8,    9,   10,   11,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 14,   13,   15,
    QMetaType::Void, 0x80000000 | 17, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,   18,   19,   20,   21,   22,   23,   24,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   26,   10,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   29,   30,
    QMetaType::Void, QMetaType::QString,   26,
    QMetaType::Void, QMetaType::QString,   26,
    QMetaType::Void, QMetaType::QString,   26,
    QMetaType::Void, QMetaType::QString,   24,
    QMetaType::Void, 0x80000000 | 14,   36,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   39,
    QMetaType::Void, 0x80000000 | 14,   36,
    QMetaType::Void, 0x80000000 | 14,   36,
    QMetaType::Void, 0x80000000 | 14,   36,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, 0x80000000 | 14,   36,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 14,   46,   36,
    QMetaType::Void, QMetaType::Int,   46,
    QMetaType::Void, QMetaType::Int,   46,
    QMetaType::Void, QMetaType::Int,   50,
    QMetaType::Void, 0x80000000 | 14,   36,
    QMetaType::Void, 0x80000000 | 14, QMetaType::Int,   36,   11,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,    2,    2,    2,    2,    2,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 14,   39,   36,
    QMetaType::Void, QMetaType::QString,   39,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,

       0        // eod
};

void ChatServer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ChatServer *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->updateChannelConf((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4])),(*reinterpret_cast< bool(*)>(_a[5])),(*reinterpret_cast< bool(*)>(_a[6])),(*reinterpret_cast< int(*)>(_a[7])),(*reinterpret_cast< int(*)>(_a[8])),(*reinterpret_cast< QString(*)>(_a[9]))); break;
        case 1: _t->newConnection((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QWebSocket*(*)>(_a[2]))); break;
        case 2: _t->updateNetwork((*reinterpret_cast< uint8_t(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5])),(*reinterpret_cast< QString(*)>(_a[6])),(*reinterpret_cast< QString(*)>(_a[7]))); break;
        case 3: _t->updateScheduler((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->updateFirmware(); break;
        case 5: _t->toggleGpioOut((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->updateNTPServer((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->setcurrentDatetime((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->setLocation((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->restartnetwork((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->resetnetwork((*reinterpret_cast< QWebSocket*(*)>(_a[1]))); break;
        case 11: _t->rebootSystem(); break;
        case 12: _t->onNewMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 13: _t->getMonitorPage((*reinterpret_cast< QWebSocket*(*)>(_a[1]))); break;
        case 14: _t->getNetworkPage((*reinterpret_cast< QWebSocket*(*)>(_a[1]))); break;
        case 15: _t->getSystemPage((*reinterpret_cast< QWebSocket*(*)>(_a[1]))); break;
        case 16: _t->getSystemPageIP((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 17: _t->getSwitchingPage((*reinterpret_cast< QWebSocket*(*)>(_a[1]))); break;
        case 18: _t->getCtrlInfoPage((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QWebSocket*(*)>(_a[2]))); break;
        case 19: _t->toggleRxEnable((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 20: _t->toggleTxEnable((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 21: _t->onNumClientChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 22: _t->getChannelList((*reinterpret_cast< QWebSocket*(*)>(_a[1]))); break;
        case 23: _t->getCtrlinfoPage((*reinterpret_cast< QWebSocket*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 24: _t->updateNewNetwork((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5])),(*reinterpret_cast< QString(*)>(_a[6]))); break;
        case 25: _t->updatePostHost((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 26: _t->getStatusSwitch((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 27: _t->controlswitch((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 28: _t->controlAllswitch((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 29: _t->getLabelName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 30: _t->getipnetwork((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 31: _t->getSystemPage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 32: _t->getupdateFirmware((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 33: _t->showonDisplay((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 34: _t->requectFromClient((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 35: _t->testMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 36: _t->receiveRequestWS((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 37: _t->updateSystem((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 38: _t->updatefireware((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 39: _t->uploadfireware((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 40: _t->systembackup((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 41: _t->downloadFile((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 42: _t->reboosystem((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 43: _t->monitorPage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 44: _t->onNewConnection(); break;
        case 45: _t->commandProcess((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QWebSocket*(*)>(_a[2]))); break;
        case 46: _t->processMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 47: _t->socketDisconnected(); break;
        case 48: _t->boardcasttomessaege((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWebSocket* >(); break;
            }
            break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWebSocket* >(); break;
            }
            break;
        case 13:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWebSocket* >(); break;
            }
            break;
        case 14:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWebSocket* >(); break;
            }
            break;
        case 15:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWebSocket* >(); break;
            }
            break;
        case 17:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWebSocket* >(); break;
            }
            break;
        case 18:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWebSocket* >(); break;
            }
            break;
        case 22:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWebSocket* >(); break;
            }
            break;
        case 23:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWebSocket* >(); break;
            }
            break;
        case 45:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWebSocket* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ChatServer::*)(QString , QString , bool , bool , bool , bool , int , int , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatServer::updateChannelConf)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ChatServer::*)(QString , QWebSocket * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatServer::newConnection)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ChatServer::*)(uint8_t , QString , QString , QString , QString , QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatServer::updateNetwork)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ChatServer::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatServer::updateScheduler)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (ChatServer::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatServer::updateFirmware)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (ChatServer::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatServer::toggleGpioOut)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (ChatServer::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatServer::updateNTPServer)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (ChatServer::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatServer::setcurrentDatetime)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (ChatServer::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatServer::setLocation)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (ChatServer::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatServer::restartnetwork)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (ChatServer::*)(QWebSocket * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatServer::resetnetwork)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (ChatServer::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatServer::rebootSystem)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (ChatServer::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatServer::onNewMessage)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (ChatServer::*)(QWebSocket * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatServer::getMonitorPage)) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (ChatServer::*)(QWebSocket * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatServer::getNetworkPage)) {
                *result = 14;
                return;
            }
        }
        {
            using _t = void (ChatServer::*)(QWebSocket * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatServer::getSystemPage)) {
                *result = 15;
                return;
            }
        }
        {
            using _t = void (ChatServer::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatServer::getSystemPageIP)) {
                *result = 16;
                return;
            }
        }
        {
            using _t = void (ChatServer::*)(QWebSocket * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatServer::getSwitchingPage)) {
                *result = 17;
                return;
            }
        }
        {
            using _t = void (ChatServer::*)(int , QWebSocket * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatServer::getCtrlInfoPage)) {
                *result = 18;
                return;
            }
        }
        {
            using _t = void (ChatServer::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatServer::toggleRxEnable)) {
                *result = 19;
                return;
            }
        }
        {
            using _t = void (ChatServer::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatServer::toggleTxEnable)) {
                *result = 20;
                return;
            }
        }
        {
            using _t = void (ChatServer::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatServer::onNumClientChanged)) {
                *result = 21;
                return;
            }
        }
        {
            using _t = void (ChatServer::*)(QWebSocket * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatServer::getChannelList)) {
                *result = 22;
                return;
            }
        }
        {
            using _t = void (ChatServer::*)(QWebSocket * , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatServer::getCtrlinfoPage)) {
                *result = 23;
                return;
            }
        }
        {
            using _t = void (ChatServer::*)(QString , QString , QString , QString , QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatServer::updateNewNetwork)) {
                *result = 24;
                return;
            }
        }
        {
            using _t = void (ChatServer::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatServer::updatePostHost)) {
                *result = 25;
                return;
            }
        }
        {
            using _t = void (ChatServer::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatServer::getStatusSwitch)) {
                *result = 26;
                return;
            }
        }
        {
            using _t = void (ChatServer::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatServer::controlswitch)) {
                *result = 27;
                return;
            }
        }
        {
            using _t = void (ChatServer::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatServer::controlAllswitch)) {
                *result = 28;
                return;
            }
        }
        {
            using _t = void (ChatServer::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatServer::getLabelName)) {
                *result = 29;
                return;
            }
        }
        {
            using _t = void (ChatServer::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatServer::getipnetwork)) {
                *result = 30;
                return;
            }
        }
        {
            using _t = void (ChatServer::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatServer::getSystemPage)) {
                *result = 31;
                return;
            }
        }
        {
            using _t = void (ChatServer::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatServer::getupdateFirmware)) {
                *result = 32;
                return;
            }
        }
        {
            using _t = void (ChatServer::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatServer::showonDisplay)) {
                *result = 33;
                return;
            }
        }
        {
            using _t = void (ChatServer::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatServer::requectFromClient)) {
                *result = 34;
                return;
            }
        }
        {
            using _t = void (ChatServer::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatServer::testMessage)) {
                *result = 35;
                return;
            }
        }
        {
            using _t = void (ChatServer::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatServer::receiveRequestWS)) {
                *result = 36;
                return;
            }
        }
        {
            using _t = void (ChatServer::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatServer::updateSystem)) {
                *result = 37;
                return;
            }
        }
        {
            using _t = void (ChatServer::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatServer::updatefireware)) {
                *result = 38;
                return;
            }
        }
        {
            using _t = void (ChatServer::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatServer::uploadfireware)) {
                *result = 39;
                return;
            }
        }
        {
            using _t = void (ChatServer::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatServer::systembackup)) {
                *result = 40;
                return;
            }
        }
        {
            using _t = void (ChatServer::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatServer::downloadFile)) {
                *result = 41;
                return;
            }
        }
        {
            using _t = void (ChatServer::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatServer::reboosystem)) {
                *result = 42;
                return;
            }
        }
        {
            using _t = void (ChatServer::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatServer::monitorPage)) {
                *result = 43;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ChatServer::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ChatServer.data,
    qt_meta_data_ChatServer,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ChatServer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ChatServer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ChatServer.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ChatServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 49)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 49;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 49)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 49;
    }
    return _id;
}

// SIGNAL 0
void ChatServer::updateChannelConf(QString _t1, QString _t2, bool _t3, bool _t4, bool _t5, bool _t6, int _t7, int _t8, QString _t9)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t5))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t6))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t7))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t8))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t9))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ChatServer::newConnection(QString _t1, QWebSocket * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ChatServer::updateNetwork(uint8_t _t1, QString _t2, QString _t3, QString _t4, QString _t5, QString _t6, QString _t7)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t5))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t6))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t7))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ChatServer::updateScheduler(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ChatServer::updateFirmware()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void ChatServer::toggleGpioOut(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void ChatServer::updateNTPServer(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void ChatServer::setcurrentDatetime(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void ChatServer::setLocation(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void ChatServer::restartnetwork(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void ChatServer::resetnetwork(QWebSocket * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void ChatServer::rebootSystem()
{
    QMetaObject::activate(this, &staticMetaObject, 11, nullptr);
}

// SIGNAL 12
void ChatServer::onNewMessage(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void ChatServer::getMonitorPage(QWebSocket * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void ChatServer::getNetworkPage(QWebSocket * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void ChatServer::getSystemPage(QWebSocket * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void ChatServer::getSystemPageIP(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}

// SIGNAL 17
void ChatServer::getSwitchingPage(QWebSocket * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 17, _a);
}

// SIGNAL 18
void ChatServer::getCtrlInfoPage(int _t1, QWebSocket * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 18, _a);
}

// SIGNAL 19
void ChatServer::toggleRxEnable(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 19, _a);
}

// SIGNAL 20
void ChatServer::toggleTxEnable(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 20, _a);
}

// SIGNAL 21
void ChatServer::onNumClientChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 21, _a);
}

// SIGNAL 22
void ChatServer::getChannelList(QWebSocket * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 22, _a);
}

// SIGNAL 23
void ChatServer::getCtrlinfoPage(QWebSocket * _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 23, _a);
}

// SIGNAL 24
void ChatServer::updateNewNetwork(QString _t1, QString _t2, QString _t3, QString _t4, QString _t5, QString _t6)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t5))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t6))) };
    QMetaObject::activate(this, &staticMetaObject, 24, _a);
}

// SIGNAL 25
void ChatServer::updatePostHost(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 25, _a);
}

// SIGNAL 26
void ChatServer::getStatusSwitch(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 26, _a);
}

// SIGNAL 27
void ChatServer::controlswitch(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 27, _a);
}

// SIGNAL 28
void ChatServer::controlAllswitch(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 28, _a);
}

// SIGNAL 29
void ChatServer::getLabelName(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 29, _a);
}

// SIGNAL 30
void ChatServer::getipnetwork(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 30, _a);
}

// SIGNAL 31
void ChatServer::getSystemPage(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 31, _a);
}

// SIGNAL 32
void ChatServer::getupdateFirmware(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 32, _a);
}

// SIGNAL 33
void ChatServer::showonDisplay(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 33, _a);
}

// SIGNAL 34
void ChatServer::requectFromClient(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 34, _a);
}

// SIGNAL 35
void ChatServer::testMessage(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 35, _a);
}

// SIGNAL 36
void ChatServer::receiveRequestWS(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 36, _a);
}

// SIGNAL 37
void ChatServer::updateSystem(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 37, _a);
}

// SIGNAL 38
void ChatServer::updatefireware(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 38, _a);
}

// SIGNAL 39
void ChatServer::uploadfireware(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 39, _a);
}

// SIGNAL 40
void ChatServer::systembackup(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 40, _a);
}

// SIGNAL 41
void ChatServer::downloadFile(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 41, _a);
}

// SIGNAL 42
void ChatServer::reboosystem(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 42, _a);
}

// SIGNAL 43
void ChatServer::monitorPage(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 43, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
