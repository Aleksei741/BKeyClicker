#include "MainWindow.h"

MainWindow::MainWindow(QWidget* parent)
	: QWidget(parent)
{
	
	QPushButton* btnAddTimerKey;

	setWindowIcon(QIcon(":/icon1.ico"));

	QVBoxLayout* layerGeneral = new QVBoxLayout(this);

	//Поле состояния 
	//-----------------------------------------------------------------------------------
	QHBoxLayout* layerStatus = new QHBoxLayout();

	layerGeneral->addLayout(layerStatus, 0);

	//-----------------------------------------------------------------------------------
	//Поле кнопок
	QTabWidget* tabAction = new QTabWidget();
	tabAction->setMinimumSize(QSize(320, 180));

	//Нажатие кнопок по таймеру
	{
		// Прокручиваемая область
		QScrollArea* scrollArea = new QScrollArea(this);
		scrollArea->setWidgetResizable(true);
		scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

		// Вложенный виджет внутри scroll
		QWidget* tabContent = new QWidget(this);
		QVBoxLayout* tabTimerLayout = new QVBoxLayout(tabContent);
		tabTimerLayout->setContentsMargins(0, 0, 0, 0);
		tabTimerLayout->setSpacing(0);
		tabContent->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
	
		btnAddTimerKey = new QPushButton("&+");
		btnAddTimerKey->setFixedSize(QSize(25, 25));
		tabTimerLayout->addWidget(btnAddTimerKey, 0, Qt::AlignLeft);
		

		for (qsizetype i = 0; i < 10; ++i)
		{
			QWidget* ButtonField = new QWidget(this);
			QHBoxLayout* itemLayer = new QHBoxLayout(ButtonField);

			QCheckBox* active = new QCheckBox();
			active->setText(QString(""));
			itemLayer->addWidget(active);

			TimerCtrl_s TimerCtrl_;
			TimerCtrl_.active = active;

			TimerCtrl.append(TimerCtrl_);

			ButtonField->setLayout(itemLayer);
			tabTimerLayout->addWidget(ButtonField);
		}

		tabContent->setLayout(tabTimerLayout);
		scrollArea->setWidget(tabContent); // установить содержимое

		tabAction->addTab(scrollArea, "&Таймер"); // добавить scrollArea как виджет во вкладку
	}
	layerGeneral->addWidget(tabAction, 1);


	setLayout(layerGeneral);
	

	show();
	
}

MainWindow::~MainWindow() {}