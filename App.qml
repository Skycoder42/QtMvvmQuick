import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Controls.Material 2.1

AppBase {
	id: root

	property var popups: []

	function presentItem(item) {
		return mainStack.presentItem(item);
	}

	function presentPopup(popup) {
		popup.parent = root.contentItem;
		popup.closed.connect(function() {
			var index = popups.indexOf(popup);
			if(index > -1)
				popups.splice(index, 1);
			popup.destroy();
		});
		popup.open();
		popups.push(popup);
		return true;
	}

	function showMessage(result, type, title, text, positiveText, negativeText, neutralText, inputUrl, editProperties) {
		messageBox.showMessageBox(result, type, title, text, positiveText, negativeText, neutralText, inputUrl, editProperties);
	}

	function withdrawItem(item) {
		return mainStack.withdrawItem(item);
	}

	function withdrawPopup(popup) {
		popup.close();
		return true;
	}

	PresentingStackView {
		id: mainStack
	}

	MessageBox {
		id:messageBox
	}

	onClosing: {
		var notClosed = messageBox.closeAction();

		if(notClosed) {
			if(popups.length > 0) {
				popups[popups.length - 1].close();
				notClosed = false;
			}
		}

		if(notClosed)
			notClosed = mainStack.closeAction();

		close.accepted = notClosed;
	}
}
