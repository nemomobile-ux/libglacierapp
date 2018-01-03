/*
 * Copyright (C) 2017 Chupligin Sergey <neochapay@gmail.com>
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

QGuiApplication *GlacierApp::app(int &argc, char **argv)
{
    setenv("QT_QUICK_CONTROLS_STYLE", "Nemo", 1);

    QGuiApplication *app = new QGuiApplication(argc, argv);

    QFileInfo exe = QFileInfo(app->applicationFilePath());
    app->setApplicationName(exe.fileName());

    QTranslator myappTranslator;
    myappTranslator.load(QStringLiteral("/usr/share/%1/translations/%1_%2.qm").arg(app->applicationName()).arg(QLocale::system().name()));
    app->installTranslator(&myappTranslator);

    return app;
}

QQuickWindow *GlacierApp::showWindow()
{
    QQmlApplicationEngine* engine = new QQmlApplicationEngine(qApp);
    engine->load(QUrl::fromLocalFile(QStringLiteral("/usr/share/%1/qml/%1.qml").arg(QCoreApplication::applicationName())));
    if (engine->rootObjects().isEmpty())
    {
        qCritical() << "Root object is empty";
        engine->deleteLater();
        return nullptr;
    }

    QObject *topLevel = engine->rootObjects().first();
    QQuickWindow *window = qobject_cast<QQuickWindow *>(topLevel);

    if (!window) {
        qCritical() << "Top object is not Window!";
        engine->deleteLater();
        return nullptr;
    }

    if (QCoreApplication::arguments().contains("--window") || QCoreApplication::arguments().contains("-w"))
    {
        window->show();
    }
    else
    {
        window->showFullScreen();
    }

    return window;
}
