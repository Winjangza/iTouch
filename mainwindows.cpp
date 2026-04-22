#include "mainwindows.h"

mainwindows::mainwindows(QString platform,QObject *parent) : QObject(parent){
    qDebug() << "hello windows";
    system("sudo pigpiod");
    QThread::msleep(10);
    system("sudo pigs p 13 255");
    qDebug() << "SwVersion:" << SwVersion;
    if(platform == "VNC"){
        qDebug() << "hello VNC";
        port = 1235;
    }
    wedSocket = new WebServer(1239);
    peer = new PeerWs(1240);

    SocketServer = new ChatServer(port);
    mysql = new Database("ITouch", "pi", "rpi3!2024", "localhost", this);
    client = new SocketClient();
    clientNetwork = new SocketClient();
    clientNetworkIP = new SocketClient();
    reconnectTimerMaster = new QTimer();
    reconnectTimerSlave = new QTimer();
    networks = new Network;
    Timer = new QTimer();
    TimerPlotGraph = new QTimer();
    TimerPlotSurgeGraph = new QTimer();
    TimerPlotPatternGraph = new QTimer(this);

    screenShot = new ImageProvider();
    QTimer *timer = new QTimer(this);
    TimerVerify = new QTimer();
    QTimer *timer2 = new QTimer(this);
    setIPDisplay = new QTimer();
    networking = new NetworkMng(this);
    downloader = new FileDownloader;
    reconnectPing = new QTimer(this);


//    connect(reconnectTimerMaster,SIGNAL(timeout()),this,SLOT(reconnectTimerTimeoutMaster()));
    connect(reconnectTimerSlave,SIGNAL(timeout()),this,SLOT(reconnectTimerTimeoutSlave()));
    connect(TimerPlotGraph,SIGNAL(timeout()),this,SLOT(findMinMaxValues()));
    connect(TimerPlotSurgeGraph,SIGNAL(timeout()),this,SLOT(findMinMaxSurgeValues()));
    connect(TimerPlotPatternGraph, &QTimer::timeout, this, &mainwindows::findMinMaxPatternValues);
    connect(setIPDisplay,SIGNAL(timeout()),this,SLOT(iScreenIPNetwork()));

//    connect(Timer,SIGNAL(timeout()),this,SLOT(connectTimeOut()));
//    connect(SocketServer,SIGNAL(updatefireware(QString)),this,SLOT(updateSystemiTouch(QString)));
    connect(this, SIGNAL(getStatusOfButtonHidding()), mysql, SLOT(GetStatusOfButtonHidding()));
    connect(this, SIGNAL(updateStatusOfButtonHidding(QString)), mysql, SLOT(UpdateStatusOfButtonHidding(QString)));
    connect(this, SIGNAL(getTablePhaseA(QString)), mysql, SLOT(getMySqlPhaseA(QString)));
    connect(this, SIGNAL(getTablePhaseB(QString)), mysql, SLOT(getMySqlPhaseB(QString)));
    connect(this, SIGNAL(getTablePhaseC(QString)), mysql, SLOT(getMySqlPhaseC(QString)));
    connect(this, SIGNAL(deletedMySQLA(QString)), mysql, SLOT(deletedDataMySQLPhaseA(QString)));
    connect(this, SIGNAL(deletedMySQLB(QString)), mysql, SLOT(deletedDataMySQLPhaseB(QString)));
    connect(this, SIGNAL(deletedMySQLC(QString)), mysql, SLOT(deletedDataMySQLPhaseC(QString)));
    connect(this, SIGNAL(updateTablePhaseA(QString)), mysql, SLOT(updateTablePhaseA(QString)));
    connect(this, SIGNAL(updateTablePhaseB(QString)), mysql, SLOT(updateTablePhaseB(QString)));
    connect(this, SIGNAL(updateTablePhaseC(QString)), mysql, SLOT(updateTablePhaseC(QString)));
//    connect(this,SIGNAL(settingNetWorkandSNMP(QString)),mysql,SLOT(SettingNetworkSNMP(QString)));
    connect(this,SIGNAL(settingNetWorkandSNMP(QString)),client, SLOT(sendMessage(QString)));

    connect(this,SIGNAL(taggingpoint(QString)),mysql,SLOT(taggingpoint(QString)));
    connect(this, SIGNAL(cursorDistance(QString)), mysql, SLOT(getPositionDistance(QString)));
    connect(this, SIGNAL(moveCursor(QString)), mysql, SLOT(controlCursor(QString)));
    connect(this, SIGNAL(changeDistanceRange(QString)), mysql, SLOT(getChangeDistance(QString)));
    connect(this,SIGNAL(getDataThreshold()),mysql,SLOT(getThreshold()));
    connect(this,SIGNAL(preiodicSetting()),mysql,SLOT(getpreiodicInfo()));
    connect(this,SIGNAL(updateDisplayInfoSetting(QString)),mysql,SLOT(updateSettingInfo(QString)));
    connect(mysql,SIGNAL(cursorPosition(QString)),this,SLOT(cppSubmitTextFiled(QString)));
    connect(mysql,SIGNAL(updatanewdistance(QString)),this,SLOT(cppSubmitTextFiled(QString)));
    connect(mysql,SIGNAL(positionCursorChange(QString)),this,SLOT(cppSubmitTextFiled(QString)));
    connect(mysql, SIGNAL(cmdmsg(QString)),this,SLOT(cppSubmitTextFiled(QString)));
//------------------------------show information on Gerneral and graph ----------------------------------//displaysetting
    connect(mysql,SIGNAL(buttonStatusUpdated(QString)),this,SLOT(cppSubmitTextFiled(QString)));
    connect(downloader,SIGNAL(downloadCompleted(const QString)), this, SLOT(downloadCompleted(const QString)));
    connect(mysql, SIGNAL(selectMasterMode(QString,QString,QString,QString,QString,QString)),this,SLOT(selectMasterMode(QString,QString,QString,QString,QString,QString)));
    connect(this, SIGNAL(updateMasterMode(QString, QString, QString,QString)),mysql,SLOT(updateMasterMode(QString, QString, QString,QString)));
//------------------------------client command to Display----------------------------------//displaysetting
    connect(client,SIGNAL(newCommandProcess(QString)),this,SLOT(ServerCommand(QString)));
    connect(client,SIGNAL(newCommandProcess(QString)),this,SLOT(cppSubmitTextFiled(QString)));
    connect(clientNetwork,SIGNAL(newCommandProcess(QString)),this,SLOT(cppSubmitTextFiled(QString)));
    connect(mysql,SIGNAL(databasesToCpp(QString)),this,SLOT(cppSubmitTextFiled(QString)));

//------------------------------client command to Display----------------------------------//displaysetting
//    connect(clientNetwork,SIGNAL(newCommandProcess(QString)),this,SLOT(ServerCommand(QString)));
    connect(this,SIGNAL(sendToWeb(QString)),clientNetwork,SLOT(sendMessage(QString)));
//------------------------------Send command to client----------------------------------//
    connect(this, SIGNAL(rawdataPlot(QString)),client, SLOT(sendMessage(QString)));
    connect(this,SIGNAL(clearPatternGraph(QString)),client, SLOT(sendMessage(QString)));
    connect(this,SIGNAL(clearDisplay(QString)),client, SLOT(sendMessage(QString)));
    connect(this,SIGNAL(settingdisplay(QString)),client,SLOT(sendMessage(QString)));
    connect(this,SIGNAL(parameterThreshold(QString)),client,SLOT(sendMessage(QString)));
    connect(this,SIGNAL(sendMessage(QString)),client,SLOT(sendMessage(QString)));
    connect(this,SIGNAL(updateWeekly(QString)),client,SLOT(sendMessage(QString)));
    connect(this,SIGNAL(updateTimer(QString)),client,SLOT(sendMessage(QString)));
    connect(this, SIGNAL(updateRelay(QString)),client,SLOT(sendMessage(QString)));
    connect(this, SIGNAL(SettingAndUpdateMargin(QString)),client,SLOT(sendMessage(QString)));
    connect(this, SIGNAL(parameterMarginA(QString)),client,SLOT(sendMessage(QString)));
    connect(this, SIGNAL(parameterMarginB(QString)),client,SLOT(sendMessage(QString)));
    connect(this, SIGNAL(parameterMarginC(QString)),client,SLOT(sendMessage(QString)));
    connect(this,SIGNAL(updataListOfMarginA(QString)),client,SLOT(sendMessage(QString)));
    connect(this,SIGNAL(updataListOfMarginB(QString)),client,SLOT(sendMessage(QString)));
    connect(this,SIGNAL(updataListOfMarginC(QString)),client,SLOT(sendMessage(QString)));
    connect(this, SIGNAL(sendToSocket(QString)), client, SLOT(sendMessage(QString)));
    connect(this, SIGNAL(sendToServer(QString)), client, SLOT(sendMessage(QString)));

    connect(mysql,SIGNAL(SetNetworkSNMP(QString)),client,SLOT(sendMessage(QString)));
    //------------------------------Send command to client----------------------------------//
    connect(this, SIGNAL(rawdataPlot(QString)),client, SLOT(sendMessage(QString)));
    connect(this,SIGNAL(clearPatternGraph(QString)),client, SLOT(sendMessage(QString)));
    connect(this,SIGNAL(clearDisplay(QString)),client, SLOT(sendMessage(QString)));
//    connect(this,SIGNAL(settingdisplay(QString)),client,SLOT(sendMessage(QString)));
    connect(this,SIGNAL(parameterThreshold(QString)),client,SLOT(sendMessage(QString)));
    connect(this,SIGNAL(ButtonPattern(QString)),client,SLOT(sendMessage(QString)));
    //----------------------------get pattern datastorag from DB ---------------------------//
    connect(this,&mainwindows::getdatapatternDataDb,mysql,&Database::getdatapatternDataDb);
    connect(this,&mainwindows::sortnamePattern,mysql,&Database::sortByName);
    connect(this,&mainwindows::sortdatePattern,mysql,&Database::sortByDate);
    connect(this,&mainwindows::searchByName,mysql,&Database::searchByName);
    connect(this,&mainwindows::searchByDate,mysql,&Database::searchByDate);
//    connect(this,&mainwindows::captureScreenshot,this,&mainwindows::captureScreenshotseand);
    connect(this,&mainwindows::positionCursorChange,mysql,&Database::upDateCursorPosition);
    //----------------------------WebSocket---------------------------//
//    connect(this, SIGNAL(updateMasterMode(QString)),mysql,SLOT(updateMasterMode(QString)));
//    connect(mysql, SIGNAL(getupdateLocalNetwork(QString, QWebSocket *)),SocketServer,SLOT(sendMessage(QString, QWebSocket *)));
    connect(this, SIGNAL(broadcastMessage(QString)), wedSocket, SLOT(broadcastMessage(QString)));
    connect(wedSocket, SIGNAL(newCommandProcess(QString, QWebSocket*)), this, SLOT(manageData(QString, QWebSocket*)));
    connect(mysql, SIGNAL(getupdateLocalNetwork(QString, QWebSocket *)),wedSocket,SLOT(sendMessage(QString, QWebSocket *)));
    connect(mysql, SIGNAL(getUserMode(QString, QWebSocket *)),wedSocket,SLOT(sendMessage(QString, QWebSocket *)));
    connect(mysql, SIGNAL(sendtoMonitor(QString)),this,SLOT(cppSubmitTextFiled(QString)));
    connect(mysql, SIGNAL(databasesToCpp(QString)),this,SLOT(cppSubmitTextFiled(QString)));
//=====================================DISPLAY CONNECTED=========================================
    connect(this, &mainwindows::sendDisplay,peer, &PeerWs::sendMessageDisplay);
    connect(peer, &PeerWs::messageReceived, this, &mainwindows::handlePeerRx);

    mysql->getLocalMonitor();
    qDebug() << "mysql->" << mysql->gatewayMonitor << mysql->iPaddressMonitor;

    int ret=pthread_create(&idThread, NULL, ThreadFunc, this);
    if(ret==0){
        qDebug() <<("Thread created successfully.\n");
    }    else{
        qDebug() <<("Thread not created.\n");
    }
    ret = pthread_create(&idThread5, NULL, ThreadFuncRemoveFile, this);
    if (ret == 0) {
        qDebug() << "Thread created successfully.";
    } else {
        qDebug() << "Thread not created.";
    }

    serverPort = 5520;

//    getSetting();
    mysql->selectMasterMode();
    mysql->checkDatabaseAndUpdate();
    mysql->updateDataBase();
//    userMode = networks->userTypeSelect;
    qDebug() << "networks->userTypeSelect:" << networks->userTypeSelect << userMode;
//    mysql->getEventandAlarm("getEventandAlarm");
    connect(timer, &QTimer::timeout, this, &mainwindows::updateDateTime);
    timer->start(1000);
    qDebug() << "before debug_check_userMode:" << mainIP_address << userMode;
    networks->ip_master = mysql->IP_MASTER;
    networks->ip_slave  = mysql->IP_SLAVE;
    if(networks->userTypeSelect == "STANDALONE"){
//        mainIP_address = networks->ip_master;
    }else if(networks->userTypeSelect == "MASTER"){
        mainIP_address = networks->ip_master;
    }else if(networks->userTypeSelect == "SLAVE"){
        mainIP_address = networks->ip_slave;
    }
    userMode = networks->userTypeSelect;
    reconnectTimerSlave->start(5000);
    updateDateTime();
    setIPDisplay->start(1000);
    clientNetworkIP->createConnection("127.0.0.1", 1234);
    client->createConnection(mainIP_address, 5520);

    mysql->getDataRecordZoomValue();
    qDebug() << "after debug_check_userMode:" << mainIP_address << userMode;
    mysql->fetchUserModeInfo();
    QString lastFirmWare = SwVersion;
    QString lastFirmWareupdate = SwVersion;
    if (((mysql->swversion.split(" ").size() >= 2) & (lastFirmWare.split(" ").size() >= 2)) == false)
    {
        if (mysql->swversion != lastFirmWare)
        {
            qDebug() << "(lastFirmWare != currentFirmWare)" << "lastFirmWare for download" << lastFirmWare << "currentFirmWare running" << SwVersion;
            mysql->swversion=lastFirmWareupdate;
        }
    }
    else if (mysql->swversion != lastFirmWare)
    {
        double currentVersion =  QString(mysql->swversion.split(" ").at(1)).toDouble();
        double lastVersion = QString(lastFirmWare.split(" ").at(1)).toDouble();
        QString currentFirmWare = mysql->swversion.split(" ").at(0);
        lastFirmWare = lastFirmWare.split(" ").at(0);
        qDebug() << "lastFirmWare for download" << lastVersion << lastFirmWare << "currentFirmWare running" << currentVersion << currentFirmWare;
        if (lastVersion > currentVersion)
        {
            qDebug() << "(lastFirmWare != currentFirmWare)" << "lastFirmWare for download" << lastVersion << lastFirmWare << "currentFirmWare running" << currentVersion << currentFirmWare;
            mysql->swversion=lastFirmWareupdate;
        }
    }
    emit updateMasterMode(mysql->swversion);

#ifdef HwName
    selectVNCHW =true;
#else
    selectVNCHW =false;
#endif
    // สร้าง QJsonObject ตามปกติ
    QJsonObject obj;
    obj["objectName"] = "selectVNCHW";
    obj["selectVNCHW"] = selectVNCHW;
    QJsonDocument doc(obj);
    QString jsonString = QString::fromUtf8(doc.toJson(QJsonDocument::Compact));
    qDebug() << "selectVNCHW (delayed send):" << jsonString;

    QTimer::singleShot(500, [=]() {
        cppCommand(jsonString);
    });

    if (client->isConnected == true){
        connectToPLC();
        qDebug() << "TimeOutTimer timer->stop()";
    }
}

QString mainwindows::getUPTime()
{
    system("uptime -p > /etc/uptime");
    QString fileName = QString("/etc/uptime");
    return readLine(fileName);
}
QString mainwindows::readLine(QString fileName)
{
    QFile inputFile(fileName);
    inputFile.open(QIODevice::ReadOnly);
    if (!inputFile.isOpen())
        return "";

    QTextStream stream(&inputFile);
    QString line = stream.readLine();
    inputFile.close();
//    qDebug() << line;
    return line.trimmed();
}
void* mainwindows::ThreadFunc(void* pTr )
{
    mainwindows* pThis = static_cast<mainwindows*>(pTr);
    qDebug() << "ThreadFunc";
    pThis->loopGetInfo();
//    pThis->rt2200->ConnectToRT2200();
    return NULL;
}
void mainwindows::loopGetInfo(){
    while(1){
        QString currentTime = QTime::currentTime().toString("hh:mm:ss");
        if (currentTime != lastGetCurrentTime){
            lastGetCurrentTime = currentTime;
            QString currentTime = QTime::currentTime().toString("hh:mm:ss");
            QString currentDate = QDate::currentDate().toString("dd MMM yyyy");
            QString uptimeStr = getUPTime().replace("up","");
            QString message = QString("{\"menuID\":\"broadcastLocalTime\", \"currentTime\":\"%1\", \"currentDate\":\"%2\", \"uptime\":\"%3\"}")
                      .arg(currentTime)
                      .arg(currentDate)
                      .arg(uptimeStr);
            emit broadcastMessage(message);
        }

        QThread::msleep(200);
    }
}

void mainwindows::selectMasterMode(QString user, QString ipMaster, QString ipSlave, QString ipSNMP, QString ipTimerServer,QString swVersion){
    // master slave
    qDebug() << "selectMasterMode >>> user:" << user << "ipMaster" << ipMaster << "ipSlave" << ipSlave;

    networks->userTypeSelect = user;
    networks->ip_master = ipMaster;
    networks->ip_slave = ipSlave;
    networks->ip_snmp = ipSNMP;
    networks->ip_timeserver = ipTimerServer;
    SwVersion = swVersion;
    userMode = networks->userTypeSelect;
    qDebug() << "selectMasterMode:" << networks->userTypeSelect << networks->ip_master << networks->ip_slave << SwVersion << networks->ip_snmp << networks->ip_timeserver << userMode;

}
// mainwindows.cpp
void mainwindows::FileIPMonitor()
{
    const QString filePath = "/home/pi/ipmonitor.txt";
    QFile file(filePath);

    if (!file.exists()) {
        qWarning() << "[FileIPMonitor] file not found:" << filePath;
        return;
    }

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "[FileIPMonitor] cannot open file:" << filePath
                   << "err=" << file.errorString();
        return;
    }

    const QString content = QString::fromUtf8(file.readAll());
    file.close();

    qDebug() << "[FileIPMonitor] content:\n" << content;

    QRegularExpression reIP(R"(monitorIP\s*[:=]\s*\"([^\"]*)\")");
    QRegularExpression reGW(R"(monitorGateWay\s*[:=]\s*\"([^\"]*)\")");

    QRegularExpressionMatch m1 = reIP.match(content);
    QRegularExpressionMatch m2 = reGW.match(content);

    monitorIP = m1.hasMatch() ? m1.captured(1).trimmed() : QString();
    monitorGateWay = m2.hasMatch() ? m2.captured(1).trimmed() : QString();

    qDebug() << "[FileIPMonitor] parsed monitorIP =" << monitorIP;
    qDebug() << "[FileIPMonitor] parsed monitorGateWay =" << monitorGateWay;

    QJsonObject o;
    o["menuID"] = "ipMonitor";
    o["monitorIP"] = monitorIP;
    o["monitorGateWay"] = monitorGateWay;
    o["path"] = filePath;

    const QString json = QString::fromUtf8(QJsonDocument(o).toJson(QJsonDocument::Compact));
    qDebug() << "[FileIPMonitor] broadcast json =" << json;
    emit broadcastMessage(json);
}

void mainwindows::ensurePeerCreated()
{
    if (!peer) {
        qWarning() << "[ensurePeerCreated] peer is null";
        return;
    }

    static bool connectedOnce = false;
    if (connectedOnce)
        return;

    connectedOnce = true;

    connect(peer, &PeerWs::status, this, [this](const QString &s){
        qDebug() << "[PEER][STATUS]" << s;

        QJsonObject o;
        o["objectName"] = "DisplayPeerStatus";
        o["status"] = s;
        o["localMonitorIP"] = monitorIP;
        o["remoteMonitorIP"] = peerRemoteIp;

        cppCommand(QString::fromUtf8(QJsonDocument(o).toJson(QJsonDocument::Compact)));
    });

    connect(peer, &PeerWs::linkReady, this, [this](bool ok){
        qDebug() << "[PEER][READY]" << ok;

        QJsonObject o;
        o["objectName"] = "DisplayPeerLink";
        o["connected"] = ok;
        o["localMonitorIP"] = monitorIP;
        o["remoteMonitorIP"] = peerRemoteIp;

        cppCommand(QString::fromUtf8(QJsonDocument(o).toJson(QJsonDocument::Compact)));

        if (ok && peer) {
            QJsonObject req;
            req["type"] = "peer_time_request";
            req["ip"] = monitorIP;
            req["ts"] = QDateTime::currentDateTime().toString(Qt::ISODate);

            const QString reqMsg =
                    QString::fromUtf8(QJsonDocument(req).toJson(QJsonDocument::Compact));
            qDebug() << "[PEER] send peer_time_request =" << reqMsg;
            peer->sendMessageDisplay(reqMsg);

            QJsonObject hello;
            hello["type"] = "peer_hello";
            hello["ip"] = monitorIP;
            hello["ts"] = QDateTime::currentDateTime().toString(Qt::ISODate);

            const QString helloMsg =
                    QString::fromUtf8(QJsonDocument(hello).toJson(QJsonDocument::Compact));
            qDebug() << "[PEER] send peer_hello =" << helloMsg;
            peer->sendMessageDisplay(helloMsg);
        }
    });

    connect(peer, &PeerWs::messageReceived,
            this, &mainwindows::handlePeerRx);
}
void mainwindows::startDisplayPeer()
{
    ensurePeerCreated();

    const QString mode = userMode.trimmed().toUpper();

    if (mode != "MASTER" && mode != "SLAVE") {
        qWarning() << "[startDisplayPeer] invalid userMode =" << mode;
        return;
    }

    if (mode == "MASTER") {
        qDebug() << "[startDisplayPeer] MASTER listen on 1240";
        peer->start("MASTER", QString(), 1240);
    } else {
        if (monitorIP.isEmpty()) {
            qWarning() << "[startDisplayPeer] SLAVE monitorIP empty";
            return;
        }

        qDebug() << "[startDisplayPeer] SLAVE connect to" << monitorIP << ":1240";
        peer->start("SLAVE", monitorIP, 1240);
    }
}
void mainwindows::handlePeerRx(const QString &msg)
{
    qDebug().noquote() << "[PEER][RX]" << msg;

    QJsonParseError err;
    const QJsonDocument doc = QJsonDocument::fromJson(msg.toUtf8(), &err);
    if (err.error != QJsonParseError::NoError || !doc.isObject()) {
        qWarning() << "[PEER][RX] not JSON object:" << err.errorString();
        return;
    }

    const QJsonObject o = doc.object();
    const QString type = o.value("type").toString();

    if (type == "peer_hello") {
        const QString remoteIp = o.value("ip").toString().trimmed();
        if (!remoteIp.isEmpty())
            peerRemoteIp = remoteIp;

        qDebug() << "[PEER] peer_hello remote ip =" << peerRemoteIp;

        QJsonObject ui;
        ui["objectName"] = "DisplayPeerInfo";
        ui["localPeriodicTime"] = PeriodicTime;
        ui["remotePeriodicTime"] = recordPeriodic;
        ui["displayPeriodicTime"] = displayPeriodicTime;
        ui["remoteMonitorIP"] = peerRemoteIp;
        cppCommand(QString::fromUtf8(QJsonDocument(ui).toJson(QJsonDocument::Compact)));
        return;
    }

    if (type == "peer_time_request") {
        QJsonObject out;
        out["type"] = "peer_time";
        out["ip"] = monitorIP;
        out["Time"] = PeriodicTime.trimmed();
        out["ts"] = QDateTime::currentDateTime().toString(Qt::ISODate);

        const QString s = QString::fromUtf8(QJsonDocument(out).toJson(QJsonDocument::Compact));
        qDebug() << "[PEER] reply peer_time =" << s;
        sendPeerMessageReliable(s);
        return;
    }
    if (type == "peer_time" || type == "periodic_time") {
        const QString remoteIp = o.value("ip").toString().trimmed();
        const QString remoteTime = o.value("Time").toString().trimmed();

        if (!remoteIp.isEmpty())
            peerRemoteIp = remoteIp;

        if (!remoteTime.isEmpty())
            recordPeriodic = remoteTime;

        // ✅ สำคัญ:
        // ถ้ายัง remote อยู่ -> ให้ GUI โชว์เวลาของอีกฝั่ง
        // ถ้ากลับ local แล้ว -> ห้ามเอาเวลาของอีกฝั่งไปทับ GUI
        if (remoteMode) {
            displayPeriodicTime = recordPeriodic;

            QJsonObject uiRemote;
            uiRemote["objectName"] = "updateRemotePeriodic";
            uiRemote["Time"] = displayPeriodicTime;
            cppCommand(QString::fromUtf8(QJsonDocument(uiRemote).toJson(QJsonDocument::Compact)));

            qDebug() << "[PEER] remoteMode=true -> update GUI with remote time"
                     << "displayPeriodicTime =" << displayPeriodicTime;
        } else {
            qDebug() << "[PEER] remoteMode=false -> keep GUI on local time"
                     << "PeriodicTime(local)=" << PeriodicTime
                     << "recordPeriodic(remote)=" << recordPeriodic
                     << "displayPeriodicTime(gui stays)=" << displayPeriodicTime;
        }

        qDebug() << "[PEER] peer_time remoteIp =" << peerRemoteIp
                 << "PeriodicTime(local)=" << PeriodicTime
                 << "recordPeriodic(remote)=" << recordPeriodic
                 << "displayPeriodicTime(gui)=" << displayPeriodicTime;

        if (!PeriodicTime.trimmed().isEmpty() && !recordPeriodic.trimmed().isEmpty()) {
            sendRequestDisplay();
        }
        return;
    }
    // ------------------------------------------------------------
    // remote_command -> ให้เครื่องนี้ประมวลผลแทนอีกฝั่ง
    // ------------------------------------------------------------
    if (type == "remote_command") {
        const QString remoteObject = o.value("objectName").toString();
        qDebug() << "[PEER][REMOTE_COMMAND] objectName =" << remoteObject
                 << "msg =" << msg;

        QJsonObject localCmd = o;
        localCmd.remove("type");
        localCmd.remove("from");
        localCmd.remove("ts");
        // ✅ อย่าลบ remotePayload

        const QString forwardToLocal =
                QString::fromUtf8(QJsonDocument(localCmd).toJson(QJsonDocument::Compact));

        qDebug() << "[PEER][REMOTE_COMMAND] apply locally:" << forwardToLocal;

        cppSubmitTextFiled(forwardToLocal);
        return;
    }

    qDebug() << "[PEER][RX] unknown type =" << type;
}
void mainwindows::sendDisplayJson(const QJsonObject &o)
{
    const QString s = QString::fromUtf8(QJsonDocument(o).toJson(QJsonDocument::Compact));
    qDebug().noquote() << "[PEER][TX]" << s;
    emit sendDisplay(s);
}
void mainwindows::sendPeerMessageReliable(const QString &msg)
{
    if (!peer) {
        qWarning() << "[REMOTE] peer is null, cannot send";
        return;
    }

    qDebug() << "[REMOTE] send via peer. connected =" << peer->isConnected();
    peer->sendMessageDisplay(msg);
}
bool mainwindows::pingHost(const QString &ip) {
    QProcess ping;
    QStringList arguments;

    arguments << "-c" << "1" << "-W" << "1" << ip;

    ping.start("ping", arguments);
    bool finished = ping.waitForFinished(1500);  // 1.5 วินาที timeout
    if (!finished)
        return false;

    return (ping.exitCode() == 0);  // 0 = success
}


void mainwindows::reconnectTimerTimeoutSlave()
{
    qDebug() << "reconnectTimerTimeoutSlave:"
             << "mainIP_address=" << mainIP_address
             << "port=" << serverPort
             << "userMode(before)=" << userMode
             << "dbUSER=" << (mysql ? mysql->USER : QString())
             << "remoteMode=" << remoteMode;

    if (!mysql) return;

    const QDateTime now = QDateTime::currentDateTime();

    // ------------------------------------------------------------
    // 1) userMode: อัปเดตได้ แต่ "ห้ามเอาไปทับ mainIP_address"
    // ------------------------------------------------------------
    userMode = mysql->USER.trimmed();

    QString baseIP;
    if (userMode == "STANDALONE")      baseIP = mysql->IP_MASTER;
    else if (userMode == "MASTER")     baseIP = mysql->IP_MASTER;
    else if (userMode == "SLAVE")      baseIP = mysql->IP_SLAVE;
    else                               baseIP.clear();

    // ------------------------------------------------------------
    // 2) desiredIP: ใช้ mainIP_address เป็นหลัก (CHANGE set มา)
    //    ถ้าว่างค่อย fallback เป็น baseIP
    // ------------------------------------------------------------
    QString desiredIP = mainIP_address.trimmed();
    if (desiredIP.isEmpty()) {
        desiredIP = baseIP.trimmed();
        mainIP_address = desiredIP;
        qDebug() << "[INIT TARGET] mainIP_address was empty -> set to baseIP =" << baseIP;
    }

    qDebug() << "[TARGET]"
             << "userMode=" << userMode
             << "baseIP=" << baseIP
             << "mainIP_address(now)=" << mainIP_address
             << "desiredIP=" << desiredIP;

    // ------------------------------------------------------------
    // 3) Persistent state
    // ------------------------------------------------------------
    static int        lastConnState = -1;      // -1 unknown, 0 down, 1 up
    static bool       connectingInProgress = false;
    static QDateTime  lastConnectAttempt;
    static qint64     retryIntervalMs = 1000;          // เริ่มไวขึ้น
    static const qint64 retryIntervalMaxMs = 8000;     // max 8s
    static const qint64 connectTimeoutMs   = 8000;     // timeout จริง 8s

    static int        remotePingFailStreak = 0;
    static int        remotePingOkStreak   = 0;
    static const int  REMOTE_FAIL_THRESH   = 5;        // อย่าไวเกินไป

    static QDateTime  lastValidIPTime = QDateTime::currentDateTime();
    static QString    lastDesiredIP;

    // ping cache: อย่า ping ทุก tick
    static QDateTime  lastPingCheckTime;
    static bool       lastPingOk = false;
    static const qint64 pingCheckIntervalMs = 2000;

    // ------------------------------------------------------------
    // 4) target changed -> reset state + disconnect once
    // ------------------------------------------------------------
    if (!desiredIP.isEmpty() && desiredIP != lastDesiredIP) {
        qDebug() << "🔁 target changed:" << lastDesiredIP << "->" << desiredIP;

        lastDesiredIP = desiredIP;

        {
            QJsonObject o;
            o["objectName"] = "RemoteTarget";
            o["plcIP"] = desiredIP;
            o["remoteMode"] = remoteMode;
            cppCommand(QString::fromUtf8(QJsonDocument(o).toJson(QJsonDocument::Compact)));
        }

        lastConnState = -1;
        connectingInProgress = false;
        retryIntervalMs = 1000;
        lastConnectAttempt = QDateTime();
        remotePingFailStreak = 0;
        remotePingOkStreak   = 0;
        lastPingCheckTime    = QDateTime();
        lastPingOk           = false;

        recordPeriodic.clear();
        periodicInitialChecked = false;
        isVersion = false;

        qDebug() << "[TARGET RESET]"
                 << "desiredIP =" << desiredIP
                 << "PeriodicTime =" << PeriodicTime
                 << "recordPeriodic =" << recordPeriodic;

        if (client) {
            client->disconnectFromServer();
        }
        return;
    }

    // ------------------------------------------------------------
    // helper: read carrier
    // ------------------------------------------------------------
    auto readCarrier = [](const QString &iface) -> int {
        if (iface.isEmpty()) return -1;
        QFile f(QString("/sys/class/net/%1/carrier").arg(iface));
        if (!f.open(QIODevice::ReadOnly)) return -1;
        const QByteArray s = f.readAll().trimmed();
        if (s == "1") return 1;
        if (s == "0") return 0;
        return -1;
    };

    // TODO: ใส่ชื่อ interface จริงถ้าคุณรู้ เช่น "eth0", "enP1p1s0"
    QString localIface;
    const int carrier = readCarrier(localIface);
    const bool localLanUp   = (carrier == 1) || (carrier == -1);
    const bool localLanDown = (carrier == 0);

    const bool socketUp = (client && client->isConnected);

    // ถ้าต่อสำเร็จแล้ว ให้รีเซ็ต flag ทันที
    if (socketUp && connectingInProgress) {
        qDebug() << "[CONNECT] socketUp detected -> clear connectingInProgress";
        connectingInProgress = false;
    }

    // ------------------------------------------------------------
    // ping: ใช้เป็นข้อมูลเสริมเท่านั้น
    // - ping เฉพาะตอน socket ยังไม่ขึ้น
    // - ไม่ใช้ ping ไปตัดสินว่าถ้า socketUp แล้วต้อง disconnect
    // ------------------------------------------------------------
    bool remotePingOk = lastPingOk;

    if (!desiredIP.isEmpty() && !socketUp) {
        const bool shouldCheckPing =
            !lastPingCheckTime.isValid() ||
            (lastPingCheckTime.msecsTo(now) >= pingCheckIntervalMs);

        if (shouldCheckPing) {
            lastPingCheckTime = now;
            remotePingOk = pingHost(desiredIP);
            lastPingOk = remotePingOk;

            if (remotePingOk) {
                remotePingOkStreak++;
                remotePingFailStreak = 0;
            } else {
                remotePingFailStreak++;
                remotePingOkStreak = 0;
            }
        }
    } else if (socketUp) {
        // socket connected อยู่ -> อย่าให้ ping มากดสถานะลง
        remotePingOk = true;
        lastPingOk = true;
        remotePingOkStreak = 0;
        remotePingFailStreak = 0;
    }

    const bool remoteDown = (remotePingFailStreak >= REMOTE_FAIL_THRESH);

    // ✅ สำคัญ: connected ให้ยึด socket เป็นหลัก
    const bool nowConnected = socketUp;

    // ------------------------------------------------------------
    // interlock
    // ------------------------------------------------------------
    if (interlockUser) {
        countUser++;
        if (countUser > 5) {
            interlockUser = false;
            countUser = 0;
        }
        qDebug() << "[interlock] waiting..." << "countUser=" << countUser;
        return;
    }

    // ------------------------------------------------------------
    // local clientNetwork web
    // ------------------------------------------------------------
    if (clientNetwork && !clientNetwork->isConnected) {
        clientNetwork->createConnection("127.0.0.1", 1239);
        qDebug() << "clientNetworkcreateConnection:" << clientNetwork->isConnected;
    }

    // ------------------------------------------------------------
    // watchdog connect hang
    // ------------------------------------------------------------
    if (connectingInProgress && lastConnectAttempt.isValid()) {
        const qint64 connectingElapsed = lastConnectAttempt.msecsTo(now);
        if (connectingElapsed > connectTimeoutMs) {
            qDebug() << "⚠️ Connect timeout -> reset connectingInProgress"
                     << "elapsed=" << connectingElapsed
                     << "target=" << desiredIP
                     << "port=" << serverPort;

            connectingInProgress = false;

            if (client) {
                client->disconnectFromServer();
            }
        }
    }

    // ------------------------------------------------------------
    // TRANSITION
    // ------------------------------------------------------------
    if (nowConnected) {
        if (lastConnState != 1) {
            QJsonObject obj;
            obj["objectName"] = "Pop-up";
            obj["msg"]   = "Connected";
            obj["state"] = true;
            cppCommand(QJsonDocument(obj).toJson(QJsonDocument::Compact));

            connectingInProgress = false;
            retryIntervalMs = 1000;
            lastConnectAttempt = QDateTime();

            if (!isVersion) {
                connectToPLC();
                isVersion = true;
            }
        }

        lastConnState = 1;
    } else {
        if (lastConnState != 0) {
            QJsonObject obj;
            obj["objectName"] = "Pop-up";
            obj["msg"]   = localLanDown ? "Local LAN Disconnected" : "Disconnected";
            obj["state"] = false;
            obj["targetIP"] = desiredIP;
            obj["monitortIP"] = (mysql ? mysql->iPaddressMonitor : QString());
            obj["localIface"] = localIface;
            obj["carrier"]    = carrier;

            // debug info
            obj["socketUp"]   = socketUp;
            obj["pingOk"]     = remotePingOk;
            obj["remoteDown"] = remoteDown;
            obj["connectingInProgress"] = connectingInProgress;
            obj["retryIntervalMs"] = QString::number(retryIntervalMs);

            const QString json = QString::fromUtf8(QJsonDocument(obj).toJson(QJsonDocument::Compact));
            qDebug().noquote() << "[POPUP->QML][DISCONNECTED]" << json;

            emit cppCommand(json);
            isVersion = false;
        }

        lastConnState = 0;

        const qint64 elapsed =
            lastConnectAttempt.isValid()
                ? lastConnectAttempt.msecsTo(now)
                : (retryIntervalMs + 1);

        // ✅ reconnect based on socket state, not on ping
        if (!connectingInProgress &&
            elapsed >= retryIntervalMs &&
            localLanUp &&
            !desiredIP.isEmpty())
        {
            qDebug() << "[RECONNECT ATTEMPT]"
                     << "target=" << desiredIP
                     << "port=" << serverPort
                     << "elapsed=" << elapsed
                     << "retryIntervalMs=" << retryIntervalMs
                     << "carrier=" << carrier
                     << "remotePingOk(last)=" << remotePingOk;

            connectingInProgress = true;

            startDisplayPeer();

            if (client) {
                client->createConnection(desiredIP, serverPort);
            }

            lastConnectAttempt = now;
            retryIntervalMs = std::min<qint64>(retryIntervalMs * 2, retryIntervalMaxMs);
        }
    }

    // ------------------------------------------------------------
    // logic เดิม: ขอหน้า network ถ้า IP ว่าง
    // ------------------------------------------------------------
    if (networks->ip_master.isEmpty() || networks->ip_slave.isEmpty() || desiredIP.isEmpty())
        countReconnect++;
    else
        countReconnect = 0;

    if (countReconnect > 5) {
        QJsonObject jetsonForm;
        jetsonForm["objectName"] = "getNetworkPage";
        const QString raw_data = QJsonDocument(jetsonForm).toJson(QJsonDocument::Compact);
        sendMessage(raw_data);
        countReconnect = 0;
    }

    // ------------------------------------------------------------
    // ส่ง network info ถ้า IP ยังไม่ครบ > 5s
    // ------------------------------------------------------------
    const bool ipValid = !(networks->ip_master.isEmpty()
                        || networks->ip_slave.isEmpty()
                        || desiredIP.isEmpty());

    if (ipValid) {
        lastValidIPTime = now;
    } else {
        const int elapsed2 = lastValidIPTime.msecsTo(now);
        if (elapsed2 > 5000) {
            sendNetworkAndUserModeToWeb();
            lastValidIPTime = now;
        }
    }

    qDebug() << "state=" << (lastConnState == 1 ? "UP" : "DOWN")
             << "socketUp=" << socketUp
             << "remotePingOk=" << remotePingOk
             << "remoteDown=" << remoteDown
             << "connectingInProgress=" << connectingInProgress
             << "retryIntervalMs=" << retryIntervalMs;
}
//void mainwindows::reconnectTimerTimeoutSlave()
//{
//    qDebug() << "reconnectTimerTimeoutSlave:" << mainIP_address << serverPort << userMode << networks->ip_master << mysql->IP_MASTER;
//    userMode = mysql->USER;
//    qDebug() << "mysql->USER:" << userMode << mysql->USER;
//    if(userMode == "STANDALONE"){
//        mainIP_address = mysql->IP_MASTER;
//    }else if(userMode == "MASTER"){
//        mainIP_address = mysql->IP_MASTER;
//    }else if(userMode == "SLAVE"){
//        mainIP_address = mysql->IP_SLAVE;
//    }
//    // ==== ค่าคงอยู่ระหว่างรอบ ====
//    static int        lastConnState = -1;     // -1 unknown, 0 down, 1 up
//    static bool       connectingInProgress = false;
//    static QDateTime  lastConnectAttempt;
//    static qint64     retryIntervalMs = 2000;           // เริ่ม 2s
//    static const qint64 retryIntervalMaxMs = 15000;     // เพดาน 15s
//    static const qint64 connectTimeoutMs   = 5000;      // ถ้า connect ค้างเกินนี้ -> reset

//    static int        remotePingFailStreak = 0;
//    static int        remotePingOkStreak   = 0;
//    static const int  REMOTE_FAIL_THRESH   = 2;
//    static const int  REMOTE_OK_THRESH     = 1;

//    static QDateTime  lastValidIPTime = QDateTime::currentDateTime();

//    // ✅ เพิ่ม 2 ตัวนี้ด้วย
//    static QString    lastDesiredIP;
//    static QString    lastUserMode;
//    // --- เลือก IP เป้าหมายแบบปลอดภัย (อย่าเขียนทับทุก tick แบบเดิม) ---
//    QString desiredIP;

////    if (userMode == "SLAVE") {
////        if (!mysql->IP_SLAVE.isEmpty())
////            desiredIP = mysql->IP_SLAVE;
////        else
////            desiredIP = mainIP_address; // กันค่าว่าง
////    }else if (userMode == "MASTER") {
////        // MASTER / STANDALONE ใช้ IP_MASTER
////        if (!mysql->IP_MASTER.isEmpty())
////            desiredIP = mysql->IP_MASTER;
////        else
////            desiredIP = mainIP_address;
////    }
////    mainIP_address = mysql->IP_MASTER;
//    desiredIP = mainIP_address;
//    qDebug() << "desiredIP" << desiredIP << mainIP_address;
//    // --- set เฉพาะตอนเปลี่ยนจริง ---
//    if (!desiredIP.isEmpty() && (desiredIP != lastDesiredIP || userMode != lastUserMode)) {
//        qDebug() << "🔁 target changed:"
//                 << "mode" << lastUserMode << "->" << userMode
//                 << "ip"   << lastDesiredIP << "->" << desiredIP
//                 << "netMaster=" << networks->ip_master
//                 << "netSlave=" << networks->ip_slave
//                 << "dbMaster=" << mysql->IP_MASTER
//                 << "dbSlave=" << mysql->IP_SLAVE;

//        lastDesiredIP = desiredIP;
//        lastUserMode  = userMode;

//        mainIP_address = desiredIP;

//        // รีเซ็ต state ให้ reconnect ทำงานใหม่กับ IP ใหม่
//        lastConnState = -1;
//        connectingInProgress = false;
//        retryIntervalMs = 2000;
//        lastConnectAttempt = QDateTime();
//        remotePingFailStreak = 0;
//        remotePingOkStreak   = 0;

//        if (client) client->disconnectFromServer();
//    }
//    // ==== helper: หา iface จาก IP (fallback ถ้าไม่มีชื่อ iface ให้มา) ====
//    auto findIfaceForIp = [](const QString &ip) -> QString {
//        const QHostAddress ha(ip);
//        const auto ifaces = QNetworkInterface::allInterfaces();
//        for (const QNetworkInterface &ni : ifaces) {
//            if (!(ni.flags() & QNetworkInterface::IsUp) ||
//                !(ni.flags() & QNetworkInterface::IsRunning))
//                continue;

//            const auto addrs = ni.addressEntries();
//            for (const QNetworkAddressEntry &ae : addrs) {
//                if (ae.ip() == ha)
//                    return ni.name();
//            }
//        }
//        // ถ้าไม่เจอ ip ตรง ๆ ใช้ default ที่พบบ่อย
//        return QString();
//    };

//    // ==== helper: อ่าน carrier ของ iface (local LAN หลุด/ไม่หลุด) ====
//    auto readCarrier = [](const QString &iface) -> int {
//        // return: 1=link up, 0=down, -1=unknown
//        if (iface.isEmpty()) return -1;
//        QFile f(QString("/sys/class/net/%1/carrier").arg(iface));
//        if (!f.open(QIODevice::ReadOnly)) return -1;
//        const QByteArray s = f.readAll().trimmed();
//        if (s == "1") return 1;
//        if (s == "0") return 0;
//        return -1;
//    };

//    // ==== เช็ค socket ====
//    const bool socketUp = (client && client->isConnected);

//    // ==== local LAN health ====
//    // ถ้าคุณมีตัวแปรชื่อ iface ใน networks อยู่แล้ว ให้แทนตรงนี้ได้เลย
//    QString localIface;
//    // 1) ถ้ามี ip ฝั่งเครื่องเอง (เช่น networks->ip_slave หรือ ip_master ของ local) ใช้ช่วยหา iface
//    //    (ถ้าโครงสร้าง networks คุณไม่มี ก็ปล่อยให้ findIfaceForIp คืนว่าง)
//    if (!mainIP_address.isEmpty()) {
//        // บางระบบใช้ IP เดียวกับ route -> หา iface จาก IP local ไม่ได้
//        // ถ้าเครื่องคุณมีตัวแปร local ip เช่น networks->local_ip ให้ใช้แทน
//    }
//    // fallback: ลองเดาจาก IP ของเครื่องใน interface list (ถ้าใช้ไม่ได้ localIface จะว่าง)
//    // ถ้าคุณรู้ชื่อ interface ชัด ๆ (เช่น "eth0" / "enP1p1s0") ใส่ตรงนี้เลยดีที่สุด
//    if (localIface.isEmpty()) {
//        // ใช้ iface ที่ system มีจริง ถ้าคุณกำหนดได้ให้ hardcode เป็น iface LAN ของเครื่อง
//        // localIface = "eth0";
//    }

//    const int carrier = readCarrier(localIface);
//    const bool localLanUp = (carrier == 1) || (carrier == -1); // -1 unknown -> อย่าบล็อค (กัน false positive)
//    const bool localLanDown = (carrier == 0);

//    // ==== remote (PLC) reachable? ====
//    bool remotePingOk = false;
//    if (!mainIP_address.isEmpty()) {
//        remotePingOk = pingHost(mainIP_address); // PLC reach ได้ไหม
//    }

//    if (remotePingOk) { remotePingOkStreak++; remotePingFailStreak = 0; }
//    else              { remotePingFailStreak++; remotePingOkStreak = 0; }

//    const bool remoteHealthy = (remotePingOkStreak >= REMOTE_OK_THRESH);
//    const bool remoteDown    = (remotePingFailStreak >= REMOTE_FAIL_THRESH);

//    // “ถือว่าต่อจริง” = socketUp + PLC ไม่หลุดต่อเนื่อง
//    const bool nowConnected = (socketUp && !remoteDown);

//    // ==== interlock ====
//    if (interlockUser) {
//        countUser++;
//        if (countUser > 2) { interlockUser = false; countUser = 0; }
//        qDebug() << "[interlock] waiting..." << "countUser=" << countUser;
//        return;
//    }

//    // เปิด clientNetwork ถ้ายังไม่ต่อ
//    if (clientNetwork && !clientNetwork->isConnected) {
//        clientNetwork->createConnection("127.0.0.1", 1239);
//        qDebug() << "clientNetworkcreateConnection:" << clientNetwork->isConnected;
//    }

//    // ==== watchdog: ถ้า connecting ค้างเกิน timeout ให้ปล่อยแล้วลองใหม่ ====
//    if (connectingInProgress && lastConnectAttempt.isValid()) {
//        const qint64 connectingElapsed = lastConnectAttempt.msecsTo(QDateTime::currentDateTime());
//        if (connectingElapsed > connectTimeoutMs) {
//            qDebug() << "⚠️ Connect timeout -> reset connectingInProgress"
//                     << "elapsed=" << connectingElapsed
//                     << "target=" << mainIP_address << serverPort;

//            connectingInProgress = false;
//            // ปลอดภัย: ถ้ามี method ของคุณเองให้ใช้ method นั้นแทน
//            if (client) client->disconnectFromServer();
//        }
//    }

//    // ==== TRANSITION ====
//    if (nowConnected) {
//        if (lastConnState != 1) {
//            QJsonObject obj;
//            obj["objectName"] = "Pop-up";
//            obj["msg"]   = "Connected";
//            obj["state"] = true;
//            cppCommand(QJsonDocument(obj).toJson(QJsonDocument::Compact));
//            qDebug() << "📡 Reconnected: Sent Connected popup";

//            interlockUser   = false;
//            countUser       = 0;
//            countReconnect  = 0;
//            lastValidIPTime = QDateTime::currentDateTime();

//            connectingInProgress = false;
//            retryIntervalMs = 2000;
//            lastConnectAttempt = QDateTime();

//            if (!isVersion) {
//                connectToPLC();
//                isVersion = true;
//                qDebug() << "Connected and isVersion set true (slave)";
//            }
//        }
//        lastConnState = 1;
//    } else {
//        if (lastConnState != 0) {
//            QJsonObject obj;
//            obj["objectName"] = "Pop-up";
//            obj["msg"]   = localLanDown ? "Local LAN Disconnected" : "Disconnected";
//            obj["state"] = false;
//            obj["targetIP"]   = mainIP_address;
//            obj["monitortIP"] = mysql ? mysql->iPaddressMonitor : "";
//            obj["localIface"] = localIface;
//            obj["carrier"]    = carrier;
//            cppCommand(QJsonDocument(obj).toJson(QJsonDocument::Compact));

//            qDebug() << "Disconnected popup:" << mainIP_address
//                     << (mysql ? mysql->iPaddressMonitor : QString())
//                     << "localIface=" << localIface
//                     << "carrier=" << carrier;

//            // ให้ init ใหม่รอบหน้าถ้าต่อกลับ
//            isVersion = false;

//            // ถ้า socketUp แต่ PLC ไม่ reachable ต่อเนื่อง -> disconnect เพื่อ force refresh
//            if (socketUp && remoteDown && client) {
//                client->disconnectFromServer();
//            }
//        }
//        lastConnState = 0;

//        // ==== ยิง reconnect ด้วย backoff ====
//        const qint64 elapsed =
//            lastConnectAttempt.isValid()
//                ? lastConnectAttempt.msecsTo(QDateTime::currentDateTime())
//                : (retryIntervalMs + 1);

//        // เงื่อนไขใหม่:
//        // - local LAN ถ้าหลุดจริง (carrier=0) => ไม่ต้องยิง connect ให้เปลือง รอจนสายกลับมาก่อน
//        // - remote ping fail (PLC down) "ไม่บล็อค" reconnect: ยังลอง connect ได้ตาม backoff
//        if (!socketUp && !connectingInProgress && elapsed >= retryIntervalMs && localLanUp) {
//            qDebug() << "Reconnect attempt to" << mainIP_address << serverPort
//                     << "elapsed=" << elapsed
//                     << "retryIntervalMs=" << retryIntervalMs
//                     << "localIface=" << localIface
//                     << "carrier=" << carrier
//                     << "remotePingOk=" << remotePingOk;

//            connectingInProgress = true;
//            if (client) client->createConnection(mainIP_address, serverPort);

//            lastConnectAttempt = QDateTime::currentDateTime();
//            retryIntervalMs = std::min<qint64>(retryIntervalMs * 2, retryIntervalMaxMs);
//        }
//    }

//    // ==== logic เดิม: ขอหน้า network ถ้า IP ว่าง ====
//    if (networks->ip_master.isEmpty() || networks->ip_slave.isEmpty() || mainIP_address.isEmpty())
//        countReconnect++;
//    else
//        countReconnect = 0;

//    if (countReconnect > 3) {
//        QJsonObject jetsonForm; jetsonForm["objectName"] = "getNetworkPage";
//        const QString raw_data = QJsonDocument(jetsonForm).toJson(QJsonDocument::Compact);
//        qDebug() << "raw_data:" << raw_data;
//        sendMessage(raw_data);
//        countReconnect = 0;
//    }

//    // ==== ส่ง network info ถ้า IP ยังไม่ครบ > 5s ====
//    const bool ipValid = !(networks->ip_master.isEmpty()
//                        || networks->ip_slave.isEmpty()
//                        || mainIP_address.isEmpty());

//    if (ipValid) {
//        lastValidIPTime = QDateTime::currentDateTime();
//    } else {
//        const int elapsed2 = lastValidIPTime.msecsTo(QDateTime::currentDateTime());
//        if (elapsed2 > 5000) {
//            sendNetworkAndUserModeToWeb();
//            lastValidIPTime = QDateTime::currentDateTime();
//        }
//    }

//    qDebug() << "state=" << (lastConnState==1?"UP":"DOWN")
//             << "socketUp=" << socketUp
//             << "remotePingOk=" << remotePingOk
//             << "remoteFailStreak=" << remotePingFailStreak
//             << "remoteOkStreak=" << remotePingOkStreak
//             << "connectingInProgress=" << connectingInProgress
//             << "retryIntervalMs=" << retryIntervalMs
//             << "localIface=" << localIface
//             << "carrier=" << carrier;
//}


static bool readIpMonitorTxt(QString &outIp, QString &outGw, QString *outPathUsed = nullptr)
{
    const QStringList paths = {
        "/home/pp/ipmonitor.txt",
        "/home/pi/ipmonitor.txt"
    };

    for (const QString &path : paths)
    {
        QFile f(path);
        if (!f.exists()) continue;
        if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) continue;

        const QString content = QString::fromUtf8(f.readAll());
        f.close();

        QRegularExpression reIP(R"(monitorIP\s*[:=]\s*\"([^\"]*)\")");
        QRegularExpression reGW(R"(monitorGateWay\s*[:=]\s*\"([^\"]*)\")");

        QRegularExpressionMatch m1 = reIP.match(content);
        QRegularExpressionMatch m2 = reGW.match(content);

        outIp = m1.hasMatch() ? m1.captured(1).trimmed() : QString();
        outGw = m2.hasMatch() ? m2.captured(1).trimmed() : QString();

        if (outPathUsed) *outPathUsed = path;
        return true;
    }

    outIp.clear();
    outGw.clear();
    if (outPathUsed) outPathUsed->clear();
    return false;
}
void mainwindows::sendNetworkAndUserModeToWeb() {
    QJsonObject userModeObj;
    userModeObj["menuID"] = "userMode";
    userModeObj["USER"] = networks->userTypeSelect;
    userModeObj["IP_MASTER"] = networks->ip_master;
    userModeObj["IP_SLAVE"] = networks->ip_slave;
    userModeObj["IP_SNMP"] = networks->ip_snmp;
    userModeObj["IP_TIMERSERVER"] = networks->ip_timeserver;
    userModeObj["swversion"] = SwVersion;
    sendMessage(QJsonDocument(userModeObj).toJson(QJsonDocument::Compact));
    qDebug() << "Sent userMode info to web";

    QJsonObject netObj;
    netObj["menuID"] = "network";
    netObj["dhcpmethod"] = mysql->dhcpmethodMonitor;
    netObj["ipaddress"] = mysql->iPaddressMonitor;
    netObj["gateway"] = mysql->gatewayMonitor;
    netObj["subnet"] = mysql->subnetMonitor;
    netObj["pridns"] = mysql->pridnsMonitor;
    netObj["secdns"] = mysql->secdnsMonitor;
    netObj["phyNetworkName"] = mysql->phyNameMonitor;
    sendMessage(QJsonDocument(netObj).toJson(QJsonDocument::Compact));
    qDebug() << "Sent network info to web";

}


QString mainwindows::getSystemDateTime() {
    QProcess process;
    process.start("sudo date");
    process.waitForFinished();
    QString dateTime = process.readAllStandardOutput().trimmed();
    return dateTime;
}


void mainwindows::updateDateTime() {
    QDateTime currentDateTime = QDateTime::currentDateTime();

    QString formattedDateTime = currentDateTime.toString("yyyy/MM/dd HH:mm:ss");
    QString datetime = QString("{"
                               "\"objectName\"        :\"DateTime\","
                               "\"formattedDateTime\"  :\"%1\""
                               "}")
                           .arg(formattedDateTime);
//    qDebug() << "Current Date and Time:" << formattedDateTime;
    cppCommand(datetime);

    static int lastRunHour = -1;
    QTime nowTime = QTime::currentTime();

    int targetMinute = 0;
    int targetSecond = 0;

    int currentHour = nowTime.hour();
    int currentMinute = nowTime.minute();
    int currentSecond = nowTime.second();

    if ((currentHour == 6 || currentHour == 18) &&
        currentMinute == targetMinute &&
        currentSecond == targetSecond &&
        currentHour != lastRunHour) {

        int ret = pthread_create(&idThread4, nullptr, ThreadFunc4, this);
        if (ret == 0) {
            checkStatusCaptre = true;
            qDebug() << QString("[Scheduled %1:%2] Thread4 created successfully.")
                        .arg(currentHour).arg(currentMinute, 2, 10, QChar('0'));
            lastRunHour = currentHour;
        } else {
            qWarning() << QString("[Scheduled %1:%2] Thread4 not created.")
                          .arg(currentHour).arg(currentMinute, 2, 10, QChar('0'));
        }
    }

}

void mainwindows::manageData(QString msgs, QWebSocket* wClient){
    QByteArray br = msgs.toUtf8();
    QJsonDocument doc = QJsonDocument::fromJson(br);
    QJsonObject obj = doc.object();
    QJsonObject command = doc.object();
    QString getCommand =  QJsonValue(obj["objectName"]).toString();

    qDebug() << "manageData:" << msgs << wClient;
       if(obj["menuID"].toString() == "updateLocalNetwork"){
           qDebug() << "updateLocalNetwork" << msgs << wClient;
           int dhcp = obj["dhcpmethod"].toInt();
           QString ipaddress = obj["ipaddress"].toString();
           QString subnet = obj["subnet"].toString();
           QString gateway = obj["gateway"].toString();
           QString pridns = obj["pridns"].toString();
           QString secdns = obj["secdns"].toString();
           QString phyNet = obj["phyNetworkName"].toString();
           mysql->updateLocalNetwork(msgs,wClient);
           updateNetwork(dhcp, ipaddress, subnet, gateway, pridns, secdns,phyNet);

       }else if(obj["menuID"].toString() == "getNetworkPage"){
           qDebug() << "getNetworkPage:" << msgs << wClient;

           // 1) ส่ง network จาก DB ตามเดิม
           mysql->getLocalNetwork(wClient);

           // 2) อ่าน ipmonitor.txt แล้วส่งเพิ่ม
           QString fileIp, fileGw, usedPath;
           readIpMonitorTxt(fileIp, fileGw, &usedPath);

           // ใช้ file เป็นหลัก ถ้าว่างค่อย fallback global
           const QString finalIp = !fileIp.isEmpty() ? fileIp : monitorIP;
           const QString finalGw = !fileGw.isEmpty() ? fileGw : monitorGateWay;

           // ถ้าไม่มีค่าเลยก็ไม่ต้องส่ง
           if (finalIp.isEmpty() && finalGw.isEmpty()) {
               qDebug() << "[getNetworkPage] ipMonitor empty, skip"
                        << "path=" << usedPath
                        << "globalIP=" << monitorIP
                        << "globalGW=" << monitorGateWay;
               return;
           }

           QJsonObject ipObj;
           ipObj["menuID"] = "ipMonitor";
           if (!finalIp.isEmpty()) ipObj["monitorIP"] = finalIp;
           if (!finalGw.isEmpty()) ipObj["monitorGateWay"] = finalGw;
           if (!usedPath.isEmpty()) ipObj["path"] = usedPath;

           const QString json = QString::fromUtf8(QJsonDocument(ipObj).toJson(QJsonDocument::Compact));

           // ✅ ส่งกลับไปที่ client คนที่ขอหน้า network (ไม่ broadcast)
           emit broadcastMessage(json);
           // หรือถ้าคุณมี sendTo(wClient, json) / wedSocket->sendTo(...) ก็ใช้ตัวนั้นแทน

           qDebug() << "[getNetworkPage] sent ipMonitor:" << json;
       }else if(obj["menuID"].toString() == "updateUserMode"){
           qDebug() << "<<< updateUserMode >>>" << msgs;
           // ✅ 1) อ่าน key ให้ถูก (รองรับทั้ง userType และ USER เผื่อมีของเก่า)
           const QString newMode =
               obj.contains("userType") ? obj["userType"].toString()
                                        : obj["USER"].toString();

           const QString newMaster = obj["IP_MASTER"].toString();
           const QString newSlave  = obj["IP_SLAVE"].toString();
           const QString newSnmp   = obj["IP_SNMP"].toString();
           const QString newNtp    = obj["IP_TIMERSERVER"].toString();

           qDebug() << "[updateUserMode] recv:"
                    << "mode=" << newMode
                    << "master=" << newMaster
                    << "slave=" << newSlave;

           // ✅ 2) update ตัวแปรให้เป็น source เดียว
           mysql->USER          = newMode;
           mysql->IP_MASTER     = newMaster;
           mysql->IP_SLAVE      = newSlave;
           mysql->IP_SNMP       = newSnmp;
           mysql->IP_TIMERSERVER= newNtp;

           networks->ip_master      = mysql->IP_MASTER;
           networks->ip_slave       = mysql->IP_SLAVE;
           networks->ip_timeserver  = mysql->IP_TIMERSERVER;
           qDebug() << "[updateUserMode]" << mysql->USER << mysql->IP_MASTER << mysql->IP_SLAVE << mysql->IP_SNMP << mysql->IP_TIMERSERVER << networks->ip_master << networks->ip_slave << networks->ip_timeserver;
           // ✅ 3) เก็บ DB (ต้องเก็บ STANDALONE จริง ๆ อย่าทับเป็น MASTER)
           mysql->updateDataBaseUSER();

           // ✅ 4) ตั้ง NTP
           networking->setNTPServer(networks->ip_timeserver);

           // ✅ 5) ตั้ง mainIP_address ตาม mode
           if (newMode == "MASTER") {
               mainIP_address = newMaster;     // STANDALONE ก็วิ่งไป master IP
           } else if (newMode == "SLAVE") {
               mainIP_address = newSlave;
           }

           // ✅ 6) แจ้ง UI กลับด้วย mode เดิมที่เลือก (STANDALONE ต้องส่ง STANDALONE)
           QJsonObject useModeSelect;
           useModeSelect["objectName"] = "selectUser";
           useModeSelect["userType"]   = newMode;
           const QString raw_useModeSelect =
               QString::fromUtf8(QJsonDocument(useModeSelect).toJson(QJsonDocument::Compact));

//           cppCommand(raw_useModeSelect);
           QJsonObject useModeSelects;
           useModeSelect["objectName"] = "selectUsers"; //แบบนี้คือส่งให้PLC
           useModeSelect["userType"]   = newMode;
           const QString raw_useModeSelectPLC = QString::fromUtf8(QJsonDocument(useModeSelect).toJson(QJsonDocument::Compact));
           qDebug() << "raw_useModeSelectPLC:" << raw_useModeSelectPLC;
           emit sendToServer(raw_useModeSelectPLC);

           // ✅ 7) refresh network page (ถ้าต้องการ)
           mysql->getLocalNetwork(wClient);
       }else if(obj["menuID"].toString() == "getSystemPage"){
           QJsonDocument jsonDoc;
           QJsonObject Param;
           QString raw_data;
           Param.insert("menuID","system");	             //Name
           Param.insert("objectName","system");	             //Name

           Param.insert("SwVersion",SwVersion);
           Param.insert("HwVersion",HwVersion);

           if(mysql->IP_TIMERSERVER != "" && networks->location_snmp != ""){
               Param.insert("dateTimeMethod",1);
           }else
           Param.insert("dateTimeMethod",0);
           Param.insert("ntpServer",mysql->IP_TIMERSERVER); //networks->ip_timeserver
           Param.insert("location",networks->location_snmp);
           jsonDoc.setObject(Param);
           raw_data = QJsonDocument(Param).toJson(QJsonDocument::Compact).toStdString().c_str();
           qDebug() << "raw_data:" << raw_data;

//           emit sendMessage(raw_data);
           broadcastMessage(raw_data);
       }else if(obj["menuID"].toString() == "setLocation"){
           qDebug() << "setLocation:" << msgs;

           networks->location_snmp = obj["location"].toString();
           networking->setNTPServer(networks->ip_timeserver); //networks->ip_timeserver
           mysql->setLocation(networks->location_snmp);
       }else if(obj["menuID"].toString() == "updateNTPServer"){
           qDebug() << "updateNTPServer:" << msgs;
           networks->ip_timeserver = obj["ntpServer"].toString();
           networking->setNTPServer(networks->ip_timeserver);
           mysql->getLocalNetwork(wClient);
       }else if(obj["menuID"].toString() == "updateDisplayPeer"){
           qDebug()<< "updateDisplayPeer:" << msgs;
           updateDisplayOpp(msgs);
      }else if(obj["menuID"].toString() == "updateFirmware"){
           qDebug() << "<<updateFirmware>>";
           updateFirmware();
       }
}

// helper: ดึง double จาก QJsonObject ไม่ว่าจะเป็น number หรือ string
static bool jsonGetDouble(const QJsonObject& obj, const char* key, double* out)
{
    const QJsonValue v = obj.value(QLatin1String(key));

    if (v.isDouble()) {                 // JSON number
        *out = v.toDouble();
        return true;
    }
    if (v.isString()) {                 // JSON string -> double
        QString s = v.toString().trimmed();
        // รองรับทศนิยมเครื่องยุโรป เช่น "61,22"
        s.replace(',', '.');
        bool ok = false;
        // ใช้ C locale เพื่อไม่พึ่ง locale เครื่อง
        const double d = QLocale::c().toDouble(s, &ok);
        if (ok) { *out = d; return true; }
    }
    return false; // ไม่พบ/แปลงไม่ได้
}


void mainwindows::cppSubmitTextFiled(QString qmlJson){

    QJsonDocument d = QJsonDocument::fromJson(qmlJson.toUtf8());
    QJsonObject command = d.object();
    QString getCommand =  QJsonValue(command["objectName"]).toString().trimmed();
    QString menuID =  QJsonValue(command["menuID"]).toString().trimmed();
    QString getCommand2 =  QJsonValue(command["objectNames"]).toString();
    QString getEventAndAlert =  QJsonValue(command["TrapsAlert"]).toString();
    getCommand = getCommand.trimmed();
    QJsonDocument doc = QJsonDocument::fromJson(qmlJson.toUtf8());
      qDebug() << "cppSubmitTextFiled:" << qmlJson;
     if (getCommand == "updateNetworkIP") {
          QString userType = command["USER"].toString();
          QString ipMaster = command["IP_MASTER"].toString();
          QString ipSlave = command["IP_SLAVE"].toString();
          QString ipSnmp = command["IP_SNMP"].toString();
          QString ipTimeServer = command["IP_TIMERSERVER"].toString();

          qDebug() << "USER:" << userType;
          qDebug() << "IP_MASTER:" << ipMaster;
          qDebug() << "IP_SLAVE:" << ipSlave;
          qDebug() << "IP_SNMP:" << ipSnmp;
          qDebug() << "IP_TIMERSERVER:" << ipTimeServer;

          networks->userTypeSelect = userType;
          networks->ip_master = ipMaster;
          networks->ip_slave = ipSlave;
          networks->ip_snmp = ipSnmp;
          networks->ip_timeserver = ipTimeServer;
          mysql->updateIpNetwork(userType, ipMaster, ipSlave, ipSnmp, ipTimeServer);

    }else if(getCommand == "updateisGreenBut"){
         qDebug()<< "updateisGreenButA:" << qmlJson;
         // emit updateStatusOfButtonHidding(qmlJson);
         mysql->UpdateStatusOfButtonHidding(qmlJson);
    }else if (getCommand == "selectTaggingPoint") {
         qDebug() << "selectTaggingPoint:" << qmlJson;
         sendMessage(qmlJson);
    }else if (getCommand == "zoomInOut") {
         qDebug() << "zoomInOut:" << qmlJson;
         mysql->recordZoomInOutValue(qmlJson);
    }else if (getCommand == "getZoomValueRecord") {
         qDebug() << "zoomInOutRecord:" << qmlJson;
         cppCommand(qmlJson);
    }else if (getCommand == "lastZoomVoltage") {
         qDebug() << "lastZoomVoltage:" << qmlJson;
         mysql->recordZoomInOutValue(qmlJson);
    }else if (getCommand == "getMaxMinValue") {
         qDebug() << "getMaxMinValue:" << qmlJson;
         cppCommand(qmlJson);
    }else if (menuID == "userMode") {
         qDebug()<< "updateMasterSlaveIp:" << qmlJson << QJsonValue(command["IP_MASTER"]).toString();
         auto pickMode = [&](const QJsonObject& o)->QString {
             QString m = o.value("userType").toString().trimmed();
             if (m.isEmpty()) m = o.value("USER").toString().trimmed();
             return m.toUpper();
         };

         auto pick = [&](const QString& dbVal, const QString& inVal)->QString {
             // mysql เป็นใหญ่สุด: ถ้า dbVal มีค่า ให้ใช้ dbVal เสมอ
             // ถ้า dbVal ว่าง ค่อย fallback ไป inVal
             return !dbVal.trimmed().isEmpty() ? dbVal.trimmed() : inVal.trimmed();
         };

         // -------- 1) INCOMING จาก QML/WS --------
         const QString inMode  = pickMode(command);
         const QString inM     = command.value("IP_MASTER").toString().trimmed();
         const QString inS     = command.value("IP_SLAVE").toString().trimmed();
         const QString inSnmp  = command.value("IP_SNMP").toString().trimmed();
         const QString inNtp   = command.value("IP_TIMERSERVER").toString().trimmed();
         const QString inGw    = command.value("gateway").toString().trimmed();
         const QString inMonIp = command.value("ipaddress").toString().trimmed();

         qDebug() << "[userMode] incoming:"
                  << "mode=" << inMode
                  << "M=" << inM
                  << "S=" << inS
                  << "SNMP=" << inSnmp
                  << "NTP=" << inNtp;

         // -------- 2) DB จาก mysql (source-of-truth) --------
         const QString dbMode  = mysql->USER.trimmed().toUpper();
         const QString dbM     = mysql->IP_MASTER.trimmed();
         const QString dbS     = mysql->IP_SLAVE.trimmed();
         const QString dbSnmp  = mysql->IP_SNMP.trimmed();
         const QString dbNtp   = mysql->IP_TIMERSERVER.trimmed();

         // -------- 3) NORMALIZE: mysql ใหญ่สุด --------
         const QString finalMode = pick(dbMode,  inMode);
         const QString finalM    = pick(dbM,     inM);
         const QString finalS    = pick(dbS,     inS);
         const QString finalSnmp = pick(dbSnmp,  inSnmp);
         const QString finalNtp  = pick(dbNtp,   inNtp);

         // -------- 4) Debug เช็คว่าอะไรไม่ตรง --------
         if (!dbM.isEmpty() && !inM.isEmpty() && dbM != inM)
             qWarning() << "[userMode] mismatch IP_MASTER: incoming=" << inM << "db=" << dbM << "-> use db";
         if (!dbS.isEmpty() && !inS.isEmpty() && dbS != inS)
             qWarning() << "[userMode] mismatch IP_SLAVE: incoming=" << inS << "db=" << dbS << "-> use db";
         if (!dbMode.isEmpty() && !inMode.isEmpty() && dbMode != inMode)
             qWarning() << "[userMode] mismatch MODE: incoming=" << inMode << "db=" << dbMode << "-> use db";
         if (!dbSnmp.isEmpty() && !inSnmp.isEmpty() && dbSnmp != inSnmp)
             qWarning() << "[userMode] mismatch IP_SNMP: incoming=" << inSnmp << "db=" << dbSnmp << "-> use db";
         if (!dbNtp.isEmpty() && !inNtp.isEmpty() && dbNtp != inNtp)
             qWarning() << "[userMode] mismatch IP_TIMERSERVER: incoming=" << inNtp << "db=" << dbNtp << "-> use db";

         qDebug() << "[userMode] final(use-db-first):"
                  << "mode=" << finalMode
                  << "M=" << finalM
                  << "S=" << finalS
                  << "SNMP=" << finalSnmp
                  << "NTP=" << finalNtp;

         // -------- 5) APPLY ไปตัวแปรในโปรแกรม --------
         networks->userTypeSelect = finalMode;
         networks->ip_master      = finalM;
         networks->ip_slave       = finalS;
         networks->ip_snmp        = finalSnmp;
         networks->ip_timeserver  = finalNtp;

         update_userMode      = finalMode;
         update_ip_PCL        = finalM;      // อันนี้คุณบอกจะเทียบกับ mysql->IP_MASTER -> ตอนนี้ finalM มาจาก mysql แล้ว
         update_ip_Master_PCL = finalM;
         update_ip_SLAVE_PCL  = finalS;
         update_ip_snmp       = finalSnmp;
         update_ip_timeserver = finalNtp;

         // gateway / monitor ip: ถ้า incoming ว่าง ใช้ของเดิม
         update_ip_gatewayPLC = !inGw.isEmpty() ? inGw : networks->ip_gateway;
         update_ip_monitor    = !inMonIp.isEmpty() ? inMonIp : mysql->iPaddressMonitor;

         // -------- 6) ส่งไป Jetson --------
         QJsonObject jetsonForm;
         jetsonForm["objectName"]       = "updateIP";
         jetsonForm["USERMODE"]         = update_userMode;
         jetsonForm["ip_Master_PCL"]    = update_ip_Master_PCL;
         jetsonForm["ip_SLAVE_PCL"]     = update_ip_SLAVE_PCL;
         jetsonForm["gateway"]          = update_ip_gatewayPLC;
         jetsonForm["ipaddressMonitor"] = update_ip_monitor;
         jetsonForm["IP_SNMP"]          = update_ip_snmp;
         jetsonForm["IP_TIMERSERVER"]   = update_ip_timeserver;

         const QString jsonString = QString::fromUtf8(QJsonDocument(jetsonForm).toJson(QJsonDocument::Compact));
         qDebug() << "Jetson JSON:" << jsonString;
         cppCommand(jsonString);
    }else if(getCommand == "updateFirmware"){
        qDebug()<< "updateFirmware:" << qmlJson;
//        updateFirmware();
//        updateSystemiTouch(qmlJson);
    }else if(getCommand == "updateTaggingData") {
        qDebug() << "updateTaggingData:" << qmlJson;
        cppCommand(qmlJson);
    }else if(getCommand == "updateParameterMargin"){
         qDebug()<< "updateParameterMargin:" << qmlJson;
         cppCommand(qmlJson);
    }else if(getCommand == "updatedataTableA"){
        qDebug()<< "updatedataTableA:" << qmlJson;
        cppCommand(qmlJson);
    }else if(getCommand == "updatedataTableB"){
        qDebug()<< "updatedataTableB:" << qmlJson;
        cppCommand(qmlJson);
    }else if(getCommand == "updatedataTableC"){
        qDebug()<< "updatedataTableC:" << qmlJson;
        cppCommand(qmlJson);
    }else if (getCommand == "PatternCount"){
         cppCommand(qmlJson);
    }else if(getCommand == "saveDataTaging"){
        qDebug()<< "saveDataTagingA:" << qmlJson;
        sendMessage(qmlJson);
    }else if (getCommand.contains("getDistanceDetail")) {
        sendMessage(qmlJson);
    }else if (getCommand.contains("deleteMysql")) {
        sendMessage(qmlJson);
    }else if(getCommand == "getButtonStatus"){
        qDebug()<< "getButtonStatus:" << qmlJson;
        cppCommand(qmlJson);
    }else if(qmlJson == "testRawData"){
        rawdataPlot("testRawData");
    }else if(getCommand == "LineFail"){
        qDebug()<< "line_fault :" << qmlJson;
        sendMessage(qmlJson);
    }else if(getCommand == "LineFails"){
        qDebug()<< "line_faults_re:" << qmlJson;
        cppCommand(qmlJson);
    }else if(menuID == "updateLocalNetwork"){
         qDebug()<< "updateLocalNetwork:" << qmlJson;
         updateLocalNetworkFromJson(qmlJson);

    }else if(getCommand == "restart_system"){
        qDebug()<< "restart_system :" << qmlJson;
        system("sudo systemctl restart iTouch.service ");
        system("sudo systemctl restart iTouchsettingNetwork.service ");
        system("sudo systemctl restart iTouchVNC.service");
        QJsonObject obj;
        obj["objectName"] = "Pop-up";
        obj["msg"] = "RESTART SERVICE";
        QJsonDocument doc(obj);
        QString jsonString = QString::fromUtf8(doc.toJson(QJsonDocument::Compact));
        qDebug() << "Disconnected JSON sent to QML:" << jsonString;
        cppCommand(jsonString);
    }else if(getCommand == "restartSystemItouch"){
        qDebug()<< "restartSystemItouch :" << qmlJson;
        system("sudo reboot");
    }else if(getCommand == "ShutDownSystemItouch"){
         qDebug()<< "ShutDownSystemItouch :" << qmlJson;
         sendMessage("ShutDownSystemMonitor");
         system("sudo shutdown now");
    }else if(getCommand == "resetDefalutIP"){
        qDebug()<< "resetDefalutIP :" << qmlJson;
        setDefaultIPDataBase(qmlJson);
    }else if(getCommand.contains("UserSelectM")){
         UserTypes = QJsonValue(command["userType"]).toString();
         userStatus = QJsonValue(command["userStatusMaster"]).toBool();
         selectMaster = QString("{"
                                       "\"objectName\"  :\"UserSelectM\","
                                       "\"userType\"    :\"%1\","
                                       "\"userStatusMaster\"  :\"%2\""
                                       "}")
                                .arg(UserTypes).arg(userStatus);
        qDebug() << "cppSubmitTextFiled UserM:" << selectMaster << userStatus << UserTypes;
        cppCommand(selectMaster);
    }else if(getCommand == "dateRemote") {
         qDebug() << "dateRemote:" << qmlJson;
         cppCommand(qmlJson);
    }else if(getCommand == "updateTimeRemote") {
        qDebug() << "updateTimeRemote:" << qmlJson;
        cppCommand(qmlJson);
    }else if(getCommand == "login"){
        QString user = QJsonValue(command["username"]).toString();
        QString password = QJsonValue(command["password"]).toString();
        QJsonObject jsonOutput;
        jsonOutput["objectName"] = "login";
        jsonOutput["username"] = user;
        jsonOutput["password"] = password;        QJsonDocument doc(jsonOutput);
        QString loginuser = doc.toJson(QJsonDocument::Compact);
        qDebug()<<"loginppp"<<loginuser;
        emit sendMessage(loginuser);
    }else if (getCommand == "valueMarginVoltageAauto"){
         cppCommand(qmlJson);
    }else if (getCommand == "valueMarginVoltageBauto"){
         cppCommand(qmlJson);
    }else if (getCommand == "valueMarginVoltageCauto"){
         cppCommand(qmlJson);
    }else if (getCommand == "userlevel"){
        cppCommand(qmlJson);
    }else if(getCommand == "setIPAddressGatewayDisplay") {
        qDebug() << "setIPAddressGatewayDisplay:" << qmlJson;
        UpdateiScreenIPNetwork(qmlJson);
    }else if(qmlJson == "updateTaggingList") {
        qDebug() << "updateTaggingList:" << qmlJson;
        sendMessage(qmlJson);
    }else if(getCommand == "PatternData"){
         qDebug() << "PatternData:" << qmlJson;

        cppCommand(qmlJson);
    }else if (getCommand == "Pop-up"){
        qDebug() << "Pop-up_debug:" << qmlJson;
        QString messagePopup = command["msg"].toString();
        if(messagePopup == "Logging out"){
            #ifdef HwName
            #else
                cppCommand(qmlJson);
            #endif
        }
        else{
            #ifdef HwName
                cppCommand(qmlJson);
            #else

            #endif
        }
    }else if (getCommand ==  "ReturnToHost"){
//        handleReturnToHostCommand();
    }else if (getCommand ==  "Screenshot"){
         qDebug() << "captureScreenshot:" << qmlJson;

        emit captureScreenshot();
    }else if (getCommand == "positionDistance") {
         qDebug() << "CpppositionDistance:" << qmlJson;

         QJsonParseError err;
         const QJsonDocument doc = QJsonDocument::fromJson(qmlJson.toUtf8(), &err);
         if (err.error != QJsonParseError::NoError || !doc.isObject()) {
             qWarning() << "Bad JSON:" << err.errorString();
             return;
         }
         const QJsonObject command = doc.object();

         double zeroDistance = 0.0;
         if (!jsonGetDouble(command, "distance", &zeroDistance)) {
             qWarning() << "distance missing/invalid:" << command.value("distance");
             return;
         }

         qDebug() << "ZeroDistance:" << zeroDistance;

         // เปรียบเทียบ double อย่าเทียบ == 0 ตรง ๆ ใช้ qFuzzyIsNull หรือ epsilon
         if (!qFuzzyIsNull(zeroDistance)) {
             qDebug() << "Distance is not Zero:" << zeroDistance;
             cppCommand(qmlJson);
         }
    }else if (getCommand ==  "positionDistanceChnage"){
         qDebug() << "CppPositionDistanceChnage:" << qmlJson;
         emit positionCursorChange(qmlJson);
    }else if (getCommand ==  "getStatusOfButtonHidding"){
        qDebug() << "getStatusOfButtonHidding:" << qmlJson;
        emit getStatusOfButtonHidding();
    }else if (getCommand ==  "socketConnect"){
        QString socketConnect = QJsonValue(command["socketCPP"]).toString();
        qDebug() << "socketConnect:" << socketConnect;

        if(socketConnect == "true"){
            QJsonObject obj;
            obj["objectName"] = "socketPort";
            obj["port"] = port;
            QJsonDocument doc(obj);
            QString socketPort = QString::fromUtf8(doc.toJson(QJsonDocument::Compact));
            cppCommand(socketPort);
            qDebug() << "socketPort" << socketPort;

        }
    }else if (getCommand == "SearchName"){
        Name = QJsonValue(command["text"]).toString();
        QString categories = QJsonValue(command["categories"]).toString();
        QString massage = QString("{"
                                  "\"objectName\":\"SearchName\","
                                  "\"categories\":\"%1\","
                                  "\"text\":\"%2\""
                                  "}").arg(categories).arg(Name);
        emit sendMessage(massage);
    }else if (getCommand == "SearchDate"){
        QString Date = QJsonValue(command["text"]).toString();
        QString categories = QJsonValue(command["categories"]).toString();
        QString massage = QString("{"
                                  "\"objectName\":\"SearchDate\","
                                  "\"categories\":\"%1\","
                                  "\"text\":\"%2\""
                                  "}").arg(categories).arg(Date);
        emit sendMessage(massage);

    }else if (getCommand == "sortnamePattern"){

        bool Sort = QJsonValue(command["Sort"]).toBool();
        QString categories = QJsonValue(command["categories"]).toString();

        QString message = QString("{"
                                  "\"objectName\":\"sortnamePattern\","
                                  "\"Sort\":%1,"
                                  "\"categories\":\"%2\""
                                  "}").arg(Sort ? "true" : "false").arg(categories);

        emit sendMessage(message);
        qDebug()<<"iiiii"<<message;
    }else if (getCommand == "sortdatePattern"){
        bool Sort = QJsonValue(command["Sort"]).toBool();
        QString categories = QJsonValue(command["categories"]).toString();

        QString message = QString("{"
                                  "\"objectName\":\"sortdatePattern\","
                                  "\"Sort\":%1,"
                                  "\"categories\":\"%2\""
                                  "}").arg(Sort ? "true" : "false").arg(categories);

        emit sendMessage(message);
    }else if (getCommand == "ButtonPattern"){
        QString state = QJsonValue(command["Onclicked"]).toString();
        QString category = QJsonValue(command["category"]).toString();
        QString event_time = QJsonValue(command["event_datetime"]).toString();
        QString filename = QJsonValue(command["filename"]).toString();
        qDebug()<<"ButtonPattern"<<state<<event_time<<filename;
        QString buttonPattern = QString("{"
                                        "\"objectName\":\"ButtonPattern\","
                                        "\"category\":\"%1\","
                                        "\"Onclicked\":\"%2\","
                                        "\"event_datetime\":\"%3\","
                                        "\"filename\":\"%4\""
                                        "}").arg(category).arg(state).arg(event_time).arg(filename);
        qDebug() << "ButtonPattern_test"<< buttonPattern;
        if(client){
            qDebug() << "check_connect_to_PLC"<< qmlJson;
            emit sendMessage(qmlJson);
            cppCommand(qmlJson);
        }
    }else if(getCommand.contains("UserSelectS")){
        QString userType = QJsonValue(command["userType"]).toString();
        bool userStatus = QJsonValue(command["userStatusSlave"]).toBool();
        QString selectSlave = QString("{"
                                      "\"objectName\"  :\"UserSelectS\","
                                      "\"userType\"    :\"%1\","
                                      "\"userStatusSlave\"  :\"%2\""
                                      "}").arg(userType).arg(userStatus);
        qDebug() << "cppSubmitTextFiled UserS:" << selectSlave << userStatus << userType;
        cppCommand(selectSlave);
        emit updateUser(selectSlave);
    }else if(getCommand == "VoltageInfo"){
        int valueVoltage = QJsonValue(command["Voltage"]).toInt();
        QString Voltage = QString("{"
                                  "\"objectName\"   :\"InforSettingVoltage\","
                                  "\"valueVoltage\"      :%1"
                                  "}").arg(valueVoltage);
        qDebug() << "cppSubmitTextFiled Voltage:" << Voltage << valueVoltage;
        sendMessage(Voltage);
    }else if(getCommand == "Substations"){
        QString subsationName = QJsonValue(command["Substation"]).toString();
        QString subsation = QString("{"
                                      "\"objectName\"   :\"ValueSubstation\","
                                      "\"Substation\"      :\"%1\""
                                      "}").arg(subsationName);
        qDebug() << "cppSubmitTextFiled Substation:" << subsation << subsationName;
        sendMessage(subsation);
    }else if(getCommand == "Direction"){
        QString valueDirection = QJsonValue(command["Direction"]).toString();
        QString Direction = QString("{"
                                    "\"objectName\"   :\"valueDirection\","
                                    "\"Direction\"      :\"%1\""
                                    "}").arg(valueDirection);
        qDebug() << "cppSubmitTextFiled Direction:" << Direction << valueDirection;
        sendMessage(Direction);
    }else if(getCommand == "LineNo"){
        QString valueLineNo = QJsonValue(command["LineNo"]).toString();
        QString LineNo = QString("{"
                                 "\"objectName\"   :\"valueLineNo\","
                                 "\"LineNo\"      :\"%1\""
                                 "}").arg(valueLineNo);
        qDebug() << "cppSubmitTextFiled LineNo:" << LineNo << valueLineNo;
        sendMessage(LineNo);
    }else if (getCommand.contains("updatetextTime")) {
         QString timer = QJsonValue(command["Time"]).toString().trimmed();

         QString timerupdate = QString("{"
                                       "\"objectName\":\"updateTime\","
                                       "\"Time\":\"%1\""
                                       "}").arg(timer);

         qDebug() << "cppSubmitTextFiled Time:" << timerupdate << timer
                  << "remoteMode=" << remoteMode
                  << "mainIP_address=" << mainIP_address
                  << "PeriodicTime(local)=" << PeriodicTime
                  << "recordPeriodic(remote)=" << recordPeriodic
                  << "displayPeriodicTime(gui)=" << displayPeriodicTime;

         // ------------------------------------------------------------
         // REMOTE MODE:
         // ส่งไป PLC ปลายทางเท่านั้น
         // ห้ามแก้ PeriodicTime ของเครื่องนี้
         // ------------------------------------------------------------
         if (remoteMode) {
             emit updateTimer(timerupdate);
             qDebug() << "[REMOTE] emit updateTimer to remote PLC:" << timerupdate;

             // อัปเดตเฉพาะสิ่งที่ GUI ต้องโชว์ตอน remote
             displayPeriodicTime = timer;

             QJsonObject ui;
             ui["objectName"] = "updateRemotePeriodic";
             ui["Time"] = displayPeriodicTime;
             cppCommand(QString::fromUtf8(QJsonDocument(ui).toJson(QJsonDocument::Compact)));

             qDebug() << "[REMOTE] local host NOT updated"
                      << "PeriodicTime(still)=" << PeriodicTime
                      << "recordPeriodic(still)=" << recordPeriodic
                      << "displayPeriodicTime(gui now)=" << displayPeriodicTime;
             return;
         }

         // ------------------------------------------------------------
         // LOCAL MODE:
         // แก้เวลาของเครื่องนี้เอง
         // ------------------------------------------------------------
         PeriodicTime = timer;
         displayPeriodicTime = PeriodicTime;

         qDebug() << "[LOCAL] PeriodicTime =" << PeriodicTime
                  << "recordPeriodic =" << recordPeriodic
                  << "displayPeriodicTime =" << displayPeriodicTime;

         emit updateTimer(timerupdate);
         sendRequestDisplay();

         // ส่งเวลาใหม่ของเราไปให้อีก display รู้
         if (!PeriodicTime.isEmpty() && peer) {
             QJsonObject o;
             o["type"] = "periodic_time";
             o["ip"] = monitorIP;
             o["Time"] = PeriodicTime;
             o["from"] = userMode;
             o["ts"]   = QDateTime::currentDateTime().toString(Qt::ISODate);

             const QString msg = QString::fromUtf8(QJsonDocument(o).toJson(QJsonDocument::Compact));
             qDebug() << "[PEER][PERIODIC] send local periodic_time:" << msg;
             sendPeerMessageReliable(msg);
         }
    }else if(getCommand == "distanceField"){
        double distanceField = QJsonValue(command["distanceField"]).toDouble();
        QString distance = QString("{"
                                      "\"objectName\"   :\"distanceField\","
                                      "\"distanceInfoSetting\"      :\"%1\""
                                      "}").arg(distanceField);
        qDebug() << "cppSubmitTextFiled distance:" << distance << distanceField;
        cppCommand(distance);
    }else if(getCommand == "detailField"){
        QString detailField = QJsonValue(command["detailField"]).toString();
        QString Details = QString("{"
                                      "\"objectName\"   :\"detailField\","
                                      "\"detailInfoSetting\"      :\"%1\""
                                      "}").arg(detailField);
        qDebug() << "cppSubmitTextFiled Details:" << Details << detailField;
        cppCommand(Details);
    }else if(getCommand == "getDataTaggingPhaseA") {
         qDebug() << "getDataTaggingPhaseA:" << qmlJson;
         findVoltageValueTagging(qmlJson);
         cppCommand(qmlJson);
    }else if(getCommand == "getDataTaggingPhaseB") {
        qDebug() << "getDataTaggingPhaseB:" << qmlJson;
        findVoltageValueTagging(qmlJson);
        cppCommand(qmlJson);
    }else if(getCommand == "getDataTaggingPhaseC") {
        qDebug() << "getDataTaggingPhaseC:" << qmlJson;
        findVoltageValueTagging(qmlJson);
        cppCommand(qmlJson);
    }else if(getCommand == "TaggingPhaseA") {
         qDebug() << "TaggingPhaseA_cpp:" << qmlJson;
         cppCommand(qmlJson);
    }else if(getCommand == "TaggingPhaseB") {
        qDebug() << "TaggingPhaseB_cpp:" << qmlJson;
        cppCommand(qmlJson);
    }else if(getCommand == "TaggingPhaseC") {
        qDebug() << "TaggingPhaseC_cpp:" << qmlJson;
        cppCommand(qmlJson);
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
        sendMessage(qmlJson);
    }else if (getCommand.contains("editDataPhaseB")) {
        sendMessage(qmlJson);
    }else if (getCommand.contains("editDataPhaseC")) {
        sendMessage(qmlJson);
    }else if (getCommand.contains("editDataTaggingPhaseA")) {
        cppCommand(qmlJson);
    }else if (getCommand.contains("editDataTaggingPhaseB")) {
        cppCommand(qmlJson);
    }else if (getCommand.contains("editDataTaggingPhaseC")) {
        cppCommand(qmlJson);
    }else if (getCommand =="marginCountA" || getCommand == "valueMarginVoltageA") {
        qDebug() << "SettingAndUpdateMargin:" << qmlJson;
        SettingAndUpdateMargin(qmlJson);

    }else if (getCommand == "marginCountB" || getCommand=="valueMarginVoltageB") {
        SettingAndUpdateMargin(qmlJson);

    } else if (getCommand=="marginCountC" || getCommand=="valueMarginVoltageC") {
        SettingAndUpdateMargin(qmlJson);

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
    }else if (getCommand =="positonCursor") {
         qDebug() << "CPPpositonCursor:" << qmlJson;
        cppCommand(qmlJson);
    }else if (getCommand == "DefaultUserLevel") {
        qDebug() << "logoutDefaultUser:" << qmlJson;
        cppCommand(qmlJson);
    }else if (getCommand == "logout") {
         qDebug() << "logoutLevel:" << qmlJson;
        sendMessage(qmlJson);
    }else if (getCommand == "logouts") {
        cppCommand(qmlJson);
    }else if (getCommand == "alive") {
         qDebug() << "alive:" << qmlJson;
         emit sendMessage(qmlJson);
    }else if (getCommand == "VNClogin") {
         qDebug() << "VNClogin:" << qmlJson;
         emit sendMessage(qmlJson);
    }else if (getCommand == "VNClogout") {
         qDebug() << "VNClogout:" << qmlJson;
         emit sendMessage(qmlJson);
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
        qDebug() << "PositionDistance_record:" << positionDistance << distance;
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
    }else if (getCommand.contains("updatedecreaseValue")) {
        cppCommand(qmlJson);
    }else if (getCommand.contains("updateincreaseValue")) {
        cppCommand(qmlJson);
    }else if (getCommand.contains("getDatabuttonPhaseA")) {
//        QString rawdataA = QJsonValue(command["rawdataA"]).toString();
        QString getRawDataPhaseA = QString("{"
                                        "\"objectName\"     :\"dataPlotingA\""
                                        "}");
        qDebug() << "getRawDataPhaseA:" << getRawDataPhaseA;
        emit plotingDataPhaseA(getRawDataPhaseA);
//        storeageDataPhaseA(getRawDataPhaseA);
//        emit rawdataPlot(getRawDataPhaseA);
    } else if (getCommand.contains("getDatabuttonPhaseB")) {
        QString rawdataB = QJsonValue(command["rawdataB"]).toString();
        QString getRawDataPhaseB = QString("{"
                                        "\"objectName\"     :\"getDatabuttonPhaseB\","
                                        "\"rawdataB\"         :\"%1\""
                                        "}").arg(rawdataB);
        qDebug() << "getpatternPhaseB:" << getRawDataPhaseB << rawdataB;
//        emit rawdataPlot(getRawDataPhaseB);
    } else if (getCommand.contains("getDatabuttonPhaseC")) {
        QString rawdataC = QJsonValue(command["rawdataC"]).toString();
        QString getRawDataPhaseC = QString("{"
                                        "\"objectName\"     :\"getDatabuttonPhaseC\","
                                        "\"rawdataC\"         :\"%1\""
                                        "}").arg(rawdataC);
        qDebug() << "getpatternPhaseC:" << getRawDataPhaseC << rawdataC;
//        emit rawdataPlot(getRawDataPhaseC);
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
    }else if (getCommand.contains("updateCursor")) {
        cppCommand(qmlJson);
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
    }else if (getCommand == "editSetSNMPServerIP") {
        QString snmpIP = command.value("editsSNMPServer").toString();
        qDebug() << "snmpIP:" << snmpIP;
        QString setIPSNMP = QString("{"
                                     "\"objectName\":\"updateSettingNetwork\","
                                     "\"ip_snmp\":\"%1\""
                                     "}")
                            .arg(snmpIP);
        qDebug() << "setIPSNMP:" << setIPSNMP;
        sendMessage(setIPSNMP);
        emit sendToWeb(setIPSNMP);
        mysql->IP_SNMP = command["IP_SNMP"].toString();
        mysql->updateDataBaseUSER();
    }else if (getCommand.contains("editSettingNetwork")){
        QString IPaddress = command.value("editsIPAddress").toString();
        QString GateWsys = command.value("editsGateWays").toString();
        qDebug() << "IPaddress:" << IPaddress << "GateWsys:" << GateWsys;

        QString settingNetwork = QString("{"
                                          "\"objectName\":\"updateSettingNetwork\","
                                          "\"ip_address\":\"%1\","
                                          "\"ip_gateway\":\"%2\""
                                          "}")
                                     .arg(IPaddress)
                                     .arg(GateWsys);

        qDebug() << "settingNetwork:" << settingNetwork;
        sendMessage(settingNetwork);
        emit sendToWeb(settingNetwork);
        client->isConnected = false;
    }else if (getCommand == "editTimesyncServer") {
            mysql->IP_TIMERSERVER = command["editsTimeSyncServer"].toString();
            mysql->updateDataBaseUSER();
            networks->ip_timeserver = command["editsTimeSyncServer"].toString();
            networking->setNTPServer(networks->ip_timeserver);
            QString timeServer = command["editsTimeSyncServer"].toString();
            qDebug() << "settimeServer:" << timeServer;
            QString settimeServer = QString("{"
                                         "\"objectName\":\"updateSettingNetwork\","
                                         "\"ntpServer\":\"%1\""
                                         "}")
                                .arg(timeServer);
            emit sendToWeb(settimeServer);
            emit sendMessage(settimeServer);
            qDebug() << "settimeServer:" << settimeServer;
             emit settingNetWorkandSNMP(settimeServer);
//    }else if (getCommand == "SNMPenable") {
//        bool plcDoError = command.contains("plcDOError") ? QJsonValue(command["plcDoError"]).toBool() : command.value("plcDoError").toBool();
//        bool plcDiError = command.contains("plcDiError") ? QJsonValue(command["plcDiError"]).toBool() : command.value("plcDiError").toBool();
//        bool hispeedPhaseA = command.contains("hispeedPhaseA") ? QJsonValue(command["hispeedPhaseA"]).toBool() : command.value("hispeedPhaseA").toBool();
//        bool hispeedPhaseB = command.contains("hispeedPhaseB") ? QJsonValue(command["hispeedPhaseB"]).toBool() : command.value("hispeedPhaseB").toBool();
//        bool hispeedPhaseC = command.contains("hispeedPhaseC") ? QJsonValue(command["hispeedPhaseC"]).toBool() : command.value("hispeedPhaseC").toBool();
//        bool commuPhaseA = command.contains("commuPhaseA") ? QJsonValue(command["commuPhaseA"]).toBool() : command.value("commuPhaseA").toBool();
//        bool commuPhaseB = command.contains("commuPhaseB") ? QJsonValue(command["commuPhaseB"]).toBool() : command.value("commuPhaseB").toBool();
//        bool commuPhaseC = command.contains("commuPhaseC") ? QJsonValue(command["commuPhaseC"]).toBool() : command.value("commuPhaseC").toBool();
//        bool gpsModule = command.contains("gpsModule") ? QJsonValue(command["gpsModule"]).toBool() : command.value("gpsModule").toBool();
//        bool systemInti = command.contains("systemInti") ? QJsonValue(command["systemInti"]).toBool() : command.value("systemInti").toBool();
//        bool commuError = command.contains("commuError") ? QJsonValue(command["commuError"]).toBool() : command.value("commuError").toBool();
//        bool relayStart = command.contains("relayStart") ? QJsonValue(command["relayStart"]).toBool() : command.value("relayStart").toBool();
//        bool surageStart = command.contains("surageStart") ? QJsonValue(command["surageStart"]).toBool() : command.value("surageStart").toBool();
//        bool preiodicStart = command.contains("preiodicStart") ? QJsonValue(command["preiodicStart"]).toBool() : command.value("preiodicStart").toBool();
//        bool manualTest = command.contains("manualTest") ? QJsonValue(command["manualTest"]).toBool() : command.value("manualTest").toBool();
//        bool lflfail = command.contains("lflfail") ? QJsonValue(command["lflfail"]).toBool() : command.value("lflfail").toBool();
//        bool lfloperate = command.contains("lfloperate") ? QJsonValue(command["lfloperate"]).toBool() : command.value("lfloperate").toBool();
//        if (command.contains("plcDoError")) {
//            QString setSNMP = QString("{"
//                                           "\"objectName\"     :\"updateSettingNetwork\","
//                                           "\"PLC_DO_ERROR\"         :\"%1\""
//                                           "}").arg(plcDoError ? "1" : "0");
//            qDebug() << "setSNMP plcDoError:" << setSNMP << plcDoError;
//            emit settingNetWorkandSNMP(setSNMP);
//        }else if (command.contains("plcDiError")) {
//            QString setSNMP = QString("{"
//                                           "\"objectName\"     :\"updateSettingNetwork\","
//                                           "\"PLC_DI_ERROR\"         :\"%1\""
//                                           "}").arg(plcDiError ? "1" : "0");
//            qDebug() << "setSNMP plcDiError:" << setSNMP << plcDiError;
//            emit settingNetWorkandSNMP(setSNMP);
//        }else if (command.contains("hispeedPhaseA")) {
//            QString setSNMP = QString("{"
//                                           "\"objectName\"     :\"updateSettingNetwork\","
//                                           "\"MODULE_HI_SPEED_PHASE_A_ERROR\"         :\"%1\""
//                                           "}").arg(hispeedPhaseA ? "1" : "0");
//            qDebug() << "setSNMP hispeedPhaseA:" << setSNMP << hispeedPhaseA;
//            emit settingNetWorkandSNMP(setSNMP);

//        }else if (command.contains("hispeedPhaseB")) {
//            QString setSNMP = QString("{"
//                                           "\"objectName\"     :\"updateSettingNetwork\","
//                                           "\"MODULE_HI_SPEED_PHASE_B_ERROR\"         :\"%1\""
//                                           "}").arg(hispeedPhaseB ? "1" : "0");
//            qDebug() << "setSNMP hispeedPhaseB:" << setSNMP << hispeedPhaseB;
//            emit settingNetWorkandSNMP(setSNMP);

//        }else if (command.contains("hispeedPhaseC")) {
//            QString setSNMP = QString("{"
//                                           "\"objectName\"     :\"updateSettingNetwork\","
//                                           "\"MODULE_HI_SPEED_PHASE_C_ERROR\"         :\"%1\""
//                                           "}").arg(hispeedPhaseC ? "1" : "0");
//            qDebug() << "setSNMP hispeedPhaseC:" << setSNMP << hispeedPhaseC;
//            emit settingNetWorkandSNMP(setSNMP);

//        }else if (command.contains("commuPhaseA")) {
//            QString setSNMP = QString("{"
//                                           "\"objectName\"     :\"updateSettingNetwork\","
//                                           "\"INTERNAL_PHASE_A_ERROR\"         :\"%1\""
//                                           "}").arg(commuPhaseA ? "1" : "0");
//            qDebug() << "setSNMP commuPhaseA:" << setSNMP << commuPhaseA;
//            emit settingNetWorkandSNMP(setSNMP);

//        }else if (command.contains("commuPhaseB")) {
//            QString setSNMP = QString("{"
//                                           "\"objectName\"     :\"updateSettingNetwork\","
//                                           "\"INTERNAL_PHASE_B_ERROR\"         :\"%1\""
//                                           "}").arg(commuPhaseB ? "1" : "0");
//            qDebug() << "setSNMP commuPhaseB:" << setSNMP << commuPhaseB;
//            emit settingNetWorkandSNMP(setSNMP);

//        }else if (command.contains("commuPhaseC")) {
//            QString setSNMP = QString("{"
//                                           "\"objectName\"     :\"updateSettingNetwork\","
//                                           "\"INTERNAL_PHASE_C_ERROR\"         :\"%1\""
//                                           "}").arg(commuPhaseC ? "1" : "0");
//            qDebug() << "setSNMP commuPhaseC:" << setSNMP << commuPhaseC;
//            emit settingNetWorkandSNMP(setSNMP);

//        }else if (command.contains("gpsModule")) {
//            QString setSNMP = QString("{"
//                                           "\"objectName\"     :\"updateSettingNetwork\","
//                                           "\"GPS_MODULE_FAIL\"         :\"%1\""
//                                           "}").arg(gpsModule ? "1" : "0");
//            qDebug() << "setSNMP gpsModule:" << setSNMP << gpsModule;
//            emit settingNetWorkandSNMP(setSNMP);

//        }else if (command.contains("systemInti")) {
//            QString setSNMP = QString("{"
//                                           "\"objectName\"     :\"updateSettingNetwork\","
//                                           "\"SYSTEM_INITIAL\"         :\"%1\""
//                                           "}").arg(systemInti ? "1" : "0");
//            qDebug() << "setSNMP systemInti:" << setSNMP << systemInti;
//            emit settingNetWorkandSNMP(setSNMP);

//        }else if (command.contains("commuError")) {
//            QString setSNMP = QString("{"
//                                           "\"objectName\"     :\"updateSettingNetwork\","
//                                           "\"COMMUNICATION_ERROR\"         :\"%1\""
//                                           "}").arg(commuError ? "1" : "0");
//            qDebug() << "setSNMP commuError:" << setSNMP << commuError;
//            emit settingNetWorkandSNMP(setSNMP);

//        }else if (command.contains("relayStart")) {
//            QString setSNMP = QString("{"
//                                           "\"objectName\"     :\"updateSettingNetwork\","
//                                           "\"RELAY_START_EVENT\"         :\"%1\""
//                                           "}").arg(relayStart ? "1" : "0");
//            qDebug() << "setSNMP relayStart:" << setSNMP << relayStart;
//            emit settingNetWorkandSNMP(setSNMP);

//        }else if (command.contains("surageStart")) {
//            QString setSNMP = QString("{"
//                                           "\"objectName\"     :\"updateSettingNetwork\","
//                                           "\"SURGE_START_EVENT\"         :\"%1\""
//                                           "}").arg(surageStart ? "1" : "0");
//            qDebug() << "setSNMP surageStart:" << setSNMP << surageStart;
//            emit settingNetWorkandSNMP(setSNMP);

//        }else if (command.contains("preiodicStart")) {
//            QString setSNMP = QString("{"
//                                           "\"objectName\"     :\"updateSettingNetwork\","
//                                           "\"PERIODIC_TEST_EVENT\"         :\"%1\""
//                                           "}").arg(preiodicStart ? "1" : "0");
//            qDebug() << "setSNMP preiodicStart:" << setSNMP << preiodicStart;
//            emit settingNetWorkandSNMP(setSNMP);

//        }else if (command.contains("manualTest")) {
//            QString setSNMP = QString("{"
//                                           "\"objectName\"     :\"updateSettingNetwork\","
//                                           "\"MANUAL_TEST_EVENT\"         :\"%1\""
//                                           "}").arg(manualTest ? "1" : "0");
//            qDebug() << "setSNMP manualTest:" << setSNMP << manualTest;
//            emit settingNetWorkandSNMP(setSNMP);

//        }else if (command.contains("lflfail")) {
//            QString setSNMP = QString("{"
//                                           "\"objectName\"     :\"updateSettingNetwork\","
//                                           "\"LFL_FAIL\"         :\"%1\""
//                                           "}").arg(lflfail ? "1" : "0");
//            qDebug() << "setSNMP lflfail:" << setSNMP << lflfail;
//            emit settingNetWorkandSNMP(setSNMP);

//        }else if (command.contains("lfloperate")) {
//            QString setSNMP = QString("{"
//                                           "\"objectName\"     :\"updateSettingNetwork\","
//                                           "\"LFL_OPERATE\"         :\"%1\""
//                                           "}").arg(lfloperate ? "1" : "0");
//            qDebug() << "setSNMP lfloperate:" << setSNMP << lfloperate;
//            emit settingNetWorkandSNMP(setSNMP);

//        }
//        qDebug() << "SNMPenable:" << plcDoError << plcDiError << hispeedPhaseA << hispeedPhaseB << hispeedPhaseC << commuPhaseA << commuPhaseB << commuPhaseC << gpsModule << systemInti << commuError << relayStart << surageStart << preiodicStart << manualTest << lflfail << lfloperate;
     }else if (getCommand == "SNMPenable") {
         auto sendSnmpBool = [&](const QString &key, bool value) {
             QJsonObject obj;
             obj["objectName"] = "updateSettingNetwork";
             obj[key] = value;   // ส่งเป็น bool จริง

             QString json = QString::fromUtf8(QJsonDocument(obj).toJson(QJsonDocument::Compact));
             qDebug() << "setSNMP" << key << ":" << json << value;
             emit settingNetWorkandSNMP(json);
         };

         if (command.contains("plcDoError")) {
             bool value = command.value("plcDoError").toBool();
             sendSnmpBool("PLC_DO_ERROR", value);

         } else if (command.contains("plcDiError")) {
             bool value = command.value("plcDiError").toBool();
             sendSnmpBool("PLC_DI_ERROR", value);

         } else if (command.contains("hispeedPhaseA")) {
             bool value = command.value("hispeedPhaseA").toBool();
             sendSnmpBool("MODULE_HI_SPEED_PHASE_A_ERROR", value);

         } else if (command.contains("hispeedPhaseB")) {
             bool value = command.value("hispeedPhaseB").toBool();
             sendSnmpBool("MODULE_HI_SPEED_PHASE_B_ERROR", value);

         } else if (command.contains("hispeedPhaseC")) {
             bool value = command.value("hispeedPhaseC").toBool();
             sendSnmpBool("MODULE_HI_SPEED_PHASE_C_ERROR", value);

         } else if (command.contains("commuPhaseA")) {
             bool value = command.value("commuPhaseA").toBool();
             sendSnmpBool("INTERNAL_PHASE_A_ERROR", value);

         } else if (command.contains("commuPhaseB")) {
             bool value = command.value("commuPhaseB").toBool();
             sendSnmpBool("INTERNAL_PHASE_B_ERROR", value);

         } else if (command.contains("commuPhaseC")) {
             bool value = command.value("commuPhaseC").toBool();
             sendSnmpBool("INTERNAL_PHASE_C_ERROR", value);

         } else if (command.contains("gpsModule")) {
             bool value = command.value("gpsModule").toBool();
             sendSnmpBool("GPS_MODULE_FAIL", value);

         } else if (command.contains("systemInti")) {
             bool value = command.value("systemInti").toBool();
             sendSnmpBool("SYSTEM_INITIAL", value);

         } else if (command.contains("commuError")) {
             bool value = command.value("commuError").toBool();
             sendSnmpBool("COMMUNICATION_ERROR", value);

         } else if (command.contains("relayStart")) {
             bool value = command.value("relayStart").toBool();
             sendSnmpBool("RELAY_START_EVENT", value);

         } else if (command.contains("surageStart")) {
             bool value = command.value("surageStart").toBool();
             sendSnmpBool("SURGE_START_EVENT", value);

         } else if (command.contains("preiodicStart")) {
             bool value = command.value("preiodicStart").toBool();
             sendSnmpBool("PERIODIC_TEST_EVENT", value);

         } else if (command.contains("manualTest")) {
             bool value = command.value("manualTest").toBool();
             sendSnmpBool("MANUAL_TEST_EVENT", value);

         } else if (command.contains("lflfail")) {
             bool value = command.value("lflfail").toBool();
             sendSnmpBool("LFL_FAIL", value);

         } else if (command.contains("lfloperate")) {
             bool value = command.value("lfloperate").toBool();
             sendSnmpBool("LFL_OPERATE", value);
         }

         qDebug() << "SNMPenable:" << qmlJson;
    }else if (getCommand.contains("sagText")) {
        double sagFactor = QJsonValue(command["sagText"]).toDouble();
        QString displaySetting = QString("{"
                                        "\"objectName\"     :\"displaySetting\","
                                        "\"sagFactor\"         :%1"
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
        distanceShow = QJsonValue(command["distancetoshowText"]).toDouble();
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
    }else if (getCommand == "GetSettingDisplay") {
        sagFactorInit = command["sagFactorInit"].toDouble();
        samplingRateInit = command["samplingRateInit"].toDouble();
        distanceToStartInit = command["distanceToStartInit"].toDouble();
        distanceToShowInit = command["distanceToShowInit"].toDouble();
        fulldistancesInit = command["fulldistancesInit"].toDouble();

        QString parameterDisplay = QString("{"
                                           "\"objectName\":\"GetSettingDisplay\","
                                           "\"sagFactorInit\":%1,"
                                           "\"samplingRateInit\":%2,"
                                           "\"distanceToStartInit\":%3,"
                                           "\"distanceToShowInit\":%4,"
                                           "\"fulldistancesInit\":%5"
                                           "}").arg(sagFactorInit).arg(samplingRateInit).arg(distanceToStartInit).arg(distanceToShowInit).arg(fulldistancesInit);
        qDebug() << "updataParameterDisplay:" << sagFactorInit << samplingRateInit << distanceToStartInit << distanceToShowInit << fulldistancesInit;
        cppCommand(parameterDisplay);
//        calculate(parameterDisplay);

    } else if (getCommand == "getThreshold") {
        double thresholdInitA = command["thresholdInitA"].toDouble();
        double thresholdInitB = command["thresholdInitB"].toDouble();
        double thresholdInitC = command["thresholdInitC"].toDouble();

        QString updatethresholdParam = QString("{"
                                           "\"objectName\":\"getThreshold\","
                                           "\"thresholdInitA\":%1,"
                                           "\"thresholdInitB\":%2,"
                                           "\"thresholdInitC\":%3"
                                           "}").arg(thresholdInitA).arg(thresholdInitB).arg(thresholdInitC);
        qDebug() << "updatethresholdParam:" << thresholdInitA << thresholdInitB << thresholdInitC;
        cppCommand(updatethresholdParam);
        calculate(updatethresholdParam);
    }else if(getCommand == "ManualTest"){
        cppManual = "ManualTest";
        manualtest(cppManual);
    }else if(getCommand == "PatternTest"){
        int patternNum = command["patternNum"].toInt();
        cppPattern = "PatternTest";
        patterntest(patternNum);
    }else if(getCommand == "CLEAR_ALARM"){
        cppCommand(qmlJson);
    }else if (getCommand == "dataPlotingA") {
        isProcessingA = true;
        QJsonDocument doc = QJsonDocument::fromJson(qmlJson.toUtf8());
        QJsonObject obj = doc.object();
        QString fileName = obj.contains("fileName") ? obj["fileName"].toString() : QString();
        qDebug() << "dataPlotingA:";
        clearPhaseData("A");
        processData(qmlJson, "A", fileName);
        isProcessingA = false;
    }else if (getCommand == "dataPlotingB") {
        // if (isProcessingB) return;
        isProcessingB = true;
        QJsonDocument doc = QJsonDocument::fromJson(qmlJson.toUtf8());
        QJsonObject obj = doc.object();
        QString fileName = obj.contains("fileName") ? obj["fileName"].toString() : QString();
        qDebug() << "dataPlotingB:";
         clearPhaseData("B");
        processData(qmlJson, "B", fileName);
        isProcessingB = false;
    }else if (getCommand == "dataPlotingC") {
        isProcessingB = true;
        QJsonDocument doc = QJsonDocument::fromJson(qmlJson.toUtf8());
        QJsonObject obj = doc.object();
        QString fileName = obj.contains("fileName") ? obj["fileName"].toString() : QString();
        qDebug() << "dataPlotingC:";
        clearPhaseData("C");
        processData(qmlJson, "C", fileName);
        isProcessingB = false;
    }else if (getCommand == "patternA") {
            QJsonDocument doc = QJsonDocument::fromJson(qmlJson.toUtf8());
            QJsonObject obj = doc.object();
            QString fileName = obj.contains("fileName") ? obj["fileName"].toString() : QString();
            qDebug() << "processPatternDataA:" << obj["distance"].toArray().size() << obj["voltage"].toArray().size() << obj["text"].toString() << fileName;
            if(obj["text"].toString() != ""){
                marginInterlog = true;
            }
            // qDebug() << "cppSubmitTextFiled_patternA:" << qmlJson << ;
            processPatternData(qmlJson, "A", fileName);
            return;
    }else if (getCommand == "patternB") {
        QJsonDocument doc = QJsonDocument::fromJson(qmlJson.toUtf8());
        QJsonObject obj = doc.object();
        QString fileName = obj.contains("fileName") ? obj["fileName"].toString() : QString();
        qDebug() << "processPatternDataB:";
        if(obj["text"].toString() != ""){
            marginInterlog = true;
        }
        processPatternData(qmlJson, "B", fileName);
    }else if (getCommand == "patternC") {
        QJsonDocument doc = QJsonDocument::fromJson(qmlJson.toUtf8());
        QJsonObject obj = doc.object();
        QString fileName = obj.contains("fileName") ? obj["fileName"].toString() : QString();
        qDebug() << "processPatternDataC:";
        if(obj["text"].toString() != ""){
            marginInterlog = true;
        }
        processPatternData(qmlJson, "C", fileName);
    }else if(command["objectName"].toString() == "dataSurgeA") {
         qDebug() << "dataSurgeA:" << qmlJson;
         isProcessingSurgeA = true;
         QJsonDocument doc = QJsonDocument::fromJson(qmlJson.toUtf8());
         QJsonObject obj = doc.object();
         QString fileName = obj.contains("fileName") ? obj["fileName"].toString() : QString();
         qDebug() << "dataSurgeA:" << fileName;
         clearPhaseData("A");
         processSurge(qmlJson, "A", fileName);
         isProcessingSurgeA = false;
    }else if(command["objectName"].toString() == "dataSurgeB") {
         qDebug() << "dataSurgeB:" << qmlJson;
         isProcessingSurgeB = true;
         QJsonDocument doc = QJsonDocument::fromJson(qmlJson.toUtf8());
         QJsonObject obj = doc.object();
         QString fileName = obj.contains("fileName") ? obj["fileName"].toString() : QString();
         qDebug() << "dataSurgeB:";
         clearPhaseData("B");
         processSurge(qmlJson, "B", fileName);
         isProcessingSurgeB = false;
    }else if(command["objectName"].toString() == "dataSurgeC") {
         qDebug() << "dataSurgeC:" << qmlJson;
         isProcessingSurgeC = true;
         QJsonDocument doc = QJsonDocument::fromJson(qmlJson.toUtf8());
         QJsonObject obj = doc.object();
         QString fileName = obj.contains("fileName") ? obj["fileName"].toString() : QString();
         qDebug() << "dataSurgeC:";
         clearPhaseData("C");
         processSurge(qmlJson, "C", fileName);
         isProcessingSurgeC = false;
    }else if(getCommand == "dataPlotingSurge") {
        qDebug() << "dataPlotingSurge:" << qmlJson;
//        processData(qmlJson, "A");
    }else if(getCommand == "TOWER_NO") {
        qDebug() << "TOWER_NO:" << qmlJson;
        QJsonDocument doc = QJsonDocument::fromJson(qmlJson.toUtf8());
        QJsonObject obj = doc.object();
        double distance = obj.contains("Fulldistance") ? obj["fileName"].toDouble() : double();
        cppCommand(qmlJson);
    }else if(getCommand == "TOWER_NO_INIT") {
         qDebug() << "TOWER_NO_INIT:" << qmlJson;
         QJsonDocument doc = QJsonDocument::fromJson(qmlJson.toUtf8());
         QJsonObject obj = doc.object();
         double distance = obj.contains("Fulldistance") ? obj["fileName"].toDouble() : double();
         cppCommand(qmlJson);
    }else if(getCommand == "sendMail") {
         qDebug() << "sendMail:" << qmlJson;

         cppCommand(qmlJson);
    }else if (getCommand == "Network") {
         qDebug() << "Check Network:" << command["ip_address"].toString() << command.contains("ip_address");

         QString ip = command["ip_address"].toString().trimmed();
         QString gateway = command["ip_gateway"].toString().trimmed();
         QString snmp = command["ip_snmp"].toString().trimmed();
         QString timeServer = command["ip_timeserver"].toString().trimmed();
         qDebug() << "Network_userMode:" << userMode;
         qDebug() << "before_qmlJson:" << qmlJson << gateway;
         if (!ip.isEmpty()) {
             mainIP_address = ip;
             networks->ip_gateway = gateway;
             networks->ip_snmp = snmp;
             networks->ip_timeserver = timeServer;

             // ✅ เตรียม JSON object สำหรับส่งออกไปยัง QML
             QJsonObject jsonOut;
             jsonOut["objectName"] = "Network";
             jsonOut["ip_address"] = ip;
             jsonOut["ip_gateway"] = gateway;
             jsonOut["ip_snmp"] = snmp;
             jsonOut["ip_timeserver"] = timeServer;
             jsonOut["userMode"] = userMode;
             qDebug() << "after_qmlJson:" << qmlJson;

             QJsonDocument doc(jsonOut);
             QString jsonString = QString::fromUtf8(doc.toJson(QJsonDocument::Compact));
             emit sendToWeb(jsonString);
//             cppCommand(jsonString);
         } else {
             qWarning() << "[Network] ip_address is empty. Skipping update.";
         }
    }else if(getCommand == "spinBoxDisplay"){
        int levelofligth = command["displayLight"].toInt();
        qDebug() << "levelofligth:" << levelofligth;
        if(levelofligth == 10){
            system("sudo pigs p 13 255");
        }else if(levelofligth == 9){
            system("sudo pigs p 13 230");
        }else if(levelofligth == 8){
            system("sudo pigs p 13 205");
        }else if(levelofligth == 7){
            system("sudo pigs p 13 180");
        }else if(levelofligth == 6){
            system("sudo pigs p 13 155");
        }else if(levelofligth == 5){
            system("sudo pigs p 13 130");
        }else if(levelofligth == 4){
            system("sudo pigs p 13 80");
        }else if(levelofligth == 3){
            system("sudo pigs p 13 60");
        }else if(levelofligth == 2){
            system("sudo pigs p 13 55");
        }else if(levelofligth == 1){
            system("sudo pigs p 13 50");
        }
    }else if (getCommand == "getPeriodicInfo") {
         const QString newTime = QJsonValue(command["Time"]).toString().trimmed();
         const bool isRemotePayload = command.contains("remotePayload")
                                      ? QJsonValue(command["remotePayload"]).toBool()
                                      : false;

         qDebug() << "getPeriodicInfo:" << newTime
                  << "remoteMode=" << remoteMode
                  << "isRemotePayload=" << isRemotePayload
                  << "mainIP_address=" << mainIP_address
                  << "Own Periodic Time =" << PeriodicTime
                  << "Another side Display =" << recordPeriodic
                  << "displayPeriodicTime =" << displayPeriodicTime;

         // ------------------------------------------------------------
         // REMOTE PAYLOAD:
         // ข้อมูลจากอีกฝั่ง เอาไว้เก็บเป็น recordPeriodic อย่างเดียว
         // ห้ามไปทับ time บน GUI ตอนที่เราอยู่ local mode
         // ------------------------------------------------------------
         if (isRemotePayload) {
             recordPeriodic = newTime;

             qDebug() << "[REMOTE PAYLOAD] recordPeriodic =" << recordPeriodic
                      << "PeriodicTime(local still) =" << PeriodicTime
                      << "displayPeriodicTime(gui still) =" << displayPeriodicTime;

             // อัปเดต GUI เฉพาะตอนที่ยัง remote อยู่จริง
             if (remoteMode) {
                 displayPeriodicTime = newTime;

                 QJsonObject ui;
                 ui["objectName"] = "updateRemotePeriodic";
                 ui["Time"] = displayPeriodicTime;
                 cppCommand(QString::fromUtf8(QJsonDocument(ui).toJson(QJsonDocument::Compact)));

                 qDebug() << "[REMOTE PAYLOAD] update GUI because remoteMode=true"
                          << "displayPeriodicTime =" << displayPeriodicTime;
             }

             return;
         }

         // ------------------------------------------------------------
         // REMOTE MODE:
         // forward ไปอีกฝั่ง แล้วจบ
         // ห้ามแตะ local PeriodicTime
         // ------------------------------------------------------------
         if (remoteMode) {
             QJsonObject fwd = command;
             fwd["type"] = "remote_command";
             fwd["from"] = userMode;
             fwd["ts"] = QDateTime::currentDateTime().toString(Qt::ISODate);
             fwd["remotePayload"] = true;

             const QString msg = QString::fromUtf8(QJsonDocument(fwd).toJson(QJsonDocument::Compact));
             qDebug() << "[REMOTE] forward getPeriodicInfo to peer:" << msg;

             sendPeerMessageReliable(msg);

             // ตอน remote ให้ GUI โชว์ค่าที่กำลังแก้อยู่ได้
             displayPeriodicTime = newTime;

             QJsonObject ui;
             ui["objectName"] = "updateRemotePeriodic";
             ui["Time"] = displayPeriodicTime;
             cppCommand(QString::fromUtf8(QJsonDocument(ui).toJson(QJsonDocument::Compact)));

             qDebug() << "[REMOTE] local host NOT updated"
                      << "PeriodicTime(local still) =" << PeriodicTime
                      << "recordPeriodic =" << recordPeriodic
                      << "displayPeriodicTime =" << displayPeriodicTime;
             return;
         }

         // ------------------------------------------------------------
         // LOCAL MODE:
         // update local จริง
         // ------------------------------------------------------------
         PeriodicTime = newTime;
         displayPeriodicTime = PeriodicTime;

         qDebug() << "[LOCAL] PeriodicTime =" << PeriodicTime
                  << "displayPeriodicTime =" << displayPeriodicTime;

         // อัปเดต QML local
         cppCommand(qmlJson);

         // save DB / ส่ง PLC
         emit updateTimer(qmlJson);
         qDebug() << "[LOCAL] emit updateTimer(getPeriodicInfo) =" << qmlJson;

         // ส่ง periodic_time ของเราไปให้อีกฝั่ง
         if (!PeriodicTime.isEmpty() && peer) {
             QJsonObject o;
             o["type"] = "periodic_time";
             o["ip"] = monitorIP;
             o["Time"] = PeriodicTime;
             o["from"] = userMode;
             o["ts"]   = QDateTime::currentDateTime().toString(Qt::ISODate);

             const QString msg = QString::fromUtf8(QJsonDocument(o).toJson(QJsonDocument::Compact));
             qDebug() << "[PEER][PERIODIC] send local periodic_time:" << msg;
             sendPeerMessageReliable(msg);
         }
    }else if(getCommand == "statusFail"){
         qDebug()<< "statusFails:" << qmlJson;
         sendMessage(qmlJson);
    }else if(getCommand == "statusOperate"){
         qDebug()<< "statusFails:" << qmlJson;
         sendMessage(qmlJson);
    }else if(getCommand == "statusFails"){
         qDebug()<< "update_statusFails:" << qmlJson;
         counttimerDisconnect = 0;
         cppCommand(qmlJson);
    }else if(command["objectName"].toString() == "autoSetValueMarginA"){
         qDebug()<< "AutoValueA:" << qmlJson;
         emit updataListOfMarginA(qmlJson);
    }else if(command["objectName"].toString() == "autoSetValueMarginB"){
         qDebug()<< "AutoValueB:" << qmlJson;
         emit updataListOfMarginB(qmlJson);
    }else if(command["objectName"].toString() == "autoSetValueMarginC"){
         qDebug()<< "AutoValueC:" << qmlJson;
         emit updataListOfMarginC(qmlJson);
    }else if(getCommand == "statusOperates"){
         qDebug()<< "update_statusOperates:" << qmlJson;
         cppCommand(qmlJson);
    }else if(getCommand == "updateValueMargin"){
        qDebug()<< "test_updateValueMargin:" << qmlJson;
        emit getMarginUpdate();
    }else if(getCommand == "MarginTableUpdated"){
        qDebug()<< "MarginTableUpdated:" << qmlJson;
        cppCommand(qmlJson);
    }else if(getCommand == "marginlistCountA"){
        int listNumOfMargin = QJsonValue(command["no"]).toInt();
        int listNumOfmaxmargin = QJsonValue(command["maxmargin"]).toInt();
        qDebug()<< "marginlistCountA:" << qmlJson << listNumOfMargin << listNumOfmaxmargin;
        cppCommand(qmlJson);
    }else if(getCommand == "marginlistCountB"){
        qDebug()<< "marginlistCountB:" << qmlJson;
        cppCommand(qmlJson);
    }else if(getCommand == "marginlistCountC"){
        qDebug()<< "marginlistCountC:" << qmlJson;
        cppCommand(qmlJson);
    }else if(getCommand == "updateParameterMargin"){
        qDebug()<< "updateParameterMargin:" << qmlJson;
        cppCommand(qmlJson);
    }else if(getEventAndAlert == "PLC_DO_ERROR") {
        qDebug() << "PLC_DO_ERROR" << getEventAndAlert;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(qmlJson.toUtf8());
        if (!jsonDoc.isObject()) {
            qDebug() << "Invalid JSON format.";
            return;
        }
        QJsonObject command = jsonDoc.object();
        if (command.contains("state") && command["state"].isBool()) {
            bool currentState = command["state"].toBool();
            if (isFirstEvent_DO) {
                qDebug() << "First event - Sending command...";
                cppCommand(qmlJson);
                previousStates_DO = currentState;
                isFirstEvent_DO = false;
                return;
            }
            if (currentState != previousStates_DO) {
                qDebug() << "State changed - Sending command...";
                cppCommand(qmlJson);
                previousStates_DO = currentState;
            } else {
            }
        } else {
        }
    }else if(getEventAndAlert == "PLC_DI_ERROR") {
        QJsonDocument jsonDoc = QJsonDocument::fromJson(qmlJson.toUtf8());
        if (!jsonDoc.isObject()) {
            return;
        }
        QJsonObject command = jsonDoc.object();
        if (command.contains("state") && command["state"].isBool()) {
            bool currentState = command["state"].toBool();
            if (isFirstEvent_DI) {
                qDebug() << "First event - Sending command...";
                cppCommand(qmlJson);
                previousStates_DI = currentState;
                isFirstEvent_DI = false;
                return;
            }

            if (currentState != previousStates_DI) {
                qDebug() << "State changed - Sending command...";
                cppCommand(qmlJson);
                previousStates_DI = currentState;
            } else {
            }
        } else {
            qDebug() << "Missing or invalid 'state' field.";
        }
    }else if(getEventAndAlert == "INTERNAL_PHASE_A_ERROR") {
        QJsonDocument jsonDoc = QJsonDocument::fromJson(qmlJson.toUtf8());
        if (!jsonDoc.isObject()) {
            qDebug() << "Invalid JSON format.";
            return;
        }
        QJsonObject command = jsonDoc.object();
        if (command.contains("state") && command["state"].isBool()) {
            bool currentState = command["state"].toBool();
            if (isFirstEvent_PHASE_A_ERROR) {
                qDebug() << "First event - Sending command...";
                cppCommand(qmlJson);
                previousStates_PHASE_A_ERROR = currentState;
                isFirstEvent_PHASE_A_ERROR = false;
                return;
            }
            if (currentState != previousStates_PHASE_A_ERROR) {
                qDebug() << "State changed - Sending command...";
                cppCommand(qmlJson);
                previousStates_PHASE_A_ERROR = currentState;
            } else {
            }
        } else {
        }
    }else if(getEventAndAlert == "INTERNAL_PHASE_B_ERROR") {
        QJsonDocument jsonDoc = QJsonDocument::fromJson(qmlJson.toUtf8());
        if (!jsonDoc.isObject()) {
            qDebug() << "Invalid JSON format.";
            return;
        }
        QJsonObject command = jsonDoc.object();
        if (command.contains("state") && command["state"].isBool()) {
            bool currentState = command["state"].toBool();
            if (isFirstEvent_PHASE_B_ERROR) {
                qDebug() << "First event - Sending command...";
                cppCommand(qmlJson);
                previousStates_PHASE_B_ERROR = currentState;
                isFirstEvent_PHASE_B_ERROR = false;
                return;
            }
            if (currentState != previousStates_PHASE_B_ERROR) {
                cppCommand(qmlJson);
                previousStates_PHASE_B_ERROR = currentState;
            } else {
            }
        } else {
            qDebug() << "Missing or invalid 'state' field.";
        }
    }else if(getEventAndAlert == "INTERNAL_PHASE_C_ERROR") {
        QJsonDocument jsonDoc = QJsonDocument::fromJson(qmlJson.toUtf8());
        if (!jsonDoc.isObject()) {
            qDebug() << "Invalid JSON format.";
            return;
        }
        QJsonObject command = jsonDoc.object();
        if (command.contains("state") && command["state"].isBool()) {
            bool currentState = command["state"].toBool();
            if (isFirstEvent_PHASE_C_ERROR) {
                cppCommand(qmlJson);
                previousStates_PHASE_C_ERROR = currentState;
                isFirstEvent_PHASE_C_ERROR = false;
                return;
            }
            if (currentState != previousStates_PHASE_C_ERROR) {
                cppCommand(qmlJson);
                previousStates_PHASE_C_ERROR = currentState;
            } else {
                qDebug() << "State unchanged - Ignoring.";
            }
        } else {
            qDebug() << "Missing or invalid 'state' field.";
        }
    }else if(getEventAndAlert == "MODULE_HI_SPEED_PHASE_A_ERROR") {
        QJsonDocument jsonDoc = QJsonDocument::fromJson(qmlJson.toUtf8());
        if (!jsonDoc.isObject()) {
            qDebug() << "Invalid JSON format.";
            return;
        }
        QJsonObject command = jsonDoc.object();
        if (command.contains("state") && command["state"].isBool()) {
            bool currentState = command["state"].toBool();
            if (isFirstEvent_PHASE_A_ERROR) {
                cppCommand(qmlJson);
                previousStates_PHASE_A_ERROR = currentState;
                isFirstEvent_PHASE_A_ERROR = false;
                return;
            }
            if (currentState != previousStates_PHASE_A_ERROR) {
                cppCommand(qmlJson);
                previousStates_PHASE_A_ERROR = currentState;
            } else {
            }
        } else {
            qDebug() << "Missing or invalid 'state' field.";
        }
    }else if(getEventAndAlert == "MODULE_HI_SPEED_PHASE_B_ERROR") {
        QJsonDocument jsonDoc = QJsonDocument::fromJson(qmlJson.toUtf8());
        if (!jsonDoc.isObject()) {
            qDebug() << "Invalid JSON format.";
            return;
        }
        QJsonObject command = jsonDoc.object();
        if (command.contains("state") && command["state"].isBool()) {
            bool currentState = command["state"].toBool();
            if (isFirstEvent_PHASE_B_ERROR) {
                cppCommand(qmlJson);
                previousStates_PHASE_B_ERROR = currentState;
                isFirstEvent_PHASE_B_ERROR = false;
                return;
            }
            if (currentState != previousStates_PHASE_B_ERROR) {
                cppCommand(qmlJson);
                previousStates_PHASE_B_ERROR = currentState;
            } else {
                qDebug() << "State unchanged - Ignoring.";
            }
        } else {
            qDebug() << "Missing or invalid 'state' field.";
        }
    }else if(getEventAndAlert == "MODULE_HI_SPEED_PHASE_C_ERROR") {
        QJsonDocument jsonDoc = QJsonDocument::fromJson(qmlJson.toUtf8());
        if (!jsonDoc.isObject()) {
            qDebug() << "Invalid JSON format.";
            return;
        }
        QJsonObject command = jsonDoc.object();
        if (command.contains("state") && command["state"].isBool()) {
            bool currentState = command["state"].toBool();
            if (isFirstEvent_PHASE_C_ERROR) {
                cppCommand(qmlJson);
                previousStates_PHASE_C_ERROR = currentState;
                isFirstEvent_PHASE_C_ERROR = false;
                return;
            }
            if (currentState != previousStates_PHASE_C_ERROR) {
                cppCommand(qmlJson);
                previousStates_PHASE_C_ERROR = currentState;
            } else {
                qDebug() << "State unchanged - Ignoring.";
            }
        } else {
            qDebug() << "Missing or invalid 'state' field.";
        }
    }else if(getEventAndAlert == "GPS_MODULE_FAIL") {
        QJsonDocument jsonDoc = QJsonDocument::fromJson(qmlJson.toUtf8());
        if (!jsonDoc.isObject()) {
            qDebug() << "Invalid JSON format.";
            return;
        }
        QJsonObject command = jsonDoc.object();
        if (command.contains("state") && command["state"].isBool()) {
            bool currentState = command["state"].toBool();
            if (isFirstEvent_PHASE_C_ERROR) {
                cppCommand(qmlJson);
                previousStates_GPS_MODULE = currentState;
                isFirstEvent_GPS_MODULE = false;
                return;
            }
            if (currentState != previousStates_GPS_MODULE) {
                cppCommand(qmlJson);
                previousStates_GPS_MODULE = currentState;
            } else {
            }
        } else {
        }
    }else if(getEventAndAlert == "SYSTEM_INITIAL") {
        QJsonDocument jsonDoc = QJsonDocument::fromJson(qmlJson.toUtf8());
        if (!jsonDoc.isObject()) {
            qDebug() << "Invalid JSON format.";
            return;
        }
        QJsonObject command = jsonDoc.object();
        if (command.contains("state") && command["state"].isBool()) {
            bool currentState = command["state"].toBool();
            if (isFirstEvent_PHASE_C_ERROR) {
                cppCommand(qmlJson);
                previousStates_SYSTEM_INITIAL = currentState;
                isFirstEvent_SYSTEM_INITIAL = false;
                return;
            }
            if (currentState != previousStates_SYSTEM_INITIAL) {
                cppCommand(qmlJson);
                previousStates_SYSTEM_INITIAL = currentState;
            } else {
            }
        } else {
        }
    }else if(getEventAndAlert == "COMMUNICATION_ERROR") {
        QJsonDocument jsonDoc = QJsonDocument::fromJson(qmlJson.toUtf8());
        if (!jsonDoc.isObject()) {
            qDebug() << "Invalid JSON format.";
            return;
        }
        QJsonObject command = jsonDoc.object();
        cppCommand(qmlJson);

    }else if(getEventAndAlert == "RELAY_START_EVENT") {
        QJsonDocument jsonDoc = QJsonDocument::fromJson(qmlJson.toUtf8());
        if (!jsonDoc.isObject()) {
            qDebug() << "Invalid JSON format.";
            return;
        }
        QJsonObject command = jsonDoc.object();
        if (command.contains("state") && command["state"].isBool()) {
            bool currentState = command["state"].toBool();
            if (isFirstEvent_RELAY_START_EVENT) {
                cppCommand(qmlJson);
                previousStates_RELAY_START_EVENT = currentState;
                isFirstEvent_RELAY_START_EVENT = false;
                return;
            }
            if (currentState != previousStates_RELAY_START_EVENT) {
                cppCommand(qmlJson);
                previousStates_RELAY_START_EVENT = currentState;
            } else {
            }
        } else {
        }
    }else if(getEventAndAlert == "SURGE_START_EVENT_A" || getEventAndAlert == "SURGE_START_EVENT_B" || getEventAndAlert == "SURGE_START_EVENT_C") {
         qDebug() << "getEventAndAlert:" << qmlJson;
         cppCommand(qmlJson);
    }else if(getEventAndAlert == "Send Master Start" || getEventAndAlert == "Receive Master Start") {
         cppCommand(qmlJson);
    }else if(getEventAndAlert == "PERIODIC_TEST_EVENT") {
        QJsonDocument jsonDoc = QJsonDocument::fromJson(qmlJson.toUtf8());
        if (!jsonDoc.isObject()) {
            qDebug() << "Invalid JSON format.";
            return;
        }
        QJsonObject command = jsonDoc.object();
        if (command.contains("state") && command["state"].isBool()) {
            bool currentState = command["state"].toBool();
            if (isFirstEvent_PERIODIC_TEST_EVENT) {
                cppCommand(qmlJson);
                previousStates_PERIODIC_TEST_EVENT = currentState;
                isFirstEvent_PERIODIC_TEST_EVENT = false;
                return;
            }
            if (currentState != previousStates_PERIODIC_TEST_EVENT) {
                cppCommand(qmlJson);
                previousStates_PERIODIC_TEST_EVENT = currentState;
            } else {
            }
        } else {
        }
    }else if(getEventAndAlert == "MANUAL_TEST_EVENT") {
        QJsonDocument jsonDoc = QJsonDocument::fromJson(qmlJson.toUtf8());
        if (!jsonDoc.isObject()) {
            qDebug() << "Invalid JSON format.";
            return;
        }
        QJsonObject command = jsonDoc.object();
        if (command.contains("state") && command["state"].isBool()) {
            bool currentState = command["state"].toBool();

            if (isFirstEvent_MANUAL_TEST_EVENT) {
                cppCommand(qmlJson);
                previousStates_MANUAL_TEST_EVENT = currentState;
                isFirstEvent_MANUAL_TEST_EVENT = false;
                return;
            }

            if (currentState != previousStates_MANUAL_TEST_EVENT) {
                cppCommand(qmlJson);
                previousStates_MANUAL_TEST_EVENT = currentState;
            } else {
            }
        } else {
        }
    }else if(getEventAndAlert == "LFL_FAIL") {
        QJsonDocument jsonDoc = QJsonDocument::fromJson(qmlJson.toUtf8());
        if (!jsonDoc.isObject()) {
            qDebug() << "Invalid JSON format.";
            return;
        }
        QJsonObject command = jsonDoc.object();
        if (command.contains("state") && command["state"].isBool()) {
            bool currentState = command["state"].toBool();
            if (isFirstEvent_LFL_FAIL) {
                cppCommand(qmlJson);
                previousStates_LFL_FAIL = currentState;
                isFirstEvent_LFL_FAIL = false;
                return;
            }
            if (currentState != previousStates_LFL_FAIL) {
                cppCommand(qmlJson);
                previousStates_LFL_FAIL = currentState;
            } else {
            }
        } else {
        }
    }else if(getEventAndAlert == "LFL_OPERATE") {
        QJsonDocument jsonDoc = QJsonDocument::fromJson(qmlJson.toUtf8());
        if (!jsonDoc.isObject()) {
            qDebug() << "Invalid JSON format.";
            return;
        }
        QJsonObject command = jsonDoc.object();
        if (command.contains("state") && command["state"].isBool()) {
            bool currentState = command["state"].toBool();
            if (isFirstEvent_LFL_OPERATE) {
                cppCommand(qmlJson);
                previousStates_LFL_OPERATE = currentState;
                isFirstEvent_LFL_OPERATE = false;
                return;
            }
            if (currentState != previousStates_LFL_OPERATE) {
                cppCommand(qmlJson);
                previousStates_LFL_OPERATE = currentState;
            } else {
            }
        } else {
        }
    }else if(command["objectName"].toString() == "backupParameter") {
         qDebug() << "Check backupParameter:" << qmlJson;
         backupyZoomFactor = command["yZoomFactor"].toDouble();
         QJsonObject mainObject;
         mainObject.insert("objectName", "updateyZoomFactor");
         mainObject.insert("backupyZoomFactor", backupyZoomFactor);
         QJsonDocument jsonDoc(mainObject);
         QString updateyZoomFactor = jsonDoc.toJson(QJsonDocument::Compact);
         cppCommand(updateyZoomFactor);

    }else if(getCommand == "realDistanceA") {
        qDebug() << "Check Data realDistanceA:" << qmlJson;
        cppCommand(qmlJson);
    }else if(getCommand == "realDistanceB") {
        qDebug() << "Check Data realDistanceB:" << qmlJson;
        cppCommand(qmlJson);
    }else if(getCommand == "realDistanceC") {
        qDebug() << "Check Data realDistanceC:" << qmlJson;
        cppCommand(qmlJson);
    }else if(getCommand == "updateNTPServer"){
//         networks->ip_timeserver = command["ntpServer"].toString();
//         networking->setNTPServer(networks->ip_timeserver);
//         updateNTP();
    }else if (qmlJson == "CHANGETOSLAVE") {
    }else if (getCommand == "CHANGE") {
         qDebug() << "CHANGE:" << qmlJson
                  << "before mainIP_address=" << mainIP_address
                  << "dbMaster=" << mysql->IP_MASTER
                  << "dbSlave=" << mysql->IP_SLAVE
                  << "PeriodicTime(local)=" << PeriodicTime
                  << "recordPeriodic(remote)=" << recordPeriodic
                  << "displayPeriodicTime(gui)=" << displayPeriodicTime;

         if (!mysql) {
             qWarning() << "[CHANGE] mysql is null";
             return;
         }

         const QString ipM = mysql->IP_MASTER.trimmed();
         const QString ipS = mysql->IP_SLAVE.trimmed();

         if (ipM.isEmpty() || ipS.isEmpty()) {
             qWarning() << "[CHANGE] IP_MASTER/IP_SLAVE empty -> ignore";
             return;
         }

         QString cur = mainIP_address.trimmed();
         if (cur.isEmpty())
             cur = ipM;

         QString newTarget;
         QString guiTimeToShow;
         if (cur == ipM) {
             // MASTER -> SLAVE
             newTarget = ipS;
             if (!recordPeriodic.trimmed().isEmpty()) {
                 guiTimeToShow = recordPeriodic.trimmed();
             } else {
                 guiTimeToShow = displayPeriodicTime.trimmed();   // คงค่าที่หน้าจอไว้ก่อน
             }

             qDebug() << "[CHANGE] switch MASTER -> SLAVE"
                      << "newTarget =" << newTarget
                      << "showTime =" << guiTimeToShow
                      << "PeriodicTime(local)=" << PeriodicTime
                      << "recordPeriodic(remote)=" << recordPeriodic;
         }
         else if (cur == ipS) {
             // SLAVE -> MASTER
             newTarget = ipM;
             guiTimeToShow = PeriodicTime.trimmed();

             qDebug() << "[CHANGE] switch SLAVE -> MASTER"
                      << "newTarget =" << newTarget
                      << "showTime =" << guiTimeToShow
                      << "PeriodicTime(local)=" << PeriodicTime
                      << "recordPeriodic(remote)=" << recordPeriodic;
         }
         else {
             // fallback
             if (remoteMode) {
                 newTarget = ipM;
                 guiTimeToShow = PeriodicTime.trimmed();
             } else {
                 newTarget = ipS;
                 guiTimeToShow = !recordPeriodic.trimmed().isEmpty()
                                 ? recordPeriodic.trimmed()
                                 : displayPeriodicTime.trimmed();
             }

             qDebug() << "[CHANGE] cur not match -> fallback"
                      << "newTarget =" << newTarget
                      << "showTime =" << guiTimeToShow;
         }

         if (newTarget.isEmpty()) {
             qWarning() << "[CHANGE] newTarget empty";
             return;
         }

         if (mainIP_address.trimmed() == newTarget) {
             qDebug() << "[CHANGE] target unchanged =" << newTarget;
             return;
         }

         qDebug() << "[CHANGE] oldTarget =" << mainIP_address
                  << "newTarget =" << newTarget;
         remoteMode = !remoteMode;
         mainIP_address = newTarget;
         displayPeriodicTime = guiTimeToShow;
         {
             QJsonObject remotePeriodicObj;
             remotePeriodicObj["objectName"] = "updateRemotePeriodic";
             remotePeriodicObj["Time"] = displayPeriodicTime;

             const QString updateRemotePeriodic =
                     QString::fromUtf8(QJsonDocument(remotePeriodicObj).toJson(QJsonDocument::Compact));

             cppCommand(updateRemotePeriodic);

             qDebug() << "[CHANGE] send updateRemotePeriodic to QML:" << updateRemotePeriodic;
         }

         periodicInitialChecked = false;
         isVersion = false;

         qDebug() << "[CHANGE] state after switch"
                  << "remoteMode =" << remoteMode
                  << "PeriodicTime(local)=" << PeriodicTime
                  << "recordPeriodic(remote)=" << recordPeriodic
                  << "displayPeriodicTime(gui)=" << displayPeriodicTime;
         if (reconnectTimerSlave && reconnectTimerSlave->isActive()) {
             reconnectTimerSlave->stop();
             qDebug() << "[CHANGE] reconnectTimerSlave stopped";
         }

         if (client) {
             qDebug() << "[CHANGE] disconnect old PLC client only...";
             client->disconnectFromServer();
         }
         if (peer) {
             qDebug() << "[CHANGE] keep peer connection alive. role="
                      << peer->currentMode()
                      << "target=" << peer->currentTarget();
         }
         {
             QJsonObject o;
             o["objectName"] = "RemoteTarget";
             o["plcIP"] = mainIP_address;
             o["remoteMode"] = remoteMode;
             cppCommand(QString::fromUtf8(QJsonDocument(o).toJson(QJsonDocument::Compact)));
         }
         QTimer::singleShot(300, this, [this]() {
             qDebug() << "[CHANGE] restart PLC connection only to target =" << mainIP_address;

             reconnectTimerTimeoutSlave();

             if (reconnectTimerSlave && !reconnectTimerSlave->isActive())
                 reconnectTimerSlave->start(1000);
         });
//        sendMessage(qmlJson);
//        qDebug() << "CHANGE:" << qmlJson;
//        qDebug() << "Before UserMode:" << userMode << "reconnectTimerSlave:"<<reconnectTimerSlave->isActive()<< "reconnectTimerMaster:"<< reconnectTimerMaster->isActive() << networks->userTypeSelect;
//            #ifdef HwName
//                if(networks->userTypeSelect == "MASTER"){
//                    qDebug() << "userMode MASTER:" << qmlJson;
//                    mainIP_address = networks->ip_slave;
//                    networks->userTypeSelect = "SLAVE";
//                    userMode = "SLAVE";
//                    // reconnectTimerMaster->start(5000);
//                }else if(networks->userTypeSelect == "SLAVE"){
//                    qDebug() << "userMode SLAVE:" << qmlJson;
//                    networks->userTypeSelect = "MASTER";
//                    userMode = "MASTER";
//                    mainIP_address = networks->ip_master;
//                    // reconnectTimerSlave->start(5000);
//                }
//            #else

//            #endif
//        qDebug() << "After UserMode:" << userMode << "reconnectTimerSlave:"<<reconnectTimerSlave->isActive()<< "reconnectTimerMaster:"<< reconnectTimerMaster->isActive() << networks->userTypeSelect;
//        qDebug() << "mainIP_address:" << mainIP_address;
//        interlockUser = true;
//        client->m_webSocket.close();
        // client->disconnectFromServer();
    }else if(getCommand == "updateDate") {
         cppCommand(qmlJson);
    }else if(getCommand == "combinedDataPhaseA") {
        cppCommand(qmlJson);
    }else if(getCommand == "combinedDataPhaseB") {
        cppCommand(qmlJson);
    }else if(getCommand == "combinedDataPhaseC") {
        cppCommand(qmlJson);
    }else if (getCommand == "selectUser" || getCommand == "selectUserChange") { //
         qDebug() << "<<<------getCommand---->>" << getCommand << qmlJson;
         QString newMaster    = command["ip_master"].toString().trimmed();
         QString newSlave     = command["ip_slave"].toString().trimmed();
         QString newUserType  = command["userType"].toString().trimmed();

         qDebug() << "newMaster:" << "[" + newMaster + "]"
                  << "newSlave:" << "[" + newSlave + "]"
                  << "newUserType:" << "[" + newUserType + "]";

         // 2. เช็คว่ามาครบทั้ง 3 ค่า
         if (!newMaster.isEmpty() && !newSlave.isEmpty() && !newUserType.isEmpty()) {
             // 3. Assign ทุกตัว
             networks->ip_master = newMaster;
             networks->ip_slave = newSlave;
             userMode = newUserType;
             networks->userTypeSelect = userMode;
             mysql->USER = userMode;
             // 4. Emit update to Databases
             qDebug() << "networks->ip_master->>" << networks->ip_master << networks->ip_slave << userMode << networks->userTypeSelect << mysql->USER;
             emit updateMasterMode(networks->userTypeSelect,
                                   networks->ip_master,
                                   networks->ip_slave,
                                   SwVersion);
             emit sendToWeb(qmlJson);
             cppCommand(qmlJson);
             // 6. ตั้งค่า mainIP_address ตาม userMode STANDALONE
             if (userMode == "STANDALONE"){
                 qDebug() << "STANDALONE" << userMode;
//                 mainIP_address = networks->ip_master;
                 ///NewObjWeb
                 QJsonObject NewObjWeb;
                 NewObjWeb["menuID"] = "userMode";
                 NewObjWeb["userType"] = userMode;
                 NewObjWeb["IP_MASTER"] = mainIP_address;
                 NewObjWeb["IP_SNMP"] = mysql->IP_SNMP;
                 NewObjWeb["IP_TIMERSERVER"] = mysql->IP_TIMERSERVER;
                 const QString outJsonNewObjWeb = QString::fromUtf8(QJsonDocument(NewObjWeb).toJson(QJsonDocument::Compact));
                 emit broadcastMessage(outJsonNewObjWeb);

                 return;
             }else if (userMode == "MASTER"){
                qDebug() << "ip_master>>mainIP_address:" << mainIP_address << networks->ip_slave << networks->ip_master;
                mysql->USER = userMode;
                mysql->IP_MASTER = networks->ip_master;
                mysql->IP_SLAVE = networks->ip_slave;
                mainIP_address = networks->ip_master;
                ///NewObjWeb
                QJsonObject NewObjWeb;
                NewObjWeb["menuID"] = "userMode";
                NewObjWeb["userType"] = mysql->USER;
                NewObjWeb["IP_MASTER"] = mysql->IP_MASTER;
                NewObjWeb["IP_SLAVE"] = mysql->IP_SLAVE;
                NewObjWeb["IP_SNMP"] = mysql->IP_SNMP;
                NewObjWeb["IP_TIMERSERVER"] = mysql->IP_TIMERSERVER;
                const QString outJsonNewObjWeb = QString::fromUtf8(QJsonDocument(NewObjWeb).toJson(QJsonDocument::Compact));
                emit broadcastMessage(outJsonNewObjWeb);

//                 mainIP_address = networks->ip_slave;
                return;
             }else{
                 qDebug() << "ip_slave>>mainIP_address:" << mainIP_address << networks->ip_slave << networks->ip_master;
                 mysql->USER = userMode;
                 mysql->IP_MASTER = networks->ip_master;
                 mysql->IP_SLAVE = networks->ip_slave;
                 mainIP_address = networks->ip_slave;
                 QJsonObject NewObjWeb;
                 NewObjWeb["menuID"] = "userMode";
                 NewObjWeb["userType"] = mysql->USER;
                 NewObjWeb["IP_MASTER"] = mysql->IP_MASTER;
                 NewObjWeb["IP_SLAVE"] = mysql->IP_SLAVE;
                 NewObjWeb["IP_SNMP"] = mysql->IP_SNMP;
                 NewObjWeb["IP_TIMERSERVER"] = mysql->IP_TIMERSERVER;
                 const QString outJsonNewObjWeb = QString::fromUtf8(QJsonDocument(NewObjWeb).toJson(QJsonDocument::Compact));
                 emit broadcastMessage(outJsonNewObjWeb);
//                 mainIP_address = networks->ip_master;
                 return;
             }
             if (getCommand == "selectUserChange") {
                 interlockUser = true;
                 client->m_webSocket.close();
             }
             qDebug() << "[INFO] IP/userType updated forcefully.";
         } else {
             qWarning() << "[ERROR] selectUser command missing one or more required fields!";
         }
    }else if(getCommand == "selectUsers") {
         const QString userType = command.value("userType").toString().trimmed().toUpper();
         qDebug() << "selectUsers_test:" << userMode << userType << qmlJson;
         userMode = userType;
         mysql->USER = userMode;
         mysql->updateDataBaseUSER();

         qDebug() << "selectUsers_test2:" << userMode << userType << qmlJson;
         if (userType == "STANDALONE") {
             QJsonObject out;
             out["objectName"] = "STANDALONE";

             const QString outJson =
                 QString::fromUtf8(QJsonDocument(out).toJson(QJsonDocument::Compact));
             qDebug() << "selectUsers_test_userType:" << outJson << qmlJson;
             emit sendMessage(outJson);

            ///Display
             QJsonObject NewObj;
             NewObj["objectName"] = "selectUsers";
             NewObj["userType"] = userMode;
             NewObj["ip_master"] = mainIP_address;
             const QString outJsonNewObj = QString::fromUtf8(QJsonDocument(NewObj).toJson(QJsonDocument::Compact));
             cppCommand(outJsonNewObj);
             ///NewObjWeb
             QJsonObject NewObjWeb;
             NewObjWeb["menuID"] = "userMode";
             NewObjWeb["userType"] = userMode;
             NewObjWeb["IP_MASTER"] = mainIP_address;
             NewObjWeb["IP_SNMP"] = mysql->IP_SNMP;
             NewObjWeb["IP_TIMERSERVER"] = mysql->IP_TIMERSERVER;
             const QString outJsonNewObjWeb = QString::fromUtf8(QJsonDocument(NewObjWeb).toJson(QJsonDocument::Compact));
             emit broadcastMessage(outJsonNewObjWeb);
             return;
         }else if(userType == "SLAVE") {
             QJsonObject NewObj;
             NewObj["objectName"] = "selectUsers";
             NewObj["userType"] = userMode;
             NewObj["ip_slave"] = mysql->IP_MASTER;
             const QString outJsonNewObj = QString::fromUtf8(QJsonDocument(NewObj).toJson(QJsonDocument::Compact));
             qDebug() << "selectUsers_test_userType:" << qmlJson << outJsonNewObj;
             cppCommand(outJsonNewObj);
             sendMessage(qmlJson);

             QJsonObject NewObjWeb;
             NewObjWeb["menuID"] = "userMode";
             NewObjWeb["userType"] = userMode;
             NewObjWeb["IP_MASTER"] = mysql->IP_MASTER;
             NewObjWeb["IP_SLAVE"] = mysql->IP_SLAVE;
             NewObjWeb["IP_SNMP"] = mysql->IP_SNMP;
             NewObjWeb["IP_TIMERSERVER"] = mysql->IP_TIMERSERVER;
             const QString outJsonNewObjWeb = QString::fromUtf8(QJsonDocument(NewObjWeb).toJson(QJsonDocument::Compact));
             emit broadcastMessage(outJsonNewObjWeb);

         }else if(userType == "MASTER") {
             QJsonObject NewObj;
             NewObj["objectName"] = "selectUsers";
             NewObj["userType"] = userMode;
             NewObj["ip_master"] = mysql->IP_MASTER;
             const QString outJsonNewObj = QString::fromUtf8(QJsonDocument(NewObj).toJson(QJsonDocument::Compact));
             qDebug() << "selectUsers_test_userType:" << qmlJson << outJsonNewObj;
             cppCommand(outJsonNewObj);
             sendMessage(qmlJson);

             QJsonObject NewObjWeb;
             NewObjWeb["menuID"] = "userMode";
             NewObjWeb["userType"] = userMode;
             NewObjWeb["IP_MASTER"] = mysql->IP_MASTER;
             NewObjWeb["IP_SLAVE"] = mysql->IP_SLAVE;
             NewObjWeb["IP_SNMP"] = mysql->IP_SNMP;
             NewObjWeb["IP_TIMERSERVER"] = mysql->IP_TIMERSERVER;
             const QString outJsonNewObjWeb = QString::fromUtf8(QJsonDocument(NewObjWeb).toJson(QJsonDocument::Compact));
             emit broadcastMessage(outJsonNewObjWeb);

         }
//        qDebug() << "selectUsers_test:" << userMode << command["userType"].toString();
//        sendMessage(qmlJson);
    }else if(getCommand == "getSettingInfo") {
         qDebug() << "getSettingInfo_fromServer:" << qmlJson;
         double voltageInfo = command["voltage"].toDouble();
         QString substationInfo = command["substation"].toString();
         QString directionInfo = command["direction"].toString();
         QString linenoInfo = command["line_no"].toString();

         QString getSettingInfo = QString("{"
                                            "\"objectName\":\"getSettingInfo\","
                                            "\"voltage\":%1,"
                                            "\"substation\":\"%2\","
                                            "\"direction\":\"%3\","
                                            "\"line_no\":\"%4\""
                                            "}").arg(voltageInfo).arg(substationInfo).arg(directionInfo).arg(linenoInfo);

         cppCommand(getSettingInfo);
    }else if(getCommand == "detailInfoSetting") {
         qDebug() << "detailInfoSetting_fromServer:" << qmlJson;
         cppCommand(qmlJson);
    }else if(getCommand == "TrapsEnabling"){
        qDebug() <<networks->ip_address << networks->ip_gateway << networks->ip_snmp<< networks->ip_timeserver << command["ip_address"].toString() << command["ip_snmp"].toString();
        cppCommand(qmlJson);
        qDebug()<< "TrapsEnabling:" << qmlJson;
    }else if (getCommand == "system") {
         qDebug() << "system:" << qmlJson << userMode;
         cppCommand(qmlJson);
    }else if(getCommand == "Backtohome"){
         qDebug()<< "Backtohome:" << qmlJson << userMode;
        #ifdef HwName
//                 if(command["state"].toBool() == false){
                     if(userMode == "MASTER"){
                        userMode = "SLAVE";
                        qDebug()<< "userMode_MASTER:" << qmlJson << userMode;
                        mainIP_address = networks->ip_slave;
                        mysql->USER = userMode;
                     }else if(userMode == "SLAVE"){
                        qDebug()<< "userMode_SLAVE:" << qmlJson << userMode;
                        userMode = "MASTER";
                        mainIP_address = networks->ip_master;
                        mysql->USER = userMode;
                     }
                     client->m_webSocket.close();
//                 }
        #else

        #endif

    }else if(getCommand == "network"){
         qDebug()<< "Local network:" << qmlJson;

         cppCommand(qmlJson);
    }else if(getCommand == "warningTime"){
         qDebug()<< "warningTime:" << qmlJson;

         cppCommand(qmlJson);
    }else if(command["objectName"].toString() == "CLEAR_NAME"){
         qDebug()<< "CLEAR_NAME:" << qmlJson;

         cppCommand(qmlJson);
    }else{ //updateDisplayPeer
         qDebug()<< "debug all:" << qmlJson;
         cppCommand(qmlJson);
     }
}

QString getLocalIPAddress() {
    const auto addresses = QNetworkInterface::allAddresses();
    for (const QHostAddress &address : addresses) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && !address.isLoopback()) {
            return address.toString();
        }
    }
    return "127.0.0.1";
}

void mainwindows::updateDisplayOpp(QString message)
{
    qDebug() << "[updateDisplayOpp] RX:" << message;

    QString newIP, newGW;

    // 1) parse JSON ตาม key ที่คุณส่งมาจริง
    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8(), &err);

    if (err.error != QJsonParseError::NoError || !doc.isObject())
    {
        qWarning() << "[updateDisplayOpp] JSON parse error:" << err.errorString();
        return;
    }

    QJsonObject obj = doc.object();
    qDebug() << "[updateDisplayOpp] menuID =" << obj.value("menuID").toString();

    // ✅ เอาค่าจาก IP_MONITOR/GATEWAY_MONITOR ก่อน (ตามที่คุณส่งมา)
    if (obj.contains("IP_MONITOR"))
        newIP = obj.value("IP_MONITOR").toString().trimmed();

    if (obj.contains("GATEWAY_MONITOR"))
        newGW = obj.value("GATEWAY_MONITOR").toString().trimmed();

    // ✅ fallback เผื่อบางหน้าส่ง DISPLAY_IP/DISPLAY_GATEWAY
    if (newIP.isEmpty() && obj.contains("DISPLAY_IP"))
        newIP = obj.value("DISPLAY_IP").toString().trimmed();

    if (newGW.isEmpty() && obj.contains("DISPLAY_GATEWAY"))
        newGW = obj.value("DISPLAY_GATEWAY").toString().trimmed();

    qDebug() << "[updateDisplayOpp] parsed newIP=" << newIP << "newGW=" << newGW;

    // 2) update globals
    if (!newIP.isEmpty()) monitorIP = newIP;
    if (!newGW.isEmpty()) monitorGateWay = newGW;

    qDebug() << "[updateDisplayOpp] global monitorIP =" << monitorIP;
    qDebug() << "[updateDisplayOpp] global monitorGateWay =" << monitorGateWay;

    // 3) ensure dir exists แล้วค่อยเขียนไฟล์
    const QString dirPath  = "/home/pi";
    const QString filePath = "/home/pi/ipmonitor.txt";

    QDir dir(dirPath);
    if (!dir.exists())
    {
        qDebug() << "[updateDisplayOpp] dir not exists -> creating:" << dirPath;
        if (!dir.mkpath(dirPath))
        {
            qWarning() << "[updateDisplayOpp] mkpath failed:" << dirPath;
            return;
        }
    }

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qWarning() << "[updateDisplayOpp] cannot open file for write:" << filePath
                   << "err=" << file.errorString();
        return;
    }

    QTextStream out(&file);
    out << "monitorIP: \"" << monitorIP << "\"" << "\n";
    out << "monitorGateWay: \"" << monitorGateWay << "\"" << "\n";
    file.close();

    qDebug() << "[updateDisplayOpp] saved to file:" << filePath;

    // 4) broadcast confirm กลับเว็บ
    QJsonObject o;
    o["menuID"] = "ipMonitor";
    o["monitorIP"] = monitorIP;
    o["monitorGateWay"] = monitorGateWay;
    o["saved"] = true;

    const QString json = QString::fromUtf8(QJsonDocument(o).toJson(QJsonDocument::Compact));
    emit broadcastMessage(json);
}

void mainwindows::updateNTP(){
//    qDebug() << "updateSMTP";
//    QSettings *settings;
//    const QString cfgfile = FILESETTING;
//    qDebug() << "Loading configuration from:" << cfgfile;
//    if(QDir::isAbsolutePath(cfgfile))
//    {
//        settings = new QSettings(cfgfile,QSettings::IniFormat);
//        settings->setValue(QString("%1/IP_ADDRESS").arg(TIME_SERVER),networks->ip_timeserver);
//    }
//    else{
//        qDebug() << "Loading configuration from:" << cfgfile << " FILE NOT FOUND!";
//    }
//    qDebug() << "Loading configuration completed";
//    delete settings;
}

void mainwindows::showEvent(){
    if (isVNCViewerRunningWindows()) {
        qDebug() << "VNC Viewer is already running.";
    } else {
        qDebug() << "VNC Viewer not running. Starting it now...";
        QProcess::startDetached("C:\\Program Files\\RealVNC\\VNC Viewer\\vncviewer.exe");
    }
}

//extern QString getLocalIPAddress();

void mainwindows::captureScreenshotseand()
{

    qDebug() << "captureScreenshotseand()";
    const QString saveDir = "/var/www/html/pic";
    QDir().mkpath(saveDir);

    auto toJson = [](const QJsonObject &o){
        return QString::fromUtf8(QJsonDocument(o).toJson(QJsonDocument::Compact));
    };

    QScreen *screen = QGuiApplication::primaryScreen();
    if (!screen) {
        qDebug() << "screen()";

        cppCommand(toJson({
            {"objectName","ScreenPicture"},
            {"status","error"},
            {"error","no_screen"},
            {"action","recapture"},
            {"retryAfterMs", 500}
        }));
        return;
    }

    // ชื่อ/พาธไฟล์รอบนี้
    const QString fileName = QDateTime::currentDateTime()
                                 .toString("yyyyMMdd_HHmmss_zzz") + ".png";
    const QString filePath = QDir(saveDir).filePath(fileName);

    // helper: ลบไฟล์ (ถ้ามี) และแจ้ง QML ให้รีทราย
    auto fail = [&](const char* errKey){
        if (QFile::exists(filePath))
            QFile::remove(filePath);  // ลบทิ้งทันทีถ้าไฟล์เสีย/ค้าง
        qDebug() << "fail_screen()";

        cppCommand(toJson({
            {"objectName","ScreenPicture"},
            {"status","error"},
            {"error",  QString::fromLatin1(errKey)},
            {"action","recapture"},
            {"retryAfterMs", 500}
        }));
    };

    // 1) จับภาพ
    QPixmap px = screen->grabWindow(0);
    if (px.isNull() || px.width() == 0 || px.height() == 0) {
        fail("grab_failed");
        return;
    }

    {
        QSaveFile out(filePath);
        if (!out.open(QIODevice::WriteOnly)) { fail("open_failed"); return; }
        if (!px.save(&out, "PNG"))           { out.cancelWriting(); fail("encode_failed"); return; }
        if (!out.commit())                    { fail("commit_failed"); return; }
    }

    // 3) ตรวจความสมบูรณ์: อ่านกลับด้วย QImageReader (ไม่พึ่ง file size)
    {
        QImageReader reader(filePath);
        reader.setAutoDetectImageFormat(true);
        if (!reader.canRead() || reader.size().isEmpty()
            || reader.size().width() <= 0 || reader.size().height() <= 0) {
            fail("validate_failed");
            return;
        }
    }

    // 4) ปรับสิทธิ์/ซิงก์ตามระบบ (เปลี่ยน owner ได้ตามต้องการ)
    QProcess::execute("chown", {"-R", "pi:www-data", saveDir});
    QProcess::execute("sync");
    QThread::msleep(500);

    // 5) สำเร็จ → ส่งให้ “อีกคน” ทาง socket เท่านั้น
    const QString ip = getLocalIPAddress();
    sendMessage(toJson({
        {"objectName","ScreenPicture"},
        {"status","ok"},
        {"fileName", fileName},
        {"link", QString("http://%1/pic/%2").arg(ip, fileName)}
    }));
//    // ส่ง Pop-up: ALREADY CAPTURESCREEN
//    QJsonObject obj;
//    obj["objectName"] = "Pop-up";
//    obj["msg"] = "ALREADY CAPTURESCREEN";
//    cppCommand(QJsonDocument(obj).toJson(QJsonDocument::Compact));

//    // รอ 5 วินาทีแล้วส่ง Pop-up: DONE
//    QTimer::singleShot(5000, this, [=]() {
//        QJsonObject doneObj;
//        doneObj["objectName"] = "Pop-up";
//        doneObj["msg"] = "DONE";
//        cppCommand(QJsonDocument(doneObj).toJson(QJsonDocument::Compact));
//    });


}

//void mainwindows::captureScreenshotseand() {
//    QString savePath = "/var/www/html/pic/";

//    QScreen *screen = QGuiApplication::primaryScreen();
//    if (!screen) {
//        qDebug() << "❌ Failed to get primary screen";
//        return;
//    }

//    QString fileName = QString("%1.png").arg(QDateTime::currentDateTime().toSecsSinceEpoch());
//    QString filePath = QDir::cleanPath(savePath + fileName);

//    QPixmap screenshot = screen->grabWindow(0);

//    // ✅ ตรวจสอบว่ามีภาพจริงหรือเปล่า
//    if (screenshot.isNull() || screenshot.width() == 0 || screenshot.height() == 0) {
//        qWarning() << "❌ Screenshot failed (empty pixmap)";
//        return;
//    }

//    if (!screenshot.save(filePath)) {
//        qWarning() << "❌ Can't save file";
//        return;
//    }

//    qDebug() << "✅ Saved file to:" << filePath;

//    system("sudo chown -R pi:www-data /var/www/html/pic/*");
//    system("sync");
//    QThread::msleep(1000);

//    // ✅ ตรวจสอบว่ามีไฟล์และขนาด > 0 bytes
//    QString ip = getLocalIPAddress();
//    QString link = QString("http://%1/pic/%2").arg(ip, fileName);

//    QJsonObject Param;
//    Param.insert("objectName", "ScreenPicture");
//    Param.insert("fileName", fileName);
//    Param.insert("link", link);

//    QJsonDocument jsonDoc(Param);
//    QString jsonString = jsonDoc.toJson(QJsonDocument::Compact);

//    emit sendMessage(jsonString);
//    qDebug() << "📤 JSON Payload:" << jsonString;
//}

//void mainwindows::captureScreenshotseand(){

//    QString savePath = "/var/www/html/pic/";

//    QScreen *screen = QGuiApplication::primaryScreen();
//    if (!screen) {
//        qDebug() << "Failed to get primary screen";
//        return;
//    }

//    QString fileName = QString("%1.png").arg(QDateTime::currentDateTime().toSecsSinceEpoch());
//    QString filePath = QDir::cleanPath(savePath + fileName);

//    QPixmap screenshot = screen->grabWindow(0);
//    if (screenshot.save(filePath)) {
//        qDebug() << "Saved file to:" << filePath;
//        system("sudo chown -R pi:www-data /var/www/html/pic/*");
//        system("sync");
//        QThread::msleep(500);
//    } else {
//        qDebug() << "❌Can't save file";
//        return;
//    }

//    QString ip = getLocalIPAddress();
//    QString link = QString("http://%1/pic/%2").arg(ip, fileName);

//    QJsonObject Param;
//    Param.insert("objectName", "ScreenPicture");
//    Param.insert("fileName", fileName);
//    Param.insert("link", link);
//    system("sync");
//    QThread::msleep(500);
//    QJsonDocument jsonDoc(Param);
//    QString jsonString = jsonDoc.toJson(QJsonDocument::Compact);
//    QThread::msleep(500);
//    emit sendMessage(jsonString);
//    qDebug() << "JSON Payload:" << jsonString;
//}

void mainwindows::clearDiskStorage(){
    if(checkStatusCaptre){
        system("rm -rf /var/www/html/pic/*.png");
        checkStatusCaptre=false;
    }
}

void mainwindows::ServerCommand(QString qmlJson){
//    qDebug()<< "ServerCommand" << qmlJson;
    QJsonDocument d = QJsonDocument::fromJson(qmlJson.toUtf8());
    QJsonObject command = d.object();
    QString getCommand =  QJsonValue(command["objectName"]).toString();
    QString getCommand2 =  QJsonValue(command["menuID"]).toString();
    if(getCommand.contains("SwVersion")){
            isVersion = true;
            cppCommand(isVersion);
    }
}

void mainwindows::connectToPLC(){
    qDebug() << "------Open websocket to server------" << "userMode" << userMode << mainIP_address;
    QJsonDocument jsonDoc;
    QJsonObject Param;
    Param.insert("objectName","SwVersion");	             //Name
    Param.insert("SwVersion",SwVersion);	             //Name
    Param.insert("HwVersion",HwVersion);	             //Name
    Param.insert("ipaddress",mysql->iPaddressMonitor);	             //Name

    QTimer::singleShot(500, [=]() {
        qDebug() << "<<connectToPLC>>";
        mysql->getLocalMonitor();
        mysql->checkDatabaseAndUpdate();
        mysql->getDataRecordZoomValue();
        mysql->getDataMaxMin();
        mysql->initialCursorPosition();
//        mysql->getzoomValueRecord();
        mysql->getDataRecordZoomValue();
        mysql->GetStatusOfButtonHidding();


    });
//    if(selectVNCHW){
//    }else{
//    }
    #ifdef HwName
    //    selectVNCHW =false;
        Param.insert("HwName",HwName);	             //Name
    #else
    //    selectVNCHW =true;
        Param.insert("HwName",HwNameVNC);	             //Name
    #endif
    jsonDoc.setObject(Param);
    QString raw_data = QJsonDocument(Param).toJson(QJsonDocument::Compact).toStdString().c_str();
    QThread::msleep(300);
    qDebug() << "[raw_data]check:" << raw_data;
    cppCommand(raw_data);

    emit sendToSocket(raw_data);
//==========connect to Display============
   QTimer::singleShot(3000, [=]() {
       FileIPMonitor();        // ✅ อ่านค่า monitorIP
       startDisplayPeer();     // ✅ เริ่ม peer ตาม mode (นี่แหละที่คุณถามว่าเอาไปวางตรงไหน)

       // ส่ง event ไปอีกฝั่ง
       QJsonObject o;
       o["type"] = "display_connected";
       o["from"] = networks ? networks->userTypeSelect : userMode;
       o["ip"]   = mysql ? mysql->iPaddressMonitor : "";
       o["ts"]   = QDateTime::currentDateTime().toString(Qt::ISODate);
       o["needAck"] = true;

       sendDisplayJson(o);
   });
}

static bool parseDotTimeToMinutes(const QString &s, int &outMinutes)
{
    // รองรับ: "8.33" => 8:33, "8.5" => 8:50, "08.03" => 8:03
    QString t = s.trimmed();
    if (t.isEmpty()) return false;

    const QStringList parts = t.split('.', Qt::KeepEmptyParts);
    bool okH = false;
    int h = parts.value(0).toInt(&okH);
    if (!okH) return false;

    int m = 0;
    if (parts.size() >= 2) {
        QString mmStr = parts.value(1).trimmed();
        if (mmStr.isEmpty()) mmStr = "0";
        if (mmStr.size() == 1) mmStr += "0";      // "8.5" => "50"
        if (mmStr.size() > 2) mmStr = mmStr.left(2);

        bool okM = false;
        m = mmStr.toInt(&okM);
        if (!okM) m = 0;
    }

    // clamp
    if (h < 0) h = 0;
    if (h > 23) h = 23;
    if (m < 0) m = 0;
    if (m > 59) m = 59;

    outMinutes = h * 60 + m;
    return true;
}

static int shortestDiffMinutes(int aMin, int bMin)
{
    // diff = b - a ในช่วง [-720..+720] (ถ้าอยาก wrap ข้ามวัน)
    int d = bMin - aMin;
    while (d > 720)  d -= 1440;
    while (d < -720) d += 1440;
    return d;
}
static int timeDotToMin(const QString &s)
{
    // "8.45" -> 8:45 -> 525 นาที
    QString t = s.trimmed();
    if (t.isEmpty()) return -1;

    const QStringList parts = t.split(".");
    bool okH = false;
    int h = parts.value(0).toInt(&okH);
    if (!okH) return -1;

    int m = 0;
    if (parts.size() >= 2) {
        QString mm = parts.value(1).trimmed();
        // "8.5" => 8:50
        if (mm.size() == 1) mm += "0";
        bool okM = false;
        m = mm.toInt(&okM);
        if (!okM) m = 0;
    }
    if (h < 0) h = 0;
    if (h > 23) h = 23;
    if (m < 0) m = 0;
    if (m > 59) m = 59;

    return h * 60 + m;
}

void mainwindows::sendRequestDisplay()
{
    // PeriodicTime = ของเรา
    // recordPeriodic = ของอีกฝั่ง
    const QString localT  = PeriodicTime.trimmed();
    const QString remoteT = recordPeriodic.trimmed();

    if (localT.isEmpty() || remoteT.isEmpty()) {
        qWarning() << "[sendRequest] skip (empty time) local=" << localT << "remote=" << remoteT;
        return;
    }

    int localMin = 0, remoteMin = 0;
    if (!parseDotTimeToMinutes(localT, localMin) || !parseDotTimeToMinutes(remoteT, remoteMin)) {
        qWarning() << "[sendRequest] parse fail local=" << localT << "remote=" << remoteT;
        return;
    }

    // diffMin = remote - local
    const int diffMin = shortestDiffMinutes(localMin, remoteMin);
    const int absMin  = qAbs(diffMin);

    QString diffText;
    if (diffMin == 0) diffText = "same";
    else if (diffMin > 0) diffText = QString("+%1 min").arg(absMin);
    else diffText = QString("-%1 min").arg(absMin);

    QJsonObject req;
    req["objectName"] = "Periodicwarning";
    req["mode"] = userMode;
    req["PeriodicTime"] = localT;
    req["recordPeriodic"] = remoteT;
    req["timeDiffMin"] = diffMin;
    req["timeDiffAbsMin"] = absMin;
    req["timeDiffText"] = diffText;

    const QString msg = QString::fromUtf8(QJsonDocument(req).toJson(QJsonDocument::Compact));
    qDebug() << "[sendRequest] Periodicwarning TX:" << msg;

    cppCommand(msg);
}
void mainwindows::processData(const QString& jsonStr, QString phase, const QString& fileName) {
    QJsonDocument doc = QJsonDocument::fromJson(jsonStr.toUtf8());
    QJsonObject obj = doc.object();
    QJsonArray distanceArr = obj["distance"].toArray();
    QJsonArray voltageArr = obj["voltage"].toArray();

    int dataSize = distanceArr.size();
    QVector<double> distance, voltage;
    distance.reserve(dataSize);
    voltage.reserve(dataSize);

    for (int i = 0; i < dataSize; ++i) {
        distance.append(distanceArr[i].toDouble());
        voltage.append(voltageArr[i].toDouble());
    }

    if (phase == "A") {
        distanceA = std::move(distance);
        voltageA = std::move(voltage);
        isDataAReady = true;
    } else if (phase == "B") {
        distanceB = std::move(distance);
        voltageB = std::move(voltage);
        isDataBReady = true;
    } else if (phase == "C") {
        distanceC = std::move(distance);
        voltageC = std::move(voltage);
        isDataCReady = true;
    }
    fileNames = fileName;
    TimerPlotGraph->start(1000);
}
void mainwindows::findMinMaxValues() {
    if (distanceA.isEmpty() && distanceB.isEmpty() && distanceC.isEmpty()) {
        return;
    }

    std::vector<double> allDistances, allVoltages;
    int sizeA = distanceA.size();
    int sizeB = distanceB.size();
    int sizeC = distanceC.size();

    int validCount = 0;
    int totalSize = 0;

    if (!distanceA.isEmpty()) {
        allDistances.insert(allDistances.end(), distanceA.begin(), distanceA.end());
        allVoltages.insert(allVoltages.end(), voltageA.begin(), voltageA.end());
        totalSize += sizeA;
        ++validCount;
    }
    if (!distanceB.isEmpty()) {
        allDistances.insert(allDistances.end(), distanceB.begin(), distanceB.end());
        allVoltages.insert(allVoltages.end(), voltageB.begin(), voltageB.end());
        totalSize += sizeB;
        ++validCount;
    }
    if (!distanceC.isEmpty()) {
        allDistances.insert(allDistances.end(), distanceC.begin(), distanceC.end());
        allVoltages.insert(allVoltages.end(), voltageC.begin(), voltageC.end());
        totalSize += sizeC;
        ++validCount;
    }

    if (allDistances.empty() || allVoltages.empty() || validCount == 0) {
        return;
    }

    // ✅ คำนวณ baseline จากค่ามากที่สุด
    int baselineSize = std::max({sizeA, sizeB, sizeC});

    // ✅ เติมข้อมูลให้ชุดที่ขนาดไม่ถึง baselineSize
    auto padToSize = [](QVector<qreal>& dist, QVector<qreal>& volt, int targetSize) {
        int currentSize = dist.size();
        if (currentSize == 0) return;
        while (dist.size() < targetSize) {
            dist.append(dist.last());
            volt.append(volt.last());
        }
    };

    padToSize(distanceA, voltageA, baselineSize);
    padToSize(distanceB, voltageB, baselineSize);
    padToSize(distanceC, voltageC, baselineSize);

    // ✅ อัปเดตขนาดใหม่
    sizeA = distanceA.size();
    sizeB = distanceB.size();
    sizeC = distanceC.size();

    // ✅ หาค่าต่ำสุด/สูงสุด
    auto [minDist, maxDist] = std::minmax_element(allDistances.begin(), allDistances.end());
    auto [minVolt, maxVolt] = std::minmax_element(allVoltages.begin(), allVoltages.end());

    minDistance = *minDist;
    maxDistance = *maxDist;
    minVoltage = *minVolt;
    maxVoltage = *maxVolt;

//    QVariantList distA, voltA, distB, voltB, distC, voltC;
    pointsA.clear();
    pointsB.clear();
    pointsC.clear();

    for (int i = 0; i < baselineSize; ++i) {
        if (!distanceA.isEmpty() && i < sizeA) {
            x_A = (distanceA[i]);
            y_A = (voltageA[i]);
            QVector<QPointF> points;
            points.append(QPointF(x_A, y_A));
            pointsA.append(points);
            distA.append(x_A);
            voltA.append(y_A);
        }
        if (!distanceB.isEmpty() && i < sizeB) {
            qreal x = (distanceB[i]);
            qreal y = (voltageB[i]);
            QVector<QPointF> points;
            points.append(QPointF(x, y));
            pointsB.append(points);
            distB.append(x);
            voltB.append(y);
        }
        if (!distanceC.isEmpty() && i < sizeC) {
            qreal x = (distanceC[i]);
            qreal y = (voltageC[i]);
            QVector<QPointF> points;
            points.append(QPointF(x, y));
            pointsC.append(points);
            distC.append(x);
            voltC.append(y);
        }
    }
    static quint64 sendCount = 0;
    ++sendCount;
    // qDebug() << "dist_A:" << distanceA << distanceA.length() << "voltA:" << voltA << "distB:" << distanceB << "voltB:" << voltB << "distC:" << distanceC << "voltC:" << voltC;
    QJsonObject mainObject;
    mainObject.insert("objectName", "dataPloting");

    if (!distanceA.isEmpty()) {
        mainObject.insert("distanceA", QJsonArray::fromVariantList(distA));
        mainObject.insert("voltageA", QJsonArray::fromVariantList(voltA));
    }
    if (!distanceB.isEmpty()) {
        mainObject.insert("distanceB", QJsonArray::fromVariantList(distB));
        mainObject.insert("voltageB", QJsonArray::fromVariantList(voltB));
    }
    if (!distanceC.isEmpty()) {
        mainObject.insert("distanceC", QJsonArray::fromVariantList(distC));
        mainObject.insert("voltageC", QJsonArray::fromVariantList(voltC));
    }

    mainObject.insert("baselineSize", baselineSize);
    mainObject.insert("minDistance", minDistance);
    mainObject.insert("maxDistance", maxDistance);
    mainObject.insert("minVoltage", minVoltage);
    mainObject.insert("maxVoltage", maxVoltage);
    mainObject.insert("fileName", fileNames);
    qDebug() << "minDistance:" << minDistance << "maxDistance:" << maxDistance << "minVoltage:" << minVoltage << "maxVoltage:" <<maxVoltage;
    QJsonDocument jsonDoc(mainObject);
    cppCommand(jsonDoc.toJson(QJsonDocument::Compact));

    isDataAReady = !distanceA.isEmpty();
    isDataBReady = !distanceB.isEmpty();
    isDataCReady = !distanceC.isEmpty();

    TimerPlotGraph->stop();

    minDistance = *minDist;
    maxDistance = *maxDist;
    minVoltage = *minVolt;
    maxVoltage = *maxVolt;

    // qDebug() << "minDistance:" << minDistance << "maxDistance:" << maxDistance <<
    //             "minVoltage:" << minVoltage << "maxVoltage:" << maxVoltage <<
    //             "voltageOffset:" << voltageOffset << "maxVoltagePlusOffset:" << maxVoltagePlusOffset;
    qDebug() << "[Send #" << sendCount << "] data cleared; next send will start from empty containers.";
    QJsonObject mainMaxMinValue;
    mainMaxMinValue.insert("objectName", "updateMaxMin"); // หรือจะใช้ "saveMaxMinValue" ก็ได้ ถ้าฝั่ง C++ ไม่ได้เช็คชื่อนี้
    mainMaxMinValue.insert("id", 1);                      // ถ้าจะอัปเดตแถว ID=1 ชัดเจน
    mainMaxMinValue.insert("minDistance", minDistance);
    mainMaxMinValue.insert("maxDistance", maxDistance);
    mainMaxMinValue.insert("minVoltage",  minVoltage);
    mainMaxMinValue.insert("maxVoltage",  maxVoltage);
    mainMaxMinValue.insert("voltageOffset",  voltageOffset);
    mainMaxMinValue.insert("maxVoltagePlusOffset",  maxVoltage*voltageOffset);
    qDebug() << "Only_maxVoltagePlusOffset:" << maxVoltagePlusOffset << maxVoltage*voltageOffset;

    QJsonDocument jsonDocMaxMin(mainMaxMinValue);

    // เรียกให้ตรงชื่อฟังก์ชัน และส่งเป็น QString
    mysql->updateDataMaxMin(QString::fromUtf8(jsonDocMaxMin.toJson(QJsonDocument::Compact)));
    // หากฝั่งคุณตั้งชื่อเป็น updateDataMaxMin ให้เปลี่ยนเป็นชื่อนั้นแทน

    distA.clear();  voltA.clear();
    distB.clear();  voltB.clear();
    distC.clear();  voltC.clear();
    voltageA.clear();
    voltageB.clear();
    voltageC.clear();
    distanceA.clear();
    distanceB.clear();
    distanceC.clear();
}

void mainwindows::findVoltageValueTagging(const QString &msg) {
    // qDebug() << "findVoltageValueTagging received:" << msg;

    // 1) parse JSON
    QJsonDocument doc = QJsonDocument::fromJson(msg.toUtf8());
    if (!doc.isObject()) return;
    QJsonObject obj = doc.object();

    // อ่านค่าจาก JSON
    double requestedDistance = obj.value("Distance").toString().toDouble();
    int numList              = obj.value("num_list").toInt();
    QString detail           = obj.value("Detail").toString();
    QString phaseRequest     = obj.value("Phase").toString(); // ใช้กรองโฟส

    qDebug() << "→ Request Phase =" << phaseRequest
             << "requestedDistance =" << requestedDistance
             << "numList =" << numList
             << "Detail =" << detail;

    // เตรียมโครงสร้างข้อมูลของแต่ละโฟส
    struct PhaseConfig {
        QString             name;
        const QVector<qreal>* dist;
        const QVector<qreal>* volt;
    };
    QList<PhaseConfig> configs = {
        { "A", &distanceA, &voltageA },
        { "B", &distanceB, &voltageB },
        { "C", &distanceC, &voltageC }
    };

    // เตรียม Array สำหรับรวมผลลัพธ์
    QJsonArray results;

    // สำหรับแต่ละโฟสที่ตรงกับ phaseRequest
    for (const auto &cfg : configs) {
        if (cfg.name != phaseRequest)
            continue;  // ข้ามโฟสที่ไม่ตรงกับที่ request มา

        // ตรวจว่ามีข้อมูลหรือไม่
        if (cfg.dist->isEmpty() || cfg.volt->size() < cfg.dist->size()) {
            qWarning() << "No or incomplete data for phase" << cfg.name;
            continue;
        }

        // หาจุดที่ใกล้ที่สุด
        const QVector<qreal> &distList = *cfg.dist;
        const QVector<qreal> &voltList = *cfg.volt;
        int bestIndex = 0;
        double bestDiff = qAbs(distList[0] - requestedDistance);
        for (int i = 1; i < distList.size(); ++i) {
            double diff = qAbs(distList[i] - requestedDistance);
            if (diff < bestDiff) {
                bestDiff = diff;
                bestIndex = i;
            }
        }
        double closeDist = distList[bestIndex];
        double closeVolt = voltList[bestIndex];

        qDebug() << "→ Phase" << cfg.name
                 << "closestDist =" << closeDist
                 << "voltage =" << closeVolt;

        // สร้าง JSON object สำหรับโฟสนี้
        QJsonObject entry;
        entry["Phase"]             = cfg.name;
        entry["requestedDistance"] = requestedDistance;
        entry["closestDist"]       = closeDist;
        entry["voltage"]           = closeVolt;
        entry["num_list"]          = numList;
        entry["Detail"]            = detail;
        results.append(entry);
    }

    // 5) ส่ง Array กลับไป QML
    QJsonObject reply;
    reply["objectName"] = QStringLiteral("voltageTaggingResults");
    reply["results"]    = results;
    QJsonDocument outDoc(reply);
    cppCommand(outDoc.toJson(QJsonDocument::Compact));
}


void mainwindows::clearPhaseData(const QString& phase) {
    if (phase == "A") {
        distanceA.clear();
        voltageA.clear();
        isDataAReady = false;
    } else if (phase == "B") {
        distanceB.clear();
        voltageB.clear();
        isDataBReady = false;
    } else if (phase == "C") {
        distanceC.clear();
        voltageC.clear();
        isDataCReady = false;
    }
}

void mainwindows::processPatternData(const QString& jsonStr, QString phase, const QString& fileName) {
    QJsonDocument doc = QJsonDocument::fromJson(jsonStr.toUtf8());
    QJsonObject obj = doc.object();
    QJsonArray distanceArr = obj["distance"].toArray();
    QJsonArray voltageArr = obj["voltage"].toArray();
    // qDebug() << "distanceArr:" << distanceArr << "voltageArr:" << voltageArr;
    int dataSize = distanceArr.size();
    QVector<double> distance, voltage;
    distance.reserve(dataSize);
    voltage.reserve(dataSize);
    for (int i = 0; i < dataSize; ++i) {
        distance.append(distanceArr[i].toDouble());
        voltage.append(voltageArr[i].toDouble());
    }

    if (phase == "A") {
        patternDistanceA = std::move(distance);
        patternVoltageA = std::move(voltage);
        isPatternAReady = true;
    } else if (phase == "B") {
        patternDistanceB = std::move(distance);
        patternVoltageB = std::move(voltage);
        isPatternBReady = true;
    } else if (phase == "C") {
        patternDistanceC = std::move(distance);
        patternVoltageC = std::move(voltage);
        isPatternCReady = true;
    }
    if(fileName !=""){
        fileNamesPattern = fileName;
    }

    QJsonObject objfileName;
    obj.insert("objectName", "loadfilename");
    obj.insert("loadnewfilename", fileNamesPattern);
    qDebug() << "fileNamesPattern" << fileNamesPattern << fileName;
    QJsonDocument docfileName(obj);
    cppCommand(docfileName.toJson(QJsonDocument::Compact));

    qDebug() << "isPatternAReady:" << isPatternAReady << "isPatternBReady:" << isPatternBReady << "isPatternCReady:" << isPatternCReady;
    if(isPatternAReady && isPatternBReady && isPatternCReady){
        qDebug() << "isPatternAReady && isPatternBReady && isPatternCReady";
        TimerPlotPatternGraph->start(1000);
        isPatternAReady = false;
        isPatternBReady = false;
        isPatternCReady = false;
    }

}

//void mainwindows::findMinMaxPatternValues() {
//    qDebug() << "findMinMaxPatternValues_before:";

//    // 0) ล้าง buffer ที่จะส่งออกทุกครั้งก่อนเริ่มรอบใหม่
//    distPTA.clear();  voltPTA.clear();
//    distPTB.clear();  voltPTB.clear();
//    distPTC.clear();  voltPTC.clear();
//    pointsPA.clear(); pointsPB.clear(); pointsPC.clear();

//    qDebug() << "findMinMaxPatternValues:" << patternDistanceA << patternDistanceB << patternDistanceC;

//    int sizeA = patternDistanceA.size();
//    int sizeB = patternDistanceB.size();
//    int sizeC = patternDistanceC.size();

//    int baselineSize = std::max({sizeA, sizeB, sizeC});

//    // default เผื่อกรณีว่างทั้งหมด
//    double minDistance = 0.0;
//    double maxDistance = 0.0;
//    double minVoltage  = 0.0;
//    double maxVoltage  = 0.0;

//    if (baselineSize > 0) {
//        // 1) ทำให้ขนาดเริ่มต้นเท่ากัน (pad ด้วยค่าเดิมตัวสุดท้าย)
//        auto padToSize = [](QVector<qreal>& dist, QVector<qreal>& volt, int targetSize) {
//            if (dist.isEmpty() || volt.isEmpty()) return;
//            while (dist.size() < targetSize) {
//                dist.append(dist.last());
//                volt.append(volt.last());
//            }
//        };

//        padToSize(patternDistanceA, patternVoltageA, baselineSize);
//        padToSize(patternDistanceB, patternVoltageB, baselineSize);
//        padToSize(patternDistanceC, patternVoltageC, baselineSize);

//        // 2) ขยายจนถึง fulldistancesInit
//        const qreal fullX = fulldistancesInit;
//        auto extendToFullDistance = [fullX](QVector<qreal>& dist, QVector<qreal>& volt) {
//            if (dist.isEmpty() || volt.isEmpty()) return;

//            qreal lastD = dist.last();
//            qreal lastV = volt.last();

//            if (lastD >= fullX) return;

//            qreal step = 1.0;
//            if (dist.size() >= 2) {
//                step = dist.last() - dist[dist.size() - 2];
//                if (step <= 0.0 || step > 10.0) step = 1.0;
//            }

//            while (lastD + step <= fullX) {
//                lastD += step;
//                dist.append(lastD);
//                volt.append(lastV);
//            }
//            if (dist.last() < fullX) {
//                dist.append(fullX);
//                volt.append(lastV);
//            }
//        };

//        extendToFullDistance(patternDistanceA, patternVoltageA);
//        extendToFullDistance(patternDistanceB, patternVoltageB);
//        extendToFullDistance(patternDistanceC, patternVoltageC);

//        // 3) อัปเดตขนาดใหม่
//        sizeA = patternDistanceA.size();
//        sizeB = patternDistanceB.size();
//        sizeC = patternDistanceC.size();
//        baselineSize = std::max({sizeA, sizeB, sizeC});

//        distPTA.reserve(baselineSize);  voltPTA.reserve(baselineSize);
//        distPTB.reserve(baselineSize);  voltPTB.reserve(baselineSize);
//        distPTC.reserve(baselineSize);  voltPTC.reserve(baselineSize);

//        // 4) รวมไว้หาค่า min/max
//        std::vector<double> allDistances, allVoltages;
//        if (!patternDistanceA.isEmpty()) {
//            allDistances.insert(allDistances.end(), patternDistanceA.begin(), patternDistanceA.end());
//            allVoltages.insert(allVoltages.end(), patternVoltageA.begin(), patternVoltageA.end());
//        }
//        if (!patternDistanceB.isEmpty()) {
//            allDistances.insert(allDistances.end(), patternDistanceB.begin(), patternDistanceB.end());
//            allVoltages.insert(allVoltages.end(), patternVoltageB.begin(), patternVoltageB.end());
//        }
//        if (!patternDistanceC.isEmpty()) {
//            allDistances.insert(allDistances.end(), patternDistanceC.begin(), patternDistanceC.end());
//            allVoltages.insert(allVoltages.end(), patternVoltageC.begin(), patternVoltageC.end());
//        }

//        if (!allDistances.empty() && !allVoltages.empty()) {
//            auto [minDist, maxDist] = std::minmax_element(allDistances.begin(), allDistances.end());
//            auto [minVolt, maxVolt] = std::minmax_element(allVoltages.begin(), allVoltages.end());
//            minDistance = *minDist;
//            maxDistance = *maxDist;
//            minVoltage  = *minVolt;
//            maxVoltage  = *maxVolt;
//        }

//        // 5) เติมลงโครงสร้างส่งออก
//        for (int i = 0; i < baselineSize; ++i) {
//            if (i < patternDistanceA.size()) {
//                qreal x = patternDistanceA[i], y = patternVoltageA[i];
//                pointsPA.append(QVector<QPointF>() << QPointF(x, y));
//                distPTA.append(x);
//                voltPTA.append(y);
//            }
//            if (i < patternDistanceB.size()) {
//                qreal x = patternDistanceB[i], y = patternVoltageB[i];
//                pointsPB.append(QVector<QPointF>() << QPointF(x, y));
//                distPTB.append(x);
//                voltPTB.append(y);
//            }
//            if (i < patternDistanceC.size()) {
//                qreal x = patternDistanceC[i], y = patternVoltageC[i];
//                pointsPC.append(QVector<QPointF>() << QPointF(x, y));
//                distPTC.append(x);
//                voltPTC.append(y);
//            }
//        }
//    }

//    // 6) ส่งให้หน้า QML เสมอ แม้จะว่าง
//    QJsonObject obj;
//    obj.insert("objectName", "patternData");

//    obj.insert("distancePatternA", QJsonArray::fromVariantList(distPTA));
//    obj.insert("voltagePatternA",  QJsonArray::fromVariantList(voltPTA));
//    obj.insert("distancePatternB", QJsonArray::fromVariantList(distPTB));
//    obj.insert("voltagePatternB",  QJsonArray::fromVariantList(voltPTB));
//    obj.insert("distancePatternC", QJsonArray::fromVariantList(distPTC));
//    obj.insert("voltagePatternC",  QJsonArray::fromVariantList(voltPTC));

//    obj.insert("baselineSize", baselineSize);
//    obj.insert("minDistance",  minDistance);
//    obj.insert("maxDistance",  maxDistance);
//    obj.insert("minVoltage",   minVoltage);
//    obj.insert("maxVoltage",   maxVoltage);
//    const QString safeFileName = fileNames.trimmed();

//    if (safeFileName.compare("noname", Qt::CaseInsensitive) == 0) {
//        obj.insert("fileName", "");
//    } else if (!safeFileName.isEmpty()) {
//        obj.insert("fileName", safeFileName);
//    }

//    qDebug() << "baselineSize:" << baselineSize
//             << "minDistance:" << minDistance
//             << "maxDistance:" << maxDistance
//             << "minVoltage:"  << minVoltage
//             << "maxVoltage:"  << maxVoltage
//             << "fileNames:"   << fileNames;

//    QJsonDocument doc(obj);
//    cppCommand(doc.toJson(QJsonDocument::Compact));

//    isPatternAReady = !patternDistanceA.isEmpty();
//    isPatternBReady = !patternDistanceB.isEmpty();
//    isPatternCReady = !patternDistanceC.isEmpty();

//    TimerPlotPatternGraph->stop();
//}



void mainwindows::findMinMaxPatternValues() {
    qDebug() << "findMinMaxPatternValues_before:";
    if (patternDistanceA.isEmpty() && patternDistanceB.isEmpty() && patternDistanceC.isEmpty()) {
        return;
    }

    // 0) ล้าง buffer ที่จะส่งออกทุกครั้งก่อนเริ่มรอบใหม่
    distPTA.clear();  voltPTA.clear();
    distPTB.clear();  voltPTB.clear();
    distPTC.clear();  voltPTC.clear();
    pointsPA.clear(); pointsPB.clear(); pointsPC.clear();

    qDebug() << "findMinMaxPatternValues:" << patternDistanceA << patternDistanceB << patternDistanceC;

    int sizeA = patternDistanceA.size();
    int sizeB = patternDistanceB.size();
    int sizeC = patternDistanceC.size();

    // 1) ทำให้ขนาดเริ่มต้นเท่ากัน (pad ด้วยค่าเดิมตัวสุดท้าย)
    int baselineSize = std::max({sizeA, sizeB, sizeC});
    auto padToSize = [](QVector<qreal>& dist, QVector<qreal>& volt, int targetSize) {
        if (dist.isEmpty() || volt.isEmpty()) return;
        while (dist.size() < targetSize) {
            dist.append(dist.last());
            volt.append(volt.last());
        }
    };
    padToSize(patternDistanceA, patternVoltageA, baselineSize);
    padToSize(patternDistanceB, patternVoltageB, baselineSize);
    padToSize(patternDistanceC, patternVoltageC, baselineSize);

    // 2) ขยายจนถึง fulldistancesInit (ระยะที่ต้องการโชว์เต็มหน้าจอ)
    const qreal fullX = fulldistancesInit;   // km (ประกาศแล้วใน header)
    auto extendToFullDistance = [fullX](QVector<qreal>& dist, QVector<qreal>& volt) {
        if (dist.isEmpty() || volt.isEmpty()) return;

        qreal lastD = dist.last();
        qreal lastV = volt.last();

        if (lastD >= fullX) return;

        // ก้าวระยะ (พยายามใช้ก้าวจริง ถ้าแปลกให้ fallback = 1km)
        qreal step = 1.0;
        if (dist.size() >= 2) {
            step = dist.last() - dist[dist.size() - 2];
            if (step <= 0.0 || step > 10.0) step = 1.0;
        }

        while (lastD + step <= fullX) {
            lastD += step;
            dist.append(lastD);
            volt.append(lastV); // คงค่าโวลต์ตัวสุดท้าย
        }
        if (dist.last() < fullX) {           // ปิดท้ายให้ชน fullX พอดี
            dist.append(fullX);
            volt.append(lastV);
        }
    };
    extendToFullDistance(patternDistanceA, patternVoltageA);
    extendToFullDistance(patternDistanceB, patternVoltageB);
    extendToFullDistance(patternDistanceC, patternVoltageC);

    // 3) อัปเดตขนาดใหม่
    sizeA = patternDistanceA.size();
    sizeB = patternDistanceB.size();
    sizeC = patternDistanceC.size();
    baselineSize = std::max({sizeA, sizeB, sizeC});

    // เตรียม capacity ให้ QList/QVariantList ที่จะส่งออก (ช่วยลด realloc)
    distPTA.reserve(baselineSize);  voltPTA.reserve(baselineSize);
    distPTB.reserve(baselineSize);  voltPTB.reserve(baselineSize);
    distPTC.reserve(baselineSize);  voltPTC.reserve(baselineSize);

    // 4) รวมไว้หาค่า min/max
    std::vector<double> allDistances, allVoltages;
    if (!patternDistanceA.isEmpty()) {
        allDistances.insert(allDistances.end(), patternDistanceA.begin(), patternDistanceA.end());
        allVoltages.insert(allVoltages.end(), patternVoltageA.begin(), patternVoltageA.end());
    }
    if (!patternDistanceB.isEmpty()) {
        allDistances.insert(allDistances.end(), patternDistanceB.begin(), patternDistanceB.end());
        allVoltages.insert(allVoltages.end(), patternVoltageB.begin(), patternVoltageB.end());
    }
    if (!patternDistanceC.isEmpty()) {
        allDistances.insert(allDistances.end(), patternDistanceC.begin(), patternDistanceC.end());
        allVoltages.insert(allVoltages.end(), patternVoltageC.begin(), patternVoltageC.end());
    }
    if (allDistances.empty() || allVoltages.empty()) return;

    auto [minDist, maxDist] = std::minmax_element(allDistances.begin(), allDistances.end());
    auto [minVolt, maxVolt] = std::minmax_element(allVoltages.begin(), allVoltages.end());
    double minDistance = *minDist;
    double maxDistance = *maxDist;
    double minVoltage  = *minVolt;
    double maxVoltage  = *maxVolt;

    // 5) เติมลงโครงสร้างส่งออก
    for (int i = 0; i < baselineSize; ++i) {
        if (i < patternDistanceA.size()) {
            qreal x = patternDistanceA[i], y = patternVoltageA[i];
            pointsPA.append(QVector<QPointF>() << QPointF(x, y));
            distPTA.append(x);  voltPTA.append(y);
        }
        if (i < patternDistanceB.size()) {
            qreal x = patternDistanceB[i], y = patternVoltageB[i];
            pointsPB.append(QVector<QPointF>() << QPointF(x, y));
            distPTB.append(x);  voltPTB.append(y);
        }
        if (i < patternDistanceC.size()) {
            qreal x = patternDistanceC[i], y = patternVoltageC[i];
            pointsPC.append(QVector<QPointF>() << QPointF(x, y));
            distPTC.append(x);  voltPTC.append(y);
        }
    }

    // 6) ส่งให้หน้า QML
    QJsonObject obj;
    obj.insert("objectName", "patternData");
    if (!patternDistanceA.isEmpty()) {
        obj.insert("distancePatternA", QJsonArray::fromVariantList(distPTA));
        obj.insert("voltagePatternA",  QJsonArray::fromVariantList(voltPTA));
    }
    if (!patternDistanceB.isEmpty()) {
        obj.insert("distancePatternB", QJsonArray::fromVariantList(distPTB));
        obj.insert("voltagePatternB",  QJsonArray::fromVariantList(voltPTB));
    }
    if (!patternDistanceC.isEmpty()) {
        obj.insert("distancePatternC", QJsonArray::fromVariantList(distPTC));
        obj.insert("voltagePatternC",  QJsonArray::fromVariantList(voltPTC));
    }
    obj.insert("baselineSize", baselineSize);
    obj.insert("minDistance",  minDistance);
    obj.insert("maxDistance",  maxDistance);
    obj.insert("minVoltage",   minVoltage);
    obj.insert("maxVoltage",   maxVoltage);
    obj.insert("fileNamesPattern",     fileNamesPattern);

    qDebug() << "baselineSize:" << baselineSize
             << "minDistance:" << minDistance
             << "maxDistance:" << maxDistance
             << "minVoltage:"  << minVoltage
             << "fileNames:"  << fileNamesPattern
             << "maxVoltage:"  << maxVoltage;

    QJsonDocument doc(obj);
    cppCommand(doc.toJson(QJsonDocument::Compact));

    isPatternAReady = !patternDistanceA.isEmpty();
    isPatternBReady = !patternDistanceB.isEmpty();
    isPatternCReady = !patternDistanceC.isEmpty();

    TimerPlotPatternGraph->stop();
}

void mainwindows::appendVectorToJsonArray(QJsonArray& jsonArray, const QVector<double>& vec) {
    for (double value : vec) {
        jsonArray.append(QJsonValue(value));
    }
}

void mainwindows::processSurge(const QString& jsonStr, QString phase, const QString& fileName) {
    QJsonDocument doc = QJsonDocument::fromJson(jsonStr.toUtf8());
    QJsonObject obj = doc.object();
    QJsonArray distanceArr = obj["distance"].toArray();
    QJsonArray voltageArr = obj["voltage"].toArray();

    int dataSize = distanceArr.size();
    QVector<double> distance, voltage;
    distance.reserve(dataSize);
    voltage.reserve(dataSize);

    for (int i = 0; i < dataSize; ++i) {
        distance.append(distanceArr[i].toDouble());
        voltage.append(voltageArr[i].toDouble());
    }

    if (phase == "A") {
        distanceA = std::move(distance);
        voltageA = std::move(voltage);
        isDataAReady = true;
    } else if (phase == "B") {
        distanceB = std::move(distance);
        voltageB = std::move(voltage);
        isDataBReady = true;
    } else if (phase == "C") {
        distanceC = std::move(distance);
        voltageC = std::move(voltage);
        isDataCReady = true;
    }
    fileNames = fileName;
    TimerPlotSurgeGraph->start(1000);
}

void mainwindows::findMinMaxSurgeValues() {
    qDebug() << "findMinMaxSurgeValues:";
    if (distanceA.isEmpty() && distanceB.isEmpty() && distanceC.isEmpty())
        return;

    std::vector<double> allDistances, allVoltages;
    int sizeA = distanceA.size();
    int sizeB = distanceB.size();
    int sizeC = distanceC.size();

    int baselineSize = std::max({sizeA, sizeB, sizeC});

    auto padToSize = [](QVector<qreal>& dist, QVector<qreal>& volt, int targetSize) {
        if (dist.isEmpty()) return;
        while (dist.size() < targetSize) {
            dist.append(dist.last());
            volt.append(volt.last());
        }
    };

    padToSize(distanceA, voltageA, baselineSize);
    padToSize(distanceB, voltageB, baselineSize);
    padToSize(distanceC, voltageC, baselineSize);

    if (!distanceA.isEmpty()) {
        allDistances.insert(allDistances.end(), distanceA.begin(), distanceA.end());
        allVoltages.insert(allVoltages.end(), voltageA.begin(), voltageA.end());
    }
    if (!distanceB.isEmpty()) {
        allDistances.insert(allDistances.end(), distanceB.begin(), distanceB.end());
        allVoltages.insert(allVoltages.end(), voltageB.begin(), voltageB.end());
    }
    if (!distanceC.isEmpty()) {
        allDistances.insert(allDistances.end(), distanceC.begin(), distanceC.end());
        allVoltages.insert(allVoltages.end(), voltageC.begin(), voltageC.end());
    }

    if (allDistances.empty() || allVoltages.empty())
        return;

    // ✅ หาค่าต่ำสุดและสูงสุด
    auto [minDist, maxDist] = std::minmax_element(allDistances.begin(), allDistances.end());
    auto [minVolt, maxVolt] = std::minmax_element(allVoltages.begin(), allVoltages.end());
    minDistance = *minDist;
    maxDistance = *maxDist;
    minVoltage = *minVolt;
    maxVoltage = *maxVolt;

    QJsonObject mainObject;
    mainObject.insert("objectName", "dataSurge");
    mainObject.insert("baselineSize", baselineSize);
    mainObject.insert("minDistance", minDistance);
    mainObject.insert("maxDistance", maxDistance);
    mainObject.insert("minVoltage", minVoltage);
    mainObject.insert("maxVoltage", maxVoltage);
    mainObject.insert("fileName", fileNames);

    QVariantList distA, voltA, distB, voltB, distC, voltC;
    pointsA.clear(); pointsB.clear(); pointsC.clear();

    for (int i = 0; i < baselineSize; ++i) {
        if (!distanceA.isEmpty()) {
            distA.append(distanceA[i]);
            voltA.append(voltageA[i]);
            pointsA.append({ QPointF(distanceA[i], voltageA[i]) });
        }
        if (!distanceB.isEmpty()) {
            distB.append(distanceB[i]);
            voltB.append(voltageB[i]);
            pointsB.append({ QPointF(distanceB[i], voltageB[i]) });
        }
        if (!distanceC.isEmpty()) {
            distC.append(distanceC[i]);
            voltC.append(voltageC[i]);
            pointsC.append({ QPointF(distanceC[i], voltageC[i]) });
        }
    }

    if (!distA.isEmpty()) {
        mainObject.insert("distanceA", QJsonArray::fromVariantList(distA));
        mainObject.insert("voltageA", QJsonArray::fromVariantList(voltA));
    }
    if (!distB.isEmpty()) {
        mainObject.insert("distanceB", QJsonArray::fromVariantList(distB));
        mainObject.insert("voltageB", QJsonArray::fromVariantList(voltB));
    }
    if (!distC.isEmpty()) {
        mainObject.insert("distanceC", QJsonArray::fromVariantList(distC));
        mainObject.insert("voltageC", QJsonArray::fromVariantList(voltC));
    }

    mainObject.insert("isDataAReady", !distanceA.isEmpty());
    mainObject.insert("isDataBReady", !distanceB.isEmpty());
    mainObject.insert("isDataCReady", !distanceC.isEmpty());

    QJsonDocument jsonDoc(mainObject);
    cppCommand(jsonDoc.toJson(QJsonDocument::Compact));

    QJsonObject mainMaxMinValue;
    mainMaxMinValue.insert("objectName", "updateMaxMin");
    mainMaxMinValue.insert("id", 1);
    mainMaxMinValue.insert("minDistance", minDistance);
    mainMaxMinValue.insert("maxDistance", maxDistance);
    mainMaxMinValue.insert("minVoltage",  minVoltage);
    mainMaxMinValue.insert("maxVoltage",  maxVoltage);
    mainMaxMinValue.insert("voltageOffset",  voltageOffset);
    mainMaxMinValue.insert("maxVoltagePlusOffset",  maxVoltage * voltageOffset);
    QJsonDocument jsonDocMaxMin(mainMaxMinValue);
    mysql->updateDataMaxMin(QString::fromUtf8(jsonDocMaxMin.toJson(QJsonDocument::Compact)));

    // ✅ เคลียร์ข้อมูลหลังส่ง
    distA.clear(); voltA.clear(); distanceA.clear(); voltageA.clear();
    distB.clear(); voltB.clear(); distanceB.clear(); voltageB.clear();
    distC.clear(); voltC.clear(); distanceC.clear(); voltageC.clear();
}


void mainwindows::calculate(QString msg) {
    qDebug() << "calculate:" << msg;
    QJsonDocument d = QJsonDocument::fromJson(msg.toUtf8());
    QJsonObject command = d.object();
    QString getCommand = QJsonValue(command["objectName"]).toString();

    // เก็บค่าก่อนหน้า
    double prevSagFactor = sagFactor;
    double prevSamplingRate = samplingRate;
    double prevDistanceToStart = distanceToStart;
    double prevDistanceToShow = distanceToShow;
    double prevFulldistance = fulldistance;
    double prevThresholdA = thresholdA;
    double prevThresholdB = thresholdB;
    double prevThresholdC = thresholdC;

    // อัปเดตค่าจาก JSON ถ้ามี
    if (command.contains("sagFactorInit")) sagFactor = command.value("sagFactorInit").toDouble();
    if (command.contains("samplingRateInit")) samplingRate = command.value("samplingRateInit").toDouble();
    if (command.contains("distanceToStartInit")) distanceToStart = command.value("distanceToStartInit").toDouble();
    if (command.contains("distanceToShowInit")) distanceToShow = command.value("distanceToShowInit").toDouble();
    if (command.contains("fulldistancesInit")) fulldistance = command.value("fulldistancesInit").toDouble();
    if (command.contains("thresholdInitA")) thresholdA = command.value("thresholdInitA").toDouble();
    if (command.contains("thresholdInitB")) thresholdB = command.value("thresholdInitB").toDouble();
    if (command.contains("thresholdInitC")) thresholdC = command.value("thresholdInitC").toDouble();

    // ตรวจสอบค่าที่เปลี่ยนแปลง (Threshold)
    bool isThresholdAChanged = (prevThresholdA != thresholdA);
    bool isThresholdBChanged = (prevThresholdB != thresholdB);
    bool isThresholdCChanged = (prevThresholdC != thresholdC);

    // ตรวจสอบค่าที่เปลี่ยนแปลง (Parameter หลัก)
    bool isSagFactorChanged = (prevSagFactor != sagFactor);
    bool isSamplingRateChanged = (prevSamplingRate != samplingRate);
    bool isDistanceToStartChanged = (prevDistanceToStart != distanceToStart);
    bool isDistanceToShowChanged = (prevDistanceToShow != distanceToShow);
    bool isFulldistanceChanged = (prevFulldistance != fulldistance);

    // ตรวจสอบว่ามีการเปลี่ยนแปลงของ Threshold หรือพารามิเตอร์หลัก
    bool isAnyThresholdChanged = isThresholdAChanged || isThresholdBChanged || isThresholdCChanged;
    bool isAnyParameterChanged = isSagFactorChanged || isSamplingRateChanged ||
                                 isDistanceToStartChanged || isDistanceToShowChanged ||
                                 isFulldistanceChanged;

    // ตรวจสอบค่าที่เป็น NaN หรือ Infinity
    bool isValid = true;
    if (std::isnan(sagFactor) || std::isinf(sagFactor)) isValid = false;
    if (std::isnan(samplingRate) || std::isinf(samplingRate)) isValid = false;
    if (std::isnan(distanceToStart) || std::isinf(distanceToStart)) isValid = false;
    if (std::isnan(distanceToShow) || std::isinf(distanceToShow)) isValid = false;
    if (std::isnan(fulldistance) || std::isinf(fulldistance)) isValid = false;
    if (std::isnan(thresholdA) || std::isinf(thresholdA)) isValid = false;
    if (std::isnan(thresholdB) || std::isinf(thresholdB)) isValid = false;
    if (std::isnan(thresholdC) || std::isinf(thresholdC)) isValid = false;

    // **เช็คว่าอย่างน้อยมีการเปลี่ยนแปลงบางอย่าง**
    if (isValid && (isAnyThresholdChanged || isAnyParameterChanged)) {
        qDebug() << "Debug parameter (Valid and Changed):"
                 << sagFactor << samplingRate << distanceToStart << distanceToShow
                 << fulldistance << thresholdA << thresholdB << thresholdC;

        // ✅ **กรณีที่ Threshold หรือ Parameter เปลี่ยนแปลง**
        if ((isThresholdAChanged || isAnyParameterChanged) && thresholdA > 0) {
            qDebug() << "Threshold A triggered.";
//            plotGraphA(sagFactor, samplingRate, distanceToStart, distanceToShow, fulldistance, thresholdA);
            // plotPatternA(sagFactor, samplingRate, distanceToStart, distanceToShow, fulldistance, thresholdA);
        }
        if ((isThresholdBChanged || isAnyParameterChanged) && thresholdB > 0) {
            qDebug() << "Threshold B triggered.";
//            plotGraphB(sagFactor, samplingRate, distanceToStart, distanceToShow, fulldistance, thresholdB);
//            plotPatternB(sagFactor, samplingRate, distanceToStart, distanceToShow, fulldistance, thresholdB);
        }
        if ((isThresholdCChanged || isAnyParameterChanged) && thresholdC > 0) {
            qDebug() << "Threshold C triggered.";
//            plotGraphC(sagFactor, samplingRate, distanceToStart, distanceToShow, fulldistance, thresholdC);
//            plotPatternC(sagFactor, samplingRate, distanceToStart, distanceToShow, fulldistance, thresholdC);
        }

    } else {
        qDebug() << "Debug parameter (Invalid or Unchanged):"
                 << sagFactor << samplingRate << distanceToStart << distanceToShow
                 << fulldistance << thresholdA << thresholdB << thresholdC;
    }
}

void mainwindows::plotGraphA(double sagFactorInit, double samplingRateInit, double distanceToStartInit,
                            double distanceToShowInit, double fulldistance, double thresholdInitA) {
    qDebug() << "Debug plotGraphA:" << sagFactorInit << samplingRateInit << distanceToStartInit
             << distanceToShowInit << fulldistance << thresholdInitA;

    QString filePath = "/home/pi/data1.raw";
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
        uint16_t rawValue = static_cast<uint16_t>((static_cast<uint8_t>(ptr[1]) << 8) | static_cast<uint8_t>(ptr[0]));
        float normalizedValue = static_cast<float>(rawValue) / 32768.0f;
        if (rawValue == 0xE000 || normalizedValue < 0) {
            normalizedValue = 0.0f;
        }

        normalizedValues.push_back(normalizedValue);
        ptr += 2;
    }

    const float threshold = thresholdInitA / 32768.0f;
    auto startIt = std::find_if(normalizedValues.begin(), normalizedValues.end(), [threshold](float val) {
        return val >= threshold;
    });

    if (startIt == normalizedValues.end()) {
        qDebug() << "Threshold value not found in data.";
        return;
    }
    int startIndex = std::distance(normalizedValues.begin(), startIt);

    int resampling = samplingRateInit / (60 * sagFactorInit);
    float totalDistance = (distanceToShowInit - distanceToStartInit) * 1000;
    int fullpoint = static_cast<int>(totalDistance / (60 * sagFactorInit));
    int trueDistancepoint = fullpoint / resampling;

    float pointInterval = totalDistance / trueDistancepoint;

    std::vector<std::pair<float, float>> result;
    float currentDistance = distanceToStartInit * 1000;

    for (int i = 0; i < trueDistancepoint; ++i) {
        float currentValue = (i * resampling + startIndex < normalizedValues.size())
                             ? normalizedValues[i * resampling + startIndex] * 4096 / 2
                             : 0.0f;
        result.emplace_back(currentDistance, currentValue);
        currentDistance += pointInterval;
    }

    qDebug() << "Final Total Points:" << result.size();

    QJsonObject mainObject;
    QJsonArray dist, volt;
    for (const auto& [distance, voltage] : result) {
        dist.push_back(distance / 1000);
        volt.push_back(voltage);
    }

    mainObject.insert("objectName", "dataPlotingA");
    mainObject.insert("distance", dist);
    mainObject.insert("voltage", volt);

    QJsonDocument jsonDoc(mainObject);
    QString raw_data = jsonDoc.toJson(QJsonDocument::Compact);

    rawdataArrayA = raw_data;
    reSamplingNormalizationA(result);

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
//    qDebug() << "Starting index found at position:" << startIndex;

    int resampling = samplingRateInit / (60 * sagFactorInit); // Resampling rate
//    qDebug() << "Resampling rate:" << resampling;

    float totalDistance = (distanceToShowInit - distanceToStartInit) * 1000;
    int fullpoint = static_cast<int>(totalDistance / (60 * sagFactorInit));
    int trueDistancepoint = fullpoint / resampling; // Points after resampling

//    qDebug() << "Full points:" << fullpoint;
//    qDebug() << "True distance points after resampling:" << trueDistancepoint;

    float pointInterval = totalDistance / trueDistancepoint; // Distance interval per point
//    qDebug() << "Point interval (m):" << pointInterval;

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
//        qDebug() << "X:" << distance / 1000.0 << " km, Y:" << voltage << " mV";
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
//    qDebug() << "Generated JSON:" << raw_data;

    rawdataArrayA = raw_data;
//    emit plotingDataPhaseB(raw_data); reSamplingNormalizationB
    reSamplingNormalizationB(result);
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

//    qDebug() << "Total samples read: " << normalizedValues.size();

    const float threshold = thresholdInitC / 32768.0f;  // Convert to mV
    auto startIt = std::find_if(normalizedValues.begin(), normalizedValues.end(), [threshold](float val) {
        return val >= threshold;
    });

    if (startIt == normalizedValues.end()) {
        qDebug() << "Threshold value not found in data.";
        return;
    }
    int startIndex = std::distance(normalizedValues.begin(), startIt);
//    qDebug() << "Starting index found at position:" << startIndex;

    int resampling = samplingRateInit / (60 * sagFactorInit);
//    qDebug() << "Resampling rate:" << resampling;

    float totalDistance = (distanceToShowInit - distanceToStartInit) * 1000;
    int fullpoint = static_cast<int>(totalDistance / (60 * sagFactorInit));
    int trueDistancepoint = fullpoint / resampling; // Points after resampling

//    qDebug() << "Full points:" << fullpoint;
//    qDebug() << "True distance points after resampling:" << trueDistancepoint;

    float pointInterval = totalDistance / trueDistancepoint;
//    qDebug() << "Point interval (m):" << pointInterval;

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
//        qDebug() << "X:" << distance / 1000.0 << " km, Y:" << voltage << " mV";
    }

    // JSON Output for Plotting
    QJsonObject mainObject;
    QJsonArray dist, volt;
    for (const auto& [distance, voltage] : result) {
        dist.push_back(distance / 1000);  // Convert m to km
        volt.push_back(voltage);  // Already multiplied by 4096
    }

    mainObject.insert("objectName", "dataPlotingC");
    mainObject.insert("distance", dist);
    mainObject.insert("voltage", volt);

    QJsonDocument jsonDoc(mainObject);
    QString raw_data = jsonDoc.toJson(QJsonDocument::Compact);
//    qDebug() << "Generated JSON C:" << raw_data;

    rawdataArrayC = raw_data;
//    emit plotingDataPhaseB(raw_data); reSamplingNormalizationC
    reSamplingNormalizationC(result);
}

void mainwindows::reSamplingNormalizationA(const std::vector<std::pair<float, float>>& result) {
    if (result.size() < 3) {
        qDebug() << "Not enough data points to process.";
        return;
    }
    qDebug() << "Starting peak detection and smoothing...";
    std::vector<std::pair<float, double>> peakPoints;
    std::pair<float, double> startPoint = {0.0, 0.0};

    for (const auto& point : result) {
        if (point.second > 0.0) { // First non-zero voltage
            startPoint = {point.first, point.second};
            break;
        }
    }
    peakPoints.push_back(startPoint);

    for (size_t i = 1; i < result.size() - 1; ++i) {
        float prevVoltage = result[i - 1].second;
        float currentVoltage = result[i].second;
        float nextVoltage = result[i + 1].second;

        if (prevVoltage < currentVoltage && currentVoltage > nextVoltage) {
            peakPoints.emplace_back(result[i]);
        }
    }

    peakPoints.push_back(result.back());

    auto maxPeakIt = std::max_element(peakPoints.begin(), peakPoints.end(),
                                      [](const std::pair<float, double>& a, const std::pair<float, double>& b) {
                                          return a.second < b.second;
                                      });
    std::pair<float, double> maxPeak = *maxPeakIt;
//    qDebug() << "Maximum peak detected at X:" << maxPeak.first / 1000.0 << "km, Y:" << maxPeak.second << "mV";

    if (std::find(peakPoints.begin(), peakPoints.end(), maxPeak) == peakPoints.end()) {
        peakPoints.push_back(maxPeak);
    }

    qDebug() << "Peaks detected. Total peaks:" << peakPoints.size();

    for (const auto& peak : peakPoints) {
//        qDebug() << "Peak at X:" << peak.first / 1000.0 << "km, Y:" << peak.second << "mV";
    }

    std::vector<std::pair<float, double>> downsampledPeaks;
    size_t step = std::max<size_t>(1, peakPoints.size() / 50); // Downsample to around 50 points
    for (size_t i = 0; i < peakPoints.size(); i += step) {
        downsampledPeaks.push_back(peakPoints[i]);
    }
    if (peakPoints.back() != downsampledPeaks.back()) {
        downsampledPeaks.push_back(peakPoints.back()); // Ensure the last point is included
    }

    if (std::find(downsampledPeaks.begin(), downsampledPeaks.end(), maxPeak) == downsampledPeaks.end()) {
        downsampledPeaks.push_back(maxPeak);
    }

    std::sort(downsampledPeaks.begin(), downsampledPeaks.end()); // Sort points by X
//    qDebug() << "Downsampling completed. Total downsampled points:" << downsampledPeaks.size();

    std::vector<std::pair<float, double>> smoothCurve;
    for (size_t i = 0; i < downsampledPeaks.size() - 1; ++i) {
        float x1 = downsampledPeaks[i].first;
        float x2 = downsampledPeaks[i + 1].first;
        double y1 = downsampledPeaks[i].second;
        double y2 = downsampledPeaks[i + 1].second;

        for (float x = x1; x <= x2; x += (x2 - x1) / 10.0) { // Add 10 points per segment
            double t = (x - x1) / (x2 - x1); // Normalize x between 0 and 1
            double y = (1 - t) * y1 + t * y2; // Linear interpolation
            smoothCurve.emplace_back(x, y);
        }
    }

    qDebug() << "Smoothing completed. Total points for the curve:" << smoothCurve.size();

    QJsonObject mainObject;
    QJsonArray dist, volt;
    for (const auto& point : smoothCurve) {
        QVariantMap pointxy;
        dist.push_back(point.first / 1000.0);
        volt.push_back(point.second);
    }
    mainObject.insert("objectName", "");
    mainObject.insert("distance", dist);
    mainObject.insert("voltage", volt);

    QJsonDocument jsonDoc(mainObject);
    QString raw_data = jsonDoc.toJson(QJsonDocument::Compact);
//    qDebug() << "Generated JSON for smoothed curve:" << raw_data;

    rawdataArrayA = std::move(raw_data);
    emit plotingDataPhaseA(rawdataArrayA);
}
Q_INVOKABLE void mainwindows::getLineSeriesA(QObject* receiver)
{
    if (!receiver) return;

    QVariantList pointsList;
    for (const QPointF &pt : pointsA) {
        QVariantMap point;
        point["x"] = pt.x();
        point["y"] = pt.y();
        pointsList.append(point);
    }

    QMetaObject::invokeMethod(receiver, "updateDataFromCpp",
        Q_ARG(QVariant, QVariant("A")),
        Q_ARG(QVariant, pointsList));
}
Q_INVOKABLE void mainwindows::getLineSeriesB(QObject* receiver)
{
    if (!receiver)
        return;

    QVariantList pointsList;
    for (const QPointF &pt : pointsB) {
        QVariantMap point;
        point["x"] = pt.x();
        point["y"] = pt.y();
        pointsList.append(point);
    }

    QMetaObject::invokeMethod(receiver, "updateDataFromCpp",
        Q_ARG(QVariant, QVariant("B")),
        Q_ARG(QVariant, pointsList));
}
Q_INVOKABLE void mainwindows::getLineSeriesC(QObject* receiver)
{
    if (!receiver)
        return;

    QVariantList pointsList;
    for (const QPointF &pt : pointsC) {
        QVariantMap point;
        point["x"] = pt.x();
        point["y"] = pt.y();
        pointsList.append(point);
    }

    QMetaObject::invokeMethod(receiver, "updateDataFromCpp",
        Q_ARG(QVariant, QVariant("C")),
        Q_ARG(QVariant, pointsList));
}
Q_INVOKABLE void mainwindows::getLineSeriesPA(QObject* receiver)
{

    if (!receiver) return;

    QVariantList pointsList;
    for (const QPointF &pt : pointsPA) {  // ← หรือใช้ชื่ออื่นถ้าแตกต่าง
        QVariantMap point;
        point["x"] = pt.x();
        point["y"] = pt.y();
        pointsList.append(point);
    }

    QMetaObject::invokeMethod(receiver, "updateDataFromCpp",
        Q_ARG(QVariant, QVariant("PatternA")),
        Q_ARG(QVariant, pointsList));
}
Q_INVOKABLE void mainwindows::getLineSeriesPB(QObject* receiver)
{
    if (!receiver) return;

    QVariantList pointsList;
    for (const QPointF &pt : pointsPB) {
        QVariantMap point;
        point["x"] = pt.x();
        point["y"] = pt.y();
        pointsList.append(point);
    }

    QMetaObject::invokeMethod(receiver, "updateDataFromCpp",
        Q_ARG(QVariant, QVariant("PatternB")),
        Q_ARG(QVariant, pointsList));
}
Q_INVOKABLE void mainwindows::getLineSeriesPC(QObject* receiver)
{
    if (!receiver) return;

    QVariantList pointsList;
    for (const QPointF &pt : pointsPC) {
        QVariantMap point;
        point["x"] = pt.x();
        point["y"] = pt.y();
        pointsList.append(point);
    }

    QMetaObject::invokeMethod(receiver, "updateDataFromCpp",
        Q_ARG(QVariant, QVariant("PatternC")),
        Q_ARG(QVariant, pointsList));
}

void mainwindows::reSamplingNormalizationB(const std::vector<std::pair<float, float>>& result) {
    if (result.size() < 3) {
        qDebug() << "Not enough data points to process.";
        return;
    }

    qDebug() << "Starting peak detection and smoothing...";

    std::vector<std::pair<float, double>> peakPoints;
    std::pair<float, double> startPoint = {0.0, 0.0};

    for (const auto& point : result) {
        if (point.second > 0.0) { // First non-zero voltage
            startPoint = {point.first, point.second};
            break;
        }
    }
    peakPoints.push_back(startPoint);

    for (size_t i = 1; i < result.size() - 1; ++i) {
        float prevVoltage = result[i - 1].second;
        float currentVoltage = result[i].second;
        float nextVoltage = result[i + 1].second;

        if (prevVoltage < currentVoltage && currentVoltage > nextVoltage) {
            peakPoints.emplace_back(result[i]);
        }
    }

    peakPoints.push_back(result.back());

    auto maxPeakIt = std::max_element(peakPoints.begin(), peakPoints.end(),
                                      [](const std::pair<float, double>& a, const std::pair<float, double>& b) {
                                          return a.second < b.second;
                                      });
    std::pair<float, double> maxPeak = *maxPeakIt;
//    qDebug() << "Maximum peak detected at X:" << maxPeak.first / 1000.0 << "km, Y:" << maxPeak.second << "mV";

    if (std::find(peakPoints.begin(), peakPoints.end(), maxPeak) == peakPoints.end()) {
        peakPoints.push_back(maxPeak);
    }

//    qDebug() << "Peaks detected. Total peaks:" << peakPoints.size();

    for (const auto& peak : peakPoints) {
//        qDebug() << "Peak at X:" << peak.first / 1000.0 << "km, Y:" << peak.second << "mV";
    }

    std::vector<std::pair<float, double>> downsampledPeaks;
    size_t step = std::max<size_t>(1, peakPoints.size() / 50); // Downsample to around 50 points
    for (size_t i = 0; i < peakPoints.size(); i += step) {
        downsampledPeaks.push_back(peakPoints[i]);
    }
    if (peakPoints.back() != downsampledPeaks.back()) {
        downsampledPeaks.push_back(peakPoints.back()); // Ensure the last point is included
    }

    if (std::find(downsampledPeaks.begin(), downsampledPeaks.end(), maxPeak) == downsampledPeaks.end()) {
        downsampledPeaks.push_back(maxPeak);
    }

    std::sort(downsampledPeaks.begin(), downsampledPeaks.end()); // Sort points by X
//    qDebug() << "Downsampling completed. Total downsampled points:" << downsampledPeaks.size();

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
//    qDebug() << "Generated JSON for smoothed curve:" << raw_data;

    rawdataArrayB = std::move(raw_data);

    // Emit the signal for the curve
    emit plotingDataPhaseB(rawdataArrayB);
}

void mainwindows::reSamplingNormalizationC(const std::vector<std::pair<float, float>>& result) {
    qDebug() << "reSamplingNormalizationC:" << result;
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

    peakPoints.push_back(result.back());

    auto maxPeakIt = std::max_element(peakPoints.begin(), peakPoints.end(),
                                      [](const std::pair<float, double>& a, const std::pair<float, double>& b) {
                                          return a.second < b.second;
                                      });
    std::pair<float, double> maxPeak = *maxPeakIt;
//    qDebug() << "Maximum peak detected at X:" << maxPeak.first / 1000.0 << "km, Y:" << maxPeak.second << "mV";

    if (std::find(peakPoints.begin(), peakPoints.end(), maxPeak) == peakPoints.end()) {
        peakPoints.push_back(maxPeak);
    }

//    qDebug() << "Peaks detected. Total peaks:" << peakPoints.size();

    // Debug peaks
    for (const auto& peak : peakPoints) {
//        qDebug() << "Peak at X:" << peak.first / 1000.0 << "km, Y:" << peak.second << "mV";
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
//    qDebug() << "Downsampling completed. Total downsampled points:" << downsampledPeaks.size();

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

//    qDebug() << "Smoothing completed. Total points for the curve:" << smoothCurve.size();

    // Step 4: Prepare JSON Output
    QJsonObject mainObject;
    QJsonArray dist, volt;
    for (const auto& point : smoothCurve) {
        dist.push_back(point.first / 1000.0);  // Convert m to km
        volt.push_back(point.second);         // Voltage in mV
    }
    mainObject.insert("objectName", "dataPlotingC");
    mainObject.insert("distance", dist);
    mainObject.insert("voltage", volt);

    QJsonDocument jsonDoc(mainObject);
    QString raw_data = jsonDoc.toJson(QJsonDocument::Compact);
//    qDebug() << "Generated JSON for smoothed curve:" << raw_data;

    rawdataArrayC = std::move(raw_data);

    // Emit the signal for the curve
    emit plotingDataPhaseC(rawdataArrayC);
}

void mainwindows::plotPatternA(double sagFactorInit, double samplingRateInit, double distanceToStartInit,
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

//    qDebug() << "Total samples read: " << normalizedValues.size();

    const float threshold = thresholdInitA / 32768.0f;  // Convert to mV
    auto startIt = std::find_if(normalizedValues.begin(), normalizedValues.end(), [threshold](float val) {
        return val >= threshold;
    });

    if (startIt == normalizedValues.end()) {
        qDebug() << "Threshold value not found in data.";
        return;
    }
    int startIndex = std::distance(normalizedValues.begin(), startIt);
//    qDebug() << "Starting index found at position:" << startIndex;

    int resampling = samplingRateInit / (60 * sagFactorInit); // Resampling rate
//    qDebug() << "Resampling rate:" << resampling;

    float totalDistance = (distanceToShowInit - distanceToStartInit) * 1000;
    int fullpoint = static_cast<int>(totalDistance / (60 * sagFactorInit));
    int trueDistancepoint = fullpoint / resampling; // Points after resampling

//    qDebug() << "Full points:" << fullpoint;
//    qDebug() << "True distance points after resampling:" << trueDistancepoint;

    float pointInterval = totalDistance / trueDistancepoint; // Distance interval per point
//    qDebug() << "Point interval (m):" << pointInterval;

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
//        qDebug() << "X:" << distance / 1000.0 << " km, Y:" << voltage << " mV";
    }

    // JSON Output for Plotting
    QJsonObject mainObject;
    QJsonArray dist, volt;
    for (const auto& [distance, voltage] : result) {
        dist.push_back(distance / 1000);  // Convert m to km
        volt.push_back(voltage);  // Already multiplied by 4096
    }

    mainObject.insert("objectName", "patternA");
    mainObject.insert("distance", dist);
    mainObject.insert("voltage", volt);

    QJsonDocument jsonDoc(mainObject);
    QString raw_data = jsonDoc.toJson(QJsonDocument::Compact);
//    qDebug() << "Generated JSON:" << raw_data;

    rawdataArrayA = raw_data;
    reSamplingNormalizationPatternA(result);

}

void mainwindows::reSamplingNormalizationPatternA(const std::vector<std::pair<float, float>>& result) {
    if (result.size() < 3) {
        qDebug() << "Not enough data points to process.";
        return;
    }
    qDebug() << "Starting peak detection and smoothing...";

    // Step 1: Detect Peaks
    std::vector<std::pair<float, double>> peakPoints;
    std::pair<float, double> startPoint = {0.0, 0.0};

    for (const auto& point : result) {
        if (point.second > 0.0) { // First non-zero voltage
            startPoint = {point.first, point.second};
            break;
        }
    }
    peakPoints.push_back(startPoint);

    for (size_t i = 1; i < result.size() - 1; ++i) {
        float prevVoltage = result[i - 1].second;
        float currentVoltage = result[i].second;
        float nextVoltage = result[i + 1].second;

        if (prevVoltage < currentVoltage && currentVoltage > nextVoltage) {
            peakPoints.emplace_back(result[i]);
        }
    }

    peakPoints.push_back(result.back());

    auto maxPeakIt = std::max_element(peakPoints.begin(), peakPoints.end(),
                                      [](const std::pair<float, double>& a, const std::pair<float, double>& b) {
                                          return a.second < b.second;
                                      });
    std::pair<float, double> maxPeak = *maxPeakIt;

    if (std::find(peakPoints.begin(), peakPoints.end(), maxPeak) == peakPoints.end()) {
        peakPoints.push_back(maxPeak);
    }

    qDebug() << "Peaks detected. Total peaks:" << peakPoints.size();

    // Step 2: Downsample Peak Points
    std::vector<std::pair<float, double>> downsampledPeaks;
    size_t step = std::max<size_t>(1, peakPoints.size() / 50); // Downsample to around 50 points
    for (size_t i = 0; i < peakPoints.size(); i += step) {
        downsampledPeaks.push_back(peakPoints[i]);
    }
    if (peakPoints.back() != downsampledPeaks.back()) {
        downsampledPeaks.push_back(peakPoints.back()); // Ensure the last point is included
    }

    if (std::find(downsampledPeaks.begin(), downsampledPeaks.end(), maxPeak) == downsampledPeaks.end()) {
        downsampledPeaks.push_back(maxPeak);
    }

    std::sort(downsampledPeaks.begin(), downsampledPeaks.end()); // Sort points by X

    std::vector<std::pair<float, double>> smoothCurve;
    for (size_t i = 0; i < downsampledPeaks.size() - 1; ++i) {
        float x1 = downsampledPeaks[i].first;
        float x2 = downsampledPeaks[i + 1].first;
        double y1 = downsampledPeaks[i].second;
        double y2 = downsampledPeaks[i + 1].second;

        for (float x = x1; x <= x2; x += (x2 - x1) / 10.0) { // Add 10 points per segment
            double t = (x - x1) / (x2 - x1); // Normalize x between 0 and 1
            double y = (1 - t) * y1 + t * y2; // Linear interpolation
            smoothCurve.emplace_back(x, y);
        }
    }

    qDebug() << "Smoothing completed. Total points for the curve:" << smoothCurve.size();

    QJsonObject mainObject;
    QJsonArray dist, volt;
    for (const auto& point : smoothCurve) {
        dist.push_back(point.first / 1000.0);  // Convert m to km
        volt.push_back(point.second);         // Voltage in mV
    }
    mainObject.insert("objectName", "patternA");
    mainObject.insert("distance", dist);
    mainObject.insert("voltage", volt);

    QJsonDocument jsonDoc(mainObject);
    QString raw_data = jsonDoc.toJson(QJsonDocument::Compact);

    rawdataArrayA = std::move(raw_data);
    emit plotingDataPhaseA(rawdataArrayA);

    QDir dir("/home/pi/patternData");
    if (!dir.exists()) {
        if (!dir.mkpath(".")) {
            qDebug() << "Failed to create directory:" << dir.absolutePath();
            return;
        }
    }

    QString dateStr = QDate::currentDate().toString("dd_MM_yyyy");
    QString timeStr = QTime::currentTime().toString("hh_mm_ss");
    QString filePath = QString("/home/pi/patternData/patternA_1_%1_%2.csv").arg(dateStr).arg(timeStr);

    QFile file(filePath);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Failed to create CSV file:" << filePath;
        return;
    }

    QTextStream out(&file);
    out << "Distance (km),Voltage (mV)\n";
    for (const auto& point : smoothCurve) {
        double distance = point.first / 1000.0; // Convert to km
        double voltage = point.second;         // Voltage in mV
        out << QString::number(distance, 'f', 6) << "," << QString::number(voltage, 'f', 6) << "\n";
    }

    file.close();

    qDebug() << "CSV file created successfully at:" << filePath;
}


void mainwindows::plotPatternB(double sagFactorInit, double samplingRateInit, double distanceToStartInit,
                            double distanceToShowInit, double fulldistance, double thresholdInitB) {
    qDebug() << "Debug plotPatternB:" << sagFactorInit << samplingRateInit << distanceToStartInit
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

//    qDebug() << "Total samples read: " << normalizedValues.size();

    const float threshold = thresholdInitB / 32768.0f;  // Convert to mV
    auto startIt = std::find_if(normalizedValues.begin(), normalizedValues.end(), [threshold](float val) {
        return val >= threshold;
    });

    if (startIt == normalizedValues.end()) {
        qDebug() << "Threshold value not found in data.";
        return;
    }
    int startIndex = std::distance(normalizedValues.begin(), startIt);
//    qDebug() << "Starting index found at position:" << startIndex;

    int resampling = samplingRateInit / (60 * sagFactorInit); // Resampling rate
//    qDebug() << "Resampling rate:" << resampling;

    float totalDistance = (distanceToShowInit - distanceToStartInit) * 1000;
    int fullpoint = static_cast<int>(totalDistance / (60 * sagFactorInit));
    int trueDistancepoint = fullpoint / resampling; // Points after resampling

//    qDebug() << "Full points:" << fullpoint;
//    qDebug() << "True distance points after resampling:" << trueDistancepoint;

    float pointInterval = totalDistance / trueDistancepoint; // Distance interval per point
//    qDebug() << "Point interval (m):" << pointInterval;

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
//        qDebug() << "X:" << distance / 1000.0 << " km, Y:" << voltage << " mV";
    }

    // JSON Output for Plotting
    QJsonObject mainObject;
    QJsonArray dist, volt;
    for (const auto& [distance, voltage] : result) {
        dist.push_back(distance / 1000);  // Convert m to km
        volt.push_back(voltage);  // Already multiplied by 4096
    }

    mainObject.insert("objectName", "patternB");
    mainObject.insert("distance", dist);
    mainObject.insert("voltage", volt);

    QJsonDocument jsonDoc(mainObject);
    QString raw_data = jsonDoc.toJson(QJsonDocument::Compact);
//    qDebug() << "Generated JSON:" << raw_data;

    rawdataArrayB = raw_data;
    reSamplingNormalizationPatternB(result);

}

void mainwindows::reSamplingNormalizationPatternB(const std::vector<std::pair<float, float>>& result) {
    if (result.size() < 3) {
        qDebug() << "Not enough data points to process.";
        return;
    }
    qDebug() << "Starting peak detection and smoothing...";

    // Step 1: Detect Peaks
    std::vector<std::pair<float, double>> peakPoints;
    std::pair<float, double> startPoint = {0.0, 0.0};

    for (const auto& point : result) {
        if (point.second > 0.0) { // First non-zero voltage
            startPoint = {point.first, point.second};
            break;
        }
    }
    peakPoints.push_back(startPoint);

    for (size_t i = 1; i < result.size() - 1; ++i) {
        float prevVoltage = result[i - 1].second;
        float currentVoltage = result[i].second;
        float nextVoltage = result[i + 1].second;

        if (prevVoltage < currentVoltage && currentVoltage > nextVoltage) {
            peakPoints.emplace_back(result[i]);
        }
    }

    peakPoints.push_back(result.back());

    auto maxPeakIt = std::max_element(peakPoints.begin(), peakPoints.end(),
                                      [](const std::pair<float, double>& a, const std::pair<float, double>& b) {
                                          return a.second < b.second;
                                      });
    std::pair<float, double> maxPeak = *maxPeakIt;
//    qDebug() << "Maximum peak detected at X:" << maxPeak.first / 1000.0 << "km, Y:" << maxPeak.second << "mV";

    if (std::find(peakPoints.begin(), peakPoints.end(), maxPeak) == peakPoints.end()) {
        peakPoints.push_back(maxPeak);
    }

    qDebug() << "Peaks detected. Total peaks:" << peakPoints.size();

    for (const auto& peak : peakPoints) {
//        qDebug() << "Peak at X:" << peak.first / 1000.0 << "km, Y:" << peak.second << "mV";
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

    if (std::find(downsampledPeaks.begin(), downsampledPeaks.end(), maxPeak) == downsampledPeaks.end()) {
        downsampledPeaks.push_back(maxPeak);
    }

    std::sort(downsampledPeaks.begin(), downsampledPeaks.end()); // Sort points by X
//    qDebug() << "Downsampling completed. Total downsampled points:" << downsampledPeaks.size();

    // Step 3: Generate Smooth Curve
    std::vector<std::pair<float, double>> smoothCurve;
    for (size_t i = 0; i < downsampledPeaks.size() - 1; ++i) {
        float x1 = downsampledPeaks[i].first;
        float x2 = downsampledPeaks[i + 1].first;
        double y1 = downsampledPeaks[i].second;
        double y2 = downsampledPeaks[i + 1].second;

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
    mainObject.insert("objectName", "patternB");
    mainObject.insert("distance", dist);
    mainObject.insert("voltage", volt);

    QJsonDocument jsonDoc(mainObject);
    QString raw_data = jsonDoc.toJson(QJsonDocument::Compact);
//    qDebug() << "Generated JSON for smoothed curve:" << raw_data;

    // Emit the signal for the curve
    rawdataArrayB = std::move(raw_data);
    emit plotingDataPhaseB(rawdataArrayB);
}

void mainwindows::plotPatternC(double sagFactorInit, double samplingRateInit, double distanceToStartInit,
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

//    qDebug() << "Total samples read: " << normalizedValues.size();

    const float threshold = thresholdInitC / 32768.0f;  // Convert to mV
    auto startIt = std::find_if(normalizedValues.begin(), normalizedValues.end(), [threshold](float val) {
        return val >= threshold;
    });

    if (startIt == normalizedValues.end()) {
        qDebug() << "Threshold value not found in data.";
        return;
    }
    int startIndex = std::distance(normalizedValues.begin(), startIt);
//    qDebug() << "Starting index found at position:" << startIndex;

    int resampling = samplingRateInit / (60 * sagFactorInit); // Resampling rate
//    qDebug() << "Resampling rate:" << resampling;

    float totalDistance = (distanceToShowInit - distanceToStartInit) * 1000;
    int fullpoint = static_cast<int>(totalDistance / (60 * sagFactorInit));
    int trueDistancepoint = fullpoint / resampling; // Points after resampling

//    qDebug() << "Full points:" << fullpoint;
//    qDebug() << "True distance points after resampling:" << trueDistancepoint;

    float pointInterval = totalDistance / trueDistancepoint; // Distance interval per point
//    qDebug() << "Point interval (m):" << pointInterval;

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
//        qDebug() << "X:" << distance / 1000.0 << " km, Y:" << voltage << " mV";
    }

    // JSON Output for Plotting
    QJsonObject mainObject;
    QJsonArray dist, volt;
    for (const auto& [distance, voltage] : result) {
        dist.push_back(distance / 1000);  // Convert m to km
        volt.push_back(voltage);  // Already multiplied by 4096
    }

    mainObject.insert("objectName", "patternC");
    mainObject.insert("distance", dist);
    mainObject.insert("voltage", volt);

    QJsonDocument jsonDoc(mainObject);
    QString raw_data = jsonDoc.toJson(QJsonDocument::Compact);
//    qDebug() << "Generated JSON:" << raw_data;

    rawdataArrayC = raw_data;
    reSamplingNormalizationPatternC(result);

}

void mainwindows::reSamplingNormalizationPatternC(const std::vector<std::pair<float, float>>& result) {
    if (result.size() < 3) {
        qDebug() << "Not enough data points to process.";
        return;
    }
    qDebug() << "Starting peak detection and smoothing...";

    // Step 1: Detect Peaks
    std::vector<std::pair<float, double>> peakPoints;
    std::pair<float, double> startPoint = {0.0, 0.0};

    for (const auto& point : result) {
        if (point.second > 0.0) { // First non-zero voltage
            startPoint = {point.first, point.second};
            break;
        }
    }
    peakPoints.push_back(startPoint);

    for (size_t i = 1; i < result.size() - 1; ++i) {
        float prevVoltage = result[i - 1].second;
        float currentVoltage = result[i].second;
        float nextVoltage = result[i + 1].second;

        if (prevVoltage < currentVoltage && currentVoltage > nextVoltage) {
            peakPoints.emplace_back(result[i]);
        }
    }

    peakPoints.push_back(result.back());

    auto maxPeakIt = std::max_element(peakPoints.begin(), peakPoints.end(),
                                      [](const std::pair<float, double>& a, const std::pair<float, double>& b) {
                                          return a.second < b.second;
                                      });
    std::pair<float, double> maxPeak = *maxPeakIt;
//    qDebug() << "Maximum peak detected at X:" << maxPeak.first / 1000.0 << "km, Y:" << maxPeak.second << "mV";

    if (std::find(peakPoints.begin(), peakPoints.end(), maxPeak) == peakPoints.end()) {
        peakPoints.push_back(maxPeak);
    }

    qDebug() << "Peaks detected. Total peaks:" << peakPoints.size();

    for (const auto& peak : peakPoints) {
//        qDebug() << "Peak at X:" << peak.first / 1000.0 << "km, Y:" << peak.second << "mV";
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

    if (std::find(downsampledPeaks.begin(), downsampledPeaks.end(), maxPeak) == downsampledPeaks.end()) {
        downsampledPeaks.push_back(maxPeak);
    }

    std::sort(downsampledPeaks.begin(), downsampledPeaks.end()); // Sort points by X
//    qDebug() << "Downsampling completed. Total downsampled points:" << downsampledPeaks.size();

    // Step 3: Generate Smooth Curve
    std::vector<std::pair<float, double>> smoothCurve;
    for (size_t i = 0; i < downsampledPeaks.size() - 1; ++i) {
        float x1 = downsampledPeaks[i].first;
        float x2 = downsampledPeaks[i + 1].first;
        double y1 = downsampledPeaks[i].second;
        double y2 = downsampledPeaks[i + 1].second;

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
    mainObject.insert("objectName", "patternC");
    mainObject.insert("distance", dist);
    mainObject.insert("voltage", volt);

    QJsonDocument jsonDoc(mainObject);
    QString raw_data = jsonDoc.toJson(QJsonDocument::Compact);
//    qDebug() << "Generated JSON for smoothed curve:" << raw_data;

    // Emit the signal for the curve
    rawdataArrayC = std::move(raw_data);
    emit plotingDataPhaseC(rawdataArrayC);
}



void* mainwindows::ThreadFuncA(void* pTr) {
    ThreadData* data = static_cast<ThreadData*>(pTr);
    data->instance->plotGraphA(data->sagFactorInit, data->samplingRateInit, data->distanceToStartInit,
                               data->distanceToShowInit, data->fulldistance, data->thresholdInit);
    return NULL;
}
void* mainwindows::ThreadFuncB(void* pTr) {
    ThreadData* data = static_cast<ThreadData*>(pTr);
    data->instance->plotGraphB(data->sagFactorInit, data->samplingRateInit, data->distanceToStartInit,
                               data->distanceToShowInit, data->fulldistance, data->thresholdInit);
    return NULL;
}

void* mainwindows::ThreadFuncC(void* pTr) {
    ThreadData* data = static_cast<ThreadData*>(pTr);
    data->instance->plotGraphC(data->sagFactorInit, data->samplingRateInit, data->distanceToStartInit,
                               data->distanceToShowInit, data->fulldistance, data->thresholdInit);
    return NULL;
}
void mainwindows::startThreads(double sagFactorInit, double samplingRateInit, double distanceToStartInit,
                               double distanceToShowInit, double fulldistance, double thresholdInitA,
                               double thresholdInitB, double thresholdInitC) {
    dataA = {this, sagFactorInit, samplingRateInit, distanceToStartInit, distanceToShowInit, fulldistance, thresholdInitA};
    dataB = {this, sagFactorInit, samplingRateInit, distanceToStartInit, distanceToShowInit, fulldistance, thresholdInitB};
    dataC = {this, sagFactorInit, samplingRateInit, distanceToStartInit, distanceToShowInit, fulldistance, thresholdInitC};

    int ret;
    ret = pthread_create(&idThreadA, NULL, ThreadFuncA, &dataA);
    if (ret == 0) {
        qDebug() << "Thread A created successfully.";
    } else {
        qDebug() << "Thread A not created.";
    }

    ret = pthread_create(&idThreadB, NULL, ThreadFuncB, &dataB);
    if (ret == 0) {
        qDebug() << "Thread B created successfully.";
    } else {
        qDebug() << "Thread B not created.";
    }

    ret = pthread_create(&idThreadC, NULL, ThreadFuncC, &dataC);
    if (ret == 0) {
        qDebug() << "Thread C created successfully.";
    } else {
        qDebug() << "Thread C not created.";
    }
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


void mainwindows::patterntest(int msg) {
    qDebug() << "PatternTest:" << msg;
//    if(msg == "PatternTest"){
//        uint8_t n = obj["number"].toInt();
        QJsonDocument jsonDoc;
        QJsonObject Param;
        Param.insert("objectName","PatternTest");
        Param.insert("number",msg);//
        QString raw_data = QJsonDocument(Param).toJson(QJsonDocument::Compact).toStdString().c_str();
        emit sendMessage(raw_data);
//    }
}


void mainwindows::RecalculateWithMargin(QString msg) {
    qDebug() << "RecalculateWithMargin called with data:" << msg;

    QJsonDocument doc = QJsonDocument::fromJson(msg.toUtf8());
    QJsonObject obj = doc.object();
    QJsonObject command = doc.object();
    QString getCommand =  QJsonValue(command["objectName"]).toString();
    if(getCommand.contains("combinedDataPhaseA")){
        int marginA = obj["marginA"].toInt();
        int valueVoltageA = obj["valueVoltageA"].toInt();
        int focusIndex = obj["focusIndex"].toInt();
        QString phase = obj["PHASE"].toString();
        qDebug() << "Processing MarginA:" << marginA << " ValueVoltageA:" << valueVoltageA
                 << " focusIndex:" << focusIndex << " Phase:" << phase;

        QDir directory("/home/pi/patternData/");
        if (!directory.exists()) {
            qDebug() << "Directory does not exist!";
            return;
        }

        QStringList filters;
        filters << "patternA_*.csv";
        directory.setNameFilters(filters);
        directory.setSorting(QDir::Time | QDir::Reversed); // เรียงจากใหม่ไปเก่า
        QFileInfoList fileList = directory.entryInfoList(QDir::Files);

        if (fileList.isEmpty()) {
            qDebug() << "No CSV files found in directory.";
            return;
        }

        QString latestFile = fileList.first().absoluteFilePath();
        qDebug() << "Opening latest CSV file:" << latestFile;

        QFile file(latestFile);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Unable to open file:" << latestFile;
            return;
        }

        QTextStream in(&file);
        QVector<double> distanceArray;
        QVector<double> voltageArray;
        static QVector<double> segmentAdjustments;

        bool firstLine = true;

        while (!in.atEnd()) {
            QString line = in.readLine();
            if (firstLine) { firstLine = false; continue; }

            QStringList values = line.split(",");
            if (values.size() == 2) {
                double distance = values[0].toDouble();
                double voltage = values[1].toDouble();
                distanceArray.append(distance);
                voltageArray.append(voltage);
            }
        }
        file.close();

        qDebug() << "CSV Data Loaded Successfully! Total data points:" << distanceArray.size();

        if (distanceArray.isEmpty()) {
            qDebug() << "No data available for processing!";
            return;
        }

        double maxDistance = distanceArray.last();
        int totalSegments = marginA; // จำนวนช่วง
        double segmentSize = maxDistance / totalSegments;

        qDebug() << "Max Distance:" << maxDistance << " Total Segments:" << totalSegments
                 << " Segment Size:" << segmentSize;

        if (segmentAdjustments.size() != totalSegments) {
            segmentAdjustments.fill(0, totalSegments);
        }

        for (int i = 0; i < distanceArray.size(); ++i) {
            int segmentIndex = static_cast<int>(distanceArray[i] / segmentSize);

            if (segmentIndex >= totalSegments) {
                segmentIndex = totalSegments - 1;
            }

            voltageArray[i] += segmentAdjustments[segmentIndex];

            if (segmentIndex == focusIndex) {
                voltageArray[i] += valueVoltageA;
            }
        }

        segmentAdjustments[focusIndex] += valueVoltageA;

        QJsonObject mainObject;
        QJsonArray dist, volt;

        for (int i = 0; i < distanceArray.size(); ++i) {
            dist.push_back(distanceArray[i]);
            volt.push_back(voltageArray[i]);
        }

        mainObject.insert("objectName", "patternA");
        mainObject.insert("distance", dist);
        mainObject.insert("voltage", volt);

        QJsonDocument jsonDoc(mainObject);
        QString raw_data = jsonDoc.toJson(QJsonDocument::Compact);

        rawdataArrayA = std::move(raw_data);
        emit plotingDataPhaseA(rawdataArrayA);

        qDebug() << "Updated data sent for plotting!";
    }else if (getCommand.contains("autoSetValueMargin")) {
        int marginA = obj["rangeofmargin"].toInt();
        int valueVoltageA = obj["autoValueVoltage"].toInt();
        QString phase = obj["PHASE"].toString();

        qDebug() << "Processing Auto Value Margin. Range:" << marginA
                 << " AutoValueVoltage:" << valueVoltageA << " Phase:" << phase;

        QDir directory("/home/pi/patternData/");
        if (!directory.exists()) {
            qDebug() << "Directory does not exist!";
            return;
        }

        QStringList filters;
        filters << "patternA_*.csv";
        directory.setNameFilters(filters);
        directory.setSorting(QDir::Time | QDir::Reversed);
        QFileInfoList fileList = directory.entryInfoList(QDir::Files);

        if (fileList.isEmpty()) {
            qDebug() << "No CSV files found in directory.";
            return;
        }

        QString latestFile = fileList.first().absoluteFilePath();
        qDebug() << "Opening latest CSV file:" << latestFile;

        QFile file(latestFile);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Unable to open file:" << latestFile;
            return;
        }

        QTextStream in(&file);
        QVector<double> distanceArray;
        QVector<double> voltageArray;

        bool firstLine = true;
        while (!in.atEnd()) {
            QString line = in.readLine();
            if (firstLine) { firstLine = false; continue; }

            QStringList values = line.split(",");
            if (values.size() == 2) {
                double distance = values[0].toDouble();
                double voltage = values[1].toDouble();
                distanceArray.append(distance);
                voltageArray.append(voltage);
            }
        }
        file.close();

        qDebug() << "CSV Data Loaded Successfully! Total data points:" << distanceArray.size();
        if (distanceArray.isEmpty()) {
            qDebug() << "No data available for processing!";
            return;
        }

        for (int i = 0; i < voltageArray.size(); ++i) {
            voltageArray[i] += valueVoltageA; // Apply voltage increase to ALL values
        }

        QJsonObject mainObject;
        QJsonArray dist, volt;

        for (int i = 0; i < distanceArray.size(); ++i) {
            dist.push_back(distanceArray[i]);
            volt.push_back(voltageArray[i]);
        }

        mainObject.insert("objectName", "patternA");
        mainObject.insert("distance", dist);
        mainObject.insert("voltage", volt);

        QJsonDocument jsonDoc(mainObject);
        QString raw_data = jsonDoc.toJson(QJsonDocument::Compact);

        rawdataArrayA = std::move(raw_data);
        emit plotingDataPhaseA(rawdataArrayA);

        qDebug() << "Updated data sent for plotting!";
    }

}

void mainwindows::getSetting()
{
//    qDebug() << "getSetting";
//    QSettings *settings;
//    const QString cfgfile = FILESETTINGMASTER;
//    qDebug() << "Loading configuration from:" << cfgfile;
//    if(QDir::isAbsolutePath(cfgfile))
//    {
//        qDebug() << "isAbsolutePath";
//        settings = new QSettings(cfgfile,QSettings::IniFormat);
//        networks->dhcpmethod = settings->value(QString("%1/DHCP").arg(NETWORK_SERVER),0).toInt();
//        networks->ip_address = settings->value(QString("%1/IP_ADDRESS").arg(NETWORK_SERVER),"").toString();
//        networks->subnet = settings->value(QString("%1/NETMASK").arg(NETWORK_SERVER),"").toString();
//        networks->ip_gateway = settings->value(QString("%1/IP_GATEWAY").arg(NETWORK_SERVER),"").toString();
//        networks->pridns = settings->value(QString("%1/PRIDNS").arg(NETWORK_SERVER),"").toString();
//        networks->secdns = settings->value(QString("%1/SECDNS").arg(NETWORK_SERVER),"").toString();
//        networks->phyName = settings->value(QString("%1/PHYNAME").arg(NETWORK_SERVER),"").toString();
//        networks->ip_snmp = settings->value(QString("%1/IP_ADDRESS").arg(SNMP_SERVER),"0.0.0.0").toString();
//        networks->ip_timeserver = settings->value(QString("%1/IP_ADDRESS").arg(TIME_SERVER),"0.0.0.0").toString();
//        networks->location_snmp = settings->value(QString("%1/LOCATION").arg(TIME_SERVER),"").toString();
//    }
//    else{
//        qDebug() << "Loading configuration from:" << cfgfile << " FILE NOT FOUND!";
//    }
//    qDebug() << "Loading configuration completed" << networks->subnet;
//    networks->printinfo();
//    delete settings;
}

void mainwindows::iScreenIPNetwork(){
    QJsonObject mainObject;
    mainObject.insert("objectName", "iTouchOwnIP");
    mainObject.insert("iTouchIPAddress", mysql->iPaddressMonitor);
    mainObject.insert("iTouchIPGateway", mysql->gatewayMonitor);
    QJsonDocument jsonDoc(mainObject);
    QString ip_iTouch = jsonDoc.toJson(QJsonDocument::Compact);
    qDebug() << "ip_iTouch:" << ip_iTouch;
    cppCommand(ip_iTouch);
    setIPDisplay->stop();
}

void mainwindows::setDefaultIPDataBase(QString msg) {
    qDebug() << "[setDefaultIPDataBase] JSON message:" << msg;

    QJsonDocument d = QJsonDocument::fromJson(msg.toUtf8());
    QJsonObject command = d.object();

    QString getCommand = command["objectName"].toString().trimmed();
    QString ipAddressInput = command["defalutip"].toString().trimmed();
    QString ipGatewayInput = command["defalutgateways"].toString().trimmed();
    QString ipNetmaskInput = command["defalutnetmask"].toString().trimmed();

    // ❗ fallback: if input is empty, use existing value from networks
    QString ipAddress = ipAddressInput.isEmpty() ? networks->ip_address : ipAddressInput;
    QString ipGateway = ipGatewayInput.isEmpty() ? networks->ip_gateway : ipGatewayInput;
    QString ipNetmask = ipNetmaskInput.isEmpty() ? networks->subnet : ipNetmaskInput;

    // ✅ Update in-memory struct
    networks->ip_address = ipAddress;
    networks->ip_gateway = ipGateway;
    networks->subnet = ipNetmask;

    qDebug() << "[setDefaultIPDataBase] Applied IP:" << ipAddress
             << "Gateway:" << ipGateway
             << "Netmask:" << ipNetmask;

    // ✅ Apply with nmcli
    QStringList commands;
    commands << QString("nmcli con mod 'Wired connection 1' ipv4.addresses %1/24").arg(ipAddress)
             << QString("nmcli con mod 'Wired connection 1' ipv4.gateway %1").arg(ipGateway)
             << "nmcli con mod 'Wired connection 1' ipv4.method manual"
             << "nmcli con up 'Wired connection 1'";

    for (const QString &cmd : commands) {
        qDebug() << "Executing:" << cmd;
        int result = QProcess::execute("bash", QStringList() << "-c" << cmd);
        if (result != 0) {
            qWarning() << "Command failed:" << cmd;
        }
    }

    // ✅ Restart related services
    iScreenIPNetwork();
    QThread::msleep(1000);
    QProcess::execute("sudo", QStringList() << "systemctl" << "restart" << "iTouchsettingNetwork.service");
    QProcess::execute("sudo", QStringList() << "systemctl" << "restart" << "NetworkManager.service");

    // ✅ Debug info
    networks->printinfo();
}

void mainwindows::UpdateiScreenIPNetwork(QString msg) {

    QJsonDocument d = QJsonDocument::fromJson(msg.toUtf8());
    QJsonObject command = d.object();

    QString getCommand = command["objectName"].toString().trimmed();
    QString ipAddressInput = command["editsIPAddress"].toString().trimmed();
    QString ipGatewayInput = command["editsGateWays"].toString().trimmed();


    qDebug() << "[UpdateiScreenIPNetwork] Command:" << getCommand;
    qDebug() << "[UpdateiScreenIPNetwork] Input IP:" << ipAddressInput << ", Input Gateway:" << ipGatewayInput;

    QString ipAddress = ipAddressInput.isEmpty() ? networks->ip_address : ipAddressInput;
    QString ipGateway = ipGatewayInput.isEmpty() ? networks->ip_gateway : ipGatewayInput;

    networks->ip_address = ipAddress;
    networks->ip_gateway = ipGateway;

    qDebug() << "[UpdateiScreenIPNetwork] Updated network struct: IP=" << ipAddress << ", Gateway=" << ipGateway;

    QStringList commands;
    commands << QString("nmcli con mod 'Wired connection 1' ipv4.addresses %1/24").arg(ipAddress)
             << QString("nmcli con mod 'Wired connection 1' ipv4.gateway %1").arg(ipGateway)
             << "nmcli con mod 'Wired connection 1' ipv4.method manual"
             << "nmcli con up 'Wired connection 1'";

    for (const QString &cmd : commands) {
        qDebug() << "Executing:" << cmd;
        int result = QProcess::execute("bash", QStringList() << "-c" << cmd);
        if (result != 0) {
            qWarning() << "Command failed:" << cmd;
        }
    }

    iScreenIPNetwork();
    QThread::msleep(1000);
    QProcess::execute("sudo", QStringList() << "systemctl" << "restart" << "iTouchsettingNetwork.service");
    QProcess::execute("sudo", QStringList() << "systemctl" << "restart" << "NetworkManager.service");

    networks->printinfo();

}

void mainwindows::updateSystemiTouch(QString message) {
    qDebug() << "message" << message;
    QJsonDocument d = QJsonDocument::fromJson(message.toUtf8());
    QJsonObject command = d.object();
    QString getCommand =  QJsonValue(command["objectName"]).toString();
    QString lastFirmWare = command["text"].toString();
    QString lastFirmWareupdate = command["text"].toString();

    QString link = command["link"].toString();
    qDebug() << "lastFirmWare for download" << lastFirmWare << "currentFirmWare running" << SwVersion << link;
    if (((SwVersion.split(" ").size() >= 2) & (lastFirmWare.split(" ").size() >= 2)) == false)
    {
        if (SwVersion != lastFirmWare)
        {
            qDebug() << "(lastFirmWare != currentFirmWare)" << "lastFirmWare for download" << lastFirmWare << "currentFirmWare running" << SwVersion;
            SwVersion=lastFirmWareupdate;

            downloader->downloadFile(link, "/var/www/html/uploads/update.tar");
        }
    }
    else if (SwVersion != lastFirmWare)
    {
        double currentVersion =  QString(SwVersion.split(" ").at(1)).toDouble();
        double lastVersion = QString(lastFirmWare.split(" ").at(1)).toDouble();
        QString currentFirmWare = SwVersion.split(" ").at(0);
        lastFirmWare = lastFirmWare.split(" ").at(0);
        qDebug() << "lastFirmWare for download" << lastVersion << lastFirmWare << "currentFirmWare running" << currentVersion << currentFirmWare;
        if (lastVersion > currentVersion)
        {
            qDebug() << "(lastFirmWare != currentFirmWare)" << "lastFirmWare for download" << lastVersion << lastFirmWare << "currentFirmWare running" << currentVersion << currentFirmWare;
            SwVersion=lastFirmWareupdate;

            downloader->downloadFile(link, "/var/www/html/uploads/update.tar");

        }
    }
}

void mainwindows::downloadCompleted(const QString &outputPath)
{

    if (outputPath.contains("update.tar"))
    {
        updateFirmware();
    }
}

void mainwindows::updateFirmware()
{
    system("sync");
    qDebug() << "Start updateFirmware";

    foundfileupdate = true;

    const QString tarPath = "/var/www/html/uploads/update.tar";
    if (!QFile::exists(tarPath)) {
        qWarning() << "❌ update.tar not found:" << tarPath;
        foundfileupdate = false;
        return;
    }

    // Prepare temp folder
    system("sudo rm -rf /tmp/update");
    system("sudo mkdir -p /tmp/update");

    // Extract tar
    const QString cmdTar = QString("tar -xf \"%1\" -C /tmp/update/").arg(tarPath);
    int retTar = system(cmdTar.toStdString().c_str());
    if (retTar != 0) {
        qWarning() << "❌ tar extract failed, ret =" << retTar;
        foundfileupdate = false;
        return;
    }

    // README path
    const QString versionFilePath = "/tmp/update/README.txt";
    if (!QFile::exists(versionFilePath)) {
        qWarning() << "❌ README.txt not found at:" << versionFilePath;
        system("ls -la /tmp/update/");
        foundfileupdate = false;
        return;
    }

    // Read + parse SwVersionupdate
    QString newSwVersion;
    {
        QFile f(versionFilePath);
        if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qWarning() << "❌ Cannot open README.txt:" << versionFilePath;
            foundfileupdate = false;
            return;
        }

        const QString content = QString::fromUtf8(f.readAll());
        f.close();

        qDebug() << "📄 Full README.txt content:\n" << content;

        QRegularExpression re("SwVersionupdate\\s*=\\s*\"([^\"]+)\"");
        QRegularExpressionMatch m = re.match(content);
        if (m.hasMatch()) {
            newSwVersion = m.captured(1).trimmed();
            qDebug() << "✅ Extracted SwVersionupdate =" << newSwVersion;
        } else {
            qWarning() << "❌ Cannot find SwVersionupdate in README.txt -> ABORT update";
            foundfileupdate = false;
            return;
        }
    }

    if (newSwVersion.isEmpty()) {
        qWarning() << "❌ newSwVersion empty -> ABORT update";
        foundfileupdate = false;
        return;
    }

    qDebug() << "🆕 New SwVersionupdate from README.txt:" << newSwVersion;

    // Copy README to /home/pi
    const QString destReadme = "/home/pi/README.txt";
    if (QFile::exists(destReadme))
        QFile::remove(destReadme);

    if (QFile::copy(versionFilePath, destReadme)) {
        qDebug() << "📄 Copied README.txt to" << destReadme;
    } else {
        qWarning() << "❌ Failed to copy README.txt to" << destReadme;
        // not fatal
    }

    // Debug before DB update
    qDebug() << "🔄 Updating DB: Old version =" << mysql->swversion
             << "New version =" << newSwVersion;

    // Update RAM first
    SwVersion = newSwVersion;
    mysql->swversion = newSwVersion;

    // Update DB (call both if you already have both; keep as-is)
    // NOTE: if one of these does not exist in your Database class, remove that line.
    if (mysql) {
        // 1) if you have this function
        if (mysql->metaObject()->indexOfMethod("updateSwVersion(QString)") != -1) {
            QMetaObject::invokeMethod(mysql, "updateSwVersion",
                                      Qt::DirectConnection,
                                      Q_ARG(QString, newSwVersion));
            qDebug() << "📊 updateSwVersion called with:" << newSwVersion;
        } else {
            qDebug() << "ℹ️ updateSwVersion(QString) not found (skip)";
        }

        // 2) if you have this function
        if (mysql->metaObject()->indexOfMethod("setSwVersion(QString)") != -1) {
            QMetaObject::invokeMethod(mysql, "setSwVersion",
                                      Qt::DirectConnection,
                                      Q_ARG(QString, newSwVersion));
            qDebug() << "📊 setSwVersion called with:" << newSwVersion;
        } else {
            qDebug() << "ℹ️ setSwVersion(QString) not found (skip)";
        }
    } else {
        qWarning() << "❌ mysql is null -> DB not updated";
        foundfileupdate = false;
        return;
    }

    // Optional: give DB a moment if your DB writes are async/queued in your app
    // QThread::msleep(50);

    qDebug() << "📊 DB update requested with version:" << newSwVersion;

    // Update status + run update script
    updateStatus = 1;
    qDebug() << "🚀 Running update.sh ...";
    int retSh = system("sh /tmp/update/update.sh");
    qDebug() << "update.sh ret =" << retSh;

    system("sync");
    system("sudo rm -rf /tmp/update");
    system("sync");

    updateStatus = 2;
    qDebug() << "✅ Update complete -> rebooting";

    emit updateMasterMode(networks->userTypeSelect,
                          networks->ip_master,
                          networks->ip_slave,
                          SwVersion);

    QProcess::startDetached("sudo reboot");
    exit(0);
}
QStringList mainwindows::findFile()
{
    QStringList listfilename;
    QString ss="/var/www/html/uploads/";
    const char *sss ;
    sss = ss.toStdString().c_str();
    QDir dir1("/var/www/html/uploads/");
    QString filepath;
    QString filename;
    QFileInfoList fi1List( dir1.entryInfoList( QDir::Files, QDir::Name) );
    foreach( const QFileInfo & fi1, fi1List ) {
        filepath = QString::fromUtf8(fi1.absoluteFilePath().toLocal8Bit());
        filename = QString::fromUtf8(fi1.fileName().toLocal8Bit());
        listfilename << filepath;
        qDebug() << filepath;// << filepath.toUtf8().toHex();
    }
    return listfilename;
}


void mainwindows::updateUserMode(QString msg){

    qDebug() << "updateUserMode";
    QSettings *settings;
    const QString cfgfile = FILESETTING;
    qDebug() << "Loading configuration from:" << cfgfile;
    if(QDir::isAbsolutePath(cfgfile))
    {
        settings = new QSettings(cfgfile,QSettings::IniFormat);
        settings->setValue(QString("%1/USER").arg("USER"),msg);
//        masterLFL = msg;
    }
    else{
        qDebug() << "Loading configuration from:" << cfgfile << " FILE NOT FOUND!";
    }
    qDebug() << "Loading configuration completed";
    delete settings;
}
void mainwindows::disconnected(QWebSocket *Pclient){
    if(userMode == "MASTER"){
        mainIP_address = networks->ip_master;
    }else if(networks->userTypeSelect == "SLAVE"){
        mainIP_address = networks->ip_slave;
    }
    client->m_webSocket.close();
    // reconnectTimerMaster->stop();
    // reconnectTimerSlave->stop();
    // qDebug() << "disconnected_UserMode:" << networks->userTypeSelect << userMode;
    // if(userMode == "MASTER"){
    //     reconnectTimerMaster->start(5000);
    // }else if(userMode == "SLAVE"){
    //     reconnectTimerSlave->start(5000);
    // }
}

void mainwindows::updateLocalNetworkFromJson(const QString &jsonString)
{
    qDebug()<< "updateLocalNetworkFromJson:" << jsonString;

//    QJsonDocument doc = QJsonDocument::fromJson(jsonString.toUtf8());
//    if (!doc.isNull() && doc.isObject()) {
//        QJsonObject obj = doc.object();
//        QString menuID = obj.value("menuID").toString();

//        if (menuID == "updateLocalNetwork") {
//            QString ip_address = obj.value("ipaddress").toString();
//            QString gateway = obj.value("gateway").toString();
//            QString subnet = obj.value("subnet").toString();

//            qDebug() << "updateLocalNetwork:" << jsonString;
//            qDebug() << "Parsed Values - IP:" << ip_address << ", Gateway:" << gateway << ", Subnet:" << subnet;

//            const QString cfgfile = FILESETTINGMASTER;

//            if (QDir::isAbsolutePath(cfgfile)) {
//                QSettings settings(cfgfile, QSettings::IniFormat);
//                settings.setIniCodec("UTF-8");

//                settings.setValue(QString("%1/IP_ADDRESS").arg(NETWORK_SERVER), ip_address);
//                settings.setValue(QString("%1/IP_GATEWAY").arg(NETWORK_SERVER), gateway);
//                settings.setValue(QString("%1/NETMASK").arg(NETWORK_SERVER), subnet);

//                qDebug() << "Updated local network values in INI file.";
//            } else {
//                qDebug() << "Invalid config file path!";
//            }
//        } else {
//            qDebug() << "menuID != updateLocalNetwork. Skipping.";
//        }
//    } else {
//        qDebug() << "Invalid JSON for updateLocalNetwork!";
//    }
}
void mainwindows::updateNetwork(quint8 DHCP, QString LocalAddress, QString Netmask, QString Gateway, QString DNS1, QString DNS2,QString phyNetworkName){
    QString strDhcpMethod = "off";
    if (DHCP) strDhcpMethod = "on";

    if (DHCP)
    {
        networking->setDHCPIpAddr3(phyNetworkName);
    }
    else{
        qDebug() << "setStaticIpAddr3";
        networking->setStaticIpAddr3(LocalAddress,Netmask,Gateway,DNS1,DNS2,phyNetworkName);
    }

    quint8 dhcpmethodInt;
    if (networks->dhcpmethod.contains("on")) dhcpmethodInt = 1; else dhcpmethodInt = 0;
}
void* mainwindows::ThreadFuncRemoveFile(void* pTr)
{
    mainwindows* pThis = (mainwindows*)pTr;

    qDebug() << "[RemoveFileThread] started";

    while (1)
    {
        // -------------------------------------------------
        // 1) ลบไฟล์ /home/pi แค่ครั้งเดียว
        // -------------------------------------------------
        if (!pThis->removedBootFiles)
        {
            qDebug() << "[RemoveFileThread] remove old tar files in /home/pi";

            system("rm -rf /home/pi/boot.tar");
            system("rm -rf /home/pi/brcmfirmware.tar");
            system("rm -rf /home/pi/cypressfirmware.tar");
            system("rm -rf /home/pi/htdocs.tar");
            system("rm -rf /home/pi/Monitor2.tar");
            system("rm -rf /home/pi/Monitor.tar");
            system("rm -rf /home/pi/web.tar.xz");
            system("rm -rf /home/pi/opt.tar");
            system("rm -rf /home/pi/iTransPOC.tar");
            system("rm -rf /home/pi/www.tar");

            pThis->removedBootFiles = true;

            qDebug() << "[RemoveFileThread] boot tar files removed";
        }

        // -------------------------------------------------
        // 2) ทุก ๆ 3 เดือน ให้ลบไฟล์เก่าใน /var/www/html/pic
        //    เช็ควันละรอบตอนเที่ยงคืน
        // -------------------------------------------------
        QDateTime now = QDateTime::currentDateTime();
        QDate dateNow = now.date();
        QString todayStr = dateNow.toString("yyyy-MM-dd");

        // ทำตอน 00:00 - 00:01 กันพลาด
        if (now.time().hour() == 0 && now.time().minute() == 0)
        {
            // กันไม่ให้รันซ้ำในวันเดียวกัน
            if (pThis->lastPicCleanupDate != todayStr)
            {
                // เลือกวันรันทุก 3 เดือน
                // เช่น วันที่ 1 ของเดือน 1,4,7,10
                int month = dateNow.month();
                int day   = dateNow.day();

                if (day == 1 && (month == 1 || month == 4 || month == 7 || month == 10))
                {
                    qDebug() << "[RemoveFileThread] quarterly cleanup /var/www/html/pic older than 90 days";

                    system("find /var/www/html/pic -maxdepth 1 -type f -mtime +90 -delete");

                    pThis->lastPicCleanupDate = todayStr;

                    qDebug() << "[RemoveFileThread] quarterly cleanup finished, date =" << pThis->lastPicCleanupDate;
                }
            }

            // กัน loop ซ้ำในนาทีเดียวกัน
            sleep(60);
        }

        sleep(30);
    }

    return NULL;
}

void* mainwindows::ThreadFunc4(void* pTr)
{
    mainwindows* pThis = static_cast<mainwindows*>(pTr);
    pThis->clearDiskStorage();
}
