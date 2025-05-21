#pragma once
#include <QColor>
#include <QPoint>

class IMonitorScreen
{
	virtual QColor GetColorPixel(const QPoint& point) = 0;
};