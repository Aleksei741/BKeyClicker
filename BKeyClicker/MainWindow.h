#pragma once

//include Основные
#include <QApplication>
#include <QWidget>

//include Сайзеры
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QScrollArea>

//include Элементы окна
#include <QLabel>
#include <QPushButton>
#include <QTabWidget>
#include <QCheckBox>
#include <QCheckBox>
#include <QComboBox>
#include <QSpinBox>
#include <QLineEdit>
#include "ListButtonComboBox.h"
#include "ListWindowComboBox.h"
#include "ConditionalComboBox.h"

#include <QFont>
#include <QVariant>

#include "Definitions.h"

constexpr qint8 NumItemsTimerCtrl = 10;

class MainWindow : public QWidget
{
	struct TimerCtrl_s
	{
		QCheckBox* active = nullptr;
		QComboBox* n_window = nullptr;
		QComboBox* button = nullptr;
		QSpinBox* period = nullptr;
		QSpinBox* repeat = nullptr;
		QSpinBox* pause = nullptr;
		QCheckBox* ctrl = nullptr;
		QCheckBox* alt = nullptr;
		QCheckBox* shift = nullptr;
		QLineEdit* counting = nullptr;
	};

	struct PixelCtrl_s
	{
		QCheckBox* active = nullptr;
		QComboBox* n_window = nullptr;
		QComboBox* button = nullptr;
		QLineEdit* set_color = nullptr;
		QComboBox* conditional = nullptr;
		QLineEdit* pixel_color = nullptr;
		QPushButton* set = nullptr;
		QSpinBox* period = nullptr;
		QSpinBox* repeat = nullptr;
		QSpinBox* pause = nullptr;
		QCheckBox* ctrl = nullptr;
		QCheckBox* alt = nullptr;
		QCheckBox* shift = nullptr;
		QLineEdit* counting = nullptr;
	};

	Q_OBJECT

public:
	MainWindow(int timerCount, int pixelCount, QWidget* parent = nullptr);
	~MainWindow();

signals: 
	void elementTimerChanged(const MainWindowSignal_DType signal, const QVariant& value, int rowIndex);
	void elementPixelChanged(const MainWindowSignal_DType signal, const QVariant& value, int rowIndex);
	void clickButtonSetPixel(int rowIndex);

private slots:
	void handleStatusConnection(bool status);

private:

	QVector<TimerCtrl_s> TimerCtrl;
	QVector<PixelCtrl_s> PixelCtrl;

	QFrame* createWidgetsTimers();
	QFrame* createWidgetsPixel();

	QLabel* imageUSBLabel;
	QLabel* imageEthernetLabel;
};