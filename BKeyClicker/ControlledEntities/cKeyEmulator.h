#pragma once
#include "IKeyEmulator.h"

class cKeyEmulator
{
	static IKeyEmulator* emulator;
protected:
	bool ClickKey(const Buttons_DType indexKey, 
		const bool flagShift, const bool flagAlt, const bool flagCtrl) const
	{
		if (!emulator)
			return false;
		return emulator->ClickKey(indexKey, flagShift, flagAlt, flagCtrl);
	}
	
	bool PressKey(const Buttons_DType indexKey,
		const bool flagShift, const bool flagAlt, const bool flagCtrl) const
	{
		if (!emulator)
			return false;
		return emulator->PressKey(indexKey, flagShift, flagAlt, flagCtrl);
	}
	
	bool UnpressKey(const Buttons_DType indexKey) const
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