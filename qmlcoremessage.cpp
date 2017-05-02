#include "qmlcoremessage.h"
#include <coremessage.h>

QmlCoreMessage::QmlCoreMessage(QJSEngine *engine, QObject *parent) :
	QObject(parent),
	_engine(engine)
{}

void QmlCoreMessage::information(const QString &title, const QString &text, QJSValue onResult, const QString &okText)
{
	if(onResult.isCallable()) {
		CoreMessage::information(title, text, [onResult](){
			QJSValue(onResult).call();
		}, okText);
	} else
		CoreMessage::information(title, text, {}, okText);
}

void QmlCoreMessage::question(const QString &title, const QString &text, QJSValue onResult, const QString &yesText, const QString &noText)
{
	if(onResult.isCallable()) {
		CoreMessage::question(title, text, [onResult](bool yes){
			QJSValue(onResult).call({yes});
		}, yesText, noText);
	} else
		CoreMessage::question(title, text, {}, yesText, noText);
}

void QmlCoreMessage::warning(const QString &title, const QString &text, QJSValue onResult, const QString &okText)
{
	if(onResult.isCallable()) {
		CoreMessage::warning(title, text, [onResult](){
			QJSValue(onResult).call();
		}, okText);
	} else
		CoreMessage::warning(title, text, {}, okText);
}

void QmlCoreMessage::critical(const QString &title, const QString &text, QJSValue onResult, const QString &okText)
{
	if(onResult.isCallable()) {
		CoreMessage::critical(title, text, [onResult](){
			QJSValue(onResult).call();
		}, okText);
	} else
		CoreMessage::critical(title, text, {}, okText);
}

void QmlCoreMessage::about(const QString &content, bool includeCompany, const QUrl &companyUrl, bool includeQtVersion)
{
	CoreMessage::about(content, includeCompany, companyUrl, includeQtVersion);
}

void QmlCoreMessage::getInput(const QString &title, const QString &text, const QString inputType, QJSValue onResult, const QVariant &defaultValue, const QVariantMap &editProperties, const QString &okText, const QString &cancelText)
{
	if(onResult.isCallable()) {
		auto engine = _engine;
		CoreMessage::getInput(title, text, inputType.toUtf8().constData(), [engine, onResult](QVariant result){
			QJSValue(onResult).call({engine->toScriptValue(result)});//TODO proper type detection
		}, defaultValue, editProperties, okText, cancelText);
	} else
		CoreMessage::getInput(title, text, inputType.toUtf8().constData(), {}, defaultValue, editProperties, okText, cancelText);
}

void QmlCoreMessage::getInput(const QString &title, const QString &text, int inputType, QJSValue onResult, const QVariant &defaultValue, const QVariantMap &editProperties, const QString &okText, const QString &cancelText)
{
	if(onResult.isCallable()) {
		auto engine = _engine;
		CoreMessage::getInput(title, text, inputType, [engine, onResult](QVariant result){
			QJSValue(onResult).call({engine->toScriptValue(result)});//TODO proper type detection
		}, defaultValue, editProperties, okText, cancelText);
	} else
		CoreMessage::getInput(title, text, inputType, {}, defaultValue, editProperties, okText, cancelText);
}
