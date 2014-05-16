import QtQuick 2.2
import QtQuick.Controls 1.1

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Dipylon")

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }

    SplitView {
        id: mainSplitter
        anchors.fill: parent
        orientation: 0

        Flow {
            id: flowMenu
            x: 0
            y: 0

            Row {
                id: rowMainMenu

                Button {
                    id: buttonFile
                    text: qsTr("Files")
                }

                Button {
                    id: buttonExit
                    text: qsTr("Exit")
                    onClicked: Qt.quit();
                }

            }

            Row {
                id: rowSecondaryMenu

                Button {
                    id: buttonSound0
                    text: qsTr("<<")
                }

                Button {
                    id: buttonSound1
                    text: qsTr("<")
                }

                Button {
                    id: buttonSound2
                    text: qsTr(".")
                }

                Button {
                    id: buttonSound3
                    text: qsTr(">")
                }

                Button {
                    id: buttonSound4
                    text: qsTr(">>")
                }

                CheckBox {
                    id: checkBoxPlaySound
                    text: qsTr("sound")
                }

                CheckBox {
                    id: checkBoxShowNotes
                    text: qsTr("notes")
                }

            }

        }

        TextArea {
            id: textSource
            textColor: "#4913e2"
        }

        TextArea {
                id: textCommentary
                textColor: "#d62424"
        }

    }

}
