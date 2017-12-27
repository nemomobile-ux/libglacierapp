import QtQuick 2.6
import QtQuick.Window 2.0
import QtQuick.Controls 1.0
import QtQuick.Controls.Nemo 1.0
import QtQuick.Controls.Styles.Nemo 1.0


ApplicationWindow {
    id: appWindow

    initialPage: Page {
        id: root

        headerTools: HeaderToolsLayout { title: "Example" }

        Column {
            spacing: 40
            anchors.centerIn: parent
            Label {
                text: "Test example of libglacierapp"
            }
        }
    }
}
