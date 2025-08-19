//******************************************************************************
//include
//******************************************************************************
#include "cScreenImageProcessing.h"

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
cScreenImageProcessing::cScreenImageProcessing()
{
    
}
//------------------------------------------------------------------------------
cScreenImageProcessing::~cScreenImageProcessing() 
{

}
//------------------------------------------------------------------------------
cMonitorScreen::Status cScreenImageProcessing::FindImagePositionOnScreen(scv::Mat& targetTemplate, cv::Rect targetWindow, cv::Point& pos)
{
    //**************************************************************************
	// --- Проверка шаблона ---
	if (targetTemplate.empty())
	{		
		return cMonitorScreen::IMAGE_EMPTY;
	}

    //**************************************************************************
	// --- Захват экрана ---
	cv::Mat screenCopy;
    if(GetMat(cv::Mat& screenCopy) != cMonitorScreen::SUCCESS)
        return cMonitorScreen::IMAGE_EMPTY;
        
    //**************************************************************************
	// --- Проверка границ окна ---
	// Расчёт ширины и высоты окна
	if (targetWindow.width <= 0 || targetWindow.height <= 0)
        return cMonitorScreen::INVALIG_REGION;
	
    //**************************************************************************
	// --- Вычисление ROI ---
	// Берём видимую часть окна
    int roiLeft = std::max(targetWindow.x, 0);
    int roiTop = std::max(targetWindow.y, 0);
    int roiRight = std::min(targetWindow.x + targetWindow.width, screenCopy.cols);
    int roiBottom = std::min(targetWindow.y + targetWindow.height, screenCopy.rows);

    if (roiRight <= roiLeft || roiBottom <= roiTop) 
    {
        cMonitorScreen::INVALIG_REGION;
    }
	
    //**************************************************************************
	// Создаём ROI для поиска
	cv::Rect searchROI(roiLeft, roiTop, roiRight - roiLeft, roiBottom - roiTop);
    cv::Mat searchArea = screenCopy(searchROI);

    //**************************************************************************
    // --- Проверка размера шаблона ---
	if (targetTemplate.cols > searchArea.cols || targetTemplate.rows > searchArea.rows) 
    {
        return cMonitorScreen::INVALIG_REGION;
    }

    //**************************************************************************
	// --- Поиск шаблона ---
	cv::Mat result;
    cv::matchTemplate(searchArea, targetTemplate, result, cv::TM_CCOEFF_NORMED);

    //**************************************************************************
	// Находим максимум совпадения
	double maxVal;
    cv::Point maxLoc;
    cv::minMaxLoc(result, nullptr, &maxVal, nullptr, &maxLoc);

    // Порог схожести
    const double threshold = 0.8;
    if (maxVal < threshold)
        return cMonitorScreen::NOT_FOUND;

    //**************************************************************************
	// --- Расчёт координат центра ---
    int foundX = roiLeft + maxLoc.x + targetTemplate.cols / 2;
    int foundY = roiTop + maxLoc.y + targetTemplate.rows / 2;

    if (foundX < 0 || foundY < 0 || foundX >= screenCopy.cols || foundY >= screenCopy.rows) 
    {
        return cMonitorScreen::NOT_FOUND;
    }

    pos = cv::Point(foundX, foundY);
    return cMonitorScreen::SUCCESS;
}
//------------------------------------------------------------------------------