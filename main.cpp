#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "rgbhistogram.h"
#include "rgbhistogrammodel.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterType<RgbHistogram>("com.bigcorp.ImageAnalysis", 1, 0, "RgbHistogram");
    qmlRegisterType<RgbHistogramModel>("com.bigcorp.ImageAnalysis", 1, 0, "RgbHistogramModel");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
