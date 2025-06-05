#pragma once
#include "ButtonFTimerTypes.h"

struct ButtonFCondition_DType : ButtonFTimer_DType
{
	QPoint pixel_position;
	QColor color_set;
	Condition_DType color_condition;
};