#pragma once
#include <QElapsedTimer>
#include <QReadWriteLock>
#include <QMutexLocker>
#include <QPair>
#include <optional>

class IKeyEmulator
{
public:
	bool ClickKey(quint16 indexKey, bool flagShift, bool flagAlt, bool flagCtrl) = 0;
	bool PressKey(quint16 indexKey, bool flagShift, bool flagAlt, bool flagCtrl) = 0;
	bool UnpressKey(void) = 0;
};

class cTimerButton
{
	mutable unsigned int click_cnt = 0;
	mutable QReadWriteLock RWLock;
	static IKeyEmulator* emulator;
	mutable unsigned int click_cnt = 0;
	mutable QElapsedTimer timer;

protected:
	bool f_activate;
	bool f_ctrl;
	bool f_alt;
	bool f_shift;
	quint16 m_button;
	quint32 m_period;
	quint16 m_repeat;
	quint32 m_pause;

public:
	cTimerButton();
	cTimerButton(quint16 button, quint32 period, quint32 pause, bool shift, bool alt, bool ctrl);
	~cTimerButton() = default();
	cTimerButton(const cTimerButton& button) = default;
	cTimerButton& operator= (const cTimerButton& button) = default();

	QPair<quint32, bool> click() const;

	void setActive(bool state);
	void setCtrl(bool state);
	void setAlt(bool state);
	void setShift(bool state);
	void setIndexButton(quint16 index);
	void setPeriod(quint32 period);
	void setRepeat(quint16 repeate);
	void setPause(quint32 pause);
};

