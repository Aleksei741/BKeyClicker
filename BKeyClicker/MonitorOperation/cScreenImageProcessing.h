#pragma once
#include "cMonitorScreen.h"
#include "IncludeOpenCV.h"
#include "IncludeWindpws.h"

class cScreenImageProcessing : public virtual cMonitorScreen
{
private:

public:
	cScreenImageProcessing();
    ~cScreenImageProcessing();
    cMonitorScreen::Status cScreenImageProcessing::FindImagePositionOnScreen(scv::Mat& targetTemplate, cv::Rect targetWindow, cv::Point& pos);
protected:

};

