#pragma once

struct ButtonFTimer_DType
{
	bool activate;
	bool ctrl;
	bool alt;
	bool shift;
	nWindows_DType n_window;
	Buttons_DType button;
	unsigned int period;
	unsigned int repeat;
	unsigned int pause;
};