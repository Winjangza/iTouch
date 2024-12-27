#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <mainwindows.h>
#include <QtWidgets/QApplication>
#include <QtQuick/QQuickView>
#include <QtCore/QDir>
#include <QtQml/QQmlEngine>
#include <QQuickWindow>

//sudo mysql -u root -pOTL324$
int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
    if (qEnvironmentVariableIsEmpty("QTGLESSTREAM_DISPLAY")) {
        qputenv("QT_QPA_EGLFS_PHYSICAL_WIDTH", QByteArray("213"));
        qputenv("QT_QPA_EGLFS_PHYSICAL_HEIGHT", QByteArray("120"));

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    }

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.load(url);
    mainwindows mainwindows;
    QObject *topLevel = engine.rootObjects().value(0);
    QQuickWindow *qmlWindow = qobject_cast<QQuickWindow *>(topLevel);
    QObject::connect(qmlWindow, SIGNAL(qmlCommand(QString)),&mainwindows, SLOT(cppSubmitTextFiled(QString)));
    QObject::connect(&mainwindows,SIGNAL(cppCommand(QVariant)),qmlWindow, SLOT(qmlSubmitTextFiled(QVariant)));
    return app.exec();
}
