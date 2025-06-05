#include "MainWindow.h"
//------------------------------------------------------------------------------
MainWindow::MainWindow(int timerCount, int pixelCount, QWidget* parent)
	: QWidget(parent)
{
	TimerCtrl = QVector<TimerCtrl_s>(timerCount);
	PixelCtrl = QVector<PixelCtrl_s>(pixelCount);
	//-----------------------------------------------------------------------------------
	setWindowTitle("Кликер");
	setObjectName("KAMzila");
	setWindowIcon(QIcon(":/icon1.ico"));
	
	QVBoxLayout* layerGeneral = new QVBoxLayout(this);
	
	//-----------------------------------------------------------------------------------
	//Поле состояния 
	QHBoxLayout* layerStatus = new QHBoxLayout();

	//------------------------------------
	//Картинки состояния
	QVBoxLayout* layerimage = new QVBoxLayout();
		
	QPixmap pixmapUSB(":/usb.png");
	pixmapUSB = pixmapUSB.scaled(30, 30, Qt::KeepAspectRatio);

	QPixmap pixmapEthernet(":/ethernet.png");
	pixmapEthernet = pixmapEthernet.scaled(30, 30, Qt::KeepAspectRatio);

	imageUSBLabel = new QLabel();
	imageUSBLabel->setPixmap(pixmapUSB);
	imageUSBLabel->setAttribute(Qt::WA_TranslucentBackground);
	imageUSBLabel->setStyleSheet("background: transparent;");
	imageUSBLabel->setFixedSize(pixmapUSB.size());
	imageUSBLabel->raise();  // Поднять над другими, но не блокировать
	imageUSBLabel->setFixedSize(30, 30);
	layerimage->addWidget(imageUSBLabel);

	imageEthernetLabel = new QLabel();
	imageEthernetLabel->setPixmap(pixmapEthernet);
	imageEthernetLabel->setAttribute(Qt::WA_TranslucentBackground);
	imageEthernetLabel->setStyleSheet("background: transparent;");
	imageEthernetLabel->setFixedSize(pixmapEthernet.size());
	imageEthernetLabel->raise();  // Поднять над другими, но не блокировать
	imageEthernetLabel->setFixedSize(30, 30);
	layerimage->addWidget(imageEthernetLabel);	

	layerStatus->addLayout(layerimage, 0);

	
	//------------------------------------

	layerGeneral->addLayout(layerStatus, 0);

	//-----------------------------------------------------------------------------------
	//Поле кнопок
	QTabWidget* tabAction = new QTabWidget();
	tabAction->setMinimumSize(QSize(320, 180));

	//Нажатие кнопок по таймеру
	tabAction->addTab(createWidgetsTimers(), "&Таймер"); // добавить scrollArea как виджет во вкладку

	//Нажатие кнопок по таймеру и пикселям
	tabAction->addTab(createWidgetsPixel(), "&Пиксель"); // добавить scrollArea как виджет во вкладку

	layerGeneral->addWidget(tabAction, 1);


	setLayout(layerGeneral);
	

	show();
	
}
//------------------------------------------------------------------------------
MainWindow::~MainWindow() {}
//------------------------------------------------------------------------------
QFrame* MainWindow::createWidgetsTimers()
{
	int cnt;

	// Прокручиваемая область
	QScrollArea* scrollArea = new QScrollArea(this);
	scrollArea->setWidgetResizable(true);
	scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	scrollArea->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);

	// Вложенный виджет внутри scroll
	QWidget* tabContent = new QWidget(this);
	QGridLayout* tabTimerLayout = new QGridLayout(tabContent);
	tabTimerLayout->setContentsMargins(5, 5, 2, 2);
	tabTimerLayout->setSpacing(5);

	cnt = 0;
	tabTimerLayout->addWidget(new QLabel("Вкл"), 0, ++cnt, Qt::AlignCenter);
	tabTimerLayout->itemAtPosition(0, cnt)->widget()->setToolTip("Включает компонент");

	tabTimerLayout->addWidget(new QLabel("Окно"), 0, ++cnt, Qt::AlignCenter);
	tabTimerLayout->itemAtPosition(0, cnt)->widget()->setToolTip("Номер активного окна, в котором активируются события");

	tabTimerLayout->addWidget(new QLabel("Кнопка"), 0, ++cnt, Qt::AlignCenter);
	tabTimerLayout->itemAtPosition(0, cnt)->widget()->setToolTip("Эмулируемая клавиша клавиатуры. L0-L9 - клавиши NumLock");

	tabTimerLayout->addWidget(new QLabel("Период"), 0, ++cnt, Qt::AlignCenter);
	tabTimerLayout->itemAtPosition(0, cnt)->widget()->setToolTip("Промежут времени в мс, через который кнопка будет повторно нажата");

	tabTimerLayout->addWidget(new QLabel("Повтор"), 0, ++cnt, Qt::AlignCenter);
	tabTimerLayout->itemAtPosition(0, cnt)->widget()->setToolTip("Сколько раз нажать кнопку, если пришло время нажимать кнопку");

	tabTimerLayout->addWidget(new QLabel("Пауза"), 0, ++cnt, Qt::AlignCenter);
	tabTimerLayout->itemAtPosition(0, cnt)->widget()->setToolTip("Промежут времени в мс, в течени которого будет запрещена любая уэмуляция нажатия кнопок");

	tabTimerLayout->addWidget(new QLabel("Отсчет"), 0, ++cnt, Qt::AlignCenter);
	tabTimerLayout->itemAtPosition(0, cnt)->widget()->setToolTip("До следующей эмуляции нажатия, мс");

	tabTimerLayout->addWidget(new QLabel("Ctrl"), 0, ++cnt, Qt::AlignCenter);
	tabTimerLayout->itemAtPosition(0, cnt)->widget()->setToolTip("ЭМуляция кнопки с нажатым Ctrl");

	tabTimerLayout->addWidget(new QLabel("Alt"), 0, ++cnt, Qt::AlignCenter);
	tabTimerLayout->itemAtPosition(0, cnt)->widget()->setToolTip("ЭМуляция кнопки с нажатым Alt");

	tabTimerLayout->addWidget(new QLabel("Shift"), 0, ++cnt, Qt::AlignCenter);
	tabTimerLayout->itemAtPosition(0, cnt)->widget()->setToolTip("ЭМуляция кнопки с нажатым Shift");

	//tabTimerLayout->setColumnStretch(0, 1);
	//tabTimerLayout->setColumnStretch(11, 1);
	for (int row = 2; row <= cnt-3; ++row) 
		tabTimerLayout->setColumnStretch(row, 1);

	tabTimerLayout->setColumnMinimumWidth(0, 5);
	tabTimerLayout->setColumnMinimumWidth(cnt+1, 5);

	for (int row = 0; row < TimerCtrl.size(); ++row)
	{
		auto& element = TimerCtrl[row];
		cnt = 1;

		element.active = new QCheckBox();
		element.active->setText(QString(""));
		tabTimerLayout->addWidget(element.active, row + 1, cnt++, Qt::AlignCenter);

		element.n_window = new ListWindowComboBox();		
		tabTimerLayout->addWidget(element.n_window, row + 1, cnt++, Qt::AlignVCenter);

		element.button = new ListButtonComboBox();
		element.button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
		tabTimerLayout->addWidget(element.button, row + 1, cnt++, Qt::AlignVCenter);

		element.period = new QSpinBox();
		element.period->setRange(1, 7200000);
		element.period->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
		tabTimerLayout->addWidget(element.period, row + 1, cnt++, Qt::AlignVCenter);

		element.repeat = new QSpinBox();
		element.repeat->setRange(1, 100);
		element.repeat->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
		tabTimerLayout->addWidget(element.repeat, row + 1, cnt++, Qt::AlignVCenter);

		element.pause = new QSpinBox();
		element.pause->setRange(1, 300000);
		element.pause->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
		tabTimerLayout->addWidget(element.pause, row + 1, cnt++, Qt::AlignVCenter);

		element.counting = new QLineEdit();
		element.counting->setReadOnly(true);
		element.counting->setMinimumWidth(50);
		element.counting->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
		tabTimerLayout->addWidget(element.counting, row + 1, cnt++, Qt::AlignVCenter);

		element.ctrl = new QCheckBox();
		element.ctrl->setText(QString(""));
		tabTimerLayout->addWidget(element.ctrl, row + 1, cnt++, Qt::AlignCenter);

		element.alt = new QCheckBox();
		element.alt->setText(QString(""));
		tabTimerLayout->addWidget(element.alt, row + 1, cnt++, Qt::AlignCenter);

		element.shift = new QCheckBox();
		element.shift->setText(QString(""));
		tabTimerLayout->addWidget(element.shift, row + 1, cnt++, Qt::AlignCenter);

		connect(element.active, &QCheckBox::checkStateChanged, this, [this, row](Qt::CheckState state)
			{
				qDebug() << "MainWindow Timer active " << row << ": " << state;
				emit elementTimerChanged(MainWindowSignal_DType::Active, static_cast<int>(state), row);
			}
		);

		connect(element.n_window, QOverload<int>::of(&ListWindowComboBox::currentIndexChanged), this, [this, row, element](const int index)
			{
				qDebug() << "MainWindow Timer n_window " << row << ": index " << index << " text " << element.n_window->itemText(index);
				emit elementTimerChanged(MainWindowSignal_DType::Window, index, row);
			}
		);

		connect(element.button, QOverload<int>::of(&ListButtonComboBox::currentIndexChanged), this, [this, row, element](const int index)
			{
				qDebug() << "MainWindow Timer button " << row << ": index " << index << " text " << element.button->itemText(index);
				emit elementTimerChanged(MainWindowSignal_DType::Button, index, row);
			}
		);

		connect(element.period, &QSpinBox::valueChanged, this, [this, row](const int state)
			{
				qDebug() << "MainWindow Timer period " << row << ": " << state;
				emit elementTimerChanged(MainWindowSignal_DType::Period, state, row);
			}
		);

		connect(element.repeat, &QSpinBox::valueChanged, this, [this, row](const int state)
			{
				qDebug() << "MainWindow Timer repeat " << row << ": " << state;
				emit elementTimerChanged(MainWindowSignal_DType::Repeate, state, row);
			}
		);

		connect(element.pause, &QSpinBox::valueChanged, this, [this, row](const int state)
			{
				qDebug() << "MainWindow Timer pause " << row << ": " << state;
				emit elementTimerChanged(MainWindowSignal_DType::Pause, state, row);
			}
		);

		connect(element.ctrl, &QCheckBox::checkStateChanged, this, [this, row](Qt::CheckState state)
			{
				qDebug() << "MainWindow Timer ctrl " << row << ": " << state;
				emit elementTimerChanged(MainWindowSignal_DType::Ctrl, state, row);
			}
		);

		connect(element.alt, &QCheckBox::checkStateChanged, this, [this, row](Qt::CheckState state)
			{
				qDebug() << "MainWindow Timer alt " << row << ": " << state;
				emit elementTimerChanged(MainWindowSignal_DType::Alt, state, row);
			}
		);

		connect(element.shift, &QCheckBox::checkStateChanged, this, [this, row](Qt::CheckState state)
			{
				qDebug() << "MainWindow Timer shift " << row << ": " << state;
				emit elementTimerChanged(MainWindowSignal_DType::Shift, state, row);
			}
		);
	}

	tabTimerLayout->setRowStretch(TimerCtrl.size() + 1, 1);


	tabContent->setLayout(tabTimerLayout);
	scrollArea->setWidget(tabContent); // установить содержимое

	return scrollArea;
}
//------------------------------------------------------------------------------
QFrame* MainWindow::createWidgetsPixel()
{
	int cnt = 0;

	// Прокручиваемая область
	QScrollArea* scrollArea = new QScrollArea(this);
	scrollArea->setWidgetResizable(true);
	scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	scrollArea->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);

	// Вложенный виджет внутри scroll
	QWidget* tabContent = new QWidget(this);
	QGridLayout* tabPixelLayout = new QGridLayout(tabContent);
	tabPixelLayout->setContentsMargins(5, 5, 2, 2);
	tabPixelLayout->setSpacing(5);

	tabPixelLayout->addWidget(new QLabel("Вкл"), 0, ++cnt, Qt::AlignCenter);
	tabPixelLayout->itemAtPosition(0, cnt)->widget()->setToolTip("Включает эмуляцию кнопки");

	tabPixelLayout->addWidget(new QLabel("Окно"), 0, ++cnt, Qt::AlignCenter);
	tabPixelLayout->itemAtPosition(0, cnt)->widget()->setToolTip("Номер активного окна, в котором активируются события");

	tabPixelLayout->addWidget(new QLabel("Кнопка"), 0, ++cnt, Qt::AlignCenter);
	tabPixelLayout->itemAtPosition(0, cnt)->widget()->setToolTip("Эмулируемая клавиша клавиатуры. L0-L9 - клавиши NumLock");

	tabPixelLayout->addWidget(new QLabel("Заданный цвет"), 0, ++cnt, Qt::AlignCenter);
	tabPixelLayout->itemAtPosition(0, cnt)->widget()->setToolTip("Установленный цвет пикселя");

	tabPixelLayout->addWidget(new QLabel("Условие"), 0, ++cnt, Qt::AlignCenter);
	tabPixelLayout->itemAtPosition(0, cnt)->widget()->setToolTip("Условие, при котором активируется срабатывание клавиши");

	tabPixelLayout->addWidget(new QLabel("Текущий цвет"), 0, ++cnt, Qt::AlignCenter);
	tabPixelLayout->itemAtPosition(0, cnt)->widget()->setToolTip("Текущй цвет пикселя");

	tabPixelLayout->addWidget(new QLabel("Установить"), 0, ++cnt, Qt::AlignCenter);
	tabPixelLayout->itemAtPosition(0, cnt)->widget()->setToolTip("Кнопка устанавливает цвет пикселя и координаты. Для установки пикселя нажать кнопку и переместить мышку по координатам.");

	tabPixelLayout->addWidget(new QLabel("Период"), 0, ++cnt, Qt::AlignCenter);
	tabPixelLayout->itemAtPosition(0, cnt)->widget()->setToolTip("Промежут времени в мс, через который кнопка будет повторно нажата");

	tabPixelLayout->addWidget(new QLabel("Повтор"), 0, ++cnt, Qt::AlignCenter);
	tabPixelLayout->itemAtPosition(0, cnt)->widget()->setToolTip("Сколько раз нажать кнопку, если пришло время нажимать кнопку");

	tabPixelLayout->addWidget(new QLabel("Пауза"), 0, ++cnt, Qt::AlignCenter);
	tabPixelLayout->itemAtPosition(0, cnt)->widget()->setToolTip("Промежут времени в мс, в течени которого будет запрещена любая уэмуляция нажатия кнопок");

	tabPixelLayout->addWidget(new QLabel("Отсчет"), 0, ++cnt, Qt::AlignCenter);
	tabPixelLayout->itemAtPosition(0, cnt)->widget()->setToolTip("До следующей эмуляции нажатия, мс");

	tabPixelLayout->addWidget(new QLabel("Ctrl"), 0, ++cnt, Qt::AlignCenter);
	tabPixelLayout->itemAtPosition(0, cnt)->widget()->setToolTip("ЭМуляция кнопки с нажатым Ctrl");

	tabPixelLayout->addWidget(new QLabel("Alt"), 0, ++cnt, Qt::AlignCenter);
	tabPixelLayout->itemAtPosition(0, cnt)->widget()->setToolTip("ЭМуляция кнопки с нажатым Alt");

	tabPixelLayout->addWidget(new QLabel("Shift"), 0, ++cnt, Qt::AlignCenter);
	tabPixelLayout->itemAtPosition(0, cnt)->widget()->setToolTip("ЭМуляция кнопки с нажатым Shift");

	//tabPixelLayout->setColumnStretch(0, 1);
	//tabPixelLayout->setColumnStretch(cnt+1, 1);
	for(int collumn = 2; collumn < cnt-3; ++collumn)
		if(collumn != 7) tabPixelLayout->setColumnStretch(collumn, 1);

	tabPixelLayout->setColumnMinimumWidth(0, 5);
	tabPixelLayout->setColumnMinimumWidth(cnt+1, 5);
	
	for (int row = 0; row < PixelCtrl.size(); ++row)
	{
		auto& element = PixelCtrl[row];
		cnt = 1;

		element.active = new QCheckBox();
		element.active->setText(QString(""));
		tabPixelLayout->addWidget(element.active, row + 1, cnt++, Qt::AlignCenter);

		element.n_window = new ListWindowComboBox();
		element.n_window->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
		tabPixelLayout->addWidget(element.n_window, row + 1, cnt++, Qt::AlignVCenter);

		element.button = new ListButtonComboBox();
		element.button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
		tabPixelLayout->addWidget(element.button, row + 1, cnt++, Qt::AlignVCenter);

		element.set_color = new QLineEdit();
		element.set_color->setText(QString("R: G: B:"));
		element.set_color->setMinimumWidth(70);
		element.set_color->setReadOnly(true);
		element.set_color->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
		tabPixelLayout->addWidget(element.set_color, row + 1, cnt++, Qt::AlignVCenter);

		element.conditional = new ConditionalComboBox();
		//element.conditional->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
		tabPixelLayout->addWidget(element.conditional, row + 1, cnt++, Qt::AlignCenter);

		element.pixel_color = new QLineEdit();
		element.pixel_color->setText(QString("R: G: B:"));
		element.pixel_color->setMinimumWidth(70);
		element.pixel_color->setReadOnly(true);
		element.pixel_color->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
		tabPixelLayout->addWidget(element.pixel_color, row + 1, cnt++, Qt::AlignVCenter);

		element.set = new QPushButton();
		element.set->setMinimumSize(40, 19);
		if(row < 9)
			element.set->setText(QString("&%1").arg(row + 1));
		else
			element.set->setText(QString("1&0"));
		//element.set->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
		tabPixelLayout->addWidget(element.set, row + 1, cnt++, Qt::AlignCenter);

		element.period = new QSpinBox();
		element.period->setRange(1, 7200000);
		element.period->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
		tabPixelLayout->addWidget(element.period, row + 1, cnt++, Qt::AlignVCenter);		

		element.repeat = new QSpinBox();
		element.repeat->setRange(1, 100);
		element.repeat->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
		tabPixelLayout->addWidget(element.repeat, row + 1, cnt++, Qt::AlignVCenter);

		element.pause = new QSpinBox();
		element.pause->setRange(1, 300000);
		element.pause->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
		tabPixelLayout->addWidget(element.pause, row + 1, cnt++, Qt::AlignVCenter);

		element.counting = new QLineEdit();
		element.counting->setReadOnly(true);
		element.counting->setMinimumWidth(50);
		element.counting->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
		tabPixelLayout->addWidget(element.counting, row + 1, cnt++, Qt::AlignVCenter);

		element.ctrl = new QCheckBox();
		element.ctrl->setText(QString(""));
		tabPixelLayout->addWidget(element.ctrl, row + 1, cnt++, Qt::AlignCenter);

		element.alt = new QCheckBox();
		element.alt->setText(QString(""));
		tabPixelLayout->addWidget(element.alt, row + 1, cnt++, Qt::AlignCenter);

		element.shift = new QCheckBox();
		element.shift->setText(QString(""));
		tabPixelLayout->addWidget(element.shift, row + 1, cnt++, Qt::AlignCenter);

		connect(element.active, &QCheckBox::checkStateChanged, this, [this, row](Qt::CheckState state)
			{
				qDebug() << "MainWindow Pixel active " << row << ": " << state;
				emit elementPixelChanged(MainWindowSignal_DType::Active, static_cast<int>(state), row);
			}
		);

		connect(element.n_window, QOverload<int>::of(&ListWindowComboBox::currentIndexChanged), this, [this, row, element](const int index)
			{
				qDebug() << "MainWindow Pixel n_window " << row << ": index " << index << " text " << element.n_window->itemText(index);
				emit elementPixelChanged(MainWindowSignal_DType::Window, index, row);
			}
		);

		connect(element.button, QOverload<int>::of(&ListButtonComboBox::currentIndexChanged), this, [this, row, element](const int index)
			{
				QVariant data = index;
				qDebug() << "MainWindow Pixel button " << row << ": index " << index << " text " << element.button->itemText(index);
				emit elementPixelChanged(MainWindowSignal_DType::Button, index, row);
			}
		);

		connect(element.conditional, QOverload<int>::of(&ConditionalComboBox::currentIndexChanged), this, [this, row, element](const int index)
			{
				QVariant data = index;
				if (data.canConvert<Condition_DType>())
				{
					qDebug() << "MainWindow Pixel conditional " << row << ": index " << index << " text " << element.conditional->itemText(index);
					emit elementPixelChanged(MainWindowSignal_DType::Conditional, index, row);
				}				
			}
		);

		connect(element.set, &QPushButton::clicked, this, [this, row]()
			{
				qDebug() << "MainWindow Pixel PushButton set " << row << " clcked";
				emit clickButtonSetPixel(row);
			}
		);

		connect(element.period, &QSpinBox::valueChanged, this, [this, row](const int state)
			{
				qDebug() << "MainWindow Pixel period " << row << ": " << state;
				emit elementPixelChanged(MainWindowSignal_DType::Period, state, row);
			}
		);

		connect(element.repeat, &QSpinBox::valueChanged, this, [this, row](const int state)
			{
				qDebug() << "MainWindow Pixel repeat " << row << ": " << state;
				emit elementPixelChanged(MainWindowSignal_DType::Repeate, state, row);
			}
		);

		connect(element.pause, &QSpinBox::valueChanged, this, [this, row](const int state)
			{
				qDebug() << "MainWindow Pixel pause " << row << ": " << state;
				emit elementPixelChanged(MainWindowSignal_DType::Pause, state, row);
			}
		);

		connect(element.ctrl, &QCheckBox::checkStateChanged, this, [this, row](Qt::CheckState state)
			{
				qDebug() << "MainWindow Pixel ctrl " << row << ": " << state;
				emit elementPixelChanged(MainWindowSignal_DType::Ctrl, state, row);
			}
		);

		connect(element.alt, &QCheckBox::checkStateChanged, this, [this, row](Qt::CheckState state)
			{
				qDebug() << "MainWindow Pixel alt " << row << ": " << state;
				emit elementPixelChanged(MainWindowSignal_DType::Alt, state, row);
			}
		);

		connect(element.shift, &QCheckBox::checkStateChanged, this, [this, row](Qt::CheckState state)
			{
				qDebug() << "MainWindow Pixel shift " << row << ": " << state;
				emit elementPixelChanged(MainWindowSignal_DType::Shift, state, row);
			}
		);
	}

	//tabPixelLayout->setRowStretch(1, 1);
	
	tabContent->setLayout(tabPixelLayout);
	scrollArea->setWidget(tabContent); // установить содержимое
	return scrollArea;
}
//------------------------------------------------------------------------------
void MainWindow::SetGUITimerButton(qint32 num, const ButtonFTimer_DType& button_timer)
{
	if(button_timer.activate)
		TimerCtrl[num].active->setCheckState(Qt::Checked);
	else
		TimerCtrl[num].active->setCheckState(Qt::Unchecked);

	if (button_timer.ctrl)
		TimerCtrl[num].ctrl->setCheckState(Qt::Checked);
	else
		TimerCtrl[num].ctrl->setCheckState(Qt::Unchecked);

	if (button_timer.alt)
		TimerCtrl[num].alt->setCheckState(Qt::Checked);
	else
		TimerCtrl[num].alt->setCheckState(Qt::Unchecked);

	if (button_timer.shift)
		TimerCtrl[num].shift->setCheckState(Qt::Checked);
	else
		TimerCtrl[num].shift->setCheckState(Qt::Unchecked);

	TimerCtrl[num].n_window->setCurrentIndex(static_cast<int>(button_timer.n_window));
	TimerCtrl[num].button->setCurrentIndex(static_cast<int>(button_timer.button));

	TimerCtrl[num].repeat->blockSignals(true);
	TimerCtrl[num].repeat->setValue(button_timer.repeat);
	TimerCtrl[num].repeat->blockSignals(false);

	TimerCtrl[num].period->blockSignals(true);
	TimerCtrl[num].period->setValue(button_timer.period);
	TimerCtrl[num].period->blockSignals(false);

	TimerCtrl[num].pause->blockSignals(true);
	TimerCtrl[num].pause->setValue(button_timer.pause);
	TimerCtrl[num].pause->blockSignals(false);
}
//------------------------------------------------------------------------------
void MainWindow::SetGUIConditionButton(qint32 num, const ButtonFCondition_DType& button_condition)
{
	if (button_condition.activate)
		PixelCtrl[num].active->setCheckState(Qt::Checked);
	else
		PixelCtrl[num].active->setCheckState(Qt::Unchecked);

	if (button_condition.ctrl)
		PixelCtrl[num].ctrl->setCheckState(Qt::Checked);
	else
		PixelCtrl[num].ctrl->setCheckState(Qt::Unchecked);

	if (button_condition.alt)
		PixelCtrl[num].alt->setCheckState(Qt::Checked);
	else
		PixelCtrl[num].alt->setCheckState(Qt::Unchecked);

	if (button_condition.shift)
		PixelCtrl[num].shift->setCheckState(Qt::Checked);
	else
		PixelCtrl[num].shift->setCheckState(Qt::Unchecked);

	PixelCtrl[num].n_window->setCurrentIndex(static_cast<int>(button_condition.n_window));
	PixelCtrl[num].button->setCurrentIndex(static_cast<int>(button_condition.button));

	PixelCtrl[num].repeat->blockSignals(true);
	PixelCtrl[num].repeat->setValue(button_condition.repeat);
	PixelCtrl[num].repeat->blockSignals(false);

	PixelCtrl[num].period->blockSignals(true);
	PixelCtrl[num].period->setValue(button_condition.period);
	PixelCtrl[num].period->blockSignals(false);

	PixelCtrl[num].pause->blockSignals(true);
	PixelCtrl[num].pause->setValue(button_condition.pause);
	PixelCtrl[num].pause->blockSignals(false);
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// slots
//------------------------------------------------------------------------------
void MainWindow::handleStatusConnection(bool status)
{
	if(status)
		imageUSBLabel->show();
	else
		imageUSBLabel->hide();
}
//------------------------------------------------------------------------------