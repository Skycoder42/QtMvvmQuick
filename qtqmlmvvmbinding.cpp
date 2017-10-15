#include "qtqmlmvvmbinding.h"

QtQmlMvvmBinding::QtQmlMvvmBinding(QObject *parent) :
	QObject(parent),
	QQmlParserStatus(),
	_binding(nullptr),
	_completed(false),
	_control(nullptr),
	_controlProperty(),
	_view(nullptr),
	_viewProperty(),
	_type(QtMvvmBinding::TwoWay)
{}

void QtQmlMvvmBinding::classBegin() {}

void QtQmlMvvmBinding::componentComplete()
{
	_completed = true;
	resetBinding();
}

QObject *QtQmlMvvmBinding::control() const
{
	return _control;
}

QString QtQmlMvvmBinding::controlProperty() const
{
	return _controlProperty;
}

QObject *QtQmlMvvmBinding::view() const
{
	return _view;
}

QString QtQmlMvvmBinding::viewProperty() const
{
	return _viewProperty;
}

QtQmlMvvmBinding::BindingDirection QtQmlMvvmBinding::type() const
{
	return _type;
}

void QtQmlMvvmBinding::setControl(QObject *control)
{
	if (_control == control)
		return;

	_control = control;
	emit controlChanged(_control);
	resetBinding();
}

void QtQmlMvvmBinding::setControlProperty(QString controlProperty)
{
	if (_controlProperty == controlProperty)
		return;

	_controlProperty = controlProperty;
	emit controlPropertyChanged(_controlProperty);
	resetBinding();
}

void QtQmlMvvmBinding::setView(QObject *view)
{
	if (_view == view)
		return;

	_view = view;
	emit viewChanged(_view);
	resetBinding();
}

void QtQmlMvvmBinding::setViewProperty(QString viewProperty)
{
	if (_viewProperty == viewProperty)
		return;

	_viewProperty = viewProperty;
	emit viewPropertyChanged(_viewProperty);
	resetBinding();
}

void QtQmlMvvmBinding::setType(BindingDirection type)
{
	if (_type == type)
		return;

	_type = type;
	emit typeChanged(_type);
	resetBinding();
}

void QtQmlMvvmBinding::resetBinding()
{
	if(!_completed || !_control || !_view)
		return;

	if(_binding)
		_binding->deleteLater();

	QtMvvmBinding::BindingDirection rType;
	if(_type.testFlag(SingleInit))
		rType.setFlag(QtMvvmBinding::SingleInit);
	if(_type.testFlag(OneWayFromControl))
		rType.setFlag(QtMvvmBinding::OneWayFromControl);
	if(_type.testFlag(OneWayToControl))
		rType.setFlag(QtMvvmBinding::OneWayToControl);
	if(_type.testFlag(TwoWay))
		rType.setFlag(QtMvvmBinding::TwoWay);

	_binding = QtMvvmBinding::bind(_control, qUtf8Printable(_controlProperty),
								   _view, qUtf8Printable(_viewProperty),
								   rType);
}
