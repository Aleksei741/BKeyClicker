#pragma once
#include "Definitions.h"

class IKeyEmulator
{
public:
	virtual ~IKeyEmulator() = default;

	virtual bool ClickKey(const Buttons_DType indexKey, 
		const bool flagShift, 
		const bool flagAlt, 
		const bool flagCtrl) = 0;

	virtual bool PressKey(const Buttons_DType indexKey, 
		const bool flagShift, 
		const bool flagAlt, 
		const bool flagCtrl) = 0;

	virtual bool UnpressKey(const Buttons_DType indexKey) = 0;
};