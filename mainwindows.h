#ifndef MAINWINDOWS_H
#define MAINWINDOWS_H
#include <QTimer>
#include <QDateTime>
#include <QString>
#include <QStringList>
#include <QFileInfoList>
#include <QDir>
#include <QSettings>
#include <database.h>
#include "ChatServer.h"
#include "QWebSocket"
#include <iostream>
#include <sstream>
#include <fstream>
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <QProcess>
#include <QCoreApplication>

typedef int		pj_status_t;
class mainwindows : public QObject
{
    Q_OBJECT

signals:
     void getEventandAlarm(QString msg);
     void cppCommand(QVariant jsonMsg);
     void getDistanceandDetailA(QString msg);
     void getDistanceandDetailB(QString msg);
     void getDistanceandDetailC(QString msg);
     void getTablePhaseA(QString msg);
     void getTablePhaseB(QString msg);
     void getTablePhaseC(QString msg);
     void updateTablePhaseA(QString msg);
     void updateTablePhaseB(QString msg);
     void updateTablePhaseC(QString msg);

     void deletedMySQLA(QString msg);
     void deletedMySQLB(QString msg);
     void deletedMySQLC(QString msg);

public:
    explicit mainwindows(QObject *parent = nullptr);
    static mainwindows *instance();

public slots:
//    void boardcasttomessaege(QString msg);
//    void receivemessaege(QString msg);
    void cppSubmitTextFiled(QString qmlJson);
    QString getSystemDateTime();
    void updateDateTime();




private:
    ChatServer *SocketServer;
    Database *mysql;

};

#endif // MAINWINDOWS_H
