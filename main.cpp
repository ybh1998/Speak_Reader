#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "reader.h"
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QTranslator trans;
    if(trans.load(QString(":/%1.qm").arg(QLocale::system().name()))){
        app.installTranslator(&trans);
    }
    qmlRegisterType<Reader>("ybh1998.Reader",1,0,"Reader");
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    return app.exec();
}
