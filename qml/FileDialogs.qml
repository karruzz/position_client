import QtQuick 2.0
import QtQuick.Dialogs 1.2

Item {
    id: root
    property alias fileUrl: fileDialogLoad.fileUrl

    signal accepted()
    signal rejected()

    function open() { fileDialogLoad.open() }
    function close() { fileDialogLoad.close() }

    FileDialog {
        id: fileDialogLoad
        modality: Qt.WindowModal
        nameFilters: ["Dat File (*.dat)"]

        title: "Choose a file to open"
        selectMultiple: false

        onAccepted: root.accepted()
        onRejected: root.rejected()
    }
}



