import QtQuick 2.15

Item {
    id      : container
    width   : 1600
    height  : 800

    property int    maxValue    : 10
    property string title       : "Наиболее встречающиеся слова"

    property alias  model       : histogramView.model

    ListModel {
        id : testModel

        ListElement {
            word: "слово1"
            count: 1
            itemColor: "#336699"
        }
        ListElement {
            word: "слово2"
            count: 5
            itemColor: "#336699"
        }
        ListElement {
            word: "слово3"
            count: 4
            itemColor: "#336699"
        }
        ListElement {
            word: "слово4"
            count: 3
            itemColor: "#336699"
        }
        ListElement {
            word: "слово5"
            count: 10
            itemColor: "#336699"
        }
        ListElement {
            word: "слово6"
            count: 2
            itemColor: "#336699"
        }
        ListElement {
            word: "слово7"
            count: 3
            itemColor: "#336699"
        }
        ListElement {
            word: "слово8"
            count: 5
            itemColor: "#336699"
        }
        ListElement {
            word: "слово9"
            count: 6
            itemColor: "#336699"
        }
        ListElement {
            word: "слово10"
            count: 8
            itemColor: "#336699"
        }
        ListElement {
            word: "слово11"
            count: 8
            itemColor: "#336699"
        }
        ListElement {
            word: "слово12"
            count: 8
            itemColor: "#336699"
        }
        ListElement {
            word: "слово13"
            count: 8
            itemColor: "#336699"
        }
        ListElement {
            word: "слово14"
            count: 8
            itemColor: "#336699"
        }
        ListElement {
            word: "слово15"
            count: 8
            itemColor: "#336699"
        }
    }

    Text {
        anchors {
            top             : parent.top
            topMargin       : container.height * 0.0625
        }
        text                : container.title
        width               : parent.width
        horizontalAlignment : Text.AlignHCenter
        wrapMode            : Text.WordWrap
        font {
            pixelSize   : 24
            bold        : true
        }
    }


    Canvas {
        id          : canvas
        anchors.fill: parent

        onPaint: {
            let ctx = getContext("2d");
            let step = container.maxValue / 4;

            ctx.font = "bold 16px serif";
            ctx.textAlign = 'center';
            ctx.textBaseline = 'middle';

            ctx.clearRect(0, 0, container.width, container.height);

            ctx.beginPath()

            ctx.moveTo(container.width * 0.063, container.height * 0.188)
            ctx.lineTo(container.width * 0.063, container.height * 0.9375)

            ctx.moveTo(container.width * (0.9375 - (legendList.width / container.width)), container.height * 0.188)
            ctx.lineTo(container.width * (0.9375 - (legendList.width / container.width)), container.height * 0.9375)

            for (var i = 1; i <= 5; i++) {
                let currentY = i * (container.height * 0.1875);
                ctx.moveTo(container.width * 0.063, currentY)
                ctx.lineTo(container.width * (0.9375 - (legendList.width / container.width)), currentY)

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
            right       : legendList.left
            bottom      : parent.bottom
            topMargin   : container.height * 0.1875
            leftMargin  : container.width * 0.0938
            rightMargin : container.width * 0.0938
        }
        model       : testModel
        orientation : ListView.Horizontal
        delegate: Item {
            width   : histogramView.width / histogramView.count
            height  : container.height * 0.75
            Rectangle {
                anchors.bottom  : parent.bottom
                width           : histogramView.width / histogramView.count
                height          : ((container.height * 0.75) / container.maxValue) * count
                color           : itemColor
                border.width    : 2
                border.color    : itemColor
            }
        }
    }

    ListView {
        id : legendList
        anchors {
            top             : parent.top
            bottom          : parent.bottom
            right           : parent.right
            topMargin       : container.height * 0.1875
            rightMargin     : container.width * 0.00938
            bottomMargin    : container.height * 0.0625

        }
        model   : histogramView.model
        spacing : container.height * 0.01875
        delegate: Item {
            width   : wordColor.width + wordTitle.contentWidth + wordTitle.anchors.leftMargin
            height  : container.height * 0.01875
            onWidthChanged: {
                legendList.width = Math.max(legendList.width, width)
            }

            Rectangle {
                id                      : wordColor
                anchors.verticalCenter  : parent.verticalCenter
                width                   : container.width * 0.00938
                height                  : container.height * 0.01875
                color                   : itemColor
            }

            Text {
                id : wordTitle
                anchors {
                    verticalCenter  : parent.verticalCenter
                    left            : wordColor.right
                    leftMargin      : container.width * 0.00938
                }
                text                : word
                verticalAlignment   : Text.AlignVCenter
                horizontalAlignment : Text.AlignHCenter
                wrapMode            : Text.WrapAtWordBoundaryOrAnywhere
                font.pixelSize      : 14
            }
        }

        onCountChanged: {
            if (count == 0)
                width = 0;
        }
    }


    onMaxValueChanged: {
        canvas.requestPaint();
    }
}
