import QtQuick
import AudioAmplitude 1.0

Window {
    width: Screen.width
    height: Screen.width
    visible: true
    title: "Audio Amplitude"

    Rectangle {
        id: bg
        anchors.fill: parent
        color: "lightblue"

        Rectangle {
            id: item
            width: 250
            height: 50
            anchors.centerIn: parent
            color: "red"

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    audioAmp.getAmplitude();
                    console.log(audioAmp.samplesArr[0])
                }
            }
        }

        AudioAmplitude {
            id: audioAmp

        }
    }
}
