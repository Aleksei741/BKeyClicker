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
void SaveManager::SaveTimerParameters(const QVector<cTimerButton>& Option, QSettings& settings)
{
	settings.beginGroup("KeyFTimer");
	for (int i = 0; i < Option.size(); ++i)
	{
		settings.setValue(	QString("Activate%1").arg(i),		Option[i].getActive());
		settings.setValue(	QString("indexWindow%1").arg(i),	static_cast<int>(Option[i].getNWindow()));
		settings.setValue(	QString("indexButton%1").arg(i),	static_cast<int>(Option[i].getIndexButton()));
		settings.setValue(	QString("PeriodPress%1").arg(i),	Option[i].getPeriod());
		settings.setValue(	QString("NumPress%1").arg(i),		Option[i].getRepeat());
		settings.setValue(	QString("DelayPress%1").arg(i),		Option[i].getPause());
		settings.setValue(	QString("Shift%1").arg(i),			Option[i].getShift());
		settings.setValue(	QString("Ctrl%1").arg(i),			Option[i].getCtrl());
		settings.setValue(	QString("Alt%1").arg(i),			Option[i].getAlt());
	}
	settings.endGroup();
}
//------------------------------------------------------------------------------
void SaveManager::LoadTimerParameters(QVector<cTimerButton>& Option, QSettings& settings)
{
	settings.beginGroup("KeyFTimer");
	for (int i = 0; i < Option.size(); ++i)
	{
		Option[i].setActive(settings.value(QString("Activate%1").arg(i), false).toBool());
		Option[i].setNWindow(static_cast<nWindows_DType>(settings.value(QString("indexWindow%1").arg(i), 0).toInt()));
		Option[i].setIndexButton(static_cast<Buttons_DType>(settings.value(QString("indexButton%1").arg(i), 0).toInt()));
		Option[i].setPeriod(settings.value(QString("PeriodPress%1").arg(i), 1000).toInt());
		Option[i].setRepeat(settings.value(QString("NumPress%1").arg(i), 1).toInt());
		Option[i].setPause(settings.value(QString("DelayPress%1").arg(i), 500).toInt());
		Option[i].setShift(settings.value(QString("Shift%1").arg(i), false).toBool());
		Option[i].setCtrl(settings.value(QString("Ctrl%1").arg(i), false).toBool());
		Option[i].setAlt(settings.value(QString("Alt%1").arg(i), false).toBool());
	}
	settings.endGroup();
}
//------------------------------------------------------------------------------
void SaveManager::SaveConditionsParameters(const QVector<cConditionButton>& Option, QSettings& settings)
{
	settings.beginGroup("KeyFCondition");
	for (int i = 0; i < Option.size(); ++i)
	{
		settings.setValue(QString("Activate%1").arg(i), Option[i].getActive());
		settings.setValue(QString("indexWindow%1").arg(i), static_cast<int>(Option[i].getNWindow()));
		settings.setValue(QString("indexButton%1").arg(i), static_cast<int>(Option[i].getIndexButton()));
		settings.setValue(QString("Condition%1").arg(i), static_cast<int>(Option[i].getCondition()));
		settings.setValue(QString("PeriodPress%1").arg(i), Option[i].getPeriod());
		settings.setValue(QString("NumPress%1").arg(i), Option[i].getRepeat());
		settings.setValue(QString("DelayPress%1").arg(i), Option[i].getPause());
		settings.setValue(QString("Shift%1").arg(i), Option[i].getShift());
		settings.setValue(QString("Ctrl%1").arg(i), Option[i].getCtrl());
		settings.setValue(QString("Alt%1").arg(i), Option[i].getAlt());
	}
	settings.endGroup();
}
//------------------------------------------------------------------------------
void SaveManager::LoadConditionsParameters(QVector<cConditionButton>& Option, QSettings& settings)
{
	settings.beginGroup("KeyFCondition");
	for (int i = 0; i < Option.size(); ++i)
	{
		Option[i].setActive(settings.value(QString("Activate%1").arg(i), false).toBool());
		Option[i].setNWindow(static_cast<nWindows_DType>(settings.value(QString("indexWindow%1").arg(i), 0).toInt()));
		Option[i].setIndexButton(static_cast<Buttons_DType>(settings.value(QString("indexButton%1").arg(i), 0).toInt()));
		Option[i].setCondition(static_cast<Condition_DType>(settings.value(QString("Condition%1").arg(i), 0).toInt()));
		Option[i].setPeriod(settings.value(QString("PeriodPress%1").arg(i), 1000).toInt());
		Option[i].setRepeat(settings.value(QString("NumPress%1").arg(i), 1).toInt());
		Option[i].setPause(settings.value(QString("DelayPress%1").arg(i), 500).toInt());
		Option[i].setShift(settings.value(QString("Shift%1").arg(i), false).toBool());
		Option[i].setCtrl(settings.value(QString("Ctrl%1").arg(i), false).toBool());
		Option[i].setAlt(settings.value(QString("Alt%1").arg(i), false).toBool());
	}
	settings.endGroup();
}
//------------------------------------------------------------------------------
bool SaveManager::DecodeNameParam(qint32 num, MainWindowSignal_DType SignalType, QString& name_param)
{
	bool ret = true;

	switch (SignalType)
	{
	case MainWindowSignal_DType::Active:
		name_param = QString("Activate%1").arg(num);
		break;

	case MainWindowSignal_DType::Window:
		name_param = QString("indexWindow%1").arg(num);
		break;

	case MainWindowSignal_DType::Button:
		name_param = QString("indexButton%1").arg(num);
		break;

	case MainWindowSignal_DType::Period:
		name_param = QString("PeriodPress%1").arg(num);
		break;

	case MainWindowSignal_DType::Repeate:
		name_param = QString("NumPress%1").arg(num);
		break;

	case MainWindowSignal_DType::Pause:
		name_param = QString("DelayPress%1").arg(num);
		break;

	case MainWindowSignal_DType::Shift:
		name_param = QString("Shift%1").arg(num);
		break;

	case MainWindowSignal_DType::Ctrl:
		name_param = QString("Ctrl%1").arg(num);
		break;

	case MainWindowSignal_DType::Alt:
		name_param = QString("Alt%1").arg(num);
		break;

	case MainWindowSignal_DType::Conditional:
		name_param = QString("Condition%1").arg(num);
		break;

	default:
		ret = false;
	}

	return ret;
}
//------------------------------------------------------------------------------
void SaveManager::DefaultLoadOptions(
	QVector<cTimerButton>& ParamTimer,
	QVector<cConditionButton>& ParamCondition
)
{
	LoadTimerParameters(ParamTimer, BaseSettings);
	LoadConditionsParameters(ParamCondition, BaseSettings);
}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// slots
//------------------------------------------------------------------------------
void SaveManager::handleUpdateDefaultParamsFTimer(qint32 num, 
	MainWindowSignal_DType SignalType, const QVariant& value)
{
	QString name_param;

	if (DecodeNameParam(num, SignalType, name_param))
	{
		BaseSettings.beginGroup("KeyFTimer");
		BaseSettings.setValue(name_param, value);
		BaseSettings.endGroup();
		qDebug() << "SaveManager KeyFTimer save " << name_param << " value " << value;
	}	
}
//------------------------------------------------------------------------------
void SaveManager::handleUpdateDefaultParamsFCondition(qint32 num,
	MainWindowSignal_DType SignalType, const QVariant& value)
{
	QString name_param;

	if (DecodeNameParam(num, SignalType, name_param))
	{
		BaseSettings.beginGroup("KeyFCondition");
		BaseSettings.setValue(name_param, value);
		BaseSettings.endGroup();
		qDebug() << "SaveManager KeyFCondition save " << name_param << " value " << value;
	}
}