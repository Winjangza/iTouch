#include "database.h"
#include <QDateTime>
#include <QStringList>
#include <QString>
#include <QProcess>
#include <QVariant>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonDocument>
#include <typeinfo>
#include <QVariant>
Database::Database(QString dbName, QString user, QString password, QString host, QObject *parent) :
    QObject(parent)
{
    qDebug() << "Connecting to MySQL" << dbName << user << password << host;
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(host);
    db.setDatabaseName(dbName);
    db.setUserName(user);
    db.setPassword(password);

    if (!db.open()) {
        qDebug() << "Database connection failed:" << db.lastError().text();
        return;
    }

    qDebug() << "Database connected successfully!";
}

void Database::getEventandAlarm(QString msg){
//    qDebug() << "Database:" << msg;

    if(msg == "getEventandAlarm"){

        QSqlQuery checkTableQuery(db);
        QString checkTableSQL = QString(
            "SELECT COUNT(*) FROM information_schema.tables "
            "WHERE table_schema = '%1' AND table_name = 'eventandalarm'")
            .arg(db.databaseName());

        if (!checkTableQuery.exec(checkTableSQL)) {
            qDebug() << "Failed to check if table exists:" << checkTableQuery.lastError().text();
            return;
        }

        if (checkTableQuery.next() && checkTableQuery.value(0).toInt() > 0) {
            qDebug() << "Table `eventandalarm` exists. Fetching data...";

            QSqlQuery query(db);
            if (!query.exec("SELECT date, time, event_name, status FROM eventandalarm")) {
                qDebug() << "Query execution failed:" << query.lastError().text();
                return;
            }

            if (query.first()) {
                QString date = query.value("date").toString();
                QString time = query.value("time").toString();
                QString eventName = query.value("event_name").toString();
                QString status = query.value("status").toString();

                QString EventandAlarm = QString("{\"objectName\"    :\"getEventandAlarm\","
                                                "\"Date\"           :\"%1\","
                                                "\"Time\"           :\"%2\","
                                                "\"EventName\"      :\"%3\","
                                                "\"Status\"         :\"%4\""
                                        ).arg(date).arg(time).arg(eventName).arg(status);
                qDebug() << EventandAlarm;
                emit eventmsg(EventandAlarm);
            } else {
                qDebug() << "No data found in `eventandalarm` table.";
            }
        } else {
            qDebug() << "Table `eventandalarm` does not exist.";
        }
    }
}

void Database::getMySqlPhase(QString msg) {

    QSqlQuery query;
    QJsonDocument d = QJsonDocument::fromJson(msg.toUtf8());
    QJsonObject command = d.object();
    QString getCommand = QJsonValue(command["objectName"]).toString();

    if (getCommand.contains("TaggingPhaseA")) {
        if (query.exec("SELECT * FROM DataTagging WHERE Phase = 'A'")) {
            while (query.next()) {
                QVariant statusVar = query.value("status");
                QVariant numListVar = query.value("No");
                QVariant tempNoVar = query.value("temp_no");
                QVariant distanceVar = query.value("Distance(Km)");
                QVariant detailVar = query.value("Detail");
                QVariant phaseVar = query.value("Phase");

                // แปลงตัวแปร
                bool status = statusVar.toInt() != 0; // แปลง 0 เป็น false และอื่นๆ เป็น true
                int num_list = numListVar.toInt();
                int temp_no = tempNoVar.toInt();
                double Distance = distanceVar.toDouble();
                QString Detail = detailVar.toString();
                QString Phase = phaseVar.toString();

                // Debug ค่าของตัวแปร
                qDebug() << "Debug Variables and Types:";
                qDebug() << "status (as bool):" << (status ? "true" : "false") << "type: bool";
                qDebug() << "num_list:" << num_list << "type:" << numListVar.typeName();
                qDebug() << "temp_no:" << temp_no << "type:" << tempNoVar.typeName();
                qDebug() << "Distance:" << Distance << "type:" << distanceVar.typeName();
                qDebug() << "Detail:" << Detail << "type:" << detailVar.typeName();
                qDebug() << "Phase:" << Phase << "type:" << phaseVar.typeName();

                // หากมีปัญหาให้ข้าม
                if (Phase.isEmpty() || Detail.isEmpty()) {
                    qWarning() << "Warning: Empty Phase or Detail. Skipping this row.";
                    continue;
                }

                QString message = QString("{\"objectName\":\"getMySqlPhaseA\", "
                                          "\"status\":%1, "
                                          "\"num_list\":%2, "
                                          "\"temp_no\":%3, "
                                          "\"Distance\":\"%4\", "
                                          "\"Detail\":\"%5\", "
                                          "\"Phase\":\"%6\"}")
                                      .arg(status ? "true" : "false")
                                      .arg(num_list)
                                      .arg(temp_no)
                                      .arg(Distance)
                                      .arg(Detail)
                                      .arg(Phase);

                qDebug() << "Sent message get PhaseA:" << message;
                emit cmdmsg(message);
            }
        } else {
            qDebug() << "Failed to execute query:" << query.lastError().text();
        }
    }else if(getCommand.contains("TaggingPhaseB")) {
        if (query.exec("SELECT * FROM DataTagging WHERE Phase = 'B'")) {
            while (query.next()) {
                bool status = query.value("status").toBool();
                int num_list = query.value("No").toInt(); // ดึงค่าของ No
                int temp_no = query.value("temp_no").toInt();
                double Distance = query.value("Distance(Km)").toDouble();
                QString Detail = query.value("Detail").toString();
                QString Phase = query.value("Phase").toString();

                QString message = QString("{\"objectName\":\"getMySqlPhaseB\", "
                                          "\"status\":%1, "
                                          "\"num_list\":%2, "
                                          "\"temp_no\":%3, "
                                          "\"Distance\":\"%4\", "
                                          "\"Detail\":\"%5\", "
                                          "\"Phase\":\"%6\"}")
                                      .arg(status ? "true" : "false")
                                      .arg(num_list)       // ใส่ค่า num_list
                                      .arg(temp_no)
                                      .arg(Distance)
                                      .arg(Detail)
                                      .arg(Phase);

                qDebug() << "Sent message get PhaseB:" << message;
                emit cmdmsg(message);
            }
        } else {
            qDebug() << "Failed to execute query:" << query.lastError().text();
        }
    }else if(getCommand.contains("TaggingPhaseC")){
        if (query.exec("SELECT * FROM DataTagging WHERE Phase = 'C'")) {
            while (query.next()) {
                bool status = query.value("status").toBool();
                int num_list = query.value("No").toInt(); // ดึงค่าของ No
                int temp_no = query.value("temp_no").toInt();
                double Distance = query.value("Distance(Km)").toDouble();
                QString Detail = query.value("Detail").toString();
                QString Phase = query.value("Phase").toString();

                QString message = QString("{\"objectName\":\"getMySqlPhaseC\", "
                                          "\"status\":%1, "
                                          "\"num_list\":%2, "
                                          "\"temp_no\":%3, "
                                          "\"Distance\":\"%4\", "
                                          "\"Detail\":\"%5\", "
                                          "\"Phase\":\"%6\"}")
                                      .arg(status ? "true" : "false")
                                      .arg(num_list)       // ใส่ค่า num_list
                                      .arg(temp_no)
                                      .arg(Distance)
                                      .arg(Detail)
                                      .arg(Phase);

                qDebug() << "Sent message get PhaseB:" << message;
                emit cmdmsg(message);
            }
        } else {
            qDebug() << "Failed to execute query:" << query.lastError().text();
        }
    }
}


void Database::updateDataBaseDisplay(QString msg) {
    qDebug() << "getMySqlPhaseA:" << msg;
    QSqlQuery query;

    if (query.exec("SELECT * FROM DataTagging")) {
        // ส่งคำสั่งให้ QML ล้างข้อมูลก่อน
        QString clearMessage = "{\"objectName\":\"updateDataDisplay\"}";
        updateTableDisplay(clearMessage);

        // ส่งข้อมูลใหม่ไปยัง QML
        while (query.next()) {
            bool status = query.value("status").toBool();
            int num_list = query.value("No").toInt();
            int temp_no = query.value("temp_no").toInt();
            double Distance = query.value("Distance(Km)").toDouble();
            QString Detail = query.value("Detail").toString();
            QString Phase = query.value("Phase").toString();

            QString message = QString("{\"objectName\":\"updateDataDisplay\", "
                                      "\"status\":%1, "
                                      "\"num_list\":%2, "
                                      "\"temp_no\":%3, "
                                      "\"Distance\":\"%4\", "
                                      "\"Detail\":\"%5\", "
                                      "\"Phase\":\"%6\"}")
                                  .arg(status ? "true" : "false")
                                  .arg(num_list)
                                  .arg(temp_no)
                                  .arg(Distance)
                                  .arg(Detail)
                                  .arg(Phase);

            qDebug() << "Sent message:" << message;
            updateTableDisplay(message);
        }
    } else {
        qDebug() << "Failed to execute query:" << query.lastError().text();
    }
}

void Database::DistanceandDetailPhaseA(QString msg) {
    qDebug() << "DistanceandDetailPhaseA:" << msg;

    // Convert JSON string to QJsonObject
    QJsonDocument d = QJsonDocument::fromJson(msg.toUtf8());
    QJsonObject command = d.object();
    QString getCommand = QJsonValue(command["objectName"]).toString();

    if (getCommand.contains("getDistanceDetailA")) {
        QString phase = QJsonValue(command["PHASE"]).toString();
        double distancecmd = QJsonValue(command["Distance"]).toDouble();
        QString detailcmd = QJsonValue(command["Detail"]).toString();

        qDebug() << "getDistanceDetailA:" << distancecmd << detailcmd << "Phase:" << phase;

        if (phase.isEmpty() || detailcmd.isEmpty()) {
            qDebug() << "Invalid data: Phase or Detail is empty!";
            return;
        }

        QSqlQuery query;

        // Find the most recent temp_no for the specified Phase
        query.prepare("SELECT MAX(temp_no) FROM DataTagging WHERE Phase = :phase");
        query.bindValue(":phase", phase);

        int newTempNo = 1;
        if (!query.exec()) {
            qDebug() << "Failed to execute query:" << query.lastQuery();
            qDebug() << "Error:" << query.lastError().text();
            return;
        }

        if (query.next()) {
            QVariant maxTempNo = query.value(0);
            if (maxTempNo.isValid() && !maxTempNo.isNull()) {
                newTempNo = maxTempNo.toInt() + 1;
            }
        } else {
            qDebug() << "No data found for phase:" << phase;
        }

        // Insert the new data into the DataTagging table
        query.prepare("INSERT INTO DataTagging (status, `Distance(Km)`, Detail, Phase, temp_no) "
                      "VALUES (:status, :distance, :detail, :phase, :temp_no)");

        query.bindValue(":status", 0); // Default status as 0 (false)
        query.bindValue(":distance", distancecmd);
        query.bindValue(":detail", detailcmd);
        query.bindValue(":phase", phase);
        query.bindValue(":temp_no", newTempNo);

        if (!query.exec()) {
            qDebug() << "Failed to insert data:" << query.lastError().text();
            return;
        }

        qDebug() << "Data inserted successfully with temp_no:" << newTempNo;

        // Fetch the latest data by No in the specified phase
        query.prepare("SELECT status, No, `Distance(Km)`, Detail, Phase, temp_no FROM DataTagging WHERE Phase = :phase ORDER BY No DESC LIMIT 1");
        query.bindValue(":phase", phase);

        if (!query.exec()) {
            qDebug() << "Failed to fetch the latest data:" << query.lastError().text();
            return;
        }

        while (query.next()) {
            int statusInt = query.value("status").toInt(); // Get status as integer (0 or 1)
            bool status = (statusInt == 1); // Convert 0 to false, 1 to true
            int num_list = query.value("No").toInt();
            int temp_no = query.value("temp_no").toInt();
            double distance = query.value("Distance(Km)").toDouble();
            QString detail = query.value("Detail").toString();
            QString currentPhase = query.value("Phase").toString();

            // Debugging: Output the fetched data
            qDebug() << "Fetched Data:"
                     << "Status:" << status
                     << "Num_list:" << num_list
                     << "Temp_no:" << temp_no
                     << "Distance:" << distance
                     << "Detail:" << detail
                     << "Phase:" << currentPhase;

            // Construct the message for sending back to QML
            QString message = QString("{\"objectName\":\"getMySqlPhaseA\", "
                                      "\"status\":%1, "
                                      "\"num_list\":%2, "
                                      "\"temp_no\":%3, "
                                      "\"Distance\":\"%4\", "
                                      "\"Detail\":\"%5\", "
                                      "\"Phase\":\"%6\"}")
                                  .arg(status ? "true" : "false")  // If status is true, use "true"
                                  .arg(num_list)
                                  .arg(temp_no)
                                  .arg(distance)
                                  .arg(detail)
                                  .arg(currentPhase);

            qDebug() << "Sent messageA:" << message;

            // Emit the message to QML
            emit cmdmsg(message);
        }
    }
}

// void Database::DistanceandDetailPhaseA(QString msg) {
//     qDebug() << "DistanceandDetailPhaseA:" << msg;

//     // Convert JSON string to QJsonObject
//     QJsonDocument d = QJsonDocument::fromJson(msg.toUtf8());
//     QJsonObject command = d.object();
//     QString getCommand = QJsonValue(command["objectName"]).toString();

//     if (getCommand.contains("getDistanceDetailA")) {
//         QString phase = QJsonValue(command["PHASE"]).toString();
//         double distancecmd = QJsonValue(command["Distance"]).toDouble();
//         QString detailcmd = QJsonValue(command["Detail"]).toString();

//         qDebug() << "getDistanceDetailA:" << distancecmd << detailcmd << "Phase:" << phase;

//         if (phase.isEmpty() || detailcmd.isEmpty()) {
//             qDebug() << "Invalid data: Phase or Detail is empty!";
//             return;
//         }

//         QSqlQuery query;

//         // Find the most recent temp_no for the specified Phase
//         query.prepare("SELECT MAX(temp_no) FROM DataTagging WHERE Phase = :phase");
//         query.bindValue(":phase", phase);

//         int newTempNo = 1;
//         if (!query.exec()) {
//             qDebug() << "Failed to execute query:" << query.lastQuery();
//             qDebug() << "Error:" << query.lastError().text();
//             return;
//         }

//         if (query.next()) {
//             QVariant maxTempNo = query.value(0);
//             if (maxTempNo.isValid() && !maxTempNo.isNull()) {
//                 newTempNo = maxTempNo.toInt() + 1;
//             }
//         } else {
//             qDebug() << "No data found for phase:" << phase;
//         }

//         // Insert the new data into the DataTagging table
//         query.prepare("INSERT INTO DataTagging (status, `Distance(Km)`, Detail, Phase, temp_no) "
//                       "VALUES (:status, :distance, :detail, :phase, :temp_no)");

//         query.bindValue(":status", 0); // Default status as 0 (false)
//         query.bindValue(":distance", distancecmd);
//         query.bindValue(":detail", detailcmd);
//         query.bindValue(":phase", phase);
//         query.bindValue(":temp_no", newTempNo);

//         if (!query.exec()) {
//             qDebug() << "Failed to insert data:" << query.lastError().text();
//             return;
//         }

//         qDebug() << "Data inserted successfully with temp_no:" << newTempNo;

//         // Fetch the latest data by No in the specified phase
//         query.prepare("SELECT * FROM DataTagging WHERE Phase = :phase ORDER BY No DESC LIMIT 1");
//         query.bindValue(":phase", phase);

//         if (!query.exec()) {
//             qDebug() << "Failed to fetch the latest data:" << query.lastError().text();
//             return;
//         }

//         while (query.next()) {
//             int statusInt = query.value("status").toInt(); // Get status as integer (0 or 1)
//             bool status = (statusInt == 1); // Convert 0 to false, 1 to true
//             int num_list = query.value("No").toInt();
//             int temp_no = query.value("temp_no").toInt();
//             double distance = query.value("Distance(Km)").toDouble();
//             QString detail = query.value("Detail").toString();
//             QString currentPhase = query.value("Phase").toString();

//             // Debugging: Output the fetched data
//             qDebug() << "Fetched Data:"
//                      << "Status:" << status
//                      << "Num_list:" << num_list
//                      << "Temp_no:" << temp_no
//                      << "Distance:" << distance
//                      << "Detail:" << detail
//                      << "Phase:" << currentPhase;

//             // Construct the message for sending back to QML
//             QString message = QString("{\"objectName\":\"getMySqlPhaseA\", "
//                                       "\"status\":%1, "
//                                       "\"num_list\":%2, "
//                                       "\"temp_no\":%3, "
//                                       "\"Distance\":\"%4\", "
//                                       "\"Detail\":\"%5\", "
//                                       "\"Phase\":\"%6\"}")
//                                   .arg(status ? "true" : "false")  // If status is true, use "true"
//                                   .arg(num_list)
//                                   .arg(temp_no)
//                                   .arg(distance)
//                                   .arg(detail)
//                                   .arg(currentPhase);

//             qDebug() << "Sent messageA:" << message;

//             // Emit the message to QML
//             emit cmdmsg(message);
//         }
//     }
// }




void Database::DistanceandDetailPhaseB(QString msg){
    qDebug() << "DistanceandDetailPhaseB:" << msg;

    QJsonDocument d = QJsonDocument::fromJson(msg.toUtf8());
    QJsonObject command = d.object();
    QString getCommand = QJsonValue(command["objectName"]).toString();

    if (getCommand.contains("getDistanceDetailB")) {
        QString phase = QJsonValue(command["PHASE"]).toString();
        double distancecmd = QJsonValue(command["Distance"]).toDouble();
        QString detailcmd = QJsonValue(command["Detail"]).toString();

        qDebug() << "getDistanceDetailB:" << distancecmd << detailcmd << "Phase:" << phase;

        QSqlQuery query;
        query.prepare("SELECT MAX(temp_no) FROM DataTagging WHERE Phase = :phase");
        query.bindValue(":phase", phase);

        int newTempNo = 1;
        if (query.exec() && query.next()) {
            QVariant maxTempNo = query.value(0);
            if (maxTempNo.isValid()) {
                newTempNo = maxTempNo.toInt() + 1;
            }
        } else {
            qDebug() << "Failed to fetch max temp_no:" << query.lastError().text();
        }

        query.prepare("INSERT INTO DataTagging (status, `Distance(Km)`, Detail, Phase, temp_no) "
                      "VALUES (:status, :distance, :detail, :phase, :temp_no)");

        query.bindValue(":status", false);
        query.bindValue(":distance", distancecmd);
        query.bindValue(":detail", detailcmd);
        query.bindValue(":phase", phase);
        query.bindValue(":temp_no", newTempNo);

        if (query.exec()) {
            qDebug() << "Data inserted successfully with temp_no:" << newTempNo;
        } else {
            qDebug() << "Failed to insert data:" << query.lastError().text();
        }
    }

}
void Database::DistanceandDetailPhaseC(QString msg){
    qDebug() << "DistanceandDetailPhaseC:" << msg;

    QJsonDocument d = QJsonDocument::fromJson(msg.toUtf8());
    QJsonObject command = d.object();
    QString getCommand = QJsonValue(command["objectName"]).toString();

    if (getCommand.contains("getDistanceDetailC")) {
        QString phase = QJsonValue(command["PHASE"]).toString();
        double distancecmd = QJsonValue(command["Distance"]).toDouble();
        QString detailcmd = QJsonValue(command["Detail"]).toString();

        qDebug() << "getDistanceDetailC:" << distancecmd << detailcmd << "Phase:" << phase;

        QSqlQuery query;
        query.prepare("SELECT MAX(temp_no) FROM DataTagging WHERE Phase = :phase");
        query.bindValue(":phase", phase);

        int newTempNo = 1;
        if (query.exec() && query.next()) {
            QVariant maxTempNo = query.value(0);
            if (maxTempNo.isValid()) {
                newTempNo = maxTempNo.toInt() + 1;
            }
        } else {
            qDebug() << "Failed to fetch max temp_no:" << query.lastError().text();
        }

        query.prepare("INSERT INTO DataTagging (status, `Distance(Km)`, Detail, Phase, temp_no) "
                      "VALUES (:status, :distance, :detail, :phase, :temp_no)");

        query.bindValue(":status", false);
        query.bindValue(":distance", distancecmd);
        query.bindValue(":detail", detailcmd);
        query.bindValue(":phase", phase);
        query.bindValue(":temp_no", newTempNo);

        if (query.exec()) {
            qDebug() << "Data inserted successfully with temp_no:" << newTempNo;
        } else {
            qDebug() << "Failed to insert data:" << query.lastError().text();
        }
    }

}

void Database::updateTablePhaseA(QString msg) {
    qDebug() << "updateTablePhaseA:" << msg;

    QSqlQuery query;
    if (query.exec("SELECT * FROM DataTagging WHERE Phase = 'A'")) {
        while (query.next()) {
            bool status = query.value("status").toBool();
            int num_list = query.value("No").toInt();
            int temp_no = query.value("temp_no").toInt();
            double distance = query.value("Distance(Km)").toDouble();
            QString detail = query.value("Detail").toString();
            QString phase = query.value("Phase").toString();

            // สร้างข้อความใหม่ที่ต้องการส่ง
            QString newMessage = QString("{\"objectName\":\"updatedataTableA\", "
                                         "\"statusA\":%1, "
                                         "\"num_listA\":%2, "
                                         "\"temp_noA\":%3, "
                                         "\"DistanceA\":\"%4\", "
                                         "\"DetailA\":\"%5\", "
                                         "\"PhaseA\":\"%6\"}")
                                     .arg(status ? "true" : "false")
                                     .arg(num_list)
                                     .arg(temp_no)
                                     .arg(distance)
                                     .arg(detail)
                                     .arg(phase);

            // ส่งข้อมูลของแต่ละแถวออกไป
            emit updatedataTableA(newMessage);
        }
    } else {
        qDebug() << "Failed to execute query for Phase A:" << query.lastError().text();
    }
}


void Database::updateTablePhaseB(QString msg) {
    qDebug() << "updateTablePhaseB:" << msg;

    // เก็บ num_list ที่ถูกส่งไปแล้วเพื่อใช้ในการตรวจสอบ
    static QSet<int> sentNumLists;

    QSqlQuery query;
    // ดึงข้อมูลล่าสุดที่มี Phase = 'B'
    if (query.exec("SELECT * FROM DataTagging WHERE Phase = 'B' ORDER BY temp_no DESC LIMIT 1")) {
        if (query.next()) {
            bool status = query.value("status").toBool();
            int num_list = query.value("No").toInt();
            int temp_no = query.value("temp_no").toInt();
            double distance = query.value("Distance(Km)").toDouble();
            QString detail = query.value("Detail").toString();
            QString phase = query.value("Phase").toString();

            // สร้างข้อความใหม่ที่ต้องการส่ง
            QString newMessage = QString("{\"objectName\":\"updatedataTableB\", "
                                         "\"statusB\":%1, "
                                         "\"num_listB\":%2, "
                                         "\"temp_noB\":%3, "
                                         "\"DistanceB\":\"%4\", "
                                         "\"DetailB\":\"%5\", "
                                         "\"PhaseB\":\"%6\"}")
                                     .arg(status ? "true" : "false")
                                     .arg(num_list)
                                     .arg(temp_no)
                                     .arg(distance)
                                     .arg(detail)
                                     .arg(phase);

            // เช็คว่า num_list นี้เคยส่งไปแล้วหรือยัง
            if (!sentNumLists.contains(num_list)) {
                // ถ้า num_list ไม่เคยส่งไปแล้ว ให้ส่งข้อมูลใหม่
                emit updatedataTableB(newMessage);

                // เพิ่ม num_list ที่ส่งไปแล้วเข้าไปใน Set
                sentNumLists.insert(num_list);
            }
        }
    } else {
        qDebug() << "Failed to execute query for Phase B:" << query.lastError().text();
    }
}

void Database::updateTablePhaseC(QString msg) {
    qDebug() << "updateTablePhaseC:" << msg;

    // เก็บ num_list ที่ถูกส่งไปแล้วเพื่อใช้ในการตรวจสอบ
    static QSet<int> sentNumLists;

    QSqlQuery query;
    // ดึงข้อมูลล่าสุดที่มี Phase = 'C'
    if (query.exec("SELECT * FROM DataTagging WHERE Phase = 'C' ORDER BY temp_no DESC LIMIT 1")) {
        if (query.next()) {
            bool status = query.value("status").toBool();
            int num_list = query.value("No").toInt();
            int temp_no = query.value("temp_no").toInt();
            double distance = query.value("Distance(Km)").toDouble();
            QString detail = query.value("Detail").toString();
            QString phase = query.value("Phase").toString();

            // สร้างข้อความใหม่ที่ต้องการส่ง
            QString newMessage = QString("{\"objectName\":\"updatedataTableC\", "
                                         "\"statusC\":%1, "
                                         "\"num_listC\":%2, "
                                         "\"temp_noC\":%3, "
                                         "\"DistanceC\":\"%4\", "
                                         "\"DetailC\":\"%5\", "
                                         "\"PhaseC\":\"%6\"}")
                                     .arg(status ? "true" : "false")
                                     .arg(num_list)
                                     .arg(temp_no)
                                     .arg(distance)
                                     .arg(detail)
                                     .arg(phase);

            // เช็คว่า num_list นี้เคยส่งไปแล้วหรือยัง
            if (!sentNumLists.contains(num_list)) {
                // ถ้า num_list ไม่เคยส่งไปแล้ว ให้ส่งข้อมูลใหม่
                emit updatedataTableC(newMessage);

                // เพิ่ม num_list ที่ส่งไปแล้วเข้าไปใน Set
                sentNumLists.insert(num_list);
            }
        }
    } else {
        qDebug() << "Failed to execute query for Phase C:" << query.lastError().text();
    }
}


void Database::deletedDataMySQLPhaseA(QString msg) {
    qDebug() << "deletedDataMySQLPhaseA:" << msg;

    // แปลงข้อความ JSON เป็น QJsonObject
    QJsonDocument d = QJsonDocument::fromJson(msg.toUtf8());
    QJsonObject command = d.object();

    // ดึงค่าจาก JSON
    QString numListStr = command["num_listA"].toString();
    int list_deviceID = numListStr.toInt();
    bool checkedStates = (command["checkedStates"].toString() == "1" || command["checkedStates"].toBool());

    qDebug() << "Parsed JSON: list_deviceID =" << list_deviceID << ", checkedStates =" << checkedStates;

    if (checkedStates) {
        if (!db.isOpen() && !db.open()) {
            qWarning() << "Database is not open and failed to reopen!";
            emit databaseError();
            return;
        }

        // ตรวจสอบว่ามี Record ที่ตรงกับ No และ Phase หรือไม่
        QSqlQuery checkQuery;
        checkQuery.prepare("SELECT COUNT(*) FROM DataTagging WHERE No = :No AND Phase = 'A'");
        checkQuery.bindValue(":No", list_deviceID);

        if (!checkQuery.exec()) {
            qWarning() << "Failed to execute checkQuery:" << checkQuery.lastError().text();
            return;
        }
        if (checkQuery.next()) {
            int recordCount = checkQuery.value(0).toInt();
            qDebug() << "checkQuery result: recordCount =" << recordCount;

            if (recordCount > 0) {
                // ลบ Record
                QSqlQuery deleteQuery;
                deleteQuery.prepare("DELETE FROM DataTagging WHERE No = :No AND Phase = 'A'");
                deleteQuery.bindValue(":No", list_deviceID);
                    updateTablePhaseA("updatedataTableA");
                if (deleteQuery.exec()) {
                    qDebug() << "Phase A: Record with No =" << list_deviceID << "deleted successfully.";
                    updateTablePhaseA("updatedataTableA");
                } else {
                    qWarning() << "Phase A: ERROR! Failed to delete the record:" << deleteQuery.lastError().text();
                    emit databaseError();
                }
            } else {
                qDebug() << "Phase A: No record found with No =" << list_deviceID;
            }
        }
    } else {
        qDebug() << "Phase A: checkedStates is false. No deletion performed.";
    }
}

void Database::deletedDataMySQLPhaseB(QString msg) {
    qDebug() << "deletedDataMySQLPhaseB:" << msg;

    QJsonDocument d = QJsonDocument::fromJson(msg.toUtf8());
    QJsonObject command = d.object();

    QString numListStr = command["num_listB"].toString();
    int list_deviceID = numListStr.toInt();
    bool checkedStates = (command["checkedStates"].toString() == "1" || command["checkedStates"].toBool());

    if (checkedStates) {
        if (!db.isOpen() && !db.open()) {
            qWarning() << "Failed to open the database!";
            emit databaseError();
            return;
        }

        QSqlQuery checkQuery;
        checkQuery.prepare("SELECT COUNT(*) FROM DataTagging WHERE No = :No AND Phase = 'B'");
        checkQuery.bindValue(":No", list_deviceID);

        if (checkQuery.exec() && checkQuery.next() && checkQuery.value(0).toInt() > 0) {
            QSqlQuery deleteQuery;
            deleteQuery.prepare("DELETE FROM DataTagging WHERE No = :No AND Phase = 'B'");
            deleteQuery.bindValue(":No", list_deviceID);

            if (deleteQuery.exec()) {
                qDebug() << "Phase B: Record with No" << list_deviceID << "deleted successfully.";
            } else {
                qWarning() << "Phase B: ERROR! Failed to delete the record:" << deleteQuery.lastError().text();
                emit databaseError();
            }
        } else {
            qDebug() << "Phase B: No record found with No =" << list_deviceID;
        }
    } else {
        qDebug() << "Phase B: checkedStates is false. No deletion performed.";
    }
}

void Database::deletedDataMySQLPhaseC(QString msg) {
    qDebug() << "deletedDataMySQLPhaseC:" << msg;

    QJsonDocument d = QJsonDocument::fromJson(msg.toUtf8());
    QJsonObject command = d.object();

    QString numListStr = command["num_listC"].toString();
    int list_deviceID = numListStr.toInt();
    bool checkedStates = (command["checkedStates"].toString() == "1" || command["checkedStates"].toBool());

    if (checkedStates) {
        if (!db.isOpen() && !db.open()) {
            qWarning() << "Failed to open the database!";
            emit databaseError();
            return;
        }

        QSqlQuery checkQuery;
        checkQuery.prepare("SELECT COUNT(*) FROM DataTagging WHERE No = :No AND Phase = 'C'");
        checkQuery.bindValue(":No", list_deviceID);

        if (checkQuery.exec() && checkQuery.next() && checkQuery.value(0).toInt() > 0) {
            QSqlQuery deleteQuery;
            deleteQuery.prepare("DELETE FROM DataTagging WHERE No = :No AND Phase = 'C'");
            deleteQuery.bindValue(":No", list_deviceID);

            if (deleteQuery.exec()) {
                qDebug() << "Phase C: Record with No" << list_deviceID << "deleted successfully.";
            } else {
                qWarning() << "Phase C: ERROR! Failed to delete the record:" << deleteQuery.lastError().text();
                emit databaseError();
            }
        } else {
            qDebug() << "Phase C: No record found with No =" << list_deviceID;
        }
    } else {
        qDebug() << "Phase C: checkedStates is false. No deletion performed.";
    }
}




void Database::reloadDatabase()
{
//    system("/etc/init.d/mysql stop");
//    system("/etc/init.d/mysql start");
}

void Database::hashletPersonalize()
{
    QString prog = "/bin/bash";//shell
    QStringList arguments;
    QProcess getAddressProcess;
    QString output;

    QString filename = "/tmp/newhashlet/personalize.sh";
    QString data = QString("#!/bin/bash\n"
                           "su - nano2g -s /bin/bash -c \"hashlet -b /dev/i2c-2 personalize\"\n"
                           "echo $? > /tmp/newhashlet/personalize.txt\n");
    system("mkdir -p /tmp/newhashlet");
    QByteArray dataAyyay(data.toLocal8Bit());
    QFile file(filename);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out << dataAyyay;
    file.close();

    arguments << "-c" << QString("sh /tmp/newhashlet/personalize.sh");
    getAddressProcess.start(prog , arguments);
    getAddressProcess.waitForFinished(1000);
    output = getAddressProcess.readAll();
    arguments.clear();
}

void Database::genHashKey()
{
   QString mac = "", challenge = "", meta = "", password = "", serial = "";
   QStringList macList = getMac();
   if (macList.size() >= 3){
       Q_FOREACH (QString macStr, macList)
       {
           if (macStr.contains("mac")){
               mac = macStr.split(":").at(1);
           }
           else if(macStr.contains("challenge")){
               challenge = macStr.split(":").at(1);
           }
           else if(macStr.contains("meta")){
               meta = macStr.split(":").at(1);
           }
       }
       password = getPassword().replace("\n","");
       serial = getSerial().replace("\n","");
   }

   updateHashTable(mac, challenge, meta, serial, password);
}
bool Database::checkHashletNotData()
{
    QString mac = "", challenge = "", meta = "", password = "", serial = "";
    QString query = QString("SELECT mac, challenge, meta, password, serial  FROM hashlet LIMIT 1");
    if (!db.open()) {
        qWarning() << "c++: ERROR! "  << "database error! database can not open.";
        emit databaseError();
        return false;
    }
    QSqlQuery qry;
    qry.prepare(query);
    if (!qry.exec()){
        qWarning() << "c++: ERROR! "  << qry.lastError();
    }else{
        while (qry.next()) {
            mac         = qry.value(0).toString();
            challenge   = qry.value(1).toString();
            meta        = qry.value(2).toString();
            password    = qry.value(3).toString();
            serial      = qry.value(4).toString();
        }
    }
    db.close();

    return ((mac == "")||(challenge == "")||(meta == "")||(serial == "")||(password == ""));
}

void Database::updateHashTable(QString mac, QString challenge ,QString meta, QString serial, QString password)
{
    if ((mac != "")&(challenge != "")&(meta != "")&(serial != "")&(password != "")){
        QString query = QString("UPDATE hashlet SET mac='%1', challenge='%2', meta='%3', serial='%4', password='%5'")
                .arg(mac).arg(challenge).arg(meta).arg(serial).arg(password);
        if (!db.open()) {
            qWarning() << "c++: ERROR! "  << "database error! database can not open.";
            emit databaseError();
            return ;
        }
        QSqlQuery qry;
        qry.prepare(query);
        if (!qry.exec()){
            qWarning() << "c++: ERROR! "  << qry.lastError();
        }
        db.close();
    }
}

QStringList Database::getMac()
{
    QString prog = "/bin/bash";//shell
    QStringList arguments;
    QProcess getAddressProcess;
    QString output;

    QString filename = "/tmp/newhashlet/getmac.sh";
    QString data = QString("#!/bin/bash\n"
                           "su - nano2g -s /bin/bash -c \"hashlet -b /dev/i2c-2 mac --file /home/nano2g/.hashlet\"\n"
                           "echo $? > /tmp/newhashlet/mac.txt\n");
    system("mkdir -p /tmp/newhashlet");
    QByteArray dataAyyay(data.toLocal8Bit());
    QFile file(filename);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out << dataAyyay;
    file.close();

    arguments << "-c" << QString("sh /tmp/newhashlet/getmac.sh");
    getAddressProcess.start(prog , arguments);
    getAddressProcess.waitForFinished(1000);
    output = getAddressProcess.readAll();
    arguments.clear();
    output = output.replace(" ","");
    return output.split("\n");
}
QString Database::getPassword()
{
    QString prog = "/bin/bash";//shell
    QStringList arguments;
    QProcess getAddressProcess;
    QString output;

    QString filename = "/tmp/newhashlet/getpassword.sh";
    QString data = QString("#!/bin/bash\n"
                           "su - nano2g -s /bin/bash -c \"echo ifz8zean6969** | hashlet -b /dev/i2c-2 hmac\"\n"
                           "echo $? > /tmp/newhashlet/password.txt\n");
    system("mkdir -p /tmp/newhashlet");
    QByteArray dataAyyay(data.toLocal8Bit());
    QFile file(filename);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out << dataAyyay;
    file.close();

    arguments << "-c" << QString("sh /tmp/newhashlet/getpassword.sh");
    getAddressProcess.start(prog , arguments);
    getAddressProcess.waitForFinished(1000);
    output = getAddressProcess.readAll();
    arguments.clear();
    return output;
}
QString Database::getSerial()
{
    QString prog = "/bin/bash";//shell
    QStringList arguments;
    QProcess getAddressProcess;
    QString output;

    QString filename = "/tmp/newhashlet/getserial.sh";
    QString data = QString("#!/bin/bash\n"
                           "su - nano2g -s /bin/bash -c \"hashlet -b /dev/i2c-2 serial-num\"\n"
                           "echo $? > /tmp/newhashlet/password.txt\n");
    system("mkdir -p /tmp/newhashlet");
    QByteArray dataAyyay(data.toLocal8Bit());
    QFile file(filename);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out << dataAyyay;
    file.close();

    arguments << "-c" << QString("sh /tmp/newhashlet/getserial.sh");
    getAddressProcess.start(prog , arguments);
    getAddressProcess.waitForFinished(1000);
    output = getAddressProcess.readAll();
    arguments.clear();
    return output;
}

bool Database::passwordVerify(QString password){
    QString query = QString("SELECT password FROM hashlet LIMIT 1");
    if (!db.open()) {
        qWarning() << "c++: ERROR! "  << "database error! database can not open.";
        emit databaseError();
        return false;
    }
    QString hashPassword;
    QSqlQuery qry;
    qry.prepare(query);
    if (!qry.exec()){
        qDebug() << qry.lastError();
    }else{
        while (qry.next()) {
            hashPassword = qry.value(0).toString();
        }
    }
    db.close();
    QString prog = "/bin/bash";//shell
    QStringList arguments;
    QProcess getAddressProcess;
    QString output;

    arguments.clear();
    arguments << "-c" << QString("echo %1 | hashlet hmac").arg(password);
    getAddressProcess.start(prog , arguments);
    getAddressProcess.waitForFinished(3000);
    output = getAddressProcess.readAll();
    if (output == "") {
        qDebug() << "output == \"\"";
        return false;
    }else if(!output.contains(hashPassword)){
        qDebug() << "output != hashPassword";
        return false;
    }

    system("mkdir -p /etc/ed137");
    if (verifyMac()){
        qDebug() << "mac true";


        if (hashPassword != ""){
            QString filename = "/etc/ed137/checkpass.sh";
            QString data = QString("#!/bin/bash\n"
                                   "su - nano2g -s /bin/bash -c \"echo $1 | hashlet offline-hmac -r $2\"\n"
                                   "echo $? > /etc/ed137/checkpass\n");
            system("mkdir -p /etc/ed137");

            QByteArray dataAyyay(data.toLocal8Bit());
            QFile file(filename);
            file.open(QIODevice::WriteOnly | QIODevice::Text);
            QTextStream out(&file);
            out << dataAyyay;
            file.close();
            arguments.clear();
            arguments << "-c" << QString("sh /etc/ed137/checkpass.sh %1 %2").arg(password).arg(hashPassword);
            getAddressProcess.start(prog , arguments);
            getAddressProcess.waitForFinished(-1);
            output = getAddressProcess.readAll();
            qDebug() << output;

            arguments.clear();
            arguments << "-c" << QString("cat /etc/ed137/checkpass");
            getAddressProcess.start(prog , arguments);
            getAddressProcess.waitForFinished(-1);
            output = getAddressProcess.readAll();
            qDebug() << output;
            system("rm -r /etc/ed137");
            if (output.contains("0\n")){
                return true;
            }
            return false;
        }

    }else{
        qDebug() << "mac false";
    }
    system("rm -r /etc/ed137");
    return false;
}

bool Database::verifyMac(){
    QString query = QString("SELECT mac, challenge FROM hashlet LIMIT 1");
    if (!db.open()) {
        qWarning() << "c++: ERROR! "  << "database error! database can not open.";
        emit databaseError();
        return false;
    }
    QString mac, challenge;
    QSqlQuery qry;
    qry.prepare(query);
    if (!qry.exec()){
        qDebug() << qry.lastError();
    }else{
        while (qry.next()) {
            mac = qry.value(0).toString();
            challenge = qry.value(1).toString();
        }
    }
    db.close();

    QString prog = "/bin/bash";//shell
    QStringList arguments;
    QProcess getAddressProcess;
    QString output;

    QString filename = "/etc/ed137/checkmac.sh";
    QString data = QString("#!/bin/bash\n"
                           "su - nano2g -s /bin/bash -c \"hashlet offline-verify -c $1 -r $2\"\n"
                           "echo $? > /etc/ed137/checkmac\n");
    system("mkdir -p /etc/ed137");
    QByteArray dataAyyay(data.toLocal8Bit());
    QFile file(filename);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out << dataAyyay;
    file.close();

    arguments << "-c" << QString("sh /etc/ed137/checkmac.sh %1 %2").arg(challenge).arg(mac);
    getAddressProcess.start(prog , arguments);
    getAddressProcess.waitForFinished(1000);
    output = getAddressProcess.readAll();

    arguments.clear();
    arguments << "-c" << QString("cat /etc/ed137/checkmac");
    getAddressProcess.start(prog , arguments);
    getAddressProcess.waitForFinished(1000);
    output = getAddressProcess.readAll();
    arguments.clear();

    if (output.contains("0\n"))
        return true;
    return false;
}

bool Database::database_createConnection()
{
    if (!db.open()) {
        qWarning() << "c++: ERROR! "  << "database error! database can not open.";
        //emit databaseError();
        return false;
    }
    db.close();
    qDebug() << "Database connected";    
    return true;
}
qint64 Database::getTimeDuration(QString filePath)
{
#ifdef HWMODEL_JSNANO
    QString query = QString("SELECT timestamp FROM fileCATISAudio WHERE path='%1' LIMIT 1").arg(filePath);
    if (!db.open()) {
        qWarning() << "c++: ERROR! "  << "database error! database can not open.";
        emit databaseError();
        return 0;

    }
    QDateTime timestamp;
    QSqlQuery qry;
    qry.prepare(query);
    if (!qry.exec()){
        qDebug() << qry.lastError();
    }else{
        while (qry.next()) {
            timestamp = qry.value(0).toDateTime();
        }
    }
    db.close();
    qint64 duration = QDateTime::currentDateTime().toSecsSinceEpoch() - timestamp.toSecsSinceEpoch();
    if (duration <= 0) duration=5;
    return duration;
#else
    return 0;
#endif

}
void Database::getLastEvent()
{
#ifdef HWMODEL_JSNANO
    QString lastEvent;
    QDateTime timestamp;
    int timeDuration;
    int id;
    QString query = QString("SELECT timestamp, event, id, duration_sec FROM fileCATISAudio ORDER BY id DESC LIMIT 1");
    if (!db.open()) {
        qWarning() << "c++: ERROR! "  << "database error! database can not open.";
        emit databaseError();
        return ;

    }
    QSqlQuery qry;
    qry.prepare(query);
    if (!qry.exec()){
        qDebug() << qry.lastError();
    }else{
        while (qry.next()) {
            timestamp = qry.value(0).toDateTime();
            lastEvent = qry.value(1).toString();
            id = qry.value(2).toInt();
            timeDuration = qry.value(3).toInt();
        }
    }
    db.close();

    if ((lastEvent == "Standby") & (timeDuration == 0)){
        qint64 duration = QDateTime::currentDateTime().toSecsSinceEpoch() - timestamp.toSecsSinceEpoch();
        QString timeStamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        QString query = QString("UPDATE fileCATISAudio SET duration_sec='%1' WHERE id='%2'").arg(duration).arg(id);
        if (!db.open()) {
            qWarning() << "c++: ERROR! "  << "database error! database can not open.";
            emit databaseError();
            return ;
        }
        QSqlQuery qry;
        qry.prepare(query);
        if (!qry.exec()){
            qDebug() << qry.lastError();
        }
        db.close();
    }
#else
    return;
#endif
}
void Database::startProject(QString filePath, QString radioEvent)
{

#ifdef HWMODEL_JSNANO
    QString timeStamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    QString query = QString("INSERT INTO fileCATISAudio (path, timestamp, duration_sec, event) "
                            "VALUES ('%1', '%2', '%3', '%4')").arg(filePath).arg(timeStamp).arg(0).arg(radioEvent);
    if (!db.open()) {
        qWarning() << "c++: ERROR! "  << "database error! database can not open.";
        emit databaseError();
        return ;
    }
    QSqlQuery qry;
    qry.prepare(query);
    if (!qry.exec()){
        qDebug() << qry.lastError();
    }
    db.close();
#else
    return;
#endif
}

void Database::insertNewAudioRec(QString filePath, QString radioEvent)
{
#ifdef HWMODEL_JSNANO
    if (radioEvent != "Standby")
    {
        getLastEvent();
    }
    QString timeStamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    QString query = QString("INSERT INTO fileCATISAudio (path, timestamp, duration_sec, event) "
                            "VALUES ('%1', '%2', '%3', '%4')").arg(filePath).arg(timeStamp).arg(0).arg(radioEvent);
    if (!db.open()) {
        qWarning() << "c++: ERROR! "  << "database error! database can not open.";
        emit databaseError();
        return ;
    }
    QSqlQuery qry;
    qry.prepare(query);
    if (!qry.exec()){
        qDebug() << qry.lastError();
    }
    db.close();
#else
    return;
#endif
}

void Database::updateAudioRec(QString filePath, float avg_level, float max_level)
{
#ifdef HWMODEL_JSNANO
    qint64 duration = getTimeDuration(filePath);
    QString timeStamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    QString query = QString("UPDATE fileCATISAudio SET duration_sec='%1',avg_level=%2, max_level=%3 WHERE path='%4'").arg(duration).arg(avg_level).arg(max_level).arg(filePath);
    if (!db.open()) {
        qWarning() << "c++: ERROR! "  << "database error! database can not open.";
        emit databaseError();
        return ;
    }
    QSqlQuery qry;
    qry.prepare(query);
    if (!qry.exec()){
        qDebug() << qry.lastError();
    }
    db.close();
#else
    return;
#endif
}
void Database::removeAudioFile(int lastMin)
{
#ifdef HWMODEL_JSNANO
    QString filePath = "";
    QString timestamp = QDateTime::currentDateTime().addSecs(-(60*lastMin)).toString("yyyy-MM-dd hh:mm:ss");
    QString query = QString("SELECT path FROM fileCATISAudio WHERE timestamp<'%1' ORDER BY id ASC").arg(timestamp);
    if (!db.open()) {
        qWarning() << "c++: ERROR! "  << "database error! database can not open.";
        emit databaseError();
        return ;

    }
    QSqlQuery qry;
    qry.prepare(query);
    if (!qry.exec()){
        qDebug() << qry.lastError();
    }else{
        while (qry.next()) {
            filePath = qry.value(0).toString();
            if (filePath.contains("/home/pi/")){
                QString commanRm = QString("rm -f %1*").arg(filePath);
                system(commanRm.toStdString().c_str());
            }
        }
    }
    query = QString("DELETE FROM fileCATISAudio WHERE timestamp<'%1'").arg(timestamp);
    qry.prepare(query);
    if (!qry.exec()){
       qDebug() << qry.lastError();
    }else{
       while (qry.next()) {
           filePath = qry.value(0).toString();
           QString commanRm = QString("rm -f %1*").arg(filePath);
           system(commanRm.toStdString().c_str());
       }
    }
    db.close();
#else
    return;
#endif
}

QString Database::getNewFile(int warnPercentFault)
{
#ifdef HWMODEL_JSNANO
    QString filePath = "";
    QString query = QString("SELECT path, id FROM fileCATISAudio WHERE event='PTT On' AND id>%1 AND avg_level>%2 ORDER BY id ASC LIMIT 1").arg(currentFileID).arg(warnPercentFault);
    if (!db.open()) {
        qWarning() << "c++: ERROR! "  << "database error! database can not open.";
        emit databaseError();
        return "";

    }
    QSqlQuery qry;
    qry.prepare(query);
    if (!qry.exec()){
        qDebug() << qry.lastError();
    }else{
        while (qry.next()) {
            filePath = qry.value(0).toString();
            currentFileID = qry.value(1).toInt();
        }
    }
    db.close();
    return filePath;
#else
    return "";
#endif
}

qint64 Database::getStandbyDuration()
{
#ifdef HWMODEL_JSNANO
    qint64 duration_sec = 0;
    QString query = QString("SELECT duration_sec, id FROM fileCATISAudio WHERE event='Standby' AND id>%1  ORDER BY id ASC LIMIT 1").arg(currentFileID);
    if (!db.open()) {
        qWarning() << "c++: ERROR! "  << "database error! database can not open.";
        emit databaseError();
        return 0;

    }
    QSqlQuery qry;
    qry.prepare(query);
    if (!qry.exec()){
        qDebug() << qry.lastError();
    }else{
        while (qry.next()) {
            duration_sec = qry.value(0).toLongLong();
            currentFileID = qry.value(1).toInt();
        }
    }
    db.close();
    return duration_sec;
#else
    return 0;
#endif
}

bool Database::getLastEventCheckAudio(int time, int percentFault, int lastPttMinute)
{
#ifdef HWMODEL_JSNANO
//    qDebug() << "check Last Event And Audio Fault.";
    float avg_level = 0;
    float max_level = 0;
    float last_avg_level = 0;
    float last_max_level = 0;
    QDateTime timestamp = QDateTime::fromSecsSinceEpoch(0);
    QString refDateTime = QDateTime::currentDateTime().addSecs(-(60*lastPttMinute)).toString("yyyy-MM-dd hh:mm:ss");
    float count = 0;
    QString query = QString("SELECT avg_level, max_level, timestamp FROM fileCATISAudio WHERE event='PTT On' AND timestamp>'%2' ORDER BY timestamp DESC LIMIT %1").arg(time).arg(refDateTime);
    if (!db.open()) {
        qWarning() << "c++: ERROR! "  << "database error! database can not open.";
        emit databaseError();
        return false;

    }
    QSqlQuery qry;
    qry.prepare(query);
    if (!qry.exec()){
        qDebug() << qry.lastError();
    }else{
        while (qry.next()) {
            avg_level += qry.value(0).toFloat();
            max_level += qry.value(1).toFloat();
            last_avg_level = qry.value(0).toFloat();
            last_max_level = qry.value(1).toFloat();
            if (qry.value(2).toDateTime() > timestamp)
                timestamp = qry.value(2).toDateTime();
            count += 1;
        }
    }
    db.close();

    avg_level = avg_level/count;
    max_level = max_level/count;

    if ((last_avg_level >= percentFault) & (QDateTime::currentDateTime().addSecs(-(lastPttMinute*60)) > timestamp)) {
        emit audioFault(false);
        return true;
    }

    if (avg_level < percentFault) {
        emit audioFault(true);
        return false;
    }

    if (QDateTime::currentDateTime().addSecs(-(lastPttMinute*60)) > timestamp) {
        emit audioFault(true);
        return false;
    }
    emit audioFault(false);
    return true;
#else
    return false;
#endif
}
