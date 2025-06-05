#include "SaveManager.h"
//------------------------------------------------------------------------------
SaveManager::SaveManager() :
BaseSettings(QCoreApplication::applicationDirPath() + "/config.ini", QSettings::IniFormat)
{
	
}
//------------------------------------------------------------------------------
SaveManager::~SaveManager()
{}
//------------------------------------------------------------------------------
void SaveManager::SaveTimerParameters(const QVector<ButtonFTimer_DType>& Option, QSettings& settings)
{
	settings.beginGroup("KeyFTimer");
	for (int i = 0; i < Option.size(); ++i)
	{
		settings.setValue(	QString("Activate%1").arg(i),		Option[i].activate);
		settings.setValue(	QString("indexWindow%1").arg(i),	static_cast<int>(Option[i].n_window));
		settings.setValue(	QString("indexButton%1").arg(i),	static_cast<int>(Option[i].button));
		settings.setValue(	QString("PeriodPress%1").arg(i),	Option[i].period);
		settings.setValue(	QString("NumPress%1").arg(i),		Option[i].repeat);
		settings.setValue(	QString("DelayPress%1").arg(i),		Option[i].pause);
		settings.setValue(	QString("Shift%1").arg(i),			Option[i].shift);
		settings.setValue(	QString("Ctrl%1").arg(i),			Option[i].ctrl);
		settings.setValue(	QString("Alt%1").arg(i),			Option[i].alt);
	}
	settings.endGroup();
}
//------------------------------------------------------------------------------
void SaveManager::LoadTimerParameters(QVector<ButtonFTimer_DType>& Option, QSettings& settings)
{
	settings.beginGroup("KeyFTimer");
	for (int i = 0; i < Option.size(); ++i)
	{
		Option[i].activate = settings.value(QString("Activate%1").arg(i), false).toBool();
		Option[i].n_window = static_cast<nWindows_DType>(settings.value(QString("indexWindow%1").arg(i), 0).toBool());
		Option[i].button = static_cast<Buttons_DType>(settings.value(QString("indexButton%1").arg(i), 0).toInt());
		Option[i].period = settings.value(QString("PeriodPress%1").arg(i), 1000).toInt();
		Option[i].repeat = settings.value(QString("NumPress%1").arg(i), 1).toInt();
		Option[i].pause = settings.value(QString("DelayPress%1").arg(i), 500).toInt();
		Option[i].shift = settings.value(QString("Shift%1").arg(i), false).toBool();
		Option[i].ctrl = settings.value(QString("Ctrl%1").arg(i), false).toBool();
		Option[i].alt = settings.value(QString("Alt%1").arg(i), false).toBool();
	}
	settings.endGroup();
}
//------------------------------------------------------------------------------
void SaveManager::SaveConditionsParameters(const QVector<ButtonFCondition_DType>& Option, QSettings& settings)
{
	settings.beginGroup("KeyFCondition");
	for (int i = 0; i < Option.size(); ++i)
	{
		settings.setValue(QString("Activate%1").arg(i), Option[i].activate);
		settings.setValue(QString("indexWindow%1").arg(i), static_cast<int>(Option[i].n_window));
		settings.setValue(QString("indexButton%1").arg(i), static_cast<int>(Option[i].button));
		settings.setValue(QString("Condition%1").arg(i), static_cast<int>(Option[i].color_condition));
		settings.setValue(QString("PeriodPress%1").arg(i), Option[i].period);
		settings.setValue(QString("NumPress%1").arg(i), Option[i].repeat);
		settings.setValue(QString("DelayPress%1").arg(i), Option[i].pause);
		settings.setValue(QString("Shift%1").arg(i), Option[i].shift);
		settings.setValue(QString("Ctrl%1").arg(i), Option[i].ctrl);
		settings.setValue(QString("Alt%1").arg(i), Option[i].alt);
	}
	settings.endGroup();
}
//------------------------------------------------------------------------------
void SaveManager::LoadConditionsParameters(QVector<ButtonFCondition_DType>& Option, QSettings& settings)
{
	settings.beginGroup("KeyFCondition");
	for (int i = 0; i < Option.size(); ++i)
	{
		Option[i].activate = settings.value(QString("Activate%1").arg(i), false).toBool();
		Option[i].n_window = static_cast<nWindows_DType>(settings.value(QString("indexWindow%1").arg(i), 0).toBool());
		Option[i].button = static_cast<Buttons_DType>(settings.value(QString("indexButton%1").arg(i), 0).toInt());
		Option[i].color_condition = static_cast<Condition_DType>(settings.value(QString("Condition%1").arg(i), 0).toInt());
		Option[i].period = settings.value(QString("PeriodPress%1").arg(i), 1000).toInt();
		Option[i].repeat = settings.value(QString("NumPress%1").arg(i), 1).toInt();
		Option[i].pause = settings.value(QString("DelayPress%1").arg(i), 500).toInt();
		Option[i].shift = settings.value(QString("Shift%1").arg(i), false).toBool();
		Option[i].ctrl = settings.value(QString("Ctrl%1").arg(i), false).toBool();
		Option[i].alt = settings.value(QString("Alt%1").arg(i), false).toBool();
	}
	settings.endGroup();
}
//------------------------------------------------------------------------------
void SaveManager::SaveAllOptions( 
	const QVector<ButtonFTimer_DType>& ParamTimer, 
	const QVector<ButtonFCondition_DType>& ParamCondition,
	const QString& Path
)
{
	QSettings settings_(Path, QSettings::IniFormat);
	settings_.setAtomicSyncRequired(false);
	//--------------------------------------------------------------------------
	
	//--------------------------------------------------------------------------
	
	//--------------------------------------------------------------------------

	settings_.sync();
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// slots
//------------------------------------------------------------------------------