import QtQuick 2.0
import QtQuick.Dialogs 1.2

Item {
    id: root
    function open() { fileDialogLoad.open() }

    FileDialog {
        id: fileDialogLoad
        modality: Qt.WindowModal
    }
}



