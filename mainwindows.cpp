#include "mainwindows.h"

mainwindows::mainwindows(QObject *parent) : QObject(parent){
    qDebug() << "hello windows";
    system("sudo pigpiod");
    QThread::msleep(100);
    system("sudo pigs p 13 255");

    SocketServer = new ChatServer(1234);
    mysql = new Database("ITouch", "pi", "rpi3!2024", "localhost", this);
    client = new SocketClient();
    reconnectTimer = new QTimer();
    Timer = new QTimer();

    connect(reconnectTimer,SIGNAL(timeout()),this,SLOT(reconnectTimerTimeout()));
    connect(Timer,SIGNAL(timeout()),this,SLOT(connectTimeOut()));
    connect(mysql, SIGNAL(eventmsg(QString)), SocketServer, SLOT(boardcasttomessaege(QString)));
    connect(this, SIGNAL(updateUser(QString)), mysql, SLOT(userMode(QString)));
//    connect(this, SIGNAL(updateRelay(QString)), mysql, SLOT(storeStatusAux(QString)));
    connect(this, SIGNAL(getDistanceandDetailA(QString)), mysql, SLOT(DistanceandDetailPhaseA(QString)));
    connect(this, SIGNAL(getDistanceandDetailB(QString)), mysql, SLOT(DistanceandDetailPhaseB(QString)));
    connect(this, SIGNAL(getDistanceandDetailC(QString)), mysql, SLOT(DistanceandDetailPhaseC(QString)));
    connect(this, SIGNAL(getTablePhaseA(QString)), mysql, SLOT(getMySqlPhaseA(QString)));
    connect(this, SIGNAL(getTablePhaseB(QString)), mysql, SLOT(getMySqlPhaseB(QString)));
    connect(this, SIGNAL(getTablePhaseC(QString)), mysql, SLOT(getMySqlPhaseC(QString)));
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
//    connect(this,SIGNAL(getEditDatafromMySQLA(QString)),mysql,SLOT(closeMySQL(QString)));
    connect(mysql,SIGNAL(updataEditDataA(QString)),SocketServer,SLOT(boardcasttomessaege(QString)));
    connect(this,SIGNAL(parameterMarginA(QString)),mysql,SLOT(configParemeterMarginA(QString)));
    connect(mysql,SIGNAL(listOfMarginA(QString)),SocketServer,SLOT(boardcasttomessaege(QString)));
//    connect(this,SIGNAL(parameterThreshold(QString)),mysql,SLOT(configParemeterThreshold(QString)));
    connect(mysql,SIGNAL(updateThresholdA(QString)),SocketServer,SLOT(boardcasttomessaege(QString)));
    connect(mysql,SIGNAL(updateThresholdB(QString)),SocketServer,SLOT(boardcasttomessaege(QString)));
    connect(mysql,SIGNAL(updateThresholdC(QString)),SocketServer,SLOT(boardcasttomessaege(QString)));
    connect(this,SIGNAL(getDataThreshold()),mysql,SLOT(getThreshold()));
    connect(this,SIGNAL(settingGeneral()),mysql,SLOT(getSettingInfo()));
    connect(mysql,SIGNAL(UpdateSettingInfo(QString)),SocketServer,SLOT(boardcasttomessaege(QString)));
    connect(this,SIGNAL(preiodicSetting()),mysql,SLOT(getpreiodicInfo()));
    connect(mysql,SIGNAL(UpdatepreiodicInfo(QString)),SocketServer,SLOT(boardcasttomessaege(QString)));
//    connect(this,SIGNAL(updateTimer(QString)),mysql,SLOT(getUpdatePeriodic(QString)));
//    connect(this,SIGNAL(updateWeekly(QString)),mysql,SLOT(getUpdateWeekly(QString)));
//    connect(this, SIGNAL(rawdataPlot(QString)), mysql, SLOT(getRawData(QString)));
//    connect(mysql,SIGNAL(packageRawData(QString)),SocketServer,SLOT(boardcasttomessaege(QString)));
    connect(this, SIGNAL(cursorDistance(QString)), mysql, SLOT(getPositionDistance(QString)));
    connect(mysql,SIGNAL(cursorPosition(QString)),SocketServer,SLOT(boardcasttomessaege(QString)));
    connect(this, SIGNAL(moveCursor(QString)), mysql, SLOT(controlCursor(QString)));
    connect(mysql,SIGNAL(positionCursorChange(QString)),SocketServer,SLOT(boardcasttomessaege(QString)));
    connect(this, SIGNAL(changeDistanceRange(QString)), mysql, SLOT(getChangeDistance(QString)));
    connect(mysql,SIGNAL(updatanewdistance(QString)),SocketServer,SLOT(boardcasttomessaege(QString)));
//    connect(this, SIGNAL(changeDistanceRange(QString)), mysql, SLOT(getChangeDistance(QString)));
    connect(this, SIGNAL(sendToSocket(QString)), client, SLOT(sendMessage(QString)));
    connect(this,SIGNAL(taggingpoint(QString)),mysql,SLOT(taggingpoint(QString)));
    connect(mysql,SIGNAL(showtaggingpoint(QString)),SocketServer,SLOT(boardcasttomessaege(QString)));
//    connect(this,SIGNAL(clearDisplay(QString)),mysql,SLOT(cleanDataInGraph(QString)));
//    connect(this,SIGNAL(clearDisplay(QString)),SocketServer,SLOT(boardcasttomessaege(QString)));  //SetNetworkSNMP
    connect(this,SIGNAL(settingNetWorkandSNMP(QString)),mysql,SLOT(SettingNetworkSNMP(QString)));
//    connect(this,SIGNAL(settingdisplay(QString)),mysql,SLOT(SettingDisplay(QString)));
    connect(mysql,SIGNAL(updateDisplaySetting(QString)),SocketServer,SLOT(boardcasttomessaege(QString)));
    connect(this,SIGNAL(plotingDataPhaseA(QString)),SocketServer,SLOT(boardcasttomessaege(QString)));
    connect(this,SIGNAL(plotingDataPhaseB(QString)),SocketServer,SLOT(boardcasttomessaege(QString)));
    connect(this,SIGNAL(plotingDataPhaseC(QString)),SocketServer,SLOT(boardcasttomessaege(QString)));
//    connect(this,SIGNAL(settingdisplay(QString)),SocketServer,SLOT(boardcasttomessaege(QString)));
//    connect(this,SIGNAL(getsettingdisplay()),mysql,SLOT(GetSettingDisplay()));
//    connect(mysql,SIGNAL(settingDisplayInfo(QString)),SocketServer,SLOT(boardcasttomessaege(QString)));
//    connect(mysql,SIGNAL(settingDisplayInfo(QString)),this,SLOT(calculate(QString)));
//    connect(mysql,SIGNAL(updateThresholdA(QString)),this,SLOT(calculate(QString)));
    connect(this,SIGNAL(settingdisplay(QString)),this,SLOT(calculate(QString)));

//------------------------------client command to Display----------------------------------//displaysetting
    connect(client,SIGNAL(newCommandProcess(QString)),this,SLOT(ServerCommand(QString)));
    connect(client,SIGNAL(newCommandProcess(QString)),this,SLOT(cppSubmitTextFiled(QString)));
    connect(client,SIGNAL(newCommandProcess(QString)),SocketServer,SLOT(boardcasttomessaege(QString)));

//------------------------------Send command to client----------------------------------//
    connect(this, SIGNAL(rawdataPlot(QString)),client, SLOT(sendMessage(QString)));
    connect(this,SIGNAL(clearPatternGraph(QString)),client, SLOT(sendMessage(QString)));
    connect(this,SIGNAL(clearDisplay(QString)),client, SLOT(sendMessage(QString)));
    connect(mysql,SIGNAL(SetNetworkSNMP(QString)),client,SLOT(sendMessage(QString)));
    connect(this,SIGNAL(settingdisplay(QString)),client,SLOT(sendMessage(QString)));
    connect(this,SIGNAL(parameterThreshold(QString)),client,SLOT(sendMessage(QString)));
    connect(this,SIGNAL(sendMessage(QString)),client,SLOT(sendMessage(QString)));
    connect(this,SIGNAL(updateWeekly(QString)),client,SLOT(sendMessage(QString)));
    connect(this,SIGNAL(updateTimer(QString)),client,SLOT(sendMessage(QString)));
    connect(this, SIGNAL(updateRelay(QString)),client,SLOT(sendMessage(QString)));


        serverAddress = "192.168.10.192";
        serverPort = 5520;
        qDebug() << "serverAddress:" << serverAddress << " serverPort:" << serverPort;
        client->createConnection(serverAddress,serverPort);

    if (client->isConnected == true){
        connectToPLC();
        qDebug() << "TimeOutTimer timer->stop()";
    }

    mysql->getEventandAlarm("getEventandAlarm");  //rawdataPlot
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &mainwindows::updateDateTime);
    timer->start(1000); // Update every 1000 milliseconds (1 second)
    reconnectTimer->start(3000);
    Timer->start(100);
}

void mainwindows::reconnectTimerTimeout(){
    if (client->isConnected == false){
    if ((serverAddress != "") & (serverPort > 0) & (serverPort < 65536)){
        isVersion= false;
        cppCommand(isVersion);
        client->createConnection(serverAddress,serverPort);
    }
//    qDebug() << "reconnectTimerTimeout" << isVersion;

}
if (client->isConnected == true){

        if(!isVersion){
            connectToPLC();
            qDebug() << "isVersion" << isVersion;
        }
    }
cppCommand(isVersion);
//qDebug() << "reconnectTimerTimeout" << isVersion;
//qDebug() << "isVersion" << isVersion;
}

void mainwindows::connectTimeOut(){
if (client->isConnected == true){
        if(!isVersion){
            connectToPLC();
            Timer->stop();
            cppCommand(isVersion);
        }
    }
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
//   qDebug() << "Raw Date and Time: " << dateTimeRaw;

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
//        qDebug() << "Failed to parse date and time!";
    }
}


void mainwindows::cppSubmitTextFiled(QString qmlJson){
    qDebug() << "cppSubmitTextFiled:" << qmlJson;
    QJsonDocument d = QJsonDocument::fromJson(qmlJson.toUtf8());
    QJsonObject command = d.object();
    QString getCommand =  QJsonValue(command["objectName"]).toString();
    QString getCommand2 =  QJsonValue(command["menuID"]).toString();
    qDebug() << "Raw JSON:" << qmlJson;
    qDebug() << "Parsed JSON:" << command;
    qDebug() << "getCommand:" << getCommand;
    qDebug() << "editsSNMPServer type:" << command.value("editsSNMPServer").type();
    qDebug() << "editsSNMPServer value:" << command.value("editsSNMPServer").toString();

    if(qmlJson == "testRawData"){

        rawdataPlot("testRawData");
    }else if(getCommand.contains("UserSelectM")){
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
        emit updateUser(selectMaster);
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
        emit updateUser(selectSlave);
    }else if(getCommand.contains("statusOperate")){
        bool activeStatus = QJsonValue(command["LFLOPERATE"]).toBool();
        QString auxiliary = QString("{"
                                      "\"objectName\"  :\"statusOperate\","
                                      "\"LFLOPERATE\"  :\"%1\""
                                      "}").arg(activeStatus);
        qDebug() << "auxiliary:" << auxiliary;
        emit updateRelay(auxiliary);
    }else if(getCommand.contains("statusFail")){
        bool activeStatus = QJsonValue(command["LFLFAIL"]).toBool();
        QString auxiliary = QString("{"
                                      "\"objectName\"  :\"statusFail\","
                                      "\"LFLFAIL\"  :\"%1\""
                                      "}").arg(activeStatus);
        emit updateRelay(auxiliary);
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
    }else if(getCommand.contains("updatetextTime")){
        double timer = QJsonValue(command["Time"]).toDouble();
        QString timerupdate = QString("{"
                                      "\"objectName\"   :\"updateTime\","
                                      "\"Time\"      :%1"
                                      "}").arg(timer);
        qDebug() << "cppSubmitTextFiled Time:" << timerupdate << timer;
        emit updateTimer(timerupdate);
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
        emit getDistanceandDetailA(DetailsAndDistance);
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
        emit getDistanceandDetailB(DetailsAndDistance);
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
        emit getDistanceandDetailC(DetailsAndDistance);
    }else if (getCommand.contains("TaggingPhaseA")) {
        QString tableTaggingPhaseA = QJsonValue(command["tableTaggingPhaseA"]).toString();
        QString getTaggingPhaseA = QString("{"
                                             "\"objectName\":\"TaggingPhaseA\","
                                             "\"tableTaggingPhaseA\":\"%1\""
                                             "}").arg(tableTaggingPhaseA);

        qDebug() << "getTaggingPhaseA:" << getTaggingPhaseA;
        emit getTablePhaseA(getTaggingPhaseA);
    }else if (getCommand.contains("TaggingPhaseB")) {
        QString tableTaggingPhaseB = QJsonValue(command["tableTaggingPhaseB"]).toString();
        QString getTaggingPhaseB = QString("{"
                                           "\"objectName\":\"TaggingPhaseB\","
                                           "\"tableTaggingPhaseB\":\"%1\""
                                           "}").arg(tableTaggingPhaseB);

        qDebug() << "getTaggingPhaseB:" << tableTaggingPhaseB;
        emit getTablePhaseB(getTaggingPhaseB);
    }else if (getCommand.contains("TaggingPhaseC")) {
        QString tableTaggingPhaseC = QJsonValue(command["tableTaggingPhaseC"]).toString();
        QString getTaggingPhaseC = QString("{"
                                           "\"objectName\":\"TaggingPhaseC\","
                                           "\"tableTaggingPhaseC\":\"%1\""
                                           "}").arg(tableTaggingPhaseC);

        qDebug() << "getTaggingPhaseC:" << tableTaggingPhaseC;
        emit getTablePhaseC(getTaggingPhaseC);
    }else if (getCommand.contains("delectmysqlA")) {
        bool checkedStates = QJsonValue(command["checkedStates"]).toBool();
        int num_list = QJsonValue(command["num_listA"]).toInt();

        QString deletedtmySQLA = QString("{"
                                         "\"objectName\":\"delectmysqlA\","
                                          "\"checkedStates\":\"%1\","
                                          "\"num_listA\":\"%2\""
                                         "}").arg(checkedStates).arg(num_list);

        qDebug() << "delectmySQLA:" << deletedtmySQLA;
        emit deletedMySQLA(deletedtmySQLA);
    }else if (getCommand.contains("delectmysqlB")) {
        bool checkedStates = QJsonValue(command["checkedStates"]).toBool();
        int num_list = QJsonValue(command["num_listB"]).toInt();

        QString deletedtmySQLB = QString("{"
                                        "\"objectName\":\"delectmysqlB\","
                                        "\"checkedStates\":\"%1\","
                                        "\"num_listB\":\"%2\""
                                        "}").arg(checkedStates).arg(num_list);

        qDebug() << "delectmySQLB:" << deletedtmySQLB;
        emit deletedMySQLB(deletedtmySQLB);
    }else if (getCommand.contains("delectmysqlC")) {
        bool checkedStates = QJsonValue(command["checkedStates"]).toBool();
        int num_list = QJsonValue(command["num_listC"]).toInt();

        QString deletedtmySQLC = QString("{"
                                        "\"objectName\":\"delectmysqlC\","
                                        "\"checkedStates\":\"%1\","
                                        "\"num_listC\":\"%2\""
                                        "}").arg(checkedStates).arg(num_list);

        qDebug() << "delectmySQLC:" << deletedtmySQLC;
        emit deletedMySQLC(deletedtmySQLC);
    }else if (getCommand.contains("UpdatePhaseA")) {
        QString updatetablePhaseA = QJsonValue(command["updatetablePhaseA"]).toString();
        QString getupdatePhaseA = QString("{"
                                          "\"objectName\":\"UpdatePhaseA\","
                                          "\"updatetablePhaseA\":\"%1\""
                                          "}").arg(updatetablePhaseA);

        qDebug() << "getupdatePhaseA:" << getupdatePhaseA;
        emit updateTablePhaseA(getupdatePhaseA);
    }else if (getCommand.contains("UpdatePhaseB")) {
        QString updatetablePhaseB = QJsonValue(command["updatetablePhaseB"]).toString();
        QString getupdatePhaseB = QString("{"
                                          "\"objectName\":\"UpdatePhaseB\","
                                          "\"updatetablePhaseB\":\"%1\""
                                          "}").arg(updatetablePhaseB);

        qDebug() << "getupdatePhaseB:" << getupdatePhaseB;
        emit updateTablePhaseA(getupdatePhaseB);
    }else if (getCommand.contains("UpdatePhaseC")) {
        QString updatetablePhaseC = QJsonValue(command["updatetablePhaseC"]).toString();
        QString getupdatePhaseC = QString("{"
                                          "\"objectName\":\"UpdatePhaseC\","
                                          "\"updatetablePhaseC\":\"%1\""
                                          "}").arg(updatetablePhaseC);

        qDebug() << "getupdatePhaseA:" << getupdatePhaseC;
        emit updateTablePhaseA(getupdatePhaseC);
    }else if (getCommand.contains("editDataPhaseA")) {
        double checkedStates = QJsonValue(command["checkedStates"]).toDouble();
        QString phase = QJsonValue(command["PHASE"]).toString();
        int IndexNum = QJsonValue(command["num_listA"]).toInt();
        QString EditDatalist = QString("{"
                                             "\"objectName\":\"editDataPhaseA\","
                                             "\"IndexNum\":%1,"
                                             "\"PHASE\":\"%2\""
                                             "}").arg(IndexNum).arg(phase);

        qDebug() << "Debug editDataPhaseA:" << EditDatalist << phase << checkedStates;
        emit getEditDatafromMySQLA(EditDatalist);
    }else if (getCommand.contains("marginCountA")) {
        int marginA = QJsonValue(command["valueMarginA"]).toInt();
        QString phase = QJsonValue(command["PHASE"]).toString();
        QString parameterA = QString("{"
                                         "\"objectName\":\"marginCountA\","
                                         "\"marginA\":%1,"
                                         "\"phase\":\"%2\""
                                         "}").arg(marginA).arg(phase);

        qDebug() << "Debug marginCountA:" << marginA << phase;
        emit parameterMarginA(parameterA);
     }else if (getCommand.contains("textPhaseA")) {
        int thresholdA = QJsonValue(command["thresholdA"]).toInt();
        QString phase = QJsonValue(command["PHASE"]).toString();
        QString paraThresholdA = QString("{"
                                         "\"objectName\":\"thresholdA\","
                                         "\"thresholdInitA\":%1,"
                                         "\"phase\":\"%2\""
                                         "}").arg(thresholdA).arg(phase);

        qDebug() << "textPhaseA:" << thresholdA << phase;
        emit parameterThreshold(paraThresholdA);
     }else if (getCommand.contains("textPhaseB")) {
        int thresholdB = QJsonValue(command["thresholdB"]).toInt();
        QString phase = QJsonValue(command["PHASE"]).toString();
        QString paraThresholdB = QString("{"
                                         "\"objectName\":\"thresholdB\","
                                         "\"thresholdInitB\":%1,"
                                         "\"phase\":\"%2\""
                                         "}").arg(thresholdB).arg(phase);

        qDebug() << "textPhaseB:" << thresholdB << phase;
        emit parameterThreshold(paraThresholdB);
     }else if (getCommand.contains("textPhaseC")) {
        int thresholdC = QJsonValue(command["thresholdC"]).toInt();
        QString phase = QJsonValue(command["PHASE"]).toString();
        QString paraThresholdC = QString("{"
                                         "\"objectName\":\"thresholdC\","
                                         "\"thresholdInitC\":%1,"
                                         "\"phase\":\"%2\""
                                         "}").arg(thresholdC).arg(phase);

        qDebug() << "textPhaseC:" << thresholdC << phase;
        emit parameterThreshold(paraThresholdC);
     }else if (qmlJson == "getCurrentThreshold") {
        emit getDataThreshold();
     }else if (qmlJson == "SettingGeneral") {
        emit settingGeneral();
     }else if (qmlJson == "getpreiodicInfo") {
        emit preiodicSetting();
     }else if (getCommand.contains("date")) {
        bool monday = command.contains("Monday") ? QJsonValue(command["Monday"]).toBool() : false;
        bool tuesday = command.contains("Tuesday") ? QJsonValue(command["Tuesday"]).toBool() : false;
        bool wednesday = command.contains("Wednesday") ? QJsonValue(command["Wednesday"]).toBool() : false;
        bool thursday = command.contains("Thursday") ? QJsonValue(command["Thursday"]).toBool() : false;
        bool friday = command.contains("Friday") ? QJsonValue(command["Friday"]).toBool() : false;
        bool saturday = command.contains("Saturday") ? QJsonValue(command["Saturday"]).toBool() : false;
        bool sunday = command.contains("Sunday") ? QJsonValue(command["Sunday"]).toBool() : false;

        qDebug() << "date:" << monday << tuesday << wednesday << thursday << friday << saturday << sunday;

        if (command.contains("Monday")) {
            QString weeklyMonday = QString("{"
                                            "\"objectName\"     :\"date\","
                                            "\"Monday\"         :\"%1\""
                                            "}").arg(monday ? "1" : "0"); // Convert bool to string "1" or "0"
            qDebug() << "weeklyMonday:" << weeklyMonday << monday;
            emit updateWeekly(weeklyMonday);
        } else if (command.contains("Tuesday")) {
            QString weeklyTuesday = QString("{"
                                             "\"objectName\"     :\"date\","
                                             "\"Tuesday\"        :\"%1\""
                                             "}").arg(tuesday ? "1" : "0");
            qDebug() << "weeklyTuesday:" << weeklyTuesday << tuesday;
            emit updateWeekly(weeklyTuesday);
        } else if (command.contains("Wednesday")) {
            QString weeklyWednesday = QString("{"
                                               "\"objectName\"     :\"date\","
                                               "\"Wednesday\"      :\"%1\""
                                               "}").arg(wednesday ? "1" : "0");
            qDebug() << "weeklyWednesday:" << weeklyWednesday << wednesday;
            emit updateWeekly(weeklyWednesday);
        } else if (command.contains("Thursday")) {
            QString weeklyThursday = QString("{"
                                              "\"objectName\"     :\"date\","
                                              "\"Thursday\"       :\"%1\""
                                              "}").arg(thursday ? "1" : "0");
            qDebug() << "weeklyThursday:" << weeklyThursday << thursday;
            emit updateWeekly(weeklyThursday);
        } else if (command.contains("Friday")) {
            QString weeklyFriday = QString("{"
                                            "\"objectName\"     :\"date\","
                                            "\"Friday\"         :\"%1\""
                                            "}").arg(friday ? "1" : "0");
            qDebug() << "weeklyFriday:" << weeklyFriday << friday;
            emit updateWeekly(weeklyFriday);
        } else if (command.contains("Saturday")) {
            QString weeklySaturday = QString("{"
                                              "\"objectName\"     :\"date\","
                                              "\"Saturday\"       :\"%1\""
                                              "}").arg(saturday ? "1" : "0");
            qDebug() << "weeklySaturday:" << weeklySaturday << saturday;
            emit updateWeekly(weeklySaturday);
        } else if (command.contains("Sunday")) {
            QString weeklySunday = QString("{"
                                            "\"objectName\"     :\"date\","
                                            "\"Sunday\"         :\"%1\""
                                            "}").arg(sunday ? "1" : "0");
            qDebug() << "weeklySunday:" << weeklySunday << sunday;
            emit updateWeekly(weeklySunday);
        }


     }else if (getCommand.contains("distance") && (command.contains("distance"))) {
        double distance = QJsonValue(command["distance"]).toDouble();
        QString positionDistance = QString("{"
                                        "\"objectName\"     :\"distance\","
                                        "\"distance\"         :\"%1\""
                                        "}").arg(distance);
        qDebug() << "positionDistance:" << positionDistance << distance;
        emit cursorDistance(positionDistance);
    }else if (getCommand.contains("decreaseValue")) {
        double decreaseValue = QJsonValue(command["decreaseValue"]).toDouble();
        QString movetoleft = QString("{"
                                        "\"objectName\"     :\"decreaseValue\","
                                        "\"decreaseValue\"         :%1"
                                        "}").arg(decreaseValue);
        qDebug() << "movetoleft:" << movetoleft << decreaseValue;
        emit moveCursor(movetoleft);
    }else if (getCommand.contains("increaseValue")) {
        double increaseValue = QJsonValue(command["increaseValue"]).toDouble();
        QString movetoright = QString("{"
                                        "\"objectName\"     :\"increaseValue\","
                                        "\"increaseValue\"         :%1"
                                        "}").arg(increaseValue);
        qDebug() << "movetoleft:" << movetoright << increaseValue;
        emit moveCursor(movetoright);
    }else if (getCommand.contains("getDatabuttonPhaseA")) {
        QString rawdataA = QJsonValue(command["rawdataA"]).toString();
        QString getRawDataPhaseA = QString("{"
                                        "\"objectName\"     :\"getDatabuttonPhaseA\","
                                        "\"rawdataA\"         :\"%1\""
                                        "}").arg(rawdataA);
        qDebug() << "getRawDataPhaseA:" << getRawDataPhaseA << rawdataA;
        emit rawdataPlot(getRawDataPhaseA);
    } else if (getCommand.contains("getDatabuttonPhaseB")) {
        QString rawdataB = QJsonValue(command["rawdataB"]).toString();
        QString getRawDataPhaseB = QString("{"
                                        "\"objectName\"     :\"getDatabuttonPhaseB\","
                                        "\"rawdataB\"         :\"%1\""
                                        "}").arg(rawdataB);
        qDebug() << "getpatternPhaseB:" << getRawDataPhaseB << rawdataB;
        emit rawdataPlot(getRawDataPhaseB);
    } else if (getCommand.contains("getDatabuttonPhaseC")) {
        QString rawdataC = QJsonValue(command["rawdataC"]).toString();
        QString getRawDataPhaseC = QString("{"
                                        "\"objectName\"     :\"getDatabuttonPhaseC\","
                                        "\"rawdataC\"         :\"%1\""
                                        "}").arg(rawdataC);
        qDebug() << "getpatternPhaseC:" << getRawDataPhaseC << rawdataC;
        emit rawdataPlot(getRawDataPhaseC);
    }else if (getCommand.contains("getpatternPhaseA")) {
        QString patternA = QJsonValue(command["patternA"]).toString();
        QString getpatternPhaseA = QString("{"
                                        "\"objectName\"     :\"getpatternPhaseA\","
                                        "\"getpatternA\"         :\"%1\""
                                        "}").arg(patternA);
        qDebug() << "getpatternPhaseA:" << getpatternPhaseA << patternA;
        emit rawdataPlot(getpatternPhaseA);
    }else if (getCommand.contains("getpatternPhaseB")) {
        QString patternB = QJsonValue(command["patternB"]).toString();
        QString getpatternPhaseB = QString("{"
                                        "\"objectName\"     :\"getpatternPhaseB\","
                                        "\"getpatternB\"         :\"%1\""
                                        "}").arg(patternB);
        qDebug() << "getpatternPhaseB:" << getpatternPhaseB << patternB;
        emit rawdataPlot(getpatternPhaseB);
    }else if (getCommand.contains("getpatternPhaseC")) {
        QString patternC = QJsonValue(command["patternC"]).toString();
        QString getpatternPhaseC = QString("{"
                                        "\"objectName\"     :\"getpatternPhaseC\","
                                        "\"getpatternC\"         :\"%1\""
                                        "}").arg(patternC);
        qDebug() << "getpatternPhaseC:" << getpatternPhaseC << patternC;
        emit rawdataPlot(getpatternPhaseC);
    }else if (getCommand.contains("ClearDisplayPhaseA")) { //CLear Display Phase A
        QString patternA = QJsonValue(command["patternA"]).toString();
        QString clearpatternPhaseA = QString("{"
                                        "\"objectName\"     :\"clearpatternPhaseA\","
                                        "\"clearpatternA\"         :\"%1\""
                                        "}").arg(patternA);
        qDebug() << "clearpatternPhaseA:" << clearpatternPhaseA << patternA;
        emit clearDisplay(clearpatternPhaseA);
    }else if (getCommand.contains("ClearDisplayPhaseB")) { //CLear Display Phase B
        QString patternB = QJsonValue(command["patternB"]).toString();
        QString clearpatternPhaseB = QString("{"
                                        "\"objectName\"     :\"clearpatternPhaseB\","
                                        "\"clearpatternB\"         :\"%1\""
                                        "}").arg(patternB);
        qDebug() << "clearpatternPhaseB:" << clearpatternPhaseB << patternB;
        emit clearDisplay(clearpatternPhaseB);
    }else if (getCommand.contains("ClearDisplayPhaseC")) { //CLear Display Phase C
        QString patternC = QJsonValue(command["patternC"]).toString();
        QString clearpatternPhaseC = QString("{"
                                        "\"objectName\"     :\"clearpatternPhaseC\","
                                        "\"clearpatternC\"         :\"%1\""
                                        "}").arg(patternC);
        qDebug() << "clearpatternPhaseC:" << clearpatternPhaseC << patternC;
        emit clearDisplay(clearpatternPhaseC);
    }else if (getCommand.contains("clearDatabuttonPhaseA")) { //CLear Display Phase A
        QString dataA = QJsonValue(command["rawdataA"]).toString();
        QString cleardataA = QString("{"
                                        "\"objectName\"     :\"clearDatabuttonPhaseA\","
                                        "\"cleardataA\"         :\"%1\""
                                        "}").arg(dataA);
        qDebug() << "clearDatabuttonPhaseA:" << cleardataA << dataA;
        emit clearDisplay(cleardataA);
    }else if (getCommand.contains("clearDatabuttonPhaseB")) { //CLear Display Phase B
        QString dataB = QJsonValue(command["rawdataB"]).toString();
        QString cleardataB = QString("{"
                                        "\"objectName\"     :\"clearDatabuttonPhaseB\","
                                        "\"cleardataB\"         :\"%1\""
                                        "}").arg(dataB);
        qDebug() << "clearDatabuttonPhaseB:" << cleardataB << dataB;
        emit clearDisplay(cleardataB);
    }else if (getCommand.contains("clearDatabuttonPhaseC")) { //CLear Display Phase C
        QString dataC = QJsonValue(command["patternC"]).toString();
        QString cleardataC = QString("{"
                                        "\"objectName\"     :\"clearDatabuttonPhaseC\","
                                        "\"cleardataC\"         :\"%1\""
                                        "}").arg(dataC);
        qDebug() << "clearpatternPhaseC:" << cleardataC << dataC;
        emit clearDisplay(cleardataC);
    }else if (getCommand.contains("rangedistance")) {
        double range = QJsonValue(command["rangedistance"]).toDouble();
        QString rangeChange = QString("{"
                                        "\"objectName\"     :\"rangedistance\","
                                        "\"rangedistance\"         :%1"
                                        "}").arg(range);
        qDebug() << "rangeChange:" << rangeChange << range;
        emit changeDistanceRange(rangeChange);
    }else if (getCommand.contains("taggingdata")) {
        int tagging = QJsonValue(command["checklist"]).toInt();
        bool statuslist = QJsonValue(command["statuslist"]).toBool();

        QString taggingdata = QString("{"
                                      "\"objectName\":\"taggingdata\","
                                      "\"checklist\":%1,"
                                      "\"statuslist\":%2"
                                      "}")
                                 .arg(tagging)
                                 .arg(statuslist ? "true" : "false");

        qDebug() << "taggingdata:" << taggingdata << "tagging:" << tagging << "statuslist:" << statuslist;
        emit taggingpoint(taggingdata);
    }else if (getCommand.contains("editSettingNetwork")){
        QString IPaddress = command.value("editsIPAddress").toString();
        QString GateWsys = command.value("editsGateWays").toString();
        qDebug() << "IPaddress:" << IPaddress << "GateWsys:" << GateWsys;

        QString settingNetwork = QString("{"
                                          "\"objectName\":\"updateSettingNetwork\","
                                          "\"ipaddress\":\"%1\","
                                          "\"gateway\":\"%2\""
                                          "}")
                                     .arg(IPaddress)
                                     .arg(GateWsys);

        qDebug() << "settingNetwork:" << settingNetwork;
         emit settingNetWorkandSNMP(settingNetwork);
    }else if (getCommand == "editSetSNMPServerIP") {
        QString snmpIP = command.value("editsSNMPServer").toString();
        qDebug() << "snmpIP:" << snmpIP;

        QString setIPSNMP = QString("{"
                                     "\"objectName\":\"updateSettingNetwork\","
                                     "\"ip_snmp\":\"%1\""
                                     "}")
                            .arg(snmpIP);

        qDebug() << "setIPSNMP:" << setIPSNMP;
         emit settingNetWorkandSNMP(setIPSNMP);
    }else if (getCommand == "editTimesyncServer") {
            QString timeServer = command.value("editsTimeSyncServer").toString();
            qDebug() << "settimeServer:" << timeServer;

            QString settimeServer = QString("{"
                                         "\"objectName\":\"updateSettingNetwork\","
                                         "\"ntpServer\":\"%1\""
                                         "}")
                                .arg(timeServer);

            qDebug() << "settimeServer:" << settimeServer;
             emit settingNetWorkandSNMP(settimeServer);
        }else if (getCommand == "SNMPenable") {
            bool plcDoError = command.contains("plcDOError") ? QJsonValue(command["plcDoError"]).toBool() : command.value("plcDoError").toBool();
            bool plcDiError = command.contains("plcDiError") ? QJsonValue(command["plcDiError"]).toBool() : command.value("plcDiError").toBool();
            bool hispeedPhaseA = command.contains("hispeedPhaseA") ? QJsonValue(command["hispeedPhaseA"]).toBool() : command.value("hispeedPhaseA").toBool();
            bool hispeedPhaseB = command.contains("hispeedPhaseB") ? QJsonValue(command["hispeedPhaseB"]).toBool() : command.value("hispeedPhaseB").toBool();
            bool hispeedPhaseC = command.contains("hispeedPhaseC") ? QJsonValue(command["hispeedPhaseC"]).toBool() : command.value("hispeedPhaseC").toBool();
            bool commuPhaseA = command.contains("commuPhaseA") ? QJsonValue(command["commuPhaseA"]).toBool() : command.value("commuPhaseA").toBool();
            bool commuPhaseB = command.contains("commuPhaseB") ? QJsonValue(command["commuPhaseB"]).toBool() : command.value("commuPhaseB").toBool();
            bool commuPhaseC = command.contains("commuPhaseC") ? QJsonValue(command["commuPhaseC"]).toBool() : command.value("commuPhaseC").toBool();
            bool gpsModule = command.contains("gpsModule") ? QJsonValue(command["gpsModule"]).toBool() : command.value("gpsModule").toBool();
            bool systemInti = command.contains("systemInti") ? QJsonValue(command["systemInti"]).toBool() : command.value("systemInti").toBool();
            bool commuError = command.contains("commuError") ? QJsonValue(command["commuError"]).toBool() : command.value("commuError").toBool();
            bool relayStart = command.contains("relayStart") ? QJsonValue(command["relayStart"]).toBool() : command.value("relayStart").toBool();
            bool surageStart = command.contains("surageStart") ? QJsonValue(command["surageStart"]).toBool() : command.value("surageStart").toBool();
            bool preiodicStart = command.contains("preiodicStart") ? QJsonValue(command["preiodicStart"]).toBool() : command.value("preiodicStart").toBool();
            bool manualTest = command.contains("manualTest") ? QJsonValue(command["manualTest"]).toBool() : command.value("manualTest").toBool();
            bool lflfail = command.contains("lflfail") ? QJsonValue(command["lflfail"]).toBool() : command.value("lflfail").toBool();
            bool lfloperate = command.contains("lfloperate") ? QJsonValue(command["lfloperate"]).toBool() : command.value("lfloperate").toBool();
            if (command.contains("plcDoError")) {
                QString setSNMP = QString("{"
                                               "\"objectName\"     :\"updateSettingNetwork\","
                                               "\"PLC_DO_ERROR\"         :\"%1\""
                                               "}").arg(plcDoError ? "1" : "0");
                qDebug() << "setSNMP plcDoError:" << setSNMP << plcDoError;
                emit settingNetWorkandSNMP(setSNMP);
            }else if (command.contains("plcDiError")) {
                QString setSNMP = QString("{"
                                               "\"objectName\"     :\"updateSettingNetwork\","
                                               "\"PLC_DI_ERROR\"         :\"%1\""
                                               "}").arg(plcDiError ? "1" : "0");
                qDebug() << "setSNMP plcDiError:" << setSNMP << plcDiError;
                emit settingNetWorkandSNMP(setSNMP);
            }else if (command.contains("hispeedPhaseA")) {
                QString setSNMP = QString("{"
                                               "\"objectName\"     :\"updateSettingNetwork\","
                                               "\"MODULE_HI_SPEED_PHASE_A_ERROR\"         :\"%1\""
                                               "}").arg(hispeedPhaseA ? "1" : "0");
                qDebug() << "setSNMP hispeedPhaseA:" << setSNMP << hispeedPhaseA;
                emit settingNetWorkandSNMP(setSNMP);

            }else if (command.contains("hispeedPhaseB")) {
                QString setSNMP = QString("{"
                                               "\"objectName\"     :\"updateSettingNetwork\","
                                               "\"MODULE_HI_SPEED_PHASE_B_ERROR\"         :\"%1\""
                                               "}").arg(hispeedPhaseB ? "1" : "0");
                qDebug() << "setSNMP hispeedPhaseB:" << setSNMP << hispeedPhaseB;
                emit settingNetWorkandSNMP(setSNMP);

            }else if (command.contains("hispeedPhaseC")) {
                QString setSNMP = QString("{"
                                               "\"objectName\"     :\"updateSettingNetwork\","
                                               "\"MODULE_HI_SPEED_PHASE_C_ERROR\"         :\"%1\""
                                               "}").arg(hispeedPhaseC ? "1" : "0");
                qDebug() << "setSNMP hispeedPhaseC:" << setSNMP << hispeedPhaseC;
                emit settingNetWorkandSNMP(setSNMP);

            }else if (command.contains("commuPhaseA")) {
                QString setSNMP = QString("{"
                                               "\"objectName\"     :\"updateSettingNetwork\","
                                               "\"INTERNAL_PHASE_A_ERROR\"         :\"%1\""
                                               "}").arg(commuPhaseA ? "1" : "0");
                qDebug() << "setSNMP commuPhaseA:" << setSNMP << commuPhaseA;
                emit settingNetWorkandSNMP(setSNMP);

            }else if (command.contains("commuPhaseB")) {
                QString setSNMP = QString("{"
                                               "\"objectName\"     :\"updateSettingNetwork\","
                                               "\"INTERNAL_PHASE_B_ERROR\"         :\"%1\""
                                               "}").arg(commuPhaseB ? "1" : "0");
                qDebug() << "setSNMP commuPhaseB:" << setSNMP << commuPhaseB;
                emit settingNetWorkandSNMP(setSNMP);

            }else if (command.contains("commuPhaseC")) {
                QString setSNMP = QString("{"
                                               "\"objectName\"     :\"updateSettingNetwork\","
                                               "\"INTERNAL_PHASE_C_ERROR\"         :\"%1\""
                                               "}").arg(commuPhaseC ? "1" : "0");
                qDebug() << "setSNMP commuPhaseC:" << setSNMP << commuPhaseC;
                emit settingNetWorkandSNMP(setSNMP);

            }else if (command.contains("gpsModule")) {
                QString setSNMP = QString("{"
                                               "\"objectName\"     :\"updateSettingNetwork\","
                                               "\"GPS_MODULE_FAIL\"         :\"%1\""
                                               "}").arg(gpsModule ? "1" : "0");
                qDebug() << "setSNMP gpsModule:" << setSNMP << gpsModule;
                emit settingNetWorkandSNMP(setSNMP);

            }else if (command.contains("systemInti")) {
                QString setSNMP = QString("{"
                                               "\"objectName\"     :\"updateSettingNetwork\","
                                               "\"SYSTEM_INITIAL\"         :\"%1\""
                                               "}").arg(systemInti ? "1" : "0");
                qDebug() << "setSNMP systemInti:" << setSNMP << systemInti;
                emit settingNetWorkandSNMP(setSNMP);

            }else if (command.contains("commuError")) {
                QString setSNMP = QString("{"
                                               "\"objectName\"     :\"updateSettingNetwork\","
                                               "\"COMMUNICATION_ERROR\"         :\"%1\""
                                               "}").arg(commuError ? "1" : "0");
                qDebug() << "setSNMP commuError:" << setSNMP << commuError;
                emit settingNetWorkandSNMP(setSNMP);

            }else if (command.contains("relayStart")) {
                QString setSNMP = QString("{"
                                               "\"objectName\"     :\"updateSettingNetwork\","
                                               "\"RELAY_START_EVENT\"         :\"%1\""
                                               "}").arg(relayStart ? "1" : "0");
                qDebug() << "setSNMP relayStart:" << setSNMP << relayStart;
                emit settingNetWorkandSNMP(setSNMP);

            }else if (command.contains("surageStart")) {
                QString setSNMP = QString("{"
                                               "\"objectName\"     :\"updateSettingNetwork\","
                                               "\"SURGE_START_EVENT\"         :\"%1\""
                                               "}").arg(surageStart ? "1" : "0");
                qDebug() << "setSNMP surageStart:" << setSNMP << surageStart;
                emit settingNetWorkandSNMP(setSNMP);

            }else if (command.contains("preiodicStart")) {
                QString setSNMP = QString("{"
                                               "\"objectName\"     :\"updateSettingNetwork\","
                                               "\"PERIODIC_TEST_EVENT\"         :\"%1\""
                                               "}").arg(preiodicStart ? "1" : "0");
                qDebug() << "setSNMP preiodicStart:" << setSNMP << preiodicStart;
                emit settingNetWorkandSNMP(setSNMP);

            }else if (command.contains("manualTest")) {
                QString setSNMP = QString("{"
                                               "\"objectName\"     :\"updateSettingNetwork\","
                                               "\"MANUAL_TEST_EVENT\"         :\"%1\""
                                               "}").arg(manualTest ? "1" : "0");
                qDebug() << "setSNMP manualTest:" << setSNMP << manualTest;
                emit settingNetWorkandSNMP(setSNMP);

            }else if (command.contains("lflfail")) {
                QString setSNMP = QString("{"
                                               "\"objectName\"     :\"updateSettingNetwork\","
                                               "\"LFL_FAIL\"         :\"%1\""
                                               "}").arg(lflfail ? "1" : "0");
                qDebug() << "setSNMP lflfail:" << setSNMP << lflfail;
                emit settingNetWorkandSNMP(setSNMP);

            }else if (command.contains("lfloperate")) {
                QString setSNMP = QString("{"
                                               "\"objectName\"     :\"updateSettingNetwork\","
                                               "\"LEL_OPERATE\"         :\"%1\""
                                               "}").arg(lfloperate ? "1" : "0");
                qDebug() << "setSNMP lfloperate:" << setSNMP << lfloperate;
                emit settingNetWorkandSNMP(setSNMP);

            }
            qDebug() << "SNMPenable:" << plcDoError << plcDiError << hispeedPhaseA << hispeedPhaseB << hispeedPhaseC << commuPhaseA << commuPhaseB << commuPhaseC << gpsModule << systemInti << commuError << relayStart << surageStart << preiodicStart << manualTest << lflfail << lfloperate;
    }else if (getCommand.contains("sagText")) {
        double sagFactor = QJsonValue(command["sagText"]).toDouble();
        QString displaySetting = QString("{"
                                        "\"objectName\"     :\"displaySetting\","
                                        "\"samplingRateInit\"         :%1"
                                        "}").arg(sagFactor);
        qDebug() << "displaySetting:" << displaySetting << sagFactor;
        settingdisplay(displaySetting);
    }else if (getCommand.contains("samplingText")) {
        double samplingRate = QJsonValue(command["samplingText"]).toDouble();
        QString displaySetting = QString("{"
                                        "\"objectName\"     :\"displaySetting\","
                                        "\"samplingRate\"         :%1"
                                        "}").arg(samplingRate);
        qDebug() << "displaySetting:" << displaySetting << samplingRate;
        settingdisplay(displaySetting);
    }else if (getCommand.contains("distancetostartText")) {
        double distanceStart = QJsonValue(command["distancetostartText"]).toDouble();
        QString displaySetting = QString("{"
                                        "\"objectName\"     :\"displaySetting\","
                                        "\"distancetostartText\"         :%1"
                                        "}").arg(distanceStart);
        qDebug() << "displaySetting:" << displaySetting << distanceStart;
        settingdisplay(displaySetting);
    }else if (getCommand.contains("distancetoshowText")) {
        double distanceShow = QJsonValue(command["distancetoshowText"]).toDouble();
        QString displaySetting = QString("{"
                                        "\"objectName\"     :\"displaySetting\","
                                        "\"distancetoshowText\"         :%1"
                                        "}").arg(distanceShow);
        qDebug() << "displaySetting:" << displaySetting << distanceShow;
        settingdisplay(displaySetting);
    }else if (getCommand.contains("distancetoshowText")) {
        double distanceShow = QJsonValue(command["distancetoshowText"]).toDouble();
        QString displaySetting = QString("{"
                                        "\"objectName\"     :\"displaySetting\","
                                        "\"distancetoshowText\"         :%1"
                                        "}").arg(distanceShow);
        qDebug() << "displaySetting:" << displaySetting << distanceShow;
        settingdisplay(displaySetting);
    }else if (getCommand.contains("fulldistanceText")) {
        double fulldistance = QJsonValue(command["fulldistanceText"]).toDouble();
        QString displaySetting = QString("{"
                                        "\"objectName\"     :\"displaySetting\","
                                        "\"fulldistanceText\"         :%1"
                                        "}").arg(fulldistance);
        qDebug() << "displaySetting:" << displaySetting << fulldistance;
        settingdisplay(displaySetting);
    }else if (getCommand == "startPlotingDataPhaseA") {
        // Extract values from the JSON command
//        double thresholdInit = command["threshold"].toDouble();
//        double sagFactorInit = command["sagFactor"].toDouble();
//        double samplingRateInit = command["samplingRate"].toDouble();
//        double distanceToStartInit = command["distanceToStart"].toDouble();
//        double distanceToShowInit = command["distanceToShow"].toDouble();

//        qDebug() << "Parsed JSON:" << command;
//        qDebug() << "check debug enablePhaseA:" << enablePhaseA;

//        bool isDefault =
//            (thresholdInit == 1500 &&
//             sagFactorInit == 0.983 &&
//             samplingRateInit == 10 &&
//             distanceToStartInit == 0 &&
//             distanceToShowInit == 8500);

//        if (isDefault) {
//            enablePhaseA = false;
//            qDebug() << "Default values detected. Skipping calculation. enablePhaseA set to false.";
//        } else {
//            enablePhaseA = true;
//            QString parameterDisplay = QString("{"
//                                               "\"objectName\":\"parameterDisplay\","
//                                               "\"thresholdInitA\":%1,"
//                                               "\"sagFactorInit\":%2,"
//                                               "\"samplingRateInit\":%3,"
//                                               "\"distanceToStartInit\":%4,"
//                                               "\"distanceToShowInit\":%5"
//                                               "}").arg(thresholdInit)
//                                                 .arg(sagFactorInit)
//                                                 .arg(samplingRateInit)
//                                                 .arg(distanceToStartInit)
//                                                 .arg(distanceToShowInit);
//            qDebug() << "parameterDisplay:" << thresholdInit << sagFactorInit << samplingRateInit << distanceToStartInit << distanceToShowInit;
//            calculate(parameterDisplay);
//        }
    }else if (getCommand == "startPlotingDataPhaseB") {
        emit plotingDataPhaseB(rawdataArrayB);
//        double thresholdInit = command["threshold"].toDouble();
//        double sagFactorInit = command["sagFactor"].toDouble();
//        double samplingRateInit = command["samplingRate"].toDouble();
//        double distanceToStartInit = command["distanceToStart"].toDouble();
//        double distanceToShowInit = command["distanceToShow"].toDouble();
//        QString parameterDisplay = QString("{"
//                                           "\"objectName\":\"parameterDisplay\","
//                                           "\"thresholdInitA\":%1,"
//                                           "\"sagFactorInit\":%2,"
//                                           "\"samplingRateInit\":%3,"
//                                           "\"distanceToStartInit\":%4,"
//                                           "\"distanceToShowInit\":%5"
//                                           "}").arg(thresholdInit).arg(sagFactorInit).arg(samplingRateInit).arg(distanceToStartInit).arg(distanceToShowInit);
//        qDebug() << "parameterDisplay:" << thresholdInit << sagFactorInit << samplingRateInit << distanceToStartInit << distanceToShowInit;
//        calculateDataPhaseB(parameterDisplay);
    }else if (getCommand == "startPlotingDataPhaseC") {
        emit plotingDataPhaseC(rawdataArrayC);
//        double thresholdInit = command["threshold"].toDouble();
//        double sagFactorInit = command["sagFactor"].toDouble();
//        double samplingRateInit = command["samplingRate"].toDouble();
//        double distanceToStartInit = command["distanceToStart"].toDouble();
//        double distanceToShowInit = command["distanceToShow"].toDouble();
//        QString parameterDisplay = QString("{"
//                                           "\"objectName\":\"parameterDisplay\","
//                                           "\"thresholdInitA\":%1,"
//                                           "\"sagFactorInit\":%2,"
//                                           "\"samplingRateInit\":%3,"
//                                           "\"distanceToStartInit\":%4,"
//                                           "\"distanceToShowInit\":%5"
//                                           "}").arg(thresholdInit).arg(sagFactorInit).arg(samplingRateInit).arg(distanceToStartInit).arg(distanceToShowInit);
//        qDebug() << "parameterDisplay:" << thresholdInit << sagFactorInit << samplingRateInit << distanceToStartInit << distanceToShowInit;
//        calculateDataPhaseB(parameterDisplay);
    }else if (getCommand == "GetSettingDisplay") {
        double sagFactorInit = command["sagFactorInit"].toDouble();
        double samplingRateInit = command["samplingRateInit"].toDouble();
        double distanceToStartInit = command["distanceToStartInit"].toDouble();
        double distanceToShowInit = command["distanceToShowInit"].toDouble();
        double fulldistancesInit = command["fulldistancesInit"].toDouble();

        QString parameterDisplay = QString("{"
                                           "\"objectName\":\"updataParameterDisplay\","
                                           "\"sagFactorInit\":%1,"
                                           "\"samplingRateInit\":%2,"
                                           "\"distanceToStartInit\":%3,"
                                           "\"distanceToShowInit\":%4,"
                                           "\"fulldistancesInit\":%5"
                                           "}").arg(sagFactorInit).arg(samplingRateInit).arg(distanceToStartInit).arg(distanceToShowInit).arg(fulldistancesInit);
        qDebug() << "updataParameterDisplay:" << sagFactorInit << samplingRateInit << distanceToStartInit << distanceToShowInit << fulldistancesInit;
        cppCommand(parameterDisplay);
        calculate(parameterDisplay);
    } else if (getCommand == "getThreshold") {
        double thresholdInitA = command["thresholdInitA"].toDouble();
        double thresholdInitB = command["thresholdInitB"].toDouble();
        double thresholdInitC = command["thresholdInitA"].toDouble();

        QString updatethresholdParam = QString("{"
                                           "\"objectName\":\"updatethresholdParam\","
                                           "\"thresholdInitA\":%1,"
                                           "\"thresholdInitB\":%2,"
                                           "\"thresholdInitA\":%5"
                                           "}").arg(thresholdInitA).arg(thresholdInitB).arg(thresholdInitC);
        qDebug() << "updatethresholdParam:" << thresholdInitA << thresholdInitB << thresholdInitC;
        cppCommand(updatethresholdParam);
        calculate(updatethresholdParam);
    }else if(getCommand == "ManualTest"){
        cppManual = "ManualTest";
        manualtest(cppManual);
    }else if(getCommand == "PatternTest"){
        cppPattern = "PatternTest";
        patterntest(cppPattern);
    }
}


void mainwindows::ServerCommand(QString qmlJson){
    qDebug()<< "ServerCommand" << qmlJson;
    QJsonDocument d = QJsonDocument::fromJson(qmlJson.toUtf8());
    QJsonObject command = d.object();
    QString getCommand =  QJsonValue(command["objectName"]).toString();
    QString getCommand2 =  QJsonValue(command["menuID"]).toString();
    if(getCommand.contains("SwVersion")){
            isVersion = true;
    }
}

void mainwindows::connectToPLC(){
    qDebug() << "------Open websocket to server------";
    QJsonDocument jsonDoc;
    QJsonObject Param;
    Param.insert("objectName","SwVersion");	             //Name
    Param.insert("SwVersion",SwVersion);	             //Name
    Param.insert("HwVersion",HwVersion);	             //Name
    Param.insert("HwName",HwName);	             //Name
    jsonDoc.setObject(Param);
    QString raw_data = QJsonDocument(Param).toJson(QJsonDocument::Compact).toStdString().c_str();
    QThread::msleep(300);
    emit sendToSocket(raw_data);
}

void mainwindows::calculate(QString msg) {
    qDebug() << "calculate:" << msg;
    QJsonDocument d = QJsonDocument::fromJson(msg.toUtf8());
    QJsonObject command = d.object();
    QString getCommand = QJsonValue(command["objectName"]).toString();

    double prevSagFactor = sagFactor;
    double prevSamplingRate = samplingRate;
    double prevDistanceToStart = distanceToStart;
    double prevDistanceToShow = distanceToShow;
    double prevFulldistance = fulldistance;
    double prevThresholdA = thresholdA;
    double prevThresholdB = thresholdB;
    double prevThresholdC = thresholdC;

    if (command.contains("sagFactorInit")) {
        sagFactor = command.value("sagFactorInit").toDouble();
    }
    if (command.contains("samplingRateInit")) {
        samplingRate = command.value("samplingRateInit").toDouble();
    }
    if (command.contains("distanceToStartInit")) {
        distanceToStart = command.value("distanceToStartInit").toDouble();
    }
    if (command.contains("distanceToShowInit")) {
        distanceToShow = command.value("distanceToShowInit").toDouble();
    }
    if (command.contains("fulldistancesInit")) {
        fulldistance = command.value("fulldistancesInit").toDouble();
    }
    if (command.contains("thresholdInitA")) {
        thresholdA = command.value("thresholdInitA").toDouble();
    }
    if (command.contains("thresholdInitB")) {
        thresholdB = command.value("thresholdInitB").toDouble();
    }
    if (command.contains("thresholdInitC")) {
        thresholdC = command.value("thresholdInitC").toDouble();
    }

    bool isChanged = (prevSagFactor != sagFactor) ||
                     (prevSamplingRate != samplingRate) ||
                     (prevDistanceToStart != distanceToStart) ||
                     (prevDistanceToShow != distanceToShow) ||
                     (prevFulldistance != fulldistance) ||
                     (prevThresholdA != thresholdA) ||
                     (prevThresholdB != thresholdB) ||
                     (prevThresholdC != thresholdC);

    bool isValid = true;
    if (std::isnan(sagFactor) || std::isinf(sagFactor)) isValid = false;
    if (std::isnan(samplingRate) || std::isinf(samplingRate)) isValid = false;
    if (std::isnan(distanceToStart) || std::isinf(distanceToStart)) isValid = false;
    if (std::isnan(distanceToShow) || std::isinf(distanceToShow)) isValid = false;
    if (std::isnan(fulldistance) || std::isinf(fulldistance)) isValid = false;
    if (std::isnan(thresholdA) || std::isinf(thresholdA)) isValid = false;
    if (std::isnan(thresholdB) || std::isinf(thresholdB)) isValid = false;
    if (std::isnan(thresholdC) || std::isinf(thresholdC)) isValid = false;

    if (isValid && isChanged) {
        qDebug() << "Debug parameter (Valid and Changed):" << sagFactor << samplingRate << distanceToStart << distanceToShow << fulldistance << thresholdA << thresholdB << thresholdC;

        // Check each threshold and call the corresponding plotGraph function
        if (thresholdA > 0) {
            qDebug() << "Threshold A triggered.";
            plotGraphA(sagFactor, samplingRate, distanceToStart, distanceToShow, fulldistance, thresholdA);
        }
        if (thresholdB > 0) {
            qDebug() << "Threshold B triggered.";
            plotGraphB(sagFactor, samplingRate, distanceToStart, distanceToShow, fulldistance, thresholdB);
        }
        if (thresholdC > 0) {
            qDebug() << "Threshold C triggered.";
            plotGraphC(sagFactor, samplingRate, distanceToStart, distanceToShow, fulldistance, thresholdC);
        }

        // If no threshold is valid, do nothing
        if (thresholdA <= 0 && thresholdB <= 0 && thresholdC <= 0) {
            qDebug() << "No valid threshold triggered. No plotting performed.";
        }
    } else {
        qDebug() << "Debug parameter (Invalid or Unchanged):" << sagFactor << samplingRate << distanceToStart << distanceToShow << fulldistance << thresholdA << thresholdB << thresholdC;
    }
}

void mainwindows::plotGraphA(double sagFactorInit, double samplingRateInit, double distanceToStartInit,
                            double distanceToShowInit, double fulldistance, double thresholdInitA) {
    qDebug() << "Debug plotGraph:" << sagFactorInit << samplingRateInit << distanceToStartInit
             << distanceToShowInit << fulldistance << thresholdInitA;

    QString filePath = "/home/pi/data0.raw";
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Unable to open file:" << filePath;
        return;
    }
    QByteArray data = file.readAll();
    file.close();

    std::vector<float> normalizedValues;
    const uint8_t* ptr = reinterpret_cast<const uint8_t*>(data.constData());
    const uint8_t* endPtr = ptr + data.size();

    while (ptr + 2 <= endPtr) {
        uint16_t signedValue = static_cast<uint16_t>((static_cast<uint8_t>(ptr[1]) << 8) | static_cast<uint8_t>(ptr[0]));
        float normalizedValue = static_cast<float>(signedValue) / 32768.0f;  // Convert to mV
        normalizedValues.push_back(normalizedValue);
        ptr += 2;
    }

    qDebug() << "Total samples read: " << normalizedValues.size();

    const float threshold = thresholdInitA / 32768.0f;  // Convert to mV
    auto startIt = std::find_if(normalizedValues.begin(), normalizedValues.end(), [threshold](float val) {
        return val >= threshold;
    });

    if (startIt == normalizedValues.end()) {
        qDebug() << "Threshold value not found in data.";
        return;
    }
    int startIndex = std::distance(normalizedValues.begin(), startIt);
    qDebug() << "Starting index found at position:" << startIndex;

    int resampling = samplingRateInit / (60 * sagFactorInit); // Resampling rate
    qDebug() << "Resampling rate:" << resampling;

    float totalDistance = (distanceToShowInit - distanceToStartInit) * 1000;
    int fullpoint = static_cast<int>(totalDistance / (60 * sagFactorInit));
    int trueDistancepoint = fullpoint / resampling; // Points after resampling

    qDebug() << "Full points:" << fullpoint;
    qDebug() << "True distance points after resampling:" << trueDistancepoint;

    float pointInterval = totalDistance / trueDistancepoint; // Distance interval per point
    qDebug() << "Point interval (m):" << pointInterval;

    std::vector<std::pair<float, float>> result;
    float currentDistance = distanceToStartInit * 1000; // Start in meters

    for (int i = 0; i < trueDistancepoint; ++i) {
        float currentValue = (i * resampling + startIndex < normalizedValues.size())
                             ? normalizedValues[i * resampling + startIndex] * 4096/2  // Multiply by 4096 here
                             : 0.0f;
        result.emplace_back(currentDistance, currentValue);
        currentDistance += pointInterval;
    }

    qDebug() << "Final Total Points:" << result.size();
    for (const auto& [distance, voltage] : result) {
        qDebug() << "X:" << distance / 1000.0 << " km, Y:" << voltage << " mV";
    }

    // JSON Output for Plotting
    QJsonObject mainObject;
    QJsonArray dist, volt;
    for (const auto& [distance, voltage] : result) {
        dist.push_back(distance / 1000);  // Convert m to km
        volt.push_back(voltage);  // Already multiplied by 4096
    }

    mainObject.insert("objectName", "dataPlotingA");
    mainObject.insert("distance", dist);
    mainObject.insert("voltage", volt);

    QJsonDocument jsonDoc(mainObject);
    QString raw_data = jsonDoc.toJson(QJsonDocument::Compact);
    qDebug() << "Generated JSON:" << raw_data;

    rawdataArrayA = raw_data;
//    emit plotingDataPhaseB(raw_data);
    reSamplingNormalization(result);
}
void mainwindows::plotGraphB(double sagFactorInit, double samplingRateInit, double distanceToStartInit,
                            double distanceToShowInit, double fulldistance, double thresholdInitB) {
    qDebug() << "Debug plotGraph:" << sagFactorInit << samplingRateInit << distanceToStartInit
             << distanceToShowInit << fulldistance << thresholdInitB;

    QString filePath = "/home/pi/data0.raw";
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Unable to open file:" << filePath;
        return;
    }
    QByteArray data = file.readAll();
    file.close();

    std::vector<float> normalizedValues;
    const uint8_t* ptr = reinterpret_cast<const uint8_t*>(data.constData());
    const uint8_t* endPtr = ptr + data.size();

    while (ptr + 2 <= endPtr) {
        uint16_t signedValue = static_cast<uint16_t>((static_cast<uint8_t>(ptr[1]) << 8) | static_cast<uint8_t>(ptr[0]));
        float normalizedValue = static_cast<float>(signedValue) / 32768.0f;  // Convert to mV
        normalizedValues.push_back(normalizedValue);
        ptr += 2;
    }

    qDebug() << "Total samples read: " << normalizedValues.size();

    const float threshold = thresholdInitB / 32768.0f;  // Convert to mV
    auto startIt = std::find_if(normalizedValues.begin(), normalizedValues.end(), [threshold](float val) {
        return val >= threshold;
    });

    if (startIt == normalizedValues.end()) {
        qDebug() << "Threshold value not found in data.";
        return;
    }
    int startIndex = std::distance(normalizedValues.begin(), startIt);
    qDebug() << "Starting index found at position:" << startIndex;

    int resampling = samplingRateInit / (60 * sagFactorInit); // Resampling rate
    qDebug() << "Resampling rate:" << resampling;

    float totalDistance = (distanceToShowInit - distanceToStartInit) * 1000;
    int fullpoint = static_cast<int>(totalDistance / (60 * sagFactorInit));
    int trueDistancepoint = fullpoint / resampling; // Points after resampling

    qDebug() << "Full points:" << fullpoint;
    qDebug() << "True distance points after resampling:" << trueDistancepoint;

    float pointInterval = totalDistance / trueDistancepoint; // Distance interval per point
    qDebug() << "Point interval (m):" << pointInterval;

    std::vector<std::pair<float, float>> result;
    float currentDistance = distanceToStartInit * 1000; // Start in meters

    for (int i = 0; i < trueDistancepoint; ++i) {
        float currentValue = (i * resampling + startIndex < normalizedValues.size())
                             ? normalizedValues[i * resampling + startIndex] * 4096/2  // Multiply by 4096 here
                             : 0.0f;
        result.emplace_back(currentDistance, currentValue);
        currentDistance += pointInterval;
    }

    qDebug() << "Final Total Points:" << result.size();
    for (const auto& [distance, voltage] : result) {
        qDebug() << "X:" << distance / 1000.0 << " km, Y:" << voltage << " mV";
    }

    // JSON Output for Plotting
    QJsonObject mainObject;
    QJsonArray dist, volt;
    for (const auto& [distance, voltage] : result) {
        dist.push_back(distance / 1000);  // Convert m to km
        volt.push_back(voltage);  // Already multiplied by 4096
    }

    mainObject.insert("objectName", "dataPlotingB");
    mainObject.insert("distance", dist);
    mainObject.insert("voltage", volt);

    QJsonDocument jsonDoc(mainObject);
    QString raw_data = jsonDoc.toJson(QJsonDocument::Compact);
    qDebug() << "Generated JSON:" << raw_data;

    rawdataArrayA = raw_data;
//    emit plotingDataPhaseB(raw_data);
    reSamplingNormalization(result);
}
void mainwindows::plotGraphC(double sagFactorInit, double samplingRateInit, double distanceToStartInit,
                            double distanceToShowInit, double fulldistance, double thresholdInitC) {
    qDebug() << "Debug plotGraph:" << sagFactorInit << samplingRateInit << distanceToStartInit
             << distanceToShowInit << fulldistance << thresholdInitC;

    QString filePath = "/home/pi/data0.raw";
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Unable to open file:" << filePath;
        return;
    }
    QByteArray data = file.readAll();
    file.close();

    std::vector<float> normalizedValues;
    const uint8_t* ptr = reinterpret_cast<const uint8_t*>(data.constData());
    const uint8_t* endPtr = ptr + data.size();

    while (ptr + 2 <= endPtr) {
        uint16_t signedValue = static_cast<uint16_t>((static_cast<uint8_t>(ptr[1]) << 8) | static_cast<uint8_t>(ptr[0]));
        float normalizedValue = static_cast<float>(signedValue) / 32768.0f;  // Convert to mV
        normalizedValues.push_back(normalizedValue);
        ptr += 2;
    }

    qDebug() << "Total samples read: " << normalizedValues.size();

    const float threshold = thresholdInitC / 32768.0f;  // Convert to mV
    auto startIt = std::find_if(normalizedValues.begin(), normalizedValues.end(), [threshold](float val) {
        return val >= threshold;
    });

    if (startIt == normalizedValues.end()) {
        qDebug() << "Threshold value not found in data.";
        return;
    }
    int startIndex = std::distance(normalizedValues.begin(), startIt);
    qDebug() << "Starting index found at position:" << startIndex;

    int resampling = samplingRateInit / (60 * sagFactorInit);
    qDebug() << "Resampling rate:" << resampling;

    float totalDistance = (distanceToShowInit - distanceToStartInit) * 1000;
    int fullpoint = static_cast<int>(totalDistance / (60 * sagFactorInit));
    int trueDistancepoint = fullpoint / resampling; // Points after resampling

    qDebug() << "Full points:" << fullpoint;
    qDebug() << "True distance points after resampling:" << trueDistancepoint;

    float pointInterval = totalDistance / trueDistancepoint;
    qDebug() << "Point interval (m):" << pointInterval;

    std::vector<std::pair<float, float>> result;
    float currentDistance = distanceToStartInit * 1000;

    for (int i = 0; i < trueDistancepoint; ++i) {
        float currentValue = (i * resampling + startIndex < normalizedValues.size())
                             ? normalizedValues[i * resampling + startIndex] * 4096/2  // Multiply by 4096 here
                             : 0.0f;
        result.emplace_back(currentDistance, currentValue);
        currentDistance += pointInterval;
    }

    qDebug() << "Final Total Points:" << result.size();
    for (const auto& [distance, voltage] : result) {
        qDebug() << "X:" << distance / 1000.0 << " km, Y:" << voltage << " mV";
    }

    // JSON Output for Plotting
    QJsonObject mainObject;
    QJsonArray dist, volt;
    for (const auto& [distance, voltage] : result) {
        dist.push_back(distance / 1000);  // Convert m to km
        volt.push_back(voltage);  // Already multiplied by 4096
    }

    mainObject.insert("objectName", "dataPlotingB");
    mainObject.insert("distance", dist);
    mainObject.insert("voltage", volt);

    QJsonDocument jsonDoc(mainObject);
    QString raw_data = jsonDoc.toJson(QJsonDocument::Compact);
    qDebug() << "Generated JSON:" << raw_data;

    rawdataArrayA = raw_data;
//    emit plotingDataPhaseB(raw_data);
//    reSamplingNormalization(result);
}

//void mainwindows::plotGraph(double sagFactorInit, double samplingRateInit, double distanceToStartInit,
//                            double distanceToShowInit, double fulldistance, double thresholdInitA) {
//    qDebug() << "Debug plotGraph:" << sagFactorInit << samplingRateInit << distanceToStartInit
//             << distanceToShowInit << fulldistance << thresholdInitA;

//    QString filePath = "/home/pi/data0.raw";
//    QFile file(filePath);
//    if (!file.open(QIODevice::ReadOnly)) {
//        qDebug() << "Unable to open file:" << filePath;
//        return;
//    }
//    QByteArray data = file.readAll();
//    file.close();

//    std::vector<float> normalizedValues;
//    const uint8_t* ptr = reinterpret_cast<const uint8_t*>(data.constData());
//    const uint8_t* endPtr = ptr + data.size();

//    while (ptr + 2 <= endPtr) {
//        uint16_t signedValue = static_cast<uint16_t>((static_cast<uint8_t>(ptr[1]) << 8) | static_cast<uint8_t>(ptr[0]));
//        float normalizedValue = static_cast<float>(signedValue) / 32768.0f;  // Convert to mV
//        normalizedValues.push_back(normalizedValue);
//        ptr += 2;
//    }

//    qDebug() << "Total samples read: " << normalizedValues.size();

//    const float threshold = thresholdInitA / 32768.0f;  // Convert to mV
//    auto startIt = std::find_if(normalizedValues.begin(), normalizedValues.end(), [threshold](float val) {
//        return val >= threshold;
//    });

//    if (startIt == normalizedValues.end()) {
//        qDebug() << "Threshold value not found in data.";
//        return;
//    }
//    int startIndex = std::distance(normalizedValues.begin(), startIt);
//    qDebug() << "Starting index found at position:" << startIndex;

//    // New Calculation Logic
//    int resampling = samplingRateInit / (60 * sagFactorInit); // Resampling rate
//    qDebug() << "Resampling rate:" << resampling;

//    float totalDistance = (distanceToShowInit - distanceToStartInit) * 1000;
//    int fullpoint = static_cast<int>(totalDistance / (60 * sagFactorInit));
//    int trueDistancepoint = fullpoint / resampling; // Points after resampling

//    qDebug() << "Full points:" << fullpoint;
//    qDebug() << "True distance points after resampling:" << trueDistancepoint;

//    float pointInterval = totalDistance / trueDistancepoint; // Distance interval per point
//    qDebug() << "Point interval (m):" << pointInterval;

//    std::vector<std::pair<float, float>> result;
//    float currentDistance = distanceToStartInit * 1000; // Start in meters

//    for (int i = 0; i < trueDistancepoint; ++i) {
//        float currentValue = (i * resampling + startIndex < normalizedValues.size())
//                             ? normalizedValues[i * resampling + startIndex]
//                             : 0.0f;
//        result.emplace_back(currentDistance, currentValue);
//        currentDistance += pointInterval;
//    }

//    qDebug() << "Final Total Points:" << result.size();
//    for (const auto& [distance, voltage] : result) {
//        qDebug() << "X:" << distance / 1000.0 << " km, Y:" << (voltage)*4096 << " mV";
//    }

//    // JSON Output for Plotting
//    QJsonObject mainObject;
//    QJsonArray dist, volt;
//    for (const auto& [distance, voltage] : result) {
//        dist.push_back(distance / 1000);  // Convert m to km
//        volt.push_back((voltage/2)*4096);  // Already in mV
//    }

//    mainObject.insert("objectName", "dataPlotingB");
//    mainObject.insert("distance", dist);
//    mainObject.insert("voltage", volt);

//    QJsonDocument jsonDoc(mainObject);
//    QString raw_data = jsonDoc.toJson(QJsonDocument::Compact);
//    qDebug() << "Generated JSON:" << raw_data;

//    rawdataArrayA = raw_data;
////    emit plotingDataPhaseB(raw_data);
//    reSamplingNormalization(result);
//}
void mainwindows::reSamplingNormalization(const std::vector<std::pair<float, float>>& result) {
    if (result.size() < 3) {
        qDebug() << "Not enough data points to process.";
        return;
    }

    qDebug() << "Starting peak detection and smoothing...";

    // Step 1: Detect Peaks
    std::vector<std::pair<float, double>> peakPoints;
    std::pair<float, double> startPoint = {0.0, 0.0};

    // Detect the starting point
    for (const auto& point : result) {
        if (point.second > 0.0) { // First non-zero voltage
            startPoint = {point.first, point.second};
            break;
        }
    }
    peakPoints.push_back(startPoint);

    // Detect peaks
    for (size_t i = 1; i < result.size() - 1; ++i) {
        float prevVoltage = result[i - 1].second;
        float currentVoltage = result[i].second;
        float nextVoltage = result[i + 1].second;

        if (prevVoltage < currentVoltage && currentVoltage > nextVoltage) {
            peakPoints.emplace_back(result[i]);
        }
    }

    // Add the last point
    peakPoints.push_back(result.back());

    // Find the maximum peak
    auto maxPeakIt = std::max_element(peakPoints.begin(), peakPoints.end(),
                                      [](const std::pair<float, double>& a, const std::pair<float, double>& b) {
                                          return a.second < b.second;
                                      });
    std::pair<float, double> maxPeak = *maxPeakIt;
    qDebug() << "Maximum peak detected at X:" << maxPeak.first / 1000.0 << "km, Y:" << maxPeak.second << "mV";

    // Ensure the maximum peak is included
    if (std::find(peakPoints.begin(), peakPoints.end(), maxPeak) == peakPoints.end()) {
        peakPoints.push_back(maxPeak);
    }

    qDebug() << "Peaks detected. Total peaks:" << peakPoints.size();

    // Debug peaks
    for (const auto& peak : peakPoints) {
        qDebug() << "Peak at X:" << peak.first / 1000.0 << "km, Y:" << peak.second << "mV";
    }

    // Step 2: Downsample Peak Points
    std::vector<std::pair<float, double>> downsampledPeaks;
    size_t step = std::max<size_t>(1, peakPoints.size() / 50); // Downsample to around 50 points
    for (size_t i = 0; i < peakPoints.size(); i += step) {
        downsampledPeaks.push_back(peakPoints[i]);
    }
    if (peakPoints.back() != downsampledPeaks.back()) {
        downsampledPeaks.push_back(peakPoints.back()); // Ensure the last point is included
    }

    // Ensure the maximum peak is included in the downsampled points
    if (std::find(downsampledPeaks.begin(), downsampledPeaks.end(), maxPeak) == downsampledPeaks.end()) {
        downsampledPeaks.push_back(maxPeak);
    }

    std::sort(downsampledPeaks.begin(), downsampledPeaks.end()); // Sort points by X
    qDebug() << "Downsampling completed. Total downsampled points:" << downsampledPeaks.size();

    // Step 3: Smoothing using Linear Interpolation
    std::vector<std::pair<float, double>> smoothCurve;
    for (size_t i = 0; i < downsampledPeaks.size() - 1; ++i) {
        float x1 = downsampledPeaks[i].first;
        float x2 = downsampledPeaks[i + 1].first;
        double y1 = downsampledPeaks[i].second;
        double y2 = downsampledPeaks[i + 1].second;

        // Interpolate between peaks
        for (float x = x1; x <= x2; x += (x2 - x1) / 10.0) { // Add 10 points per segment
            double t = (x - x1) / (x2 - x1); // Normalize x between 0 and 1
            double y = (1 - t) * y1 + t * y2; // Linear interpolation
            smoothCurve.emplace_back(x, y);
        }
    }

    qDebug() << "Smoothing completed. Total points for the curve:" << smoothCurve.size();

    // Step 4: Prepare JSON Output
    QJsonObject mainObject;
    QJsonArray dist, volt;
    for (const auto& point : smoothCurve) {
        dist.push_back(point.first / 1000.0);  // Convert m to km
        volt.push_back(point.second);         // Voltage in mV
    }
    mainObject.insert("objectName", "dataPlotingB");
    mainObject.insert("distance", dist);
    mainObject.insert("voltage", volt);

    QJsonDocument jsonDoc(mainObject);
    QString raw_data = jsonDoc.toJson(QJsonDocument::Compact);
    qDebug() << "Generated JSON for smoothed curve:" << raw_data;

    rawdataArrayA = std::move(raw_data);

    // Emit the signal for the curve
    emit plotingDataPhaseA(rawdataArrayA);
}


//void mainwindows::reSamplingNormalization(const std::vector<std::pair<float, float>>& result) {
//    if (result.size() < 3) {
//        qDebug() << "Not enough data points to detect peaks.";
//        return;
//    }

//    std::vector<std::pair<float, double>> peakPoints;
//    qDebug() << "Starting peak detection...";

//    // Step 1: Identify the starting point
//    std::pair<float, double> startPoint = {0.0, 0.0};
//    for (const auto& point : result) {
//        if (point.second > 0.0) { // Find the first non-zero voltage as the start point
//            startPoint = {point.first, point.second};
//            break;
//        }
//    }
//    peakPoints.push_back(startPoint);

//    qDebug() << "Starting point detected: X:" << startPoint.first / 1000.0 << "km, Y:" << startPoint.second << "mV";

//    // Step 2: Detect peaks
//    for (size_t i = 1; i < result.size() - 1; ++i) {
//        float prevVoltage = result[i - 1].second;
//        float currentVoltage = result[i].second;
//        float nextVoltage = result[i + 1].second;

//        // Detect a peak if the current voltage is higher than both its neighbors
//        if (prevVoltage < currentVoltage && currentVoltage > nextVoltage) {
//            peakPoints.emplace_back(result[i]);
//        }
//    }

//    qDebug() << "Peaks detected. Total peaks:" << peakPoints.size();

//    // Debug the number of points used in plotting
//    int pointsUsed = peakPoints.size();
//    qDebug() << "Total points used for plotting the graph:" << pointsUsed;

//    for (const auto& peak : peakPoints) {
//        qDebug() << "Peak at X:" << peak.first / 1000.0 << "km, Y:" << peak.second << "mV";
//    }

//    // Step 3: Prepare JSON Output
//    QJsonObject mainObject;
//    QJsonArray dist, volt;
//    for (const auto& point : peakPoints) {
//        dist.push_back(point.first / 1000.0);  // Convert m to km
//        volt.push_back(point.second);         // Voltage in mV
//    }
//    mainObject.insert("objectName", "dataPlotingA");
//    mainObject.insert("distance", dist);
//    mainObject.insert("voltage", volt);

//    QJsonDocument jsonDoc(mainObject);
//    QString raw_data = jsonDoc.toJson(QJsonDocument::Compact);
//    qDebug() << "Generated JSON for peak points:" << raw_data;

//    rawdataArrayA = std::move(raw_data);

//    // Emit the signal for the peak points
//    emit plotingDataPhaseA(rawdataArrayA);
//}

//void mainwindows::reSamplingNormalization(const std::vector<std::pair<float, float>>& result) {
//    if (result.size() < 3) {
//        qDebug() << "Not enough data points to detect peaks.";
//        return;
//    }
//    std::vector<std::pair<float, double>> peakPoints;
//    qDebug() << "Starting peak detection...";

//    // Step 1: Detect Peaks
//    peakPoints.push_back(result.front());
//    for (size_t i = 1; i < result.size() - 1; ++i) {
//        float prevVoltage = result[i - 1].second;
//        float currentVoltage = result[i].second;
//        float nextVoltage = result[i + 1].second;

//        if (prevVoltage < currentVoltage && currentVoltage > nextVoltage) {
//            peakPoints.emplace_back(result[i]);
//        }
//    }
//    peakPoints.push_back(result.back());
//    qDebug() << "Peaks detected. Total:" << peakPoints.size();

//    auto maxPeakIt = std::max_element(peakPoints.begin(), peakPoints.end(),
//                                      [](const std::pair<float, double>& a, const std::pair<float, double>& b) {
//                                          return a.second < b.second;
//                                      });
//    double maxPeakValue = maxPeakIt->second;

//    if (peakPoints.size() >= 3) {
//        const int windowSize = std::min(2, static_cast<int>(peakPoints.size())); // ถ้าน้อยมันจะไม่ละเอียดถ้ามากมันจะละเอียด
//        const double sigma = 1.5; //น้อยจะเข้าใกล้จุดพีคมากขึ้น ถ้ามากก็จะห่างออกไป
//        const int halfWindow = windowSize / 2;

//        std::vector<double> kernel(windowSize);
//        double kernelSum = 0.0;
//        for (int i = -halfWindow; i <= halfWindow; ++i) {
//            kernel[i + halfWindow] = exp(-0.5 * (i * i) / (sigma * sigma));
//            kernelSum += kernel[i + halfWindow];
//        }
//        for (auto& k : kernel) k /= kernelSum;

//        std::vector<std::pair<float, double>> smoothPeaks(peakPoints.size());
//        for (size_t i = 0; i < peakPoints.size(); ++i) {
//            if (peakPoints[i].second == maxPeakValue) {
//                smoothPeaks[i] = peakPoints[i];
//                continue;
//            }

//            double weightedSum = 0.0;
//            double weightSum = 0.0;
//            for (int j = -halfWindow; j <= halfWindow; ++j) {
//                int index = static_cast<int>(i) + j;
//                if (index >= 0 && index < static_cast<int>(peakPoints.size())) {
//                    weightedSum += peakPoints[index].second * kernel[j + halfWindow];
//                    weightSum += kernel[j + halfWindow];
//                }
//            }
//            smoothPeaks[i] = {peakPoints[i].first, weightedSum / weightSum};
//        }
//        peakPoints = std::move(smoothPeaks);
//        qDebug() << "Smoothing completed:" << peakPoints;
//    } else {
//        qDebug() << "Not enough peaks for Gaussian smoothing.";
//    }

//    // Step 3: Prepare JSON Output
//    QJsonObject mainObject;
//    QJsonArray dist, volt;
//    for (const auto& point : peakPoints) {
//        dist.push_back(point.first / 1000.0);  // Convert m to km
//        volt.push_back(point.second);
//    }
//    mainObject.insert("objectName", "dataPlotingA");
//    mainObject.insert("distance", dist);
//    mainObject.insert("voltage", volt);

//    QJsonDocument jsonDoc(mainObject);
//    QString raw_data = jsonDoc.toJson(QJsonDocument::Compact);
//    qDebug() << "Generated JSON for smoothed peaks:" << raw_data;

//    rawdataArrayA = std::move(raw_data);

//    if (temp.isEmpty()) {
//        temp = rawdataArrayA;
//    } else if (rawdataArrayA != temp && count > 2) {
//        temp = rawdataArrayA;
//    }
//    emit plotingDataPhaseA(rawdataArrayA);
//}


//void mainwindows::calculate(QString msg) {
//    qDebug() << "calculate:" << msg;
//    QJsonDocument d = QJsonDocument::fromJson(msg.toUtf8());
//    QJsonObject command = d.object();
//    QString getCommand = QJsonValue(command["objectName"]).toString();
//    // Default values
//    static double thresholdInit = 0;
//    static double sagFactorInit = 0;
//    static double samplingRateInit = 0;
//    static double distanceToStartInit = 0;
//    static double distanceToShowInit = 0;
//    static double fulldistanceInit = 0;
//    // Update parameters only if the relevant object is found
////    if (getCommand == "updataParameterDisplay") {
//        if (QString::number(command.value("sagFactorInit").toInt())!= ""){
//            sagFactorInit = command.value("sagFactorInit").toDouble();
//        }
//        if (QString::number(command.value("samplingRateInit").toInt())!= ""){
//            samplingRateInit = command.value("samplingRateInit").toDouble();
//        }
//        if (QString::number(command.value("distanceToStartInit").toInt())!= ""){
//            distanceToStartInit = command.value("distanceToStartInit").toDouble();
//        }
//        if (QString::number(command.value("distanceToShowInit").toInt())!= ""){
//            distanceToShowInit = command.value("distanceToShowInit").toDouble();
//        }
//        if (QString::number(command.value("fulldistancesInit").toInt())!= ""){
//            fulldistanceInit = command.value("fulldistancesInit").toDouble();
//        }    if (QString::number(command.value("thresholdInitA").toInt())!= ""){
//            thresholdInit = command.value("thresholdInitA").toDouble();
//        }

//        qDebug() << "GetSettingDisplay received:";
//        qDebug() << "sagFactorInit:" << sagFactorInit;
//        qDebug() << "samplingRateInit:" << samplingRateInit;
//        qDebug() << "distanceToStartInit:" << distanceToStartInit;
//        qDebug() << "distanceToShowInit:" << distanceToShowInit;
//        qDebug() << "fulldistanceInit:" << fulldistanceInit;
////    }

////    if (getCommand == "updatethresholdParam") {
//    if (QString::number(command.value("thresholdInitA").toInt())!= ""){
//        thresholdInit = command.value("thresholdInitA").toDouble();
//    }
//        qDebug() << "getThreshold received:";
//        qDebug() << "thresholdInit:" << thresholdInit;
////    }

//    // After processing the messages, use the updated values in calculations
//    qDebug() << "Debug display parameter:" << sagFactorInit << samplingRateInit << distanceToStartInit << distanceToShowInit << thresholdInit;
//    // Setting parameters
//    sagFactor = sagFactorInit;       // SAG factor
//    samplingRate = samplingRateInit; // Sampling rate (meters per sample)
//    distanceToStart = distanceToStartInit * 1000; // Starting distance (km)
//    distanceToShow = distanceToShowInit * 1000;   // Ending distance (km)
//    valuetheshold = thresholdInit; // Threshold value
//    const float threshold = valuetheshold / 32768.0f;


//        // Path of the file
//        QString filePath = "/home/pi/data0.raw"; //adc_ch1_voltage.dat
//        QFile file(filePath);

//        // Check if the file can be opened
//        if (!file.open(QIODevice::ReadOnly)) {
//            qDebug() << "Unable to open file:" << filePath;
//            return;
//        }

//        // Read data from the file
//        QByteArray data = file.readAll();
//        file.close();

//        qDebug() << "Debug display parameter:" << sagFactor << samplingRate << distanceToStart << distanceToShow << valuetheshold << threshold;

//        // Calculate total distance adjusted by SAG factor
//        float totalDistance = (distanceToShow - distanceToStart) * sagFactor;

//        // Calculate total number of points (distance / point distance) adjusted by sampling rate

//        const float pointDistance =  samplingRate / distancePointBetweenPoint; // Adjust point distance using sampling rate ยิ่งsampling rate มากใันก็จะยิ่งหยาบมากขึ้น
//        int totalPoints = static_cast<int>(std::ceil(totalDistance / pointDistance));

//        // Read data from file and normalize values
//        std::vector<float> normalizedValues;
//        const uint8_t* ptr = reinterpret_cast<const uint8_t*>(data.constData());
//        const uint8_t* endPtr = ptr + data.size();


//        while (ptr + 2 <= endPtr) {
//            // Read the raw 2 bytes as a signed 16-bit integer
//            int16_t signedValue = static_cast<int16_t>((static_cast<uint8_t>(ptr[1]) << 8) | static_cast<uint8_t>(ptr[0]));

//            // Normalize the value (handling both negative and positive values)
//            float normalizedValue = static_cast<float>(signedValue) / 32768.0f;

//            // Store the normalized value in the vector
//            normalizedValues.push_back(normalizedValue);

//            // Move the pointer forward by 2 bytes
//            ptr += 2;
//        }


//        // Find the value that matches the threshold
//        auto startIt = std::find_if(normalizedValues.begin(), normalizedValues.end(), [threshold](float val) {
//            return val >= threshold; // Find the value greater than or equal to threshold
//        });

//        if (startIt == normalizedValues.end()) {
//            qDebug() << "Threshold value not found in data";
//            return;
//        }

//        // Get the starting index of the found threshold
//        int startIndex = std::distance(normalizedValues.begin(), startIt);

//        // Create result (X: distance, Y: normalized voltage)
//        std::vector<std::pair<float, float>> result; // (X: distance, Y: normalized voltage)
//        float currentDistance = distanceToStart;

//        // Get the values starting from the threshold found
//        for (int i = startIndex; i < startIndex + totalPoints && i < normalizedValues.size(); ++i) {
//            // Set Y value (normalized voltage)
//            float currentValue = normalizedValues[i];

//            // Add the point to the result
//            result.emplace_back(currentDistance, currentValue);

//            // Increment the distance by the point distance adjusted by sampling rate
//            currentDistance += pointDistance;
//        }

//        // Display the result
//        qDebug() << "Result (Distance, Normalized Voltage):";
//        for (const auto& [distance, voltage] : result) {
//            qDebug() << "X:" << distance << "m, Y:" << voltage << "mV";
//        }

//        // Summary
//        qDebug() << "SAG Factor:" << sagFactor;
//        qDebug() << "Sampling Rate (m/samples):" << samplingRate;
//        qDebug() << "Distance to Start:" << distanceToStart;
//        qDebug() << "Distance to Show:" << distanceToShow;
//        qDebug() << "Total Distance after SAG Adjustment:" << totalDistance;
//        qDebug() << "Total Points to Plot:" << totalPoints;
//        rawdataArrayA = "";
//        // Pack the distance and voltage data into a JSON format
//        QString rawDataString = "[";
//        if(getCommand == "startPlotingDataPhaseA"){
//            QJsonObject mainObject;
//            QJsonArray dist,volt;
//            QJsonDocument jsonDoc,loraDoc;
//            QJsonObject lora_sent;
//            for (size_t i = 0; i < result.size(); i++) {
//                const auto& [distance, voltage] = result[i];
//                dist.push_back(distance);
//                volt.push_back(voltage);
//            }
//            mainObject.insert("objectName", "dataPlotingA");
//            mainObject.insert("distance", dist);
//            mainObject.insert("voltage", volt);
//            jsonDoc.setObject(mainObject);
//            QString raw_data = QJsonDocument(mainObject).toJson(QJsonDocument::Compact).toStdString().c_str();
//            qDebug() << "mainObject:" << raw_data;

//    //        QString rawDataString = "[";
//    //        for (size_t i = 0; i < result.size(); ++i) {
//    //            const auto& [distance, voltage] = result[i];
//    //            // Format each data point
//    //            QString pointData = QString(
//    //                                        "\"distance\":%1,"
//    //                                        "\"voltage \":%2}")
//    //                                    .arg(distance, 0, 'f', 6) // 6 decimal places
//    //                                    .arg(voltage, 0, 'f', 6); // 6 decimal places
//    //            rawDataString += pointData;
//    //            // Add a comma between data points
//    //            if (i < result.size() - 1) {
//    //                rawDataString += ",";
//    //            }
//    //        }
//    //        rawDataString += "]";

//            // Create the final JSON array
//    //        rawdataArray = QString("{\"objectName\":\"dataPlotingA\","
//    //                                       "\"packageRawDataA\":%1}").arg(raw_data);
//            rawdataArrayA = raw_data;
//            qDebug() << "rawdataArray" <<raw_data ;
//            if(temp == ""){
//                temp = rawdataArrayA;
//            }
//            else if(rawdataArrayA != temp && count > 2){
//                temp = rawdataArrayA;
//    //            emit cppCommand(temp);
//                emit plotingDataPhaseA(temp);
//            }

//        if(count > 2){

//        }else{
//            count++;
//        }
//        emit plotingDataPhaseA(raw_data);
//        }

//}
void mainwindows::calculateDataPhaseB(QString msg) {
//    qDebug() << "calculateDataPhaseB:" << msg;
//    QJsonDocument d = QJsonDocument::fromJson(msg.toUtf8());
//    QJsonObject command = d.object();
//    QString getCommand = QJsonValue(command["objectName"]).toString();
//    // Default values
//    static double thresholdInit = 0;
//    static double sagFactorInit = 0;
//    static double samplingRateInit = 0;
//    static double distanceToStartInit = 0;
//    static double distanceToShowInit = 0;
//    static double fulldistanceInit = 0;
//    // Update parameters only if the relevant object is found
//    if (getCommand == "updataParameterDisplay") {
//        if (QString::number(command.value("sagFactorInit").toInt())!= ""){
//            sagFactorInit = command.value("sagFactorInit").toDouble();
//        }
//        if (QString::number(command.value("samplingRateInit").toInt())!= ""){
//            samplingRateInit = command.value("samplingRateInit").toDouble();
//        }
//        if (QString::number(command.value("distanceToStartInit").toInt())!= ""){
//            distanceToStartInit = command.value("distanceToStartInit").toDouble();
//        }
//        if (QString::number(command.value("distanceToShowInit").toInt())!= ""){
//            distanceToShowInit = command.value("distanceToShowInit").toDouble();
//        }
//        if (QString::number(command.value("fulldistancesInit").toInt())!= ""){
//            fulldistanceInit = command.value("fulldistancesInit").toDouble();
//        }    if (QString::number(command.value("thresholdInitA").toInt())!= ""){
//            thresholdInit = command.value("thresholdInitA").toDouble();
//        }

//        qDebug() << "GetSettingDisplay received:";
//        qDebug() << "sagFactorInit:" << sagFactorInit;
//        qDebug() << "samplingRateInit:" << samplingRateInit;
//        qDebug() << "distanceToStartInit:" << distanceToStartInit;
//        qDebug() << "distanceToShowInit:" << distanceToShowInit;
//        qDebug() << "fulldistanceInit:" << fulldistanceInit;
//    }

//    if (getCommand == "updatethresholdParam") {
//    if (QString::number(command.value("thresholdInitB").toInt())!= ""){
//        thresholdInit = command.value("thresholdInitB").toDouble();
//    }
//        qDebug() << "getThreshold received:";
//        qDebug() << "thresholdInit:" << thresholdInit;
//    }

//    // After processing the messages, use the updated values in calculations
//    qDebug() << "Debug display parameter:" << sagFactorInit << samplingRateInit << distanceToStartInit << distanceToShowInit << thresholdInit;
//    // Setting parameters
//    sagFactor = sagFactorInit;       // SAG factor
//    samplingRate = samplingRateInit; // Sampling rate (meters per sample)
//    distanceToStart = distanceToStartInit * 1000; // Starting distance (km)
//    distanceToShow = distanceToShowInit * 1000;   // Ending distance (km)
//    valuetheshold = thresholdInit; // Threshold value
//    const float threshold = valuetheshold / 32768.0f;


//        // Path of the file
//        QString filePath = "/home/pi/data1.raw"; //adc_ch1_voltage.dat
//        QFile file(filePath);

//        // Check if the file can be opened
//        if (!file.open(QIODevice::ReadOnly)) {
//            qDebug() << "Unable to open file:" << filePath;
//            return;
//        }

//        // Read data from the file
//        QByteArray data = file.readAll();
//        file.close();

//        qDebug() << "Debug display parameter:" << sagFactor << samplingRate << distanceToStart << distanceToShow << valuetheshold << threshold;

//        // Calculate total distance adjusted by SAG factor
//        float totalDistance = (distanceToShow - distanceToStart) * sagFactor;

//        // Calculate total number of points (distance / point distance) adjusted by sampling rate

//        const float pointDistance =  samplingRate / distancePointBetweenPoint; // Adjust point distance using sampling rate ยิ่งsampling rate มากใันก็จะยิ่งหยาบมากขึ้น
//        int totalPoints = static_cast<int>(std::ceil(totalDistance / pointDistance));

//        // Read data from file and normalize values
//        std::vector<float> normalizedValues;
//        const uint8_t* ptr = reinterpret_cast<const uint8_t*>(data.constData());
//        const uint8_t* endPtr = ptr + data.size();


//        while (ptr + 2 <= endPtr) {
//            // Read the raw 2 bytes as a signed 16-bit integer
//            int16_t signedValue = static_cast<int16_t>((static_cast<uint8_t>(ptr[1]) << 8) | static_cast<uint8_t>(ptr[0]));

//            // Normalize the value (handling both negative and positive values)
//            float normalizedValue = static_cast<float>(signedValue) / 32768.0f;

//            // Store the normalized value in the vector
//            normalizedValues.push_back(normalizedValue);

//            // Move the pointer forward by 2 bytes
//            ptr += 2;
//        }


//        // Find the value that matches the threshold
//        auto startIt = std::find_if(normalizedValues.begin(), normalizedValues.end(), [threshold](float val) {
//            return val >= threshold; // Find the value greater than or equal to threshold
//        });

//        if (startIt == normalizedValues.end()) {
//            qDebug() << "Threshold value not found in data";
//            return;
//        }

//        // Get the starting index of the found threshold
//        int startIndex = std::distance(normalizedValues.begin(), startIt);

//        // Create result (X: distance, Y: normalized voltage)
//        std::vector<std::pair<float, float>> result; // (X: distance, Y: normalized voltage)
//        float currentDistance = distanceToStart;

//        // Get the values starting from the threshold found
//        for (int i = startIndex; i < startIndex + totalPoints && i < normalizedValues.size(); ++i) {
//            // Set Y value (normalized voltage)
//            float currentValue = normalizedValues[i];

//            // Add the point to the result
//            result.emplace_back(currentDistance, currentValue);

//            // Increment the distance by the point distance adjusted by sampling rate
//            currentDistance += pointDistance;
//        }

//        // Display the result
//        qDebug() << "Result (Distance, Normalized Voltage):";
//        for (const auto& [distance, voltage] : result) {
//            qDebug() << "X:" << distance << "m, Y:" << voltage << "mV";
//        }

//        // Summary
//        qDebug() << "SAG Factor:" << sagFactor;
//        qDebug() << "Sampling Rate (m/samples):" << samplingRate;
//        qDebug() << "Distance to Start:" << distanceToStart;
//        qDebug() << "Distance to Show:" << distanceToShow;
//        qDebug() << "Total Distance after SAG Adjustment:" << totalDistance;
//        qDebug() << "Total Points to Plot:" << totalPoints;
//        rawdataArrayB = "";
//        // Pack the distance and voltage data into a JSON format

//        QJsonObject mainObject;
//        QJsonArray dist,volt;
//        QJsonDocument jsonDoc,loraDoc;
//        QJsonObject lora_sent;
//        for (size_t i = 0; i < result.size(); ++i) {
//            const auto& [distance, voltage] = result[i];
//            dist.push_back(distance);
//            volt.push_back(voltage);
//        }
//        mainObject.insert("objectName", "dataPlotingB");
//        mainObject.insert("distance", dist);
//        mainObject.insert("voltage", volt);
//        jsonDoc.setObject(mainObject);
//        QString raw_data = QJsonDocument(mainObject).toJson(QJsonDocument::Compact).toStdString().c_str();
//        qDebug() << "mainObject:" << raw_data;

////        QString rawDataString = "[";
////        for (size_t i = 0; i < result.size(); ++i) {
////            const auto& [distance, voltage] = result[i];
////            // Format each data point
////            QString pointData = QString(
////                                        "\"distance\":%1,"
////                                        "\"voltage \":%2}")
////                                    .arg(distance, 0, 'f', 6) // 6 decimal places
////                                    .arg(voltage, 0, 'f', 6); // 6 decimal places
////            rawDataString += pointData;
////            // Add a comma between data points
////            if (i < result.size() - 1) {
////                rawDataString += ",";
////            }
////        }
////        rawDataString += "]";

//        // Create the final JSON array
////        rawdataArray = QString("{\"objectName\":\"dataPlotingA\","
////                                       "\"packageRawDataA\":%1}").arg(raw_data);
//        rawdataArrayB = raw_data;
//        qDebug() << "rawdataArray" <<raw_data ;
//        if(temp2 == ""){
//            temp2 = rawdataArrayB;
//        }
//        else if(rawdataArrayB != temp2 && count2 > 2){
//            temp2 = rawdataArrayB;
//            emit cppCommand(temp2);
//        }

//    if(count2 > 2){

//    }else{
//        count2++;
//    }
}

void mainwindows::calculateDataPhaseC(QString msg) {
//    qDebug() << "calculateDataPhaseC:" << msg;
//    QJsonDocument d = QJsonDocument::fromJson(msg.toUtf8());
//    QJsonObject command = d.object();
//    QString getCommand = QJsonValue(command["objectName"]).toString();
//    // Default values
//    static double thresholdInit = 0;
//    static double sagFactorInit = 0;
//    static double samplingRateInit = 0;
//    static double distanceToStartInit = 0;
//    static double distanceToShowInit = 0;
//    static double fulldistanceInit = 0;
//    // Update parameters only if the relevant object is found
//    if (getCommand == "updataParameterDisplay") {
//        if (QString::number(command.value("sagFactorInit").toInt())!= ""){
//            sagFactorInit = command.value("sagFactorInit").toDouble();
//        }
//        if (QString::number(command.value("samplingRateInit").toInt())!= ""){
//            samplingRateInit = command.value("samplingRateInit").toDouble();
//        }
//        if (QString::number(command.value("distanceToStartInit").toInt())!= ""){
//            distanceToStartInit = command.value("distanceToStartInit").toDouble();
//        }
//        if (QString::number(command.value("distanceToShowInit").toInt())!= ""){
//            distanceToShowInit = command.value("distanceToShowInit").toDouble();
//        }
//        if (QString::number(command.value("fulldistancesInit").toInt())!= ""){
//            fulldistanceInit = command.value("fulldistancesInit").toDouble();
//        }    if (QString::number(command.value("thresholdInitA").toInt())!= ""){
//            thresholdInit = command.value("thresholdInitA").toDouble();
//        }

//        qDebug() << "GetSettingDisplay received:";
//        qDebug() << "sagFactorInit:" << sagFactorInit;
//        qDebug() << "samplingRateInit:" << samplingRateInit;
//        qDebug() << "distanceToStartInit:" << distanceToStartInit;
//        qDebug() << "distanceToShowInit:" << distanceToShowInit;
//        qDebug() << "fulldistanceInit:" << fulldistanceInit;
//    }

//    if (getCommand == "updatethresholdParam") {
//    if (QString::number(command.value("thresholdInitC").toInt())!= ""){
//        thresholdInit = command.value("thresholdInitC").toDouble();
//    }
//        qDebug() << "getThreshold received:";
//        qDebug() << "thresholdInit:" << thresholdInit;
//    }

//    // After processing the messages, use the updated values in calculations
//    qDebug() << "Debug display parameter:" << sagFactorInit << samplingRateInit << distanceToStartInit << distanceToShowInit << thresholdInit;
//    // Setting parameters
//    sagFactor = sagFactorInit;       // SAG factor
//    samplingRate = samplingRateInit; // Sampling rate (meters per sample)
//    distanceToStart = distanceToStartInit * 1000; // Starting distance (km)
//    distanceToShow = distanceToShowInit * 1000;   // Ending distance (km)
//    valuetheshold = thresholdInit; // Threshold value
//    const float threshold = valuetheshold / 32768.0f;


//        // Path of the file
//        QString filePath = "/home/pi/data3.raw"; //adc_ch1_voltage.dat
//        QFile file(filePath);

//        // Check if the file can be opened
//        if (!file.open(QIODevice::ReadOnly)) {
//            qDebug() << "Unable to open file:" << filePath;
//            return;
//        }

//        // Read data from the file
//        QByteArray data = file.readAll();
//        file.close();

//        qDebug() << "Debug display parameter:" << sagFactor << samplingRate << distanceToStart << distanceToShow << valuetheshold << threshold;

//        // Calculate total distance adjusted by SAG factor
//        float totalDistance = (distanceToShow - distanceToStart) * sagFactor;

//        // Calculate total number of points (distance / point distance) adjusted by sampling rate

//        const float pointDistance =  samplingRate / distancePointBetweenPoint; // Adjust point distance using sampling rate ยิ่งsampling rate มากใันก็จะยิ่งหยาบมากขึ้น
//        int totalPoints = static_cast<int>(std::ceil(totalDistance / pointDistance));

//        // Read data from file and normalize values
//        std::vector<float> normalizedValues;
//        const uint8_t* ptr = reinterpret_cast<const uint8_t*>(data.constData());
//        const uint8_t* endPtr = ptr + data.size();


//        while (ptr + 2 <= endPtr) {
//            // Read the raw 2 bytes as a signed 16-bit integer
//            int16_t signedValue = static_cast<int16_t>((static_cast<uint8_t>(ptr[1]) << 8) | static_cast<uint8_t>(ptr[0]));

//            // Normalize the value (handling both negative and positive values)
//            float normalizedValue = static_cast<float>(signedValue) / 32768.0f;

//            // Store the normalized value in the vector
//            normalizedValues.push_back(normalizedValue);

//            // Move the pointer forward by 2 bytes
//            ptr += 2;
//        }


//        // Find the value that matches the threshold
//        auto startIt = std::find_if(normalizedValues.begin(), normalizedValues.end(), [threshold](float val) {
//            return val >= threshold; // Find the value greater than or equal to threshold
//        });

//        if (startIt == normalizedValues.end()) {
//            qDebug() << "Threshold value not found in data";
//            return;
//        }

//        // Get the starting index of the found threshold
//        int startIndex = std::distance(normalizedValues.begin(), startIt);

//        // Create result (X: distance, Y: normalized voltage)
//        std::vector<std::pair<float, float>> result; // (X: distance, Y: normalized voltage)
//        float currentDistance = distanceToStart;

//        // Get the values starting from the threshold found
//        for (int i = startIndex; i < startIndex + totalPoints && i < normalizedValues.size(); ++i) {
//            // Set Y value (normalized voltage)
//            float currentValue = normalizedValues[i];

//            // Add the point to the result
//            result.emplace_back(currentDistance, currentValue);

//            // Increment the distance by the point distance adjusted by sampling rate
//            currentDistance += pointDistance;
//        }

//        // Display the result
//        qDebug() << "Result (Distance, Normalized Voltage):";
//        for (const auto& [distance, voltage] : result) {
//            qDebug() << "X:" << distance << "m, Y:" << voltage << "mV";
//        }

//        // Summary
//        qDebug() << "SAG Factor:" << sagFactor;
//        qDebug() << "Sampling Rate (m/samples):" << samplingRate;
//        qDebug() << "Distance to Start:" << distanceToStart;
//        qDebug() << "Distance to Show:" << distanceToShow;
//        qDebug() << "Total Distance after SAG Adjustment:" << totalDistance;
//        qDebug() << "Total Points to Plot:" << totalPoints;
//        rawdataArrayC = "";
//        // Pack the distance and voltage data into a JSON format

//        QJsonObject mainObject;
//        QJsonArray dist,volt;
//        QJsonDocument jsonDoc,loraDoc;
//        QJsonObject lora_sent;
//        for (size_t i = 0; i < result.size(); ++i) {
//            const auto& [distance, voltage] = result[i];
//            dist.push_back(distance);
//            volt.push_back(voltage);
//        }
//        mainObject.insert("objectName", "dataPlotingC");
//        mainObject.insert("distance", dist);
//        mainObject.insert("voltage", volt);
//        jsonDoc.setObject(mainObject);
//        QString raw_data = QJsonDocument(mainObject).toJson(QJsonDocument::Compact).toStdString().c_str();
//        qDebug() << "mainObject:" << raw_data;

////        QString rawDataString = "[";
////        for (size_t i = 0; i < result.size(); ++i) {
////            const auto& [distance, voltage] = result[i];
////            // Format each data point
////            QString pointData = QString(
////                                        "\"distance\":%1,"
////                                        "\"voltage \":%2}")
////                                    .arg(distance, 0, 'f', 6) // 6 decimal places
////                                    .arg(voltage, 0, 'f', 6); // 6 decimal places
////            rawDataString += pointData;
////            // Add a comma between data points
////            if (i < result.size() - 1) {
////                rawDataString += ",";
////            }
////        }
////        rawDataString += "]";

//        // Create the final JSON array
////        rawdataArray = QString("{\"objectName\":\"dataPlotingA\","
////                                       "\"packageRawDataA\":%1}").arg(raw_data);
//        rawdataArrayC = raw_data;
//        qDebug() << "rawdataArray" <<raw_data ;
//        if(temp3 == ""){
//            temp3 = rawdataArrayC;
//        }
//        else if(rawdataArrayB != temp3 && count3 > 2){
//            temp3 = rawdataArrayC;
//            emit cppCommand(temp3);
//        }

//    if(count3 > 2){

//    }else{
//        count3++;
//    }
}

void mainwindows::manualtest(QString msg) {
    qDebug() << "manualtest:" << msg;
    if(msg == "ManualTest"){
        QJsonDocument jsonDoc;
        QJsonObject Param;
        Param.insert("objectName","ManualTest");
        jsonDoc.setObject(Param);
        QString raw_data = QJsonDocument(Param).toJson(QJsonDocument::Compact).toStdString().c_str();
        qDebug() << "Test button Manual test:" << raw_data;
        emit sendMessage(raw_data);
    }
}


void mainwindows::patterntest(QString msg) {
    qDebug() << "PatternTest:" << msg;
    if(msg == "PatternTest"){
//        uint8_t n = obj["number"].toInt();
        QJsonDocument jsonDoc;
        QJsonObject Param;
        Param.insert("objectName","PatternTest");
        Param.insert("number",10);//
        QString raw_data = QJsonDocument(Param).toJson(QJsonDocument::Compact).toStdString().c_str();
        emit sendMessage(raw_data);
    }
}


//void mainwindows::reSamplingNormalization(
//    const std::vector<std::pair<float, float>>& result,
//    float distanceToStart, float distanceToShow,
//    float samplingRate, float sagFactor, float thresholdA) {

//    std::vector<std::pair<float, double>> peakPoints;
//    qDebug() << "reSamplingNormalization with params:"
//             << "distanceToStart:" << distanceToStart
//             << "distanceToShow:" << distanceToShow
//             << "samplingRate:" << samplingRate
//             << "sagFactor:" << sagFactor
//             << "thresholdA:" << thresholdA;

//    if (result.size() < 3) {
//        qDebug() << "Not enough data points to detect peaks.";
//        return;
//    }

//    qDebug() << "Finding peaks from voltage data...";
//    for (size_t i = 1; i < result.size() - 1; ++i) {
//        double prevVoltage = result[i - 1].second;
//        double currentVoltage = result[i].second;
//        double nextVoltage = result[i + 1].second;

//        if (prevVoltage < currentVoltage && currentVoltage > nextVoltage && currentVoltage >= thresholdA) {
//            peakPoints.push_back(result[i]);
//            qDebug() << "Peak found at X:" << result[i].first << "m, Y:" << currentVoltage << "mV";
//        }
//    }

//    qDebug() << "Total Peaks Found:" << peakPoints.size();

//    // ปรับค่า X ให้อยู่ในระยะที่ต้องการแสดงผล
//    QJsonObject mainObject;
//    QJsonArray dist, volt;
//    for (const auto& point : peakPoints) {
//        if (point.first >= distanceToStart && point.first <= distanceToStart + distanceToShow) {
//            dist.push_back(point.first);
//            volt.push_back(point.second * sagFactor);  // ใช้ sagFactor ในการปรับค่า
//        }
//    }

//    mainObject.insert("objectName", "dataPlotingA");
//    mainObject.insert("distance", dist);
//    mainObject.insert("voltage", volt);
//    QJsonDocument jsonDoc(mainObject);
//    QString raw_data = jsonDoc.toJson(QJsonDocument::Compact);

//    qDebug() << "Updated mainObject:" << raw_data;

//    rawdataArrayA = raw_data;
//    if (temp.isEmpty() || (rawdataArrayA != temp && count > 2)) {
//        temp = rawdataArrayA;
//    }

//    emit plotingDataPhaseA(raw_data);
//}



//void mainwindows::reSamplingNormalization(const std::vector<std::pair<float, float>>& result) {
//    std::vector<std::pair<float, double>> peakPoints;  // เก็บ (X, Y) ของพีค
//    qDebug() << "reSamplingNormalization" << result;

//    if (result.size() < 3) {  // ต้องมีอย่างน้อย 3 จุดเพื่อหาพีค
//        qDebug() << "Not enough data points to detect peaks.";
//        return;
//    }

//    qDebug() << "Finding peaks from voltage data...";

//    for (size_t i = 1; i < result.size() - 1; ++i) {
//        double prevVoltage = result[i - 1].second;
//        double currentVoltage = result[i].second;
//        double nextVoltage = result[i + 1].second;

//        // ตรวจสอบว่าเป็นจุด Peak หรือไม่
//        if (prevVoltage < currentVoltage && currentVoltage > nextVoltage) {
//            peakPoints.push_back(result[i]);
//            qDebug() << "Peak found at X:" << result[i].first << "m, Y:" << currentVoltage << "mV";
//        }
//    }

//    qDebug() << "Total Peaks Found:" << peakPoints.size();

//    if (peakPoints.size() < 3) {
//        qDebug() << "Not enough peak points for smoothing.";
//    } else {
//        // Gaussian Smoothing
//        int windowSize = 10; //
//        double sigma = 1.0;
//        int halfWindow = windowSize / 2;
//        std::vector<double> kernel(windowSize);
//        double sum = 0;

//        for (int i = -halfWindow; i <= halfWindow; ++i) {
//            kernel[i + halfWindow] = exp(-0.5 * (i * i) / (sigma * sigma));
//            sum += kernel[i + halfWindow];
//        }
//        for (double& k : kernel) k /= sum;

//        std::vector<std::pair<float, double>> smoothPeaks(peakPoints.size());
//        for (size_t i = 0; i < peakPoints.size(); ++i) {
//            double weightedSum = 0;
//            double weightSum = 0;

//            for (int j = -halfWindow; j <= halfWindow; ++j) {
//                int index = i + j;
//                if (index >= 0 && index < peakPoints.size()) {
//                    weightedSum += peakPoints[index].second * kernel[j + halfWindow];
//                    weightSum += kernel[j + halfWindow];
//                }
//            }
//            smoothPeaks[i] = {peakPoints[i].first, weightedSum / weightSum};
//        }

//        peakPoints = smoothPeaks;
//    }

//    QJsonObject mainObject;
//    QJsonArray dist, volt;
//    QJsonDocument jsonDoc;

//    for (const auto& point : peakPoints) {
//        dist.push_back(point.first);
//        volt.push_back(point.second);
//    }

//    mainObject.insert("objectName", "dataPlotingA");
//    mainObject.insert("distance", dist);
//    mainObject.insert("voltage", volt);
//    jsonDoc.setObject(mainObject);
//    qDebug() << "result:" << volt << dist;
//    QString raw_data = jsonDoc.toJson(QJsonDocument::Compact);
//    qDebug() << "mainObject:" << raw_data << "volt:" << volt << "dist:" << dist;

//    rawdataArrayA = raw_data;

//    if (temp.isEmpty()) {
//        temp = rawdataArrayA;
//    } else if (rawdataArrayA != temp && count > 2) {
//        temp = rawdataArrayA;
//    }
//    emit plotingDataPhaseA(raw_data);
//}
