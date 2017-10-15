#ifndef QTQMLMVVMBINDING_H
#define QTQMLMVVMBINDING_H

#include <QObject>
#include <QPointer>
#include <QQmlParserStatus>
#include <qtmvvmbinding.h>

class QtQmlMvvmBinding : public QObject, public QQmlParserStatus
{
	Q_OBJECT
	Q_INTERFACES(QQmlParserStatus)

	Q_PROPERTY(QObject* control READ control WRITE setControl NOTIFY controlChanged)
	Q_PROPERTY(QString controlProperty READ controlProperty WRITE setControlProperty NOTIFY controlPropertyChanged)
	Q_PROPERTY(QObject* view READ view WRITE setView NOTIFY viewChanged)
	Q_PROPERTY(QString viewProperty READ viewProperty WRITE setViewProperty NOTIFY viewPropertyChanged)
	Q_PROPERTY(BindingDirection type READ type WRITE setType NOTIFY typeChanged)

public:
	enum BindingDirectionFlag {
		SingleInit = QtMvvmBinding::SingleInit,
		OneWayFromControl = QtMvvmBinding::OneWayFromControl,
		OneWayToControl = QtMvvmBinding::OneWayToControl,
		TwoWay = QtMvvmBinding::TwoWay
	};
	Q_DECLARE_FLAGS(BindingDirection, BindingDirectionFlag)
	Q_FLAG(BindingDirection)

	explicit QtQmlMvvmBinding(QObject *parent = nullptr);

	void classBegin() override;
	void componentComplete() override;

	QObject* control() const;
	QString controlProperty() const;
	QObject* view() const;
	QString viewProperty() const;
	BindingDirection type() const;

public slots:
	void setControl(QObject* control);
	void setControlProperty(QString controlProperty);
	void setView(QObject* view);
	void setViewProperty(QString viewProperty);
	void setType(BindingDirection type);

signals:
	void controlChanged(QObject* control);
	void controlPropertyChanged(QString controlProperty);
	void viewChanged(QObject* view);
	void viewPropertyChanged(QString viewProperty);
	void typeChanged(BindingDirection type);

private:
	QPointer<QtMvvmBinding> _binding;
	bool _completed;

	QObject* _control;
	QString _controlProperty;
	QObject* _view;
	QString _viewProperty;
	BindingDirection _type;

	void resetBinding();
};

#endif // QTQMLMVVMBINDING_H
