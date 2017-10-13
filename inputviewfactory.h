#ifndef INPUTVIEWFACTORY_H
#define INPUTVIEWFACTORY_H

#include <QUrl>
#include <QVariantMap>

class InputViewFactory
{
public:
	InputViewFactory();
	virtual ~InputViewFactory();

	virtual int metaTypeId(const QByteArray &type, const QVariantMap &properties);
	virtual QUrl getInput(const QByteArray &type, const QVariantMap &properties);

	virtual bool addSimpleView(const QByteArray &type, const QUrl &qmlFileUrl);
	template <typename T>
	bool addSimpleView(const QUrl &qmlFileUrl);

private:
	QHash<QByteArray, QUrl> _simpleViews;
};

template<typename T>
bool InputViewFactory::addSimpleView(const QUrl &qmlFileUrl)
{
	return addSimpleView(QMetaType::typeName(qMetaTypeId<T>()), qmlFileUrl);
}

#endif // INPUTVIEWFACTORY_H
