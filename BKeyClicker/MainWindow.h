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

#include <QFont>

constexpr qint8 NumItemsTimerCtrl = 10;

class MainWindow : public QWidget
{
	struct TimerCtrl_s
	{
		QCheckBox* active;
		QComboBox* n_window;
		QComboBox* button;
		QSpinBox* period;
		QSpinBox* repeat;
		QSpinBox* pause;
		QCheckBox* ctrl;
		QCheckBox* alt;
		QCheckBox* shift;
		QLabel* counting;
	};
	
	Q_OBJECT
public:
	MainWindow(QWidget* parent = nullptr);
	~MainWindow();
private slots:

private:
	QVector<TimerCtrl_s> TimerCtrl;
};
