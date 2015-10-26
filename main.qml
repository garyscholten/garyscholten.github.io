import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1
import com.bigcorp.ImageAnalysis 1.0

ApplicationWindow {
    title: qsTr("Histogram")
    width: 800
    height: 480
    visible: true

    Action {
       id: fileOpenAction
       text: "Open"
       iconSource: "qrc:/document-open.png"
       onTriggered: fileDialog.open()
    }

    FileDialog {
        id: fileDialog
        folder: shortcuts.home + "/RGB-analyzer/pics"
        onAccepted: imageView.source = fileUrl
    }

    menuBar: MenuBar {
        Menu {
            title: qsTr("&File")
            MenuItem {
                text: qsTr("E&xit")
                onTriggered: Qt.quit();
            }
        }
    }

    toolBar: ToolBar {
        RowLayout {
            ToolButton {
                iconSource: "qrc:/document-open.png"
                action: fileOpenAction
            }
            Slider {
                id: binCountSlider
                minimumValue: 1
                maximumValue: 8
                value: 6
                tickmarksEnabled: true
                stepSize: 1
            }
        }
    }

    RgbHistogram {
        id: hist
        imageSource: imageView.source
        binCount: Math.pow(2.0, binCountSlider.value)
        onImageSourceChanged: compute()
        onBinCountChanged: compute()
    }

    RgbHistogramModel {
        id: histModel
        histogram: hist
    }

    SplitView {
        anchors.fill: parent

        Image {
            id: imageView
            fillMode: Image.PreserveAspectFit
            Layout.minimumWidth: 200
        }

        Item {
            Layout.minimumWidth: 200

            TabView {
                anchors.fill: parent
                anchors.margins: 12

                Tab {
                    title: "Table"
                    anchors.margins: 12

                    TableView {
                        model: histModel
                        TableViewColumn {
                            title: "#"
                            width: 45
                            role: "binNumber"
                        }
                        TableViewColumn {
                            title: "Red"
                            width: 60
                            role: "redCount"
                        }
                        TableViewColumn {
                            title: "Green"
                            width: 60
                            role: "greenCount"
                        }
                        TableViewColumn {
                            title: "Blue"
                            width: 60
                            role: "blueCount"
                        }
                    }
                }
                Tab {
                    title: "Histogram"
                    anchors.margins: 12

                    RgbHistogramView {
                        histogramModel: histModel
                    }
                }
            }
        }
    }
}
