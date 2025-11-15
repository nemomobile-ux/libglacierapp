/*
 * Copyright (C) 2017-2025 Chupligin Sergey <neochapay@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include "glacierapp.h"
#include "config.h"

#include <QDBusConnection>
#include <QDBusConnectionInterface>
#include <QFileInfo>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QStandardPaths>
#include <QTranslator>
#include <QtQml>
#include <QtQuick/QQuickView>

#ifdef HAVE_CACHE
#include <MDeclarativeCache>
#endif

#ifdef HAS_MLITE
#include <MDConfItem>
#else
#include <QSettings>
#endif

Q_LOGGING_CATEGORY(lcGlacierAppCoreLog, "org.glacier.app", QtWarningMsg)

QGuiApplication* GlacierApp::app(int& argc, char** argv)
{
    setenv("QT_QUICK_CONTROLS_STYLE", "Nemo", 1);

#ifdef HAVE_CACHE
    QGuiApplication* app = MDeclarativeCache::qApplication(argc, argv);
    QLocale::Language lang = static_cast<QLocale::Language>(MDConfItem(QStringLiteral("/nemo/apps/%1/lang").arg(qApp->applicationName())).value(0).toInt())
#else
    QGuiApplication* app = new QGuiApplication(argc, argv);
    QSettings settings;
    QLocale::Language lang = static_cast<QLocale::Language>(settings.value("lang").toInt());
#endif

        QLocale locale
        = QLocale::system();
    if (lang != QLocale::Language::AnyLanguage) {
        locale = QLocale(lang);
    }

    QFileInfo exe = QFileInfo(app->applicationFilePath());
    app->setApplicationName(exe.fileName());

    QTranslator* myappTranslator = new QTranslator(app);
    if (myappTranslator->load(locale, app->applicationName(), QLatin1String("_"), QLatin1String("/usr/share/%1/translations/").arg(app->applicationName()))) {
        qCDebug(lcGlacierAppCoreLog) << "translation.load() success" << locale;
        if (app->installTranslator(myappTranslator)) {
            qCDebug(lcGlacierAppCoreLog) << "installTranslator() success" << locale;
        } else {
            qCDebug(lcGlacierAppCoreLog) << "installTranslator() failed" << locale;
        }
    } else {
        qCDebug(lcGlacierAppCoreLog) << "translation.load() failed" << locale;
    }
    connect(app, &QGuiApplication::aboutToQuit, saveWindowSize);

    if (QCoreApplication::arguments().contains("--prestart") || QCoreApplication::arguments().contains("-p")) {
        app->setQuitOnLastWindowClosed(false);
    }

    QString serviceName = QString("org.glacier.%1").arg(qApp->applicationName().replace("-", "_"));
    QDBusConnection sessionBus = QDBusConnection::sessionBus();
    if (sessionBus.interface()->isServiceRegistered(serviceName)) {
        qCWarning(lcGlacierAppCoreLog) << "Current application run shadow mode. Call and exit.";
        QDBusMessage message = QDBusMessage::createMethodCall(serviceName,
            "/",
            "glacier.app",
            "show");
        sessionBus.call(message);
        QTimer::singleShot(0, qApp, SLOT(quit()));
    }

    return app;
}

QQmlApplicationEngine* GlacierApp::engine(QObject* parent)
{
    static QQmlApplicationEngine* s_engine = nullptr;
    if (!s_engine) {
        s_engine = new QQmlApplicationEngine(parent);
    }
    return s_engine;
}

QQuickWindow* GlacierApp::showWindow(QString rootQMLPath)
{
    QQmlApplicationEngine* engine = GlacierApp::engine(qApp);
    if(rootQMLPath.isEmpty()) {
        QString rcMain(":/" + QCoreApplication::applicationName() + ".qml");
        QFile rcFile(rcMain);

        if (rcFile.exists()) {
            engine->load("qrc" + rcMain);
        } else {
            engine->load(QUrl::fromLocalFile(appDirectory() + QStringLiteral("%1.qml").arg(QCoreApplication::applicationName())));
        }
    } else {
        engine->load(QUrl::fromLocalFile(rootQMLPath));
    }

    if (engine->rootObjects().isEmpty()) {
        qCritical() << "Root object is empty";
    }

    QObject* topLevel = engine->rootObjects().constFirst();
    QQuickWindow* window = qobject_cast<QQuickWindow*>(topLevel);
    engine->rootContext()->setContextProperty("__window", window);

    if (!window) {
        qCritical() << "Top object is not Window!";
        return nullptr;
    }

    /*Load last params of window*/
#ifdef HAS_MLITE
    window->setX((MDConfItem(QStringLiteral("/nemo/apps/%1/size/x").arg(qApp->applicationName()))).value(0).toInt());
    window->setY((MDConfItem(QStringLiteral("/nemo/apps/%1/size/y").arg(qApp->applicationName()))).value(0).toInt());
    window->setWidth((MDConfItem(QStringLiteral("/nemo/apps/%1/size/w").arg(qApp->applicationName()))).value(480).toInt());
    window->setHeight((MDConfItem(QStringLiteral("/nemo/apps/%1/size/h").arg(qApp->applicationName()))).value(480).toInt());
#else
    QSettings settings;
    window->setX(settings.value("size/x", 0).toInt());
    window->setY(settings.value("size/y", 0).toInt());
    window->setWidth(settings.value("size/w", 480).toInt());
    window->setHeight(settings.value("size/h", 640).toInt());

#endif

    if (QCoreApplication::arguments().contains("--prestart") || QCoreApplication::arguments().contains("-p")) {
        qCDebug(lcGlacierAppCoreLog) << "Application run in shadow mode";
    } else {
        window->show();
    }

    return window;
}

QQuickWindow *GlacierApp::showWindow()
{
    return showWindow(QString());
}

void GlacierApp::setLanguage(QLocale::Language lang)
{
#ifdef HAS_MLITE
    MDConfItem(QStringLiteral("/nemo/apps/%1/lang").arg(qApp->applicationName())).set(lang);
#else
    QSettings settings;
    settings.setValue("lang", lang);
#endif
}

void GlacierApp::wipe()
{
    // Remove all configs
#ifdef HAS_MLITE
    QStringList appConfigs = MDConfItem(QStringLiteral("/nemo/apps/%1").arg(qApp->applicationName())).listDirs();
    for (const QString& path : appConfigs) {
        MDConfItem(path).unset();
    }
#endif
    // Remove ~/.config/<APPNAME>
    QDir(QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation)).removeRecursively();
    // Remove ~/.local/share/<APPNAME>
    QDir(QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)).removeRecursively();
    // Remove ~/.cache/<APPNAME>
    QDir(QStandardPaths::writableLocation(QStandardPaths::CacheLocation)).removeRecursively();
}

void GlacierApp::saveWindowSize()
{
    QQmlApplicationEngine* engine = GlacierApp::engine(qApp);
    QObject* topLevel = engine->rootObjects().first();
    QQuickWindow* window = qobject_cast<QQuickWindow*>(topLevel);
#ifdef HAS_MLITE
    MDConfItem(QStringLiteral("/nemo/apps/%1/size/x").arg(qApp->applicationName())).set(window->x());
    MDConfItem(QStringLiteral("/nemo/apps/%1/size/y").arg(qApp->applicationName())).set(window->y());
    MDConfItem(QStringLiteral("/nemo/apps/%1/size/w").arg(qApp->applicationName())).set(window->width());
    MDConfItem(QStringLiteral("/nemo/apps/%1/size/h").arg(qApp->applicationName())).set(window->height());
#else
    QSettings settings;
    settings.setValue("size/x", window->x());
    settings.setValue("size/y", window->y());
    settings.setValue("size/w", window->width());
    settings.setValue("size/h", window->height());
#endif
}
