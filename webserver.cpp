#include "webserver.h"
#include <QHostAddress>
#include <QDebug>
#include <QAbstractSocket>

WebServer::WebServer(quint16 port, QObject* parent)
    : QObject(parent),
      m_server(new QWebSocketServer(QStringLiteral("IFZ-WebSocket"),
                                    QWebSocketServer::NonSecureMode, this))
{
    const bool ok = m_server->listen(QHostAddress::Any, port);
    qInfo() << "[WebServer] listen port" << port << "ok?" << ok
            << "error:" << m_server->errorString();

    connect(m_server, &QWebSocketServer::newConnection,
            this, &WebServer::onNewConnection);
    connect(m_server, &QWebSocketServer::closed,
            this, &WebServer::onServerClosed);
}

WebServer::~WebServer() {
    if (m_server && m_server->isListening()) m_server->close();
    // ไม่ใช้ std::as_const เพื่อหลีกเลี่ยง C++17
    for (QWebSocket* c : m_clients) {
        if (c) c->deleteLater();
    }
}

void WebServer::onNewConnection() {
    QWebSocket* client = m_server->nextPendingConnection();
    if (!client) return;

    qInfo() << "[WebServer] new client from"
            << client->peerAddress().toString() << ":" << client->peerPort();

    // route ข้อความจาก client -> processMessage(QString)
    connect(client, &QWebSocket::textMessageReceived,
            this, &WebServer::processMessage);

    connect(client, &QWebSocket::disconnected,
            this, &WebServer::onClientDisconnected);

    m_clients.insert(client);
}

void WebServer::processMessage(const QString& message) {
    QWebSocket* pClient = qobject_cast<QWebSocket*>(sender());
    // ส่งต่อให้ MainWindow ที่ connect ไว้ (manageData(QString, QWebSocket*))
    emit newCommandProcess(message, pClient);
}

void WebServer::onClientDisconnected() {
    QWebSocket* client = qobject_cast<QWebSocket*>(sender());
    if (!client) return;
    qInfo() << "[WebServer] client disconnected";
    m_clients.remove(client);
    client->deleteLater();
}

void WebServer::onServerClosed() {
    qWarning() << "[WebServer] server closed";
}

void WebServer::broadcast(const QString& msg) {
    for (QWebSocket* c : m_clients) {
        if (c && c->state() == QAbstractSocket::ConnectedState) {
            c->sendTextMessage(msg);
        }
    }
}

void WebServer::sendTo(QWebSocket* client, const QString& msg) {
    if (!client) return;
    if (client->state() == QAbstractSocket::ConnectedState) {
        client->sendTextMessage(msg);
    } else {
        qWarning() << "[WebServer] sendTo: socket not connected, state=" << client->state();
    }
}

// <<=== slot ที่คุณต้องการให้เชื่อมกับ Database
void WebServer::sendMessage(QString message, QWebSocket* pSender) {
    qDebug() << "[WebServer] sendMessage:" << message.left(200) << "to" << pSender;
    if (!pSender) {
        qWarning() << "[WebServer] sendMessage: pSender is null, broadcasting";
        broadcast(message);
        return;
    }
    if (!m_clients.contains(pSender)) {
        // ไม่รู้จัก pointer นี้ (อาจมาจาก thread อื่น/หมดอายุ) — จะลองส่งก็ได้หรือจะทิ้งก็ได้
        qWarning() << "[WebServer] sendMessage: unknown client pointer; trying to send anyway";
    }
    if (pSender->state() == QAbstractSocket::ConnectedState) {
        pSender->sendTextMessage(message);
    } else {
        qWarning() << "[WebServer] sendMessage: socket not connected, state=" << pSender->state();
    }
}
void WebServer::broadcastMessage(QString message){
    Q_FOREACH (QWebSocket *pClient, m_clients)
    {
        qDebug() << "broadcastMessage:" << m_clients << message;
        if(pClient->state()){
            qDebug() << "broadcastMessage TRUE";
            pClient->sendTextMessage(message);
        }

    }
}
