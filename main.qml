import QtQuick 2.13
import QtQuick.Window 2.13
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.3

import "."

Item  {
    id      : container
    width   : 1600
    height  : 800

    FileDialog {
        id          : fileDialog
        title       : "Выберите файл"
        nameFilters : [ "Текстовые файлы (*.txt)" ]
        onAccepted  : {
            histogram.visible = true;
            ControllerLink.loadFile(fileUrl);
        }
    }

    Button {
        id              : openButton
        anchors {
            top         : parent.top
            left        : parent.left
            topMargin   : container.height * 0.01875
            leftMargin  : container.width * 0.00938
        }
        text            : "Открыть"
        width           : container.width * 0.3
        height          : container.height * 0.063
        font.pixelSize  : 14
        onClicked: {
            fileDialog.open();
        }
    }

    ProgressBar {
        id : progress
        anchors {
            verticalCenter  : openButton.verticalCenter
            left            : openButton.right
            right           : parent.right
            leftMargin      : container.width * 0.00938
            rightMargin     : container.width * 0.00938
        }
        value: ControllerLink.readFileProgress

        background: Rectangle {
            implicitHeight  : container.height * 0.063
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
            top         : progress.bottom
            left        : parent.left
            right       : parent.right
            bottom      : buttonsPanel.top
            bottomMargin: container.height * 0.01875
        }
        model   : ControllerLink.histogramModel
        maxValue: ControllerLink.histogramModel.maxEntriesCount
        visible : false
    }


    Row {
        id : buttonsPanel
        anchors {
            left            : parent.left
            bottom          : parent.bottom
            leftMargin      : container.width * 0.00938
            bottomMargin    : container.height * 0.01875
        }
        spacing:  container.width * 0.00938

        Button {
            id              : startButton
            text            : "Старт"
            width           : (container.width - container.width * 0.038) / 3
            height          : container.height * 0.063
            font.pixelSize  : 14
            enabled         : fileDialog.fileUrl != "" && !ControllerLink.readFileProccessing
            onClicked: {
                ControllerLink.readFile();
            }
        }

        Button {
            id              : pauseButton
            text            : ControllerLink.readFilePaused ? "Возобновить"
                                                            : "Пауза"
            width           : (container.width - container.width * 0.038) / 3
            height          : container.height * 0.063
            font.pixelSize  : 14
            enabled         : ControllerLink.readFileProccessing
            onClicked: {
                if (ControllerLink.readFilePaused)
                    ControllerLink.continueReadFile();
                else
                    ControllerLink.pauseReadFile();
            }
        }

        Button {
            id              : cancelButton
            text            : "Отмена"
            width           : (container.width - container.width * 0.038) / 3
            height          : container.height * 0.063
            font.pixelSize  : 14
            enabled         : ControllerLink.readFileProccessing
            onClicked: {
                ControllerLink.stopReadFile();
            }
        }
    }

}
