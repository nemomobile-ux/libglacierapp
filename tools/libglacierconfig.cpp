/*
 * Copyright (C) 2021 Chupligin Sergey <neochapay@gmail.com>
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


#include <QCoreApplication>
#include <QDebug>
#include <MGConfItem>
#include <QCommandLineParser>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QCommandLineParser parser;
    QCommandLineOption desktopModeOption(QStringList() << "d" << "descktopMode",
                QCoreApplication::translate("main", "Enable/Disable descktop <mode>"),
                QCoreApplication::translate("main", "mode"));
    parser.addOption(desktopModeOption);
    parser.process(app);

    bool currentDesktopMode = MGConfItem(QStringLiteral("/nemo/apps/libglacier/desktopmode")).value(0).toBool();

    QString desktopMode = parser.value(desktopModeOption);
    if(!desktopMode.isEmpty()) {
        if(desktopMode == "true" || desktopMode == "enable" || desktopMode == "on") {
            MGConfItem(QStringLiteral("/nemo/apps/libglacier/desktopmode")).set(true);
            qDebug() << "Window mode enabled";
        } else {
            MGConfItem(QStringLiteral("/nemo/apps/libglacier/desktopmode")).set(false);
            qDebug() << "Window mode disabled";
        }
    } else {
// Just print current values
        qDebug() << " desktop mode is" << currentDesktopMode;
    }

    return EXIT_SUCCESS;
}
