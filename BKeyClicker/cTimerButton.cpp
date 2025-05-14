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
cTimerButton::emulator = nullptr;

//------------------------------------------------------------------------------
// Local
//------------------------------------------------------------------------------


//******************************************************************************
// Class function
//******************************************************************************

cTimerButton::cTimerButton()
{
	timer.start();
}
//------------------------------------------------------------------------------
cTimerButton::cTimerButton(quint16 button, quint32 period, quint32 pause, bool shift, bool alt, bool ctrl) : 
	f_activate(true),
	f_ctrl(ctrl),
	f_alt(alt),
	f_shift(shift),
	m_button(button),
	m_period(period),
	m_repeat(1),
	m_pause(pause)
{
	timer.start();
}
//------------------------------------------------------------------------------
QPair<quint32, bool> cTimerButton::click() const
{
	quint16 delay = 0;
	bool Final = false;

	if (emulator == nullptr)		//if no emulator
		return { 0, true };		//delay = 0, final = true

	RWLock.lockForRead();
	if (f_activate)
	{
		if (click_cnt == 0)	//start emulated
			click_cnt = m_repeat;

		if (click_cnt)
		{
			if (timer.elapsed() > m_period)
			{
				if (emulator->ClickKey(m_button, f_shift, f_alt, f_ctrl))
				{
					timer.restart();

					if (--click_cnt)	//final emulated
						Final = true;

					delay = m_pause;
				}	
				else
					Final = true;
			}
			else
				Final = true;
		}
		else
			Final = true;
	}
	else
		Final = true;

	RWLock.unlockForRead();
	
	return { delay, Final };
}
//------------------------------------------------------------------------------
void cTimerButton::setActive(bool state)
{
	RWLock.lockForWrite();
	f_activate = state;
	RWLock.unlockForWrite();
}
//------------------------------------------------------------------------------
void cTimerButton::setCtrl(bool state)
{
	RWLock.lockForWrite();
	f_ctrl = state;
	RWLock.unlockForWrite();
}
//------------------------------------------------------------------------------
void cTimerButton::setAlt(bool state)
{
	RWLock.lockForWrite();
	f_alt = state;
	RWLock.unlockForWrite();
}
//------------------------------------------------------------------------------
void cTimerButton::setShift(bool state) 
{
	RWLock.lockForWrite();
	f_shift = state;
	RWLock.unlockForWrite();
}
//------------------------------------------------------------------------------
void cTimerButton::setIndexButton(quint16 index)
{
	RWLock.lockForWrite();
	m_button = index;
	RWLock.unlockForWrite();
}
//------------------------------------------------------------------------------
void cTimerButton::setPeriod(quint32 period)
{
	RWLock.lockForWrite();
	m_period = period;
	RWLock.unlockForWrite();
}
//------------------------------------------------------------------------------
void cTimerButton::setRepeat(quint16 repeate)
{
	RWLock.lockForWrite();
	m_repeat = repeate;
	RWLock.unlockForWrite();
}
//------------------------------------------------------------------------------
void cTimerButton::setPause(quint32 pause)
{
	RWLock.lockForWrite();
	m_pause = pause;
	RWLock.unlockForWrite();
}
//------------------------------------------------------------------------------