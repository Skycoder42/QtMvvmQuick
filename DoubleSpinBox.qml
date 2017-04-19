import QtQuick 2.8
import QtQuick.Controls 2.1
import de.skycoder42.quickextras 2.0

DoubleSpinBox {
	id: edit
	property alias inputValue: edit.dValue
	editable: true
}
