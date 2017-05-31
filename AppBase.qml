import QtQuick 2.8
import QtQuick.Controls 2.1
import de.skycoder42.qtmvvm.quick 1.0

ApplicationWindow {
	id: root
	visible: true
	width: 360
	height: 520

	signal opened(var item);
	signal closed(var item);

	function presentItem(item) {
		//present the item
		//opened(item)
		return false;
	}

	function presentPopup(popup) {
		//present the popup
		//opened(popup)
		return false;
	}

	function showMessage(result, type, title, text, positiveText, negativeText, neutralText, inputUrl, editProperties) {
		result.complete(MessageResult.NegativeResult, undefined);
	}

	function withdrawItem(item) {
		//close the item
		//closed(item)
		return false;
	}

	function withdrawPopup(popup) {
		//close the popup
		//closed(popup)
		return false;
	}

	Component.onCompleted: QuickPresenter.qmlPresenter = root

	PresenterProgress {
		z: 0
	}
}
