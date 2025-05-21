#pragma once
#include "IKeyEmulator.h"


class cKeyEmulator
{
	static IKeyEmulator* emulator;
protected:
	bool ClickKey(quint16 indexKey, bool flagShift, bool flagAlt, bool flagCtrl)
	{
		if (!emulator)
			return false;
		return emulator->ClickKey(indexKey, flagShift, flagAlt, flagCtrl);
	}
	
	bool PressKey(quint16 indexKey, bool flagShift, bool flagAlt, bool flagCtrl)
	{
		if (!emulator)
			return false;
		return emulator->PressKey(indexKey, flagShift, flagAlt, flagCtrl);
	}
	
	bool UnpressKey(void)
	{
		if (!emulator)
			return false;
		return emulator->UnpressKey(indexKey);
	}

public:
	void SetEmulator(IKeyEmulator* emulator_)
	{
		emulator = emulator_;
	}

	void SetEmulator(IKeyEmulator& emulator_)
	{
		emulator = &emulator_;
	}
};