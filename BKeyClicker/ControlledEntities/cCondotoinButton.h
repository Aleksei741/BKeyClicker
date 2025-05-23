#pragma once
#include <QColor>
#include <QPoint>

#include "Definitions.h"
#include "cTimerButton.h"
#include "IKeyEmulator.h"

struct ButtonFCondition_DType : ButtonFTimer_DType
{
	QPoint pixel_position;
	QColor color_set;
	Condition_DType color_condition;
};

class cCondotoinButton : cTimerButton, cMonitorScreen
{
	mutable unsigned int click_cnt = 0;
	mutable qint64 click_time = 0;

protected:
	QPoint pixel_position;
	QColor color_set;
	Condition_DType color_condition;

public:
	cCondotoinButton();
	cCondotoinButton(const ButtonFCondition_DType& ButtonFCondition);
	~cCondotoinButton() = default;
	cCondotoinButton(const cCondotoinButton& button) = default;
	cCondotoinButton& operator= (const cCondotoinButton& button) = default;

	bool click(const qint64& time_, quint16& delay) const override;
	
	void setPixelPosition(const QPoint& position);
	void setColor(const QColor& color);
	void setCondition(Condition_DType state);

	QPoint getPixelPosition(void);
	QColor getColor(void);
	Condition_DType getCondition(void);
};

