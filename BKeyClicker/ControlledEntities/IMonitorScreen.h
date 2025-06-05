#pragma once
#include <QColor>
#include <QPoint>

class IMonitorScreen
{
public:
	virtual ~IMonitorScreen() = default;
	virtual QColor GetColorPixel(const QPoint& point) = 0;
};