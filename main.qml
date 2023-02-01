import QtQuick
import AudioAmplitude 1.0

Window {
    id: root
    width: Screen.width
    height: Screen.width
    visible: true
    title: "Audio Amplitude"

    ListModel {
        id: samples
        ListElement { v: 0 }
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
                    audioAmp.getAmplitude();
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
                    model: samples
                    Rectangle {
                        anchors.verticalCenter: parent.verticalCenter
                        width: 3
                        height: v
                        radius: 1
                        color: "blue"
                    }

                }

            }
        }

        AudioAmplitude {
            id: audioAmp
            onSamplesChanged: (_samples) => {
                    samples.clear()
                    for(let i = 0; i < _samples.length; i++) {
                        let newItem = {}
                        // Multiply by scaleFactor and assign to the model
                        newItem.v = _samples[i];
                        samples.append(newItem)
                    }
            }
        }
    }
}
