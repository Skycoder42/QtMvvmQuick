import QtQuick 2.8
import QtQuick.Controls 2.1

AppBase {
	id: root

	property var popups: []

	function presentItem(item) {
		return mainStack.presentItem(item);
	}

	function presentPopup(popup) {
		popup.parent = root.contentItem;
		popup.opened.connect(function(){
			opened(popup);
		});
		popup.closed.connect(function() {
			var index = popups.indexOf(popup);
			if(index > -1)
				popups.splice(index, 1);
			closed(popup);
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
		var closed = messageBox.closeAction();

		if(!closed) {
			if(popups.length > 0) {
				popups[popups.length - 1].close();
				closed = true;
			}
		}

		if(!closed)
			closed = mainStack.closeAction();

		close.accepted = !closed;
	}
}
