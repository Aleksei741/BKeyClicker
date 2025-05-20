#pragma once
#include <QObject>
#include <QVectort>

#include "ButtonProcedure.h"
#include "MainWindow.h"
#include "USBProcedure.h"

struct ButtonFTimer_DType
{
	bool activate;
	bool ctrl;
	bool alt;
	bool shift;
	unsigned int n_window;
	unsigned int button;
	unsigned int period;
	unsigned int repeat;
	unsigned int pause;
};

struct ButtonFCondition_DType
{	
	bool activate;
	bool ctrl;
	bool alt;
	bool shift;
	unsigned int condition;
	unsigned int n_window;
	unsigned int button;
	unsigned int period;
	unsigned int repeat;
	unsigned int pause;
};
