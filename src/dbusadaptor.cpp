#include "dbusadaptor.h"
#include "qcoreapplication.h"

#include <QDBusConnection>

DBusAdaptor::DBusAdaptor(QQuickWindow* window)
    : QDBusAbstractAdaptor(window)
    , m_window(window)
{
    QDBusConnection sessionbus = QDBusConnection::sessionBus();
    QString serviceName = QString("org.glacier.%1").arg(qApp->applicationName().replace("-", "_"));

    QDBusConnection::sessionBus().registerService(serviceName);
    if (!QDBusConnection::sessionBus().registerObject("/", m_window)) {
        qWarning() << Q_FUNC_INFO << "Cannot register DBus object!";
    };
}

void DBusAdaptor::show(QStringList args)
{
    Q_UNUSED(args);
    qDebug() << "show window from dbus call";
    m_window->show();
}
