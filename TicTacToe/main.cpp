#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQmlContext>
#include "game.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    Game ticTacToe;

    QQmlApplicationEngine engine;

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    qmlRegisterUncreatableType<Marks>("qml.enums", 1, 0, "Marks", "Cannot instantiate enum type.");

    engine.rootContext()->setContextProperty("game_engine", &ticTacToe);
    engine.rootContext()->setContextProperty("game_board_model", &ticTacToe.game_board_model);

    engine.load(url);
    return app.exec();
}
