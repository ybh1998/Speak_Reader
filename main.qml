import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1
import ybh1998.Reader 1.0

ApplicationWindow {
    title: qsTr("Speak Reader")
    width: 640
    height: 480
    visible: true
    Reader {
        id: reader
        onSelect_Changed: {
            reader_txt.select(begin, end)
            if (begin == end) {
                start_button.text = qsTr("Start")
                reader.read_stop()
                pause_button.text = qsTr("Pause")
                pause_button.enabled = false
            }
        }
    }
    Timer {
        interval: 2000
        running: true
        repeat: true
        onTriggered: {
            reader.position_save(reader_txt.cursorPosition)
        }
    }
    FileDialog {
        id: open_dialog
        nameFilters: ["Text files (*.txt)", "All files (*)"]
        title: qsTr("Please choose your text file")
        onAccepted: {
            reader.read(fileUrl)
        }
    }
    ColumnLayout {
        anchors.margins: 5
        anchors.fill: parent
        RowLayout {
            Button {
                text: qsTr("Open")
                onClicked: {
                    start_button.text = qsTr("Start")
                    reader.read_stop()
                    pause_button.text = qsTr("Pause")
                    pause_button.enabled = false
                    open_dialog.open()
                }
            }
            Button {
                id: start_button
                text: qsTr("Start")
                onClicked: {
                    if (text === qsTr("Start")) {
                        text = qsTr("Stop")
                        reader.read_start()
                        pause_button.enabled = true
                    } else {
                        text = qsTr("Start")
                        pause_button.text = qsTr("Pause")
                        pause_button.enabled = false
                        reader.read_stop()
                    }
                }
            }
            Button {
                id: pause_button
                enabled: false
                text: qsTr("Pause")
                onClicked: {
                    if (text === qsTr("Resume")) {
                        text = qsTr("Pause")
                        reader.read_resume()
                    } else {
                        text = qsTr("Resume")
                        reader.read_pause()
                    }
                }
            }
            Button {
                text: qsTr("Select")
                onClicked: {
                    if (text === qsTr("Select")) {
                        text = qsTr("Finish")
                        reader_txt.selectByMouse = true
                    } else {
                        text = qsTr("Select")
                        reader_txt.selectByMouse = false
                    }
                }
            }
            Label {
                text: qsTr("Cursor:%1 ").arg(reader_txt.cursorPosition)
            }
            Label {
                text: qsTr("Progress:%%1 ").arg((reader_txt.cursorPosition/reader_txt.text.length).toFixed(2))
            }
        }
        RowLayout {
            Label {
                text: qsTr("Speed:%1").arg(speed_slider.value)
            }
            Slider {
                id: speed_slider
                value: 0
                minimumValue: -5
                maximumValue: 5
                stepSize: 1
                onValueChanged: reader.rate_change(value)
            }
            Label {
                text: qsTr("Volume:%1").arg(volume_slider.value)
            }
            Slider {
                id: volume_slider
                value: 80
                minimumValue: 0
                maximumValue: 100
                stepSize: 5
                onValueChanged: reader.volume_change(value)
            }
            Label {
                text: qsTr("Size:%1").arg(size_slider.value)
            }
            Slider {
                id: size_slider
                value: 24
                minimumValue: 10
                maximumValue: 40
                stepSize: 2
            }
        }
        TextArea {
            id: reader_txt
            menu: null
            text: reader.text
            anchors.margins: 5
            Layout.fillHeight: true
            Layout.fillWidth: true
            readOnly: true
            selectByKeyboard: true
            selectByMouse: false
            font.pointSize: size_slider.value
            onCursorPositionChanged: reader.position_set(cursorPosition)
        }
    }
}
