#pragma once
#include <QColor>
#include <QPoint>

#include "cTimerButton.h"
#include "IKeyEmulator.h"

struct ButtonFCondition_DType : ButtonFTimer_DType
{
	QPoint pixel_position;
	QColor color_set;
	quint16 color_condition;
};

class cCondotoinButton : cTimerButton, cMonitorScreen
{
	mutable unsigned int click_cnt = 0;
	mutable qint64 click_time = 0;

protected:
	QPoint pixel_position;
	QColor color_set;
	quint16 color_condition;

public:
	cCondotoinButton();
	cCondotoinButton(const ButtonFCondition_DType& ButtonFCondition);
	~cCondotoinButton() = default;
	cCondotoinButton(const cCondotoinButton& button) = default;
	cCondotoinButton& operator= (const cCondotoinButton& button) = default;

	bool click(const qint64& time_, quint16& delay) const override;
	
	void setPixelPosition(const QPoint& position);
	void setColor(const QColor& color);
	void setCondition(quint16 state);
};

