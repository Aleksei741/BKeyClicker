#include "SaveManager.h"
//------------------------------------------------------------------------------
SaveManager::SaveManager()
{
	settings.setAtomicSyncRequired(false);
}
//------------------------------------------------------------------------------
SaveManager::~SaveManager()
{}
//------------------------------------------------------------------------------
void SaveManager::SaveTimerParameters(const QVector<ButtonFTimer_DType>& Option, const QSettings& settings)
{
	settings.beginGroup("KeyFTimer");
	for (int i = 0; i < Option.size(); ++i)
	{
		settings.setValue(	QString("Activate%1").arg(i),		Option[i].activate);
		settings.setValue(	QString("indexWindow%1").arg(i),	Option[i].n_window);
		settings.setValue(	QString("indexButton%1").arg(i),	Option[i].button);
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
void SaveManager::LoadTimerParameters(QVector<ButtonFTimer_DType>& Option, const QSettings& settings)
{
	settings.beginGroup("KeyFTimer");
	for (int i = 0; i < Option.size(); ++i)
	{
		Option[i].activate = settings.value(QString("Activate%1").arg(i), false).toBool();
		Option[i].n_window = settings.value(QString("indexWindow%1").arg(i), 0).toBool();
		Option[i].button = settings.value(QString("indexButton%1").arg(i), 0).toInt();
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
void SaveManager::SaveConditionsParameters(const QVector<ButtonFCondition_DType>& Option, const QSettings& settings)
{
	settings.beginGroup("KeyFCondition");
	for (int i = 0; i < ParamTimer.size(); ++i)
	{
		settings.setValue(QString("Activate%1").arg(i), ParamCondition[i].activate);
		settings.setValue(QString("indexWindow%1").arg(i), ParamCondition[i].n_window);
		settings.setValue(QString("indexButton%1").arg(i), ParamCondition[i].button);
		settings.setValue(QString("Condition%1").arg(i), ParamCondition[i].condition);
		settings.setValue(QString("PeriodPress%1").arg(i), ParamCondition[i].period);
		settings.setValue(QString("NumPress%1").arg(i), ParamCondition[i].repeat);
		settings.setValue(QString("DelayPress%1").arg(i), ParamCondition[i].pause);
		settings.setValue(QString("Shift%1").arg(i), ParamCondition[i].shift);
		settings.setValue(QString("Ctrl%1").arg(i), ParamCondition[i].ctrl);
		settings.setValue(QString("Alt%1").arg(i), ParamCondition[i].alt);
	}
	settings.endGroup();
}
//------------------------------------------------------------------------------
void SaveManager::LoadConditionsParameters(QVector<ButtonFCondition_DType>& Option, const QSettings& settings)
{
	settings.beginGroup("KeyFCondition");
	for (int i = 0; i < Option.size(); ++i)
	{
		Option[i].activate = settings.value(QString("Activate%1").arg(i), false).toBool();
		Option[i].n_window = settings.value(QString("indexWindow%1").arg(i), 0).toBool();
		Option[i].button = settings.value(QString("indexButton%1").arg(i), 0).toInt();
		Option[i].condition = settings.value(QString("Condition%1").arg(i), 0).toInt();
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
void SaveManager::SaveTimerOptions(QString Path, const QVector<ButtonFTimer_DType>& Option)
{
	settings.beginGroup("KeyFTimer");
	for (int i = 0; i < Option.size(); ++i)
	{
		settings.setValue(QString("Activate%1").arg(i), Option[i].activate);
		settings.setValue(QString("indexWindow%1").arg(i), Option[i].n_window);
		settings.setValue(QString("indexButton%1").arg(i), Option[i].button);
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
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// slots
//------------------------------------------------------------------------------