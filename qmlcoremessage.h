#ifndef QMLCOREMESSAGE_H
#define QMLCOREMESSAGE_H

#include <QObject>
#include <QJSEngine>
#include <QJSValue>
#include <QUrl>
#include <QVariant>

class QmlCoreMessage : public QObject
{
	Q_OBJECT

public:
	QmlCoreMessage(QJSEngine *engine, QObject *parent = nullptr);

public slots:
	void information(const QString &title,
					 const QString &text,
					 QJSValue onResult = {},
					 const QString &okText = {});
	void question(const QString &title,
				  const QString &text,
				  QJSValue onResult = {},
				  const QString &yesText = {},
				  const QString &noText = {});
	void warning(const QString &title,
				 const QString &text,
				 QJSValue onResult = {},
				 const QString &okText = {});
	void critical(const QString &title,
				  const QString &text,
				  QJSValue onResult = {},
				  const QString &okText = {});
	QT_DEPRECATED void about(const QString &content,
							 bool includeCompany = true,
							 const QUrl &companyUrl = QUrl(),
							 bool includeQtVersion = true);
	void getInput(const QString &title,
				  const QString &text,
				  const QString inputType,
				  QJSValue onResult = {},
				  const QVariant &defaultValue = {},
				  const QVariantMap &editProperties = {},
				  const QString &okText = {},
				  const QString &cancelText = {});
	void getInput(const QString &title,
				  const QString &text,
				  int inputType,
				  QJSValue onResult = {},
				  const QVariant &defaultValue = {},
				  const QVariantMap &editProperties = {},
				  const QString &okText = {},
				  const QString &cancelText = {});

private:
	QJSEngine *_engine;
};

#endif // QMLCOREMESSAGE_H
