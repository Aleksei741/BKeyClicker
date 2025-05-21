//******************************************************************************
//include
//******************************************************************************
#include "cTimerButton.h"
//******************************************************************************
// Variables
//******************************************************************************
//------------------------------------------------------------------------------
// Global
//------------------------------------------------------------------------------
IKeyEmulator* cTimerButton::emulator = nullptr;

//------------------------------------------------------------------------------
// Local
//------------------------------------------------------------------------------


//******************************************************************************
// Class function
//******************************************************************************
cTimerButton::cTimerButton() :
	activate(false),
	ctrl(false),
	alt(false),
	shift(false),
	button(0),
	period(1000),
	repeat(1),
	pause(300)
{}
//------------------------------------------------------------------------------
cTimerButton::cTimerButton(const ButtonFTimer_DType& ButtonFTimer) :
	activate(ButtonFTimer.activate),
	ctrl(ButtonFTimer.ctrl),
	alt(ButtonFTimer.alt),
	shift(ButtonFTimer.shift),
	button(ButtonFTimer.button),
	period(ButtonFTimer.period),
	repeat(ButtonFTimer.repeat),
	pause(ButtonFTimer.pause)
{
	timer.start();
}
//------------------------------------------------------------------------------
bool cTimerButton::click(const qint64& time_, quint16& delay) const
{
	delay = 0;
	bool complited = true;

	if (activate)
	{
		if (click_cnt == 0)	//start emulated
			click_cnt = repeat;

		if (click_cnt)
		{
			if (time_ > click_time)
			{
				if (ClickKey(button, shift, alt, ctrl))
				{
					click_time = time_ + period;

					if (--click_cnt)
						complited = false;

					delay = pause;
				}	
			}
		}
	}
	else
	{
		click_cnt = 0;
		click_time = 0;
	}
	
	return complited;
}
//------------------------------------------------------------------------------
void cTimerButton::setActive(bool state)
{
	activate = state;
}
//------------------------------------------------------------------------------
void cTimerButton::setCtrl(bool state)
{
	ctrl = state;
}
//------------------------------------------------------------------------------
void cTimerButton::setAlt(bool state)
{
	alt = state;
}
//------------------------------------------------------------------------------
void cTimerButton::setShift(bool state) 
{
	shift = state;
}
//------------------------------------------------------------------------------
void cTimerButton::setIndexButton(quint16 index)
{
	button = index;
}
//------------------------------------------------------------------------------
void cTimerButton::setPeriod(quint32 period)
{
	period = period;
}
//------------------------------------------------------------------------------
void cTimerButton::setRepeat(quint16 repeate)
{
	repeat = repeate;
}
//------------------------------------------------------------------------------
void cTimerButton::setPause(quint32 pause)
{
	pause = pause;
}
//------------------------------------------------------------------------------