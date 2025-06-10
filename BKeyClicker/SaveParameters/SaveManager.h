#pragma once
#include <QCoreApplication>
#include <QSettings>
#include <QDebug>
#include <QObject>

#include <memory>

#include "main.h"
#include "cConditionButton.h"
#include "cTimerButton.h"

class SaveManager : public QObject
{
	Q_OBJECT

public:
	SaveManager();
	~SaveManager();

	void DefaultLoadOptions(
		QVector<cTimerButton>& ParamTimer,
		QVector<cConditionButton>& ParamCondition
	);

private:
	static void SaveTimerParameters(const QVector<cTimerButton>& Option, QSettings& settings);
	static void LoadTimerParameters(QVector<cTimerButton>& Option, QSettings& settings);
	static void SaveConditionsParameters(const QVector<cConditionButton>& Option, QSettings& settings);
	static void LoadConditionsParameters(QVector<cConditionButton>& Option, QSettings& settings);
	static bool DecodeNameParam(qint32 num, MainWindowSignal_DType SignalType, QString& name);

	QSettings BaseSettings;

public slots:
	void handleUpdateDefaultParamsFTimer(qint32 num, MainWindowSignal_DType SignalType, const QVariant& value);
	void handleUpdateDefaultParamsFCondition(qint32 num, MainWindowSignal_DType SignalType, const QVariant& value);
};

