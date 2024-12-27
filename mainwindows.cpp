#include "mainwindows.h"


mainwindows::mainwindows(QObject *parent) : QObject(parent){
    qDebug() << "hello windows";

    SocketServer = new ChatServer(1234);
    mysql = new Database("ITouch", "pi", "rpi3!2024", "localhost", this);
    connect(mysql, SIGNAL(eventmsg(QString)), SocketServer, SLOT(boardcasttomessaege(QString)));
    connect(this, SIGNAL(getDistanceandDetail(QString)), mysql, SLOT(DistanceandDetailPhaseA(QString)));
    connect(this, SIGNAL(getTablePhase(QString)), mysql, SLOT(getMySqlPhase(QString)));
    connect(mysql, SIGNAL(cmdmsg(QString)), SocketServer, SLOT(boardcasttomessaege(QString)));
    connect(this, SIGNAL(deletedMySQL(QString)), mysql, SLOT(deletedDataMySQL(QString)));
    connect(mysql,SIGNAL(deletedmydatabase(QString)),SocketServer,SLOT(boardcasttomessaege(QString)));

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
//    qDebug() << "Raw Date and Time: " << dateTimeRaw;

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
        getDistanceandDetail(DetailsAndDistance);
    }else if (getCommand.contains("TaggingPhaseA")) {
        QString tableTaggingPhaseA = QJsonValue(command["tableTaggingPhaseA"]).toString();
        QString getTaggingPhaseA = QString("{"
                                             "\"objectName\":\"TaggingPhaseA\","
                                             "\"tableTaggingPhaseA\":\"%1\""
                                             "}").arg(tableTaggingPhaseA);

        qDebug() << "getTaggingPhaseA:" << getTaggingPhaseA;
        getTablePhase(getTaggingPhaseA);
    }else if (getCommand.contains("delectmysql")) {
        bool checkedStates = QJsonValue(command["checkedStates"]).toBool();
        int list_device = QJsonValue(command["list_device"]).toInt();

        QString deletedtmySQL = QString("{"
                                         "\"objectName\":\"delectmysql\","
                                          "\"checkedStates\":\"%1\","
                                          "\"list_device\":\"%2\""
                                         "}").arg(checkedStates).arg(list_device);

        qDebug() << "delectmySQL:" << deletedtmySQL;
        deletedMySQL(deletedtmySQL);
    }

}



