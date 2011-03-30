import QtQuick 1.0

Rectangle {
    //id:playerViewComponent
    property alias text: textView.text
    property alias stateText: stateTextView.text
    function addPath( path ){ pathModel.append({ "path":path }) }
    function clearPaths() { pathModel.clear(); }

    signal pathSelected

    Component{
        id:listDelegate
        Item{
            Text{
                text: path.question
                anchors.fill: parent
                MouseArea{
                    anchors.fill: parent
                    onClicked: pathSelected( path );
                }
            }
        }
    }

    ListModel{
        id: pathModel
    }

    Rectangle{
        x: -297
        y: -165
        width: 600
        height: 400
        Column{
            anchors.fill: parent
            Row{
                height: parent.height * 0.7
                width: parent.width
                Text {
                    id:textView
                    width: parent.width * 0.8
                    text: "main text must be here"
                }
                Text{
                    id:stateTextView
                    width : parent.width * 0.2
                    text: "state text must be here"
                }
            }
            ListView{
                id:pathsView
                height: parent.height * 0.3
                width: parent.width
                model: pathModel
                delegate: listDelegate

            }
        }
    }
}
