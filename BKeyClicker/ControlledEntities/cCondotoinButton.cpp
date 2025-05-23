//******************************************************************************
//include
//******************************************************************************
#include "cCondotoinButton.h"
//******************************************************************************
// Variables
//******************************************************************************
//------------------------------------------------------------------------------
// Global
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Local
//------------------------------------------------------------------------------


//******************************************************************************
// Class function
//******************************************************************************
cCondotoinButton::cCondotoinButton() :
	cTimerButton(ButtonFTimer_DType{false, false, false, false, 0, 1000, 1, 300}),
	pixel_position(QPoint(0, 0)),
	color_set(Qt::black),
	color_condition(ButtonFTimer.alt)
{}
//------------------------------------------------------------------------------
cCondotoinButton::cCondotoinButton(const ButtonFCondition_DType& ButtonFCondition) :
	cTimerButton(ButtonFCondition),
	pixel_position(ButtonFCondition.pixel_position),
	color_set(ButtonFCondition.color_set),
	color_condition(ButtonFCondition.color_condition)
{}
//------------------------------------------------------------------------------
bool cCondotoinButton::click(const qint64& time_, quint16& delay) const override
{
	delay = 0;
	bool complited = true;

	if (activate)
	{
		if (click_cnt == 0)
			click_cnt = repeat;

		if (click_cnt)
		{
			if (time_ > click_time)
			{
				QColor color_pixel = GetColorPixel(pixel_position);
				if (colorsSimilar(color_pixel, color_set))
				{
					if (ClickKey(button, shift, alt, ctrl))
					{
						click_time = time_ + period;

						if (--click_cnt)
							complited = false;

						delay = pause;
					}
				}
			}
		}
	}
	else
	{
		click_cnt = 0;
		click_time = 0;
	}

	return complited;
}
//------------------------------------------------------------------------------
void cCondotoinButton::setPixelPosition(const QPoint& position)
{
	pixel_position = position;
}
//------------------------------------------------------------------------------
void cCondotoinButton::setColor(const QColor& color)
{
	color_set = color;
}
//------------------------------------------------------------------------------
void cCondotoinButton::setCondition(Condition_DType state)
{
	color_condition = state;
}
//------------------------------------------------------------------------------
QPoint cCondotoinButton::getPixelPosition(void)
{
	retirn pixel_position;
}
//------------------------------------------------------------------------------
QColor cCondotoinButton::getColor(void)
{
	retirn color_set;
}
//------------------------------------------------------------------------------
Condition_DType cCondotoinButton::getCondition(void)
{
	retirn color_condition;
}
//------------------------------------------------------------------------------