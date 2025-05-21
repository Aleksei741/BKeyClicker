#pragma once

class IKeyEmulator
{
	virtual bool ClickKey(quint16 indexKey, bool flagShift, bool flagAlt, bool flagCtrl) = 0;
	virtual bool PressKey(quint16 indexKey, bool flagShift, bool flagAlt, bool flagCtrl) = 0;
	virtual bool UnpressKey(quint16 indexKey) = 0;
};