#include "mainwindows.h"


mainwindows::mainwindows(QObject *parent) : QObject(parent){
    qDebug() << "hello windows";

    SocketServer = new ChatServer(1234);
    mysql = new Database("ITouch", "pi", "rpi3!2024", "localhost", this);
    connect(mysql, SIGNAL(eventmsg(QString)), SocketServer, SLOT(boardcasttomessaege(QString)));
    connect(this, SIGNAL(getDistanceandDetailA(QString)), mysql, SLOT(DistanceandDetailPhaseA(QString)));
    connect(this, SIGNAL(getDistanceandDetailB(QString)), mysql, SLOT(DistanceandDetailPhaseB(QString)));
    connect(this, SIGNAL(getDistanceandDetailC(QString)), mysql, SLOT(DistanceandDetailPhaseC(QString)));
    connect(this, SIGNAL(getTablePhaseA(QString)), mysql, SLOT(getMySqlPhase(QString)));
    connect(this, SIGNAL(getTablePhaseB(QString)), mysql, SLOT(getMySqlPhase(QString)));
    connect(this, SIGNAL(getTablePhaseC(QString)), mysql, SLOT(getMySqlPhase(QString)));
    connect(mysql, SIGNAL(cmdmsg(QString)), SocketServer, SLOT(boardcasttomessaege(QString)));
    connect(mysql, SIGNAL(updateTableDisplay(QString)), SocketServer, SLOT(boardcasttomessaege(QString)));
    connect(this, SIGNAL(deletedMySQLA(QString)), mysql, SLOT(deletedDataMySQLPhaseA(QString)));
    connect(this, SIGNAL(deletedMySQLB(QString)), mysql, SLOT(deletedDataMySQLPhaseB(QString)));
    connect(this, SIGNAL(deletedMySQLC(QString)), mysql, SLOT(deletedDataMySQLPhaseC(QString)));
    connect(mysql,SIGNAL(deletedmydatabase(QString)),SocketServer,SLOT(boardcasttomessaege(QString)));
    connect(this, SIGNAL(updateTablePhaseA(QString)), mysql, SLOT(updateTablePhaseA(QString)));
    connect(this, SIGNAL(updateTablePhaseB(QString)), mysql, SLOT(updateTablePhaseB(QString)));
    connect(this, SIGNAL(updateTablePhaseC(QString)), mysql, SLOT(updateTablePhaseC(QString)));
    connect(mysql,SIGNAL(updatedataTableA(QString)),SocketServer,SLOT(boardcasttomessaege(QString)));
    connect(mysql,SIGNAL(updatedataTableB(QString)),SocketServer,SLOT(boardcasttomessaege(QString)));
    connect(mysql,SIGNAL(updatedataTableC(QString)),SocketServer,SLOT(boardcasttomessaege(QString)));


    mysql->getEventandAlarm("getEventandAlarm");

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &mainwindows::updateDateTime);
    timer->start(1000); // Update every 1000 milliseconds (1 second)
}

QString mainwindows::getSystemDateTime() {
    QProcess process;
    process.start("sudo date");
    process.waitForFinished();
    QString dateTime = process.readAllStandardOutput().trimmed();
    return dateTime;
}
void mainwindows::updateDateTime() {
    QString dateTimeRaw = getSystemDateTime();
   qDebug() << "Raw Date and Time: " << dateTimeRaw;

    QDateTime dateTime = QDateTime::fromString(dateTimeRaw, "ddd MMM dd HH:mm:ss t yyyy");
    if (dateTime.isValid()) {
        QString formattedDateTime = dateTime.toString("HH:mm yyyy/MM/dd");
        QString datetime = QString("{"
                                 "\"objectName\"        :\"DateTime\","
                                 "\"formattedDateTime\"  :\"%1\""
                                 "}")
                          .arg(formattedDateTime);

//        qDebug() << "Formatted Date and Time: " << formattedDateTime;
        cppCommand(datetime);
    } else {
        qDebug() << "Failed to parse date and time!";
    }
}


void mainwindows::cppSubmitTextFiled(QString qmlJson){
    qDebug() << "cppSubmitTextFiled:" << qmlJson;
    QJsonDocument d = QJsonDocument::fromJson(qmlJson.toUtf8());
    QJsonObject command = d.object();
    QString getCommand =  QJsonValue(command["objectName"]).toString();
    QString getCommand2 =  QJsonValue(command["menuID"]).toString();
    if(getCommand.contains("UserSelectM")){
        QString userType = QJsonValue(command["userType"]).toString();
        bool userStatus = QJsonValue(command["userStatusMaster"]).toBool();
        QString selectMaster = QString("{"
                                       "\"objectName\"  :\"UserSelectM\","
                                       "\"userType\"    :\"%1\","
                                       "\"userStatusMaster\"  :\"%2\""
                                       "}")
                                .arg(userType).arg(userStatus);
//        qDebug() << "cppSubmitTextFiled UserM:" << selectMaster << userStatus << userType;
        cppCommand(selectMaster);
    }else if(getCommand.contains("UserSelectS")){
        QString userType = QJsonValue(command["userType"]).toString();
        bool userStatus = QJsonValue(command["userStatusSlave"]).toBool();
        QString selectSlave = QString("{"
                                      "\"objectName\"  :\"UserSelectS\","
                                      "\"userType\"    :\"%1\","
                                      "\"userStatusSlave\"  :\"%2\""
                                      "}").arg(userType).arg(userStatus);
//        qDebug() << "cppSubmitTextFiled UserS:" << selectSlave << userStatus << userType;
        cppCommand(selectSlave);
    }else if(getCommand.contains("valueVoltage")){
        int valueVoltage = QJsonValue(command["Voltage"]).toInt();
        QString Voltage = QString("{"
                                      "\"objectName\"   :\"valueVoltage\","
                                      "\"Voltage\"      :\"%1\""
                                      "}").arg(valueVoltage);
        qDebug() << "cppSubmitTextFiled Voltage:" << Voltage << valueVoltage;
        cppCommand(Voltage);
    }else if(getCommand.contains("valueSubstation")){
        QString valueSubstation = QJsonValue(command["Substation"]).toString();
        QString Substation = QString("{"
                                      "\"objectName\"   :\"valueSubstation\","
                                      "\"Substation\"      :\"%1\""
                                      "}").arg(valueSubstation);
        qDebug() << "cppSubmitTextFiled Substation:" << Substation << valueSubstation;
        cppCommand(Substation);
    }else if(getCommand.contains("valueDirection")){
        QString valueDirection = QJsonValue(command["Direction"]).toString();
        QString Direction = QString("{"
                                      "\"objectName\"   :\"valueDirection\","
                                      "\"Direction\"      :\"%1\""
                                      "}").arg(valueDirection);
        qDebug() << "cppSubmitTextFiled Direction:" << Direction << valueDirection;
        cppCommand(Direction);
    }else if(getCommand.contains("valueLineNo")){
        int valueLineNo = QJsonValue(command["LineNo"]).toInt();
        QString LineNo = QString("{"
                                      "\"objectName\"   :\"valueLineNo\","
                                      "\"LineNo\"      :\"%1\""
                                      "}").arg(valueLineNo);
        qDebug() << "cppSubmitTextFiled Direction:" << LineNo << valueLineNo;
        cppCommand(LineNo);
    }else if(getCommand.contains("textTime")){
        double textTime = QJsonValue(command["Time"]).toDouble();
        QString Time = QString("{"
                                      "\"objectName\"   :\"textTime\","
                                      "\"Time\"      :\"%1\""
                                      "}").arg(textTime);
        qDebug() << "cppSubmitTextFiled Time:" << Time << textTime;
        cppCommand(Time);
    }else if(getCommand.contains("textTime")){
        double textTime = QJsonValue(command["Time"]).toDouble();
        QString Time = QString("{"
                                      "\"objectName\"   :\"textTime\","
                                      "\"Time\"      :\"%1\""
                                      "}").arg(textTime);
        qDebug() << "cppSubmitTextFiled Time:" << Time << textTime;
        cppCommand(Time);
    }else if(getCommand.contains("distanceField")){
        int distanceField = QJsonValue(command["distanceField"]).toInt();
        QString distance = QString("{"
                                      "\"objectName\"   :\"distanceField\","
                                      "\"distanceField\"      :\"%1\""
                                      "}").arg(distanceField);
        qDebug() << "cppSubmitTextFiled distance:" << distance << distanceField;
//        cppCommand(distance);
    }else if(getCommand.contains("detailField")){
        double detailField = QJsonValue(command["detailField"]).toDouble();
        QString Details = QString("{"
                                      "\"objectName\"   :\"detailField\","
                                      "\"detailField\"      :\"%1\""
                                      "}").arg(Details);
        qDebug() << "cppSubmitTextFiled Details:" << Details << detailField;
//        cppCommand(Details);
    }else if (getCommand.contains("getDistanceDetailA")) {
        double distancecmd = QJsonValue(command["Distance"]).toDouble();
        QString detailcmd = QJsonValue(command["Detail"]).toString();
        QString phase = QJsonValue(command["PHASE"]).toString();
        QString DetailsAndDistance = QString("{"
                                             "\"objectName\":\"getDistanceDetailA\","
                                             "\"Distance\":\%1,"
                                             "\"Detail\":\"%2\","
                                             "\"PHASE\":\"%3\""
                                             "}").arg(distancecmd).arg(detailcmd).arg(phase);

        qDebug() << "cppSubmitTextFiled DetailsAndDistance:" << DetailsAndDistance << phase << distancecmd << detailcmd;
        getDistanceandDetailA(DetailsAndDistance);
    }else if (getCommand.contains("getDistanceDetailB")) {
        double distancecmd = QJsonValue(command["Distance"]).toDouble();
        QString detailcmd = QJsonValue(command["Detail"]).toString();
        QString phase = QJsonValue(command["PHASE"]).toString();
        QString DetailsAndDistance = QString("{"
                                             "\"objectName\":\"getDistanceDetailB\","
                                             "\"Distance\":\%1,"
                                             "\"Detail\":\"%2\","
                                             "\"PHASE\":\"%3\""
                                             "}").arg(distancecmd).arg(detailcmd).arg(phase);

        qDebug() << "cppSubmitTextFiled DetailsAndDistance:" << DetailsAndDistance << phase << distancecmd << detailcmd;
        getDistanceandDetailB(DetailsAndDistance);
    }else if (getCommand.contains("getDistanceDetailC")) {
        double distancecmd = QJsonValue(command["Distance"]).toDouble();
        QString detailcmd = QJsonValue(command["Detail"]).toString();
        QString phase = QJsonValue(command["PHASE"]).toString();
        QString DetailsAndDistance = QString("{"
                                             "\"objectName\":\"getDistanceDetailC\","
                                             "\"Distance\":\%1,"
                                             "\"Detail\":\"%2\","
                                             "\"PHASE\":\"%3\""
                                             "}").arg(distancecmd).arg(detailcmd).arg(phase);

        qDebug() << "cppSubmitTextFiled DetailsAndDistance:" << DetailsAndDistance << phase << distancecmd << detailcmd;
        getDistanceandDetailC(DetailsAndDistance);
    }else if (getCommand.contains("TaggingPhaseA")) {
        QString tableTaggingPhaseA = QJsonValue(command["tableTaggingPhaseA"]).toString();
        QString getTaggingPhaseA = QString("{"
                                             "\"objectName\":\"TaggingPhaseA\","
                                             "\"tableTaggingPhaseA\":\"%1\""
                                             "}").arg(tableTaggingPhaseA);

        qDebug() << "getTaggingPhaseA:" << getTaggingPhaseA;
        getTablePhaseA(getTaggingPhaseA);
    }else if (getCommand.contains("TaggingPhaseB")) {
        QString tableTaggingPhaseB = QJsonValue(command["tableTaggingPhaseB"]).toString();
        QString getTaggingPhaseB = QString("{"
                                           "\"objectName\":\"TaggingPhaseB\","
                                           "\"tableTaggingPhaseB\":\"%1\""
                                           "}").arg(tableTaggingPhaseB);

        qDebug() << "getTaggingPhaseB:" << tableTaggingPhaseB;
        getTablePhaseB(getTaggingPhaseB);
    }else if (getCommand.contains("TaggingPhaseC")) {
        QString tableTaggingPhaseC = QJsonValue(command["tableTaggingPhaseC"]).toString();
        QString getTaggingPhaseC = QString("{"
                                           "\"objectName\":\"TaggingPhaseC\","
                                           "\"tableTaggingPhaseC\":\"%1\""
                                           "}").arg(tableTaggingPhaseC);

        qDebug() << "getTaggingPhaseC:" << tableTaggingPhaseC;
        getTablePhaseC(getTaggingPhaseC);
    }else if (getCommand.contains("delectmysqlA")) {
        bool checkedStates = QJsonValue(command["checkedStates"]).toBool();
        int num_list = QJsonValue(command["num_listA"]).toInt();

        QString deletedtmySQLA = QString("{"
                                         "\"objectName\":\"delectmysqlA\","
                                          "\"checkedStates\":\"%1\","
                                          "\"num_listA\":\"%2\""
                                         "}").arg(checkedStates).arg(num_list);

        qDebug() << "delectmySQLA:" << deletedtmySQLA;
        deletedMySQLA(deletedtmySQLA);
    }else if (getCommand.contains("delectmysqlB")) {
        bool checkedStates = QJsonValue(command["checkedStates"]).toBool();
        int num_list = QJsonValue(command["num_listB"]).toInt();

        QString deletedtmySQLB = QString("{"
                                        "\"objectName\":\"delectmysqlB\","
                                        "\"checkedStates\":\"%1\","
                                        "\"num_listB\":\"%2\""
                                        "}").arg(checkedStates).arg(num_list);

        qDebug() << "delectmySQLB:" << deletedtmySQLB;
        deletedMySQLB(deletedtmySQLB);
    }else if (getCommand.contains("delectmysqlC")) {
        bool checkedStates = QJsonValue(command["checkedStates"]).toBool();
        int num_list = QJsonValue(command["num_listC"]).toInt();

        QString deletedtmySQLC = QString("{"
                                        "\"objectName\":\"delectmysqlC\","
                                        "\"checkedStates\":\"%1\","
                                        "\"num_listC\":\"%2\""
                                        "}").arg(checkedStates).arg(num_list);

        qDebug() << "delectmySQLC:" << deletedtmySQLC;
        deletedMySQLC(deletedtmySQLC);
    }else if (getCommand.contains("UpdatePhaseA")) {
        QString updatetablePhaseA = QJsonValue(command["updatetablePhaseA"]).toString();
        QString getupdatePhaseA = QString("{"
                                          "\"objectName\":\"UpdatePhaseA\","
                                          "\"updatetablePhaseA\":\"%1\""
                                          "}").arg(updatetablePhaseA);

        qDebug() << "getupdatePhaseA:" << getupdatePhaseA;
        updateTablePhaseA(getupdatePhaseA);
    }else if (getCommand.contains("UpdatePhaseB")) {
        QString updatetablePhaseB = QJsonValue(command["updatetablePhaseB"]).toString();
        QString getupdatePhaseB = QString("{"
                                          "\"objectName\":\"UpdatePhaseB\","
                                          "\"updatetablePhaseB\":\"%1\""
                                          "}").arg(updatetablePhaseB);

        qDebug() << "getupdatePhaseB:" << getupdatePhaseB;
        updateTablePhaseA(getupdatePhaseB);
    }else if (getCommand.contains("UpdatePhaseC")) {
        QString updatetablePhaseC = QJsonValue(command["updatetablePhaseC"]).toString();
        QString getupdatePhaseC = QString("{"
                                          "\"objectName\":\"UpdatePhaseC\","
                                          "\"updatetablePhaseC\":\"%1\""
                                          "}").arg(updatetablePhaseC);

        qDebug() << "getupdatePhaseA:" << getupdatePhaseC;
        updateTablePhaseA(getupdatePhaseC);
    }
}



