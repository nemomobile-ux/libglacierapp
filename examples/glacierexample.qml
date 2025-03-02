import QtQuick
import QtQuick.Window
import Nemo
import Nemo.Controls

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
