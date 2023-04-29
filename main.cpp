#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQmlContext>

#include "app/core/uicontrolller.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    app.setOrganizationName("orgname");
    app.setOrganizationDomain("orgdomain");

    QQuickView view;
    UIControlller controller;

    view.setSource(QUrl("qrc:/main.qml"));
    view.setTitle("Наиболее встречающиеся слова");
    view.setColor(QColor("#F8F8FF"));
    view.rootContext()->setContextProperty("ControllerLink", &controller);
    view.setResizeMode(QQuickView::SizeRootObjectToView);

#ifdef Q_OS_ANDROID
    view.showFullScreen();
#else
    view.show();
#endif

    return app.exec();
}
