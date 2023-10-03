#ifndef DBUSADAPTOR_H
#define DBUSADAPTOR_H

#include <QDBusAbstractAdaptor>
#include <QQuickWindow>

class DBusAdaptor : public QDBusAbstractAdaptor {
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "glacier.app")

public:
    explicit DBusAdaptor(QQuickWindow* window);

public slots:
    void show(QStringList args = QStringList());
    void quit(QStringList args = QStringList());

private:
    QQuickWindow* m_window;
};

#endif // DBUSADAPTOR_H
