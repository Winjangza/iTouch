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
     void getDistanceandDetail(QString msg);
     void getTablePhase(QString msg);
     void deletedMySQL(QString msg);
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
