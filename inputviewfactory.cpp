#include "inputviewfactory.h"
#include <QMetaType>

InputViewFactory::InputViewFactory() :
	_simpleViews()
{}

InputViewFactory::~InputViewFactory() {}

int InputViewFactory::metaTypeId(const QByteArray &type, const QVariantMap &properties)
{
	if(type == "string")
		return QMetaType::QString;
	else if(type == "list")
		return metaTypeId(properties.value("_list_data", "string").toByteArray(), properties);
	else
		return QMetaType::type(type);
}

QUrl InputViewFactory::getInput(const QByteArray &type, const QVariantMap &)
{
	if(_simpleViews.contains(type))
		return _simpleViews.value(type);
	else if(type == "string" || type == "QString")
		return QStringLiteral("qrc:/de/skycoder42/qtmvvm/quick/inputs/TextField.qml");
	else if(type == "int")
		return QStringLiteral("qrc:/de/skycoder42/qtmvvm/quick/inputs/SpinBox.qml");
	else if(type == "double")
		return QStringLiteral("qrc:/de/skycoder42/qtmvvm/quick/inputs/DoubleSpinBox.qml");
	else if(type == "list")
		return QStringLiteral("qrc:/de/skycoder42/qtmvvm/quick/inputs/ListEdit.qml");
	else
		return QUrl();
}

bool InputViewFactory::addSimpleView(const QByteArray &type, const QUrl &qmlFileUrl)
{
	_simpleViews.insert(type, qmlFileUrl);
	return true;
}
