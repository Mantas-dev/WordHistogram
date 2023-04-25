import QtQuick 2.13
import QtQuick.Window 2.13
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.3

import "."

Window  {
    width   : 1600
    height  : 800
    title   : "Наиболее встречающиеся слова"
    color   : "#F8F8FF"

    FileDialog {
        id          : fileDialog
        title       : "Выберите файл"
        nameFilters : [ "Текстовые файлы (*.txt)" ]
        onAccepted  : {
            histogram.visible = true;
            startButton.enabled = true;
        }
    }

    Row {
        id : buttonsPanel
        anchors {
            top         : parent.top
            left        : parent.left
            topMargin   : 15
            leftMargin  : 15
        }
        spacing: 15

        Button {
            id              : openButton
            text            : "Открыть"
            width           : 130
            height          : 50
            font.pixelSize  : 14
            onClicked: {
                fileDialog.open();
            }
        }

        Button {
            id              : startButton
            text            : "Старт"
            width           : 130
            height          : 50
            font.pixelSize  : 14
            enabled         : false
        }
    }


    ProgressBar {
        id : progress
        anchors {
            verticalCenter  : buttonsPanel.verticalCenter
            left            : buttonsPanel.right
            right           : parent.right
            leftMargin      : 20
            rightMargin     : 45
        }
        value: 0

        background: Rectangle {
            implicitHeight  : 50
            color           : "#E6E6E6"
            radius          : 3
        }

        contentItem: Item {
            implicitHeight  : 4

            Rectangle {
                width   : progress.visualPosition * parent.width
                height  : parent.height
                radius  : 2
                color   : "#17A81A"
            }
        }
    }

    Histogram {
        id : histogram
        anchors {
            top     : buttonsPanel.bottom
            left    : parent.left
            right   : parent.right
            bottom  : parent.bottom
        }
        model   : {}
        visible : false
    }
}
