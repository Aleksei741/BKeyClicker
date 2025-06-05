#pragma once
#include <QElapsedTimer>
#include <QReadWriteLock>
#include <QMutexLocker>
#include <QPair>
#include <optional>

#include "cKeyEmulator.h"
#include "ButtonFTimerTypes.h"
#include "Definitions.h"

class cTimerButton : virtual public cKeyEmulator
{
	mutable unsigned int click_cnt = 0;
	mutable qint64 click_time = 0;
protected:
	bool activate;
	bool ctrl;
	bool alt;
	bool shift;
	nWindows_DType n_window;
	Buttons_DType button;
	quint32 period;
	quint16 repeat;
	quint32 pause;

public:
	cTimerButton();
	cTimerButton(const ButtonFTimer_DType& ButtonFTimer);
	~cTimerButton() = default;
	cTimerButton(const cTimerButton& button) = default;
	cTimerButton& operator= (const cTimerButton& button) = default;

	virtual bool click(const qint64& time_, quint16& delay) const;

	void setActive(bool state);
	void setCtrl(bool state);
	void setAlt(bool state);
	void setShift(bool state);
	void setNWindow(nWindows_DType window);
	void setIndexButton(Buttons_DType index);
	void setPeriod(quint32 period);
	void setRepeat(quint16 repeate);
	void setPause(quint32 pause);

	bool getActive(void) const;
	bool getCtrl(void) const;
	bool getAlt(void) const;
	bool getShift(void) const;
	nWindows_DType getNWindow(void) const;
	Buttons_DType getIndexButton(void) const;
	quint32 getPeriod(void) const;
	quint16 getRepeat(void) const;
	quint32 getPause(void) const;
};

