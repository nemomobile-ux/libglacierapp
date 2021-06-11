/*
 * Copyright (C) 2017-2021 Chupligin Sergey <neochapay@gmail.com>
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

#include <QFileInfo>
#include <QGuiApplication>
#include <QtQuick/QQuickView>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QTranslator>
#include <QtQml>
#include <QQmlContext>
#include <QDebug>

#ifdef HAVE_CACHE
#include <MDeclarativeCache>
#endif

#ifdef HAS_MLITE5
#include <MGConfItem>
#else
#include <QSettings>
#endif

QGuiApplication *GlacierApp::app(int &argc, char **argv)
{
    setenv("QT_QUICK_CONTROLS_STYLE", "Nemo", 1);

#ifdef HAVE_CACHE
    QGuiApplication *app = MDeclarativeCache::qApplication(argc, argv);
#else
    QGuiApplication *app = new QGuiApplication(argc, argv);
#endif

    QFileInfo exe = QFileInfo(app->applicationFilePath());
    app->setApplicationName(exe.fileName());

    QTranslator myappTranslator;
    myappTranslator.load(QStringLiteral("/usr/share/%1/translations/%1_%2.qm").arg(app->applicationName()).arg(QLocale::system().name()));
    app->installTranslator(&myappTranslator);

    connect(app,&QGuiApplication::aboutToQuit, saveWindowSize);

    return app;
}

QQmlApplicationEngine *GlacierApp::engine(QObject *parent)
{
    static QQmlApplicationEngine* s_engine = nullptr;
    if (!s_engine)
    {
        s_engine = new QQmlApplicationEngine(parent);
    }
    return s_engine;
}

QQuickWindow *GlacierApp::showWindow()
{
    QQmlApplicationEngine* engine = GlacierApp::engine(qApp);
    engine->load(QUrl::fromLocalFile(QStringLiteral("/usr/share/%1/qml/%1.qml").arg(QCoreApplication::applicationName())));
    if (engine->rootObjects().isEmpty())
    {
        qCritical() << "Root object is empty";
    }

    QObject *topLevel = engine->rootObjects().first();
    QQuickWindow *window = qobject_cast<QQuickWindow *>(topLevel);
    engine->rootContext()->setContextProperty("__window", window);

    if (!window)
    {
        qCritical() << "Top object is not Window!";
        return nullptr;
    }
//Add GLACIER_FORCE_WINDOW_MODE=1 into /var/lib/compositor/*.conf to run all app in window mode
    bool forceWindowMode = false;
    if(qgetenv("GLACIER_FORCE_WINDOW_MODE") == "1"){
        forceWindowMode = true;
    }
#ifdef HAS_MLITE5
//Check desktop mode in mlite config
    if(MGConfItem(QStringLiteral("/nemo/apps/libglacier/desktopmode")).value(0).toBool() == true){
        forceWindowMode = true;
    }
#endif

    if(QCoreApplication::arguments().contains("--prestart") || QCoreApplication::arguments().contains("-p"))
    {
        qDebug() << "Application run in shadow mode";
    }
    else{
        if (QCoreApplication::arguments().contains("--window")
                || QCoreApplication::arguments().contains("-w")
                || forceWindowMode)
        {
            /*Load last params of window*/
#ifdef HAS_MLITE5
            window->setX((MGConfItem(QStringLiteral("/nemo/apps/%1/size/x").arg(qApp->applicationName()))).value(0).toInt());
            window->setY((MGConfItem(QStringLiteral("/nemo/apps/%1/size/y").arg(qApp->applicationName()))).value(0).toInt());
            window->setWidth((MGConfItem(QStringLiteral("/nemo/apps/%1/size/w").arg(qApp->applicationName()))).value(480).toInt());
            window->setHeight((MGConfItem(QStringLiteral("/nemo/apps/%1/size/h").arg(qApp->applicationName()))).value(480).toInt());
#else
            QSettings settings;
            window->setX(settings.value("size/x",0).toInt());
            window->setY(settings.value("size/y",0).toInt());
            window->setWidth(settings.value("size/w",480).toInt());
            window->setHeight(settings.value("size/h",640).toInt());

#endif
            window->show();
        }
        else
        {
            window->showFullScreen();
        }
    }
    return window;
}

void GlacierApp::saveWindowSize()
{
    QQmlApplicationEngine* engine = GlacierApp::engine(qApp);
    QObject *topLevel = engine->rootObjects().first();
    QQuickWindow *window = qobject_cast<QQuickWindow *>(topLevel);
#ifdef HAS_MLITE5
    MGConfItem(QStringLiteral("/nemo/apps/%1/size/x").arg(qApp->applicationName())).set(window->x());
    MGConfItem(QStringLiteral("/nemo/apps/%1/size/y").arg(qApp->applicationName())).set(window->y());
    MGConfItem(QStringLiteral("/nemo/apps/%1/size/w").arg(qApp->applicationName())).set(window->width());
    MGConfItem(QStringLiteral("/nemo/apps/%1/size/h").arg(qApp->applicationName())).set(window->height());
#else
    QSettings settings;
    settings.setValue("size/x",window->x());
    settings.setValue("size/y",window->y());
    settings.setValue("size/w",window->width());
    settings.setValue("size/h",window->height());
#endif
}
