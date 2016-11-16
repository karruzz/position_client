import QtQuick 2.0
import QtQuick.Dialogs 1.2

Item {
    width: 640
    height: 480

    FileDialog {
        id: fileDialogLoad
        onRejected: fileDialogLoad.close();
    }
}



