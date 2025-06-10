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
	n_window(nWindows_DType::n1),
	button(Buttons_DType::L0),
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
	n_window(ButtonFTimer.n_window),
	button(ButtonFTimer.button),
	period(ButtonFTimer.period),
	repeat(ButtonFTimer.repeat),
	pause(ButtonFTimer.pause)
{
	
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
void cTimerButton::setIndexButton(Buttons_DType index)
{
	button = index;
}
//------------------------------------------------------------------------------
void cTimerButton::setNWindow(nWindows_DType window)
{
	n_window = window;
}
//------------------------------------------------------------------------------
void cTimerButton::setPeriod(quint32 per)
{
	period = per;
}
//------------------------------------------------------------------------------
void cTimerButton::setRepeat(quint16 rep)
{
	repeat = rep;
}
//------------------------------------------------------------------------------
void cTimerButton::setPause(quint32 p)
{
	pause = p;
}
//------------------------------------------------------------------------------
bool cTimerButton::getActive(void) const
{
	return activate;
}
//------------------------------------------------------------------------------
bool cTimerButton::getCtrl(void) const
{
	return ctrl;
}
//------------------------------------------------------------------------------
bool cTimerButton::getAlt(void) const
{
	return alt;
}
//------------------------------------------------------------------------------
bool cTimerButton::getShift(void) const
{
	return shift;
}
//------------------------------------------------------------------------------
nWindows_DType cTimerButton::getNWindow(void) const
{
	return n_window;
}
//------------------------------------------------------------------------------
Buttons_DType cTimerButton::getIndexButton(void) const
{
	return button;
}
//------------------------------------------------------------------------------
quint32 cTimerButton::getPeriod(void) const
{
	return period;
}
//------------------------------------------------------------------------------
quint16 cTimerButton::getRepeat(void) const
{
	return repeat;
}
//------------------------------------------------------------------------------
quint32 cTimerButton::getPause(void) const
{
	return pause;
}
//------------------------------------------------------------------------------