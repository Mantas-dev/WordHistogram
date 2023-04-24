import QtQuick 2.15

Item {
    id : container
    width   : 1600
    height  : 800

    property int    maxValue    : 10
    property string title       : "Наиболее встречающиеся слова"
    property color  barColor    : "#336699"

    ListModel {
        id : testModel

        ListElement {
            word: "слово1"
            count: 1
        }
        ListElement {
            word: "слово2"
            count: 5
        }
        ListElement {
            word: "слово3"
            count: 4
        }
        ListElement {
            word: "слово4"
            count: 3
        }
        ListElement {
            word: "слово5"
            count: 10
        }
        ListElement {
            word: "слово6"
            count: 2
        }
        ListElement {
            word: "слово7"
            count: 3
        }
        ListElement {
            word: "слово8"
            count: 5
        }
        ListElement {
            word: "слово9"
            count: 6
        }
        ListElement {
            word: "слово10"
            count: 8
        }
    }

    Text {
        anchors {
            top             : parent.top
            horizontalCenter: parent.horizontalCenter
            topMargin       : 50
        }
        text: container.title
        font {
            pixelSize   : 24
            bold        : true
        }
    }


    Canvas {
        anchors.fill: parent
        onPaint: {
            let ctx = getContext("2d");
            let step = container.maxValue / 4;

            ctx.font = "bold 16px serif";
            ctx.textAlign = 'center';
            ctx.textBaseline = 'middle';

            ctx.beginPath()

            ctx.moveTo(container.width * 0.063, container.height * 0.188)
            ctx.lineTo(container.width * 0.063, container.height * 0.9375)

            ctx.moveTo(container.width * 0.969, container.height * 0.188)
            ctx.lineTo(container.width * 0.969, container.height * 0.9375)

            for (var i = 1; i <= 5; i++) {
                let currentY = i * (container.height * 0.1875);
                ctx.moveTo(container.width * 0.063, currentY)
                ctx.lineTo(container.width * 0.969, currentY)

                ctx.fillStyle = "black";
                ctx.fillText(Math.round((5 - i) * step),
                             container.width * 0.031, currentY);
            }

            ctx.stroke()
        }
    }

    ListView {
        id : histogramView
        anchors {
            top         : parent.top
            left        : parent.left
            right       : parent.right
            topMargin   : container.height * 0.1875
            leftMargin  : container.width * 0.0938
            rightMargin : container.width * 0.0625
        }
        model       : testModel
        orientation : ListView.Horizontal
        delegate: Item {
            width   : histogramView.width / histogramView.count
            height  : container.height * 0.8125
            Rectangle {
                anchors.bottom  : wordTitle.top
                width           : histogramView.width / histogramView.count
                height          : ((container.height * 0.75) / container.maxValue) * count
                color           : container.barColor
                border.width    : 1
            }

            Text {
                id                  : wordTitle
                anchors.bottom      : parent.bottom
                width               : parent.width
                height              : container.height * 0.0625
                text                : word
                verticalAlignment   : Text.AlignVCenter
                horizontalAlignment : Text.AlignHCenter
                wrapMode            : Text.WrapAtWordBoundaryOrAnywhere
                font.pixelSize      : 14
            }
        }
    }

}
