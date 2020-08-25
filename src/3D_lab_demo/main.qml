import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import Demo.ScriptRunner 1.0

Window {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("3D-Lab DEMO")

    ScriptRunner {
        id: scriptRunner
    }

    ColumnLayout {

        anchors.centerIn: parent
        spacing: 10

        Label {
            id: label
            text: scriptRunner.text
            Layout.alignment: Qt.AlignHCenter
            color: scriptRunner.isError ? "red"
                                        : "black"
        }

        Button {
            id: button
            Layout.alignment: Qt.AlignHCenter
            Label {
                anchors.centerIn: parent
                text: qsTr("Click me!")
            }
            onClicked: {
                scriptRunner.trigger()
            }
        }
    }
}
