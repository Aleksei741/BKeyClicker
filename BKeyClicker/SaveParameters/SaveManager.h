#pragma once
#include <QSettings>
#include <QDebug>
#include <QObject>

#include <memory>

#include "main.h"

class SaveManager : public QObject
{
	Q_OBJECT

public:
	SaveManager();
	~SaveManager();
private:
	void SaveTimerParameters(const QVector<ButtonFTimer_DType>& Option, const QSettings& settings = BaseSettings);
	void LoadTimerParameters(QVector<ButtonFTimer_DType>& Option, const QSettings& settings = BaseSettings);

	QSettings BaseSettings(QCoreApplication::applicationDirPath() + "/config.ini", QSettings::IniFormat);
};

