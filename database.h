#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QtSql>
#include <QString>
#include <QWebSocket>
class Database : public QObject
{
    Q_OBJECT
public:
    explicit Database(QString dbName, QString user, QString password, QString host, QObject *parent = nullptr);
    bool database_createConnection();
    bool passwordVerify(QString password);
    void genHashKey();
    void hashletPersonalize();
    bool checkHashletNotData();
    void insertNewAudioRec(QString filePath, QString radioEvent);
    void updateAudioRec(QString filePath, float avg_level, float max_level);
    bool getLastEventCheckAudio(int time, int percentFault, int lastPttMinute);
    QString getNewFile(int warnPercentFault);
    qint64 getStandbyDuration();
    void removeAudioFile(int lastMin);
    int currentFileID = 0;
    QString loadlog = "load_";
    QString filelog;
    QString logdata;
    int Serial_ID;


signals:
    void audioFault(bool fault);
    void setupinitialize(QString);

    void databaseError();
    void eventmsg(QString);
    void cmdmsg(QString);
    void deletedmydatabase(QString);

public slots:
    void getEventandAlarm(QString msg);
    void DistanceandDetailPhaseA(QString msg);
    void DistanceandDetailPhaseB(QString msg);
    void DistanceandDetailPhaseC(QString msg);
    void getMySqlPhase(QString msg);
    void deletedDataMySQL(QString msg);
//    void emitEvent();

private:
    QSqlDatabase db;
    bool verifyMac();
    QString getPassword();
    qint64 getTimeDuration(QString filePath);
    void getLastEvent();
    void startProject(QString filePath, QString radioEvent);

    QString getSerial();
    QStringList getMac();
    void updateHashTable(QString mac, QString challenge ,QString meta, QString serial, QString password);
    QString mySQL;

private slots:
    void reloadDatabase();
//    void getEventandAlarm(QString msg);
};

#endif // DATABASE_H
