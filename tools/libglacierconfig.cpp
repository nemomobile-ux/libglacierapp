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

#include <MGConfItem>
#include <QCommandLineParser>
#include <QCoreApplication>
#include <QDebug>

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);

    QCommandLineParser parser;
    QCommandLineOption desktopModeOption(QStringList() << "d"
                                                       << "desktopMode",
        QCoreApplication::translate("main", "Enable/Disable descktop <mode>"),
        QCoreApplication::translate("main", "mode"));
    parser.addOption(desktopModeOption);
    parser.addHelpOption();
    parser.process(app);

    bool currentDesktopMode = MGConfItem(QStringLiteral("/nemo/apps/libglacier/desktopmode")).value(0).toBool();

    QString desktopMode = parser.value(desktopModeOption);

    if (!desktopMode.isEmpty()) {
        MGConfItem* desktopModeValue = new MGConfItem(QStringLiteral("/nemo/apps/libglacier/desktopmode"));
        if (desktopMode == "true" || desktopMode == "enable" || desktopMode == "on" || desktopMode == "1") {
            desktopModeValue->set(1);
            qDebug() << "Window mode enabled";
        } else if (desktopMode == "false" || desktopMode == "disable" || desktopMode == "off" || desktopMode == "0") {
            desktopModeValue->set(0);
            qDebug() << "Window mode disabled";
        }
        desktopModeValue->sync();
    } else {
        // Just print current values
        qDebug() << " desktop mode is" << currentDesktopMode;
    }

    return EXIT_SUCCESS;
}
