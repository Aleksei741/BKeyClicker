#pragma once
#include <QCoreApplication>
#include <QSettings>
#include <QDebug>
#include <QObject>

#include <memory>

#include "main.h"
#include "cCondotoinButton.h"
#include "cTimerButton.h"

class SaveManager : public QObject
{
	Q_OBJECT

public:
	SaveManager();
	~SaveManager();
private:
	void SaveTimerParameters(const QVector<ButtonFTimer_DType>& Option, QSettings& settings);
	void LoadTimerParameters(QVector<ButtonFTimer_DType>& Option, QSettings& settings);
	void SaveConditionsParameters(const QVector<ButtonFCondition_DType>& Option, QSettings& settings);
	void LoadConditionsParameters(QVector<ButtonFCondition_DType>& Option, QSettings& settings);

	void SaveAllOptions(
		const QVector<ButtonFTimer_DType>& ParamTimer,
		const QVector<ButtonFCondition_DType>& ParamCondition,
		const QString& Path
	);

	QSettings BaseSettings;
};

