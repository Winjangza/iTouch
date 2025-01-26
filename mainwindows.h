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
#include <SocketClient.h>
#include <vector>
#include <algorithm>
#include <QFile>
#include <QTextStream>
#define SwVersion "V0.2 26122024"
#define HwVersion "Raspberry Pi"
#define HwName "Monitor"
#define PATH_BIN "/opt/OpenPLC/bin/"
#define PATH_UPDATE "/home/pi/update_firmware/OpenPLC"
#define PATH_DOWNLOAD "/home/pi/update_firmware"
#define USERS "pi"
#define PASSWORD "11111"
#define IP_ADDRESS "192.168.10.191"
#define FILES "/opt/OpenPLC/bin/OpenPLC"

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
     void getEditDatafromMySQLA(QString msg);
     void parameterMarginA(QString msg);
     void parameterThreshold(QString msg);
     void getDataThreshold();
     void settingGeneral();
     void preiodicSetting();
     void updateTimer(QString);
     void updateWeekly(QString);
     void updateUser(QString);
     void updateRelay(QString);
     void rawdataPlot(QString);
     void cursorDistance(QString);
     void moveCursor(QString);
     void changeDistanceRange(QString);
     void sendToSocket(QString);
     void taggingpoint(QString);
     void clearDisplay(QString);
     void clearPatternGraph(QString);
     void settingNetWorkandSNMP(QString);
     void settingdisplay(QString);
     void getsettingdisplay();
     void plotingDataPhaseA(QString);
     void plotingDataPhaseB(QString);
     void plotingDataPhaseC(QString);


public:
    explicit mainwindows(QObject *parent = nullptr);
    static mainwindows *instance();

public slots:
//    void boardcasttomessaege(QString msg);
//    void receivemessaege(QString msg);
    void cppSubmitTextFiled(QString qmlJson);
    void ServerCommand(QString qmlJson);

    QString getSystemDateTime();
    void updateDateTime();
    void connectToPLC();
    void reconnectTimerTimeout();
    void connectTimeOut();
    void calculate(QString);
    void calculateDataPhaseB(QString);
    void calculateDataPhaseC(QString);
//= 200*10e-9
private:
    ChatServer *SocketServer;
    Database *mysql;
    SocketClient *client;
    QString serverAddress;
    int serverPort;
    QTimer *reconnectTimer;
    QTimer *Timer;
    double sagFactor;       // SAG factor
    double samplingRate; // Sampling rate (meters per sample)
    double distanceToStart; // ระยะตั้งต้น (เมตร)
    double distanceToShow;   // ระยะปลายทาง (เมตร)
    double distancePointBetweenPoint = 60.0f;
    bool isVersion = false;
    double offset;
    int point;
    double valuetheshold; //เป็นตัวแปรที่เปลี่ยนแปลงได้
    int samplingrate; //เป็นตัวแปรที่เปลี่ยนแปลงได้ 225
    double SAG; //0.983
    double speedOfligth = 3*10e8; //m/s
    double timepoint = 200*10e-9; //s
    double distance = (speedOfligth * timepoint)/100;
    int initiation;//km เป็นตัวแปรที่เปลี่ยนแปลงได้
    double destination;//=8500/distance;//km เป็นตัวแปรที่เปลี่ยนแปลงได้
    int totalpoint = destination - initiation;     //1จุดห่างกัน60เมตร
    int sagfactor;
    int resamplingpoint; //= samplingrate % sagfactor
    QString rawdataArrayA;
    QString rawdataArrayB;
    QString rawdataArrayC;
    QString temp;
    QString temp2;
    QString temp3;

    int count=0;
    int count2=0;
    int count3=0;

//ทั้งหมดมี8500เมตรต้องplot ทั้งหมดกี่ครั้งถึงจะครบ8500ม โดยเอา8500หารด้วยresamplingpoint ซึ่งก็คือจำนวนจุดที่ต้องplot ต่อ60ม
//ตังอย่าง 8500/87=97.7 =98ครั้งจนครบ 8500ม แล้วทีนี้มันเริ่มจาก 0.0015mV ต้องบวกเพิ่มขึ้นทีละเท่าไหรจนมันไปถึง8500 โดย87จุดและแต่ละจุดมีระยะห่าง60ม
//จำนวน98ครั้งจนไปถึง8500ม
};

#endif // MAINWINDOWS_H
