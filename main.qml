import QtQuick
import AudioAmplitude 1.0

Window {
    id: root
    width: Screen.width
    height: Screen.width
    visible: true
    title: "Audio Amplitude"

    AudioAmplitude {
        id: audioAmp
    }

    Rectangle {
        id: bg
        anchors.fill: parent
        color: "lightblue"

        Rectangle {
            id: item
            width: Screen.width - 20
            height: 100
            radius: 15
            anchors.centerIn: parent
            color: "#F1908E"

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    audioAmp.getSamples();
                    clicker.visible = false;
                }
            }

            Text {
                id: clicker
                anchors.centerIn: parent
                text: "Click me)"
            }

            Row {
                anchors.centerIn: parent
                spacing: 2
                Repeater {
                    model: audioAmp.samples
                    Rectangle {
                        anchors.verticalCenter: parent.verticalCenter
                        width: 3
                        height: modelData
                        radius: 1
                        color: "blue"
                    }

                }

            }
        }

    }
}
