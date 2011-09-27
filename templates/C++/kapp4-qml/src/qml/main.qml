import Qt 4.7

Rectangle {
    id: kcfg_sillyLabel
    width: 400
    height: 400
    
    signal clicked
    
    Text {
        objectName: "kcfg_col_foreground"
        id: kcfg_col_foreground
        text: "Click me to quit!"
        font.pointSize: 16
        anchors.centerIn: parent
        
    }
	
        MouseArea {
        anchors.fill: parent
        onClicked: kcfg_sillyLabel.clicked()
    }
}

