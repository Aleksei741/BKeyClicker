#pragma once
#include <QElapsedTimer>
#include <QReadWriteLock>
#include <QMutexLocker>
#include <QPair>
#include <optional>

#include "cKeyEmulator.h"

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

class cTimerButton : cKeyEmulator
{
	mutable unsigned int click_cnt = 0;
	mutable qint64 click_time = 0;
protected:
	bool activate;
	bool ctrl;
	bool alt;
	bool shift;
	quint16 button;
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
	void setIndexButton(quint16 index);
	void setPeriod(quint32 period);
	void setRepeat(quint16 repeate);
	void setPause(quint32 pause);
};

