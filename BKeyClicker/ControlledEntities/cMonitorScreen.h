#pragma once
#include <cmath>
#include "IMonitorScreen.h"

class cMonitorScreen
{
	static IMonitorScreen* monitor_screen;
protected:
	QColor GetColorPixel(const QPoint& point) const
	{
		if (!monitor_screen)
			return Qt::white;

		return monitor_screen->GetColorPixel(point);
	}

	bool colorsSimilar(const QColor& c1, const QColor& c2, const int tolerance = 5) const
	{
		return std::abs(c1.red() - c2.red()) <= tolerance &&
			std::abs(c1.green() - c2.green()) <= tolerance &&
			std::abs(c1.blue() - c2.blue()) <= tolerance;
	}

public:
	void SetMonitorScreen(IMonitorScreen* monitor)
	{
		monitor_screen = monitor;
	}

	void SetMonitorScreen(IMonitorScreen& monitor)
	{
		monitor_screen = &monitor;
	}
};

