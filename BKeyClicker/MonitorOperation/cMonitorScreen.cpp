//******************************************************************************
//include
//******************************************************************************
#include "cMonitorScreen.h"
#include <windows.h>

#ifndef OPENC_CV_LIB
#define OPENC_CV_LIB
#ifdef _DEBUG
#pragma comment(lib, "opencv_world4130d.lib")
#pragma comment(lib, "libwebpd.lib")
#pragma comment(lib, "libtiffd.lib")
#pragma comment(lib, "libpngd.lib")
#pragma comment(lib, "zlibd.lib")
#pragma comment(lib, "libopenjp2d.lib")
#pragma comment(lib, "libjpeg-turbod.lib")
#pragma comment(lib, "aded.lib")
#pragma comment(lib, "IlmImfd.lib")
#pragma comment(lib, "ipphal.lib")
#pragma comment(lib, "ippicvmt.lib")
#pragma comment(lib, "ippiwd.lib")
#pragma comment(lib, "ittnotifyd.lib")
#pragma comment(lib, "opencv_img_hash4130d.lib")
#else
#pragma comment(lib, "opencv_world4130.lib")
#pragma comment(lib, "libwebp.lib")
#pragma comment(lib, "libtiff.lib")
#pragma comment(lib, "libpng.lib")
#pragma comment(lib, "zlib.lib")
#pragma comment(lib, "libopenjp2.lib")
#pragma comment(lib, "libjpeg-turbo.lib")
#pragma comment(lib, "ade.lib")
#pragma comment(lib, "IlmImf.lib")
#pragma comment(lib, "ipphal.lib")
#pragma comment(lib, "ippicvmt.lib")
#pragma comment(lib, "ippiw.lib")
#pragma comment(lib, "ittnotify.lib")
#pragma comment(lib, "opencv_img_hash4130.lib")
#endif
#endif

//******************************************************************************
// Variables
//******************************************************************************
//------------------------------------------------------------------------------
// Global
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Local
//------------------------------------------------------------------------------
#define SCREEN_SLEEP_MS			100

//******************************************************************************
// Class function
//******************************************************************************
cMonitorScreen::cMonitorScreen() : semaphoreMatrixScreen(1), activeMonitorSreen(false)
{
    StartProcessMonitorSreen();
}
//------------------------------------------------------------------------------
cMonitorScreen::~cMonitorScreen() 
{
    StopProcessMonitorSreen();
}
//------------------------------------------------------------------------------
void cMonitorScreen::StartProcessMonitorSreen() 
{
    if (activeMonitorSreen) 
        return;
        
    activeMonitorSreen = true;
    threadMonitorSreen = std::thread(&cMonitorScreen::processMonitorSreen, this);
}
//------------------------------------------------------------------------------
void cMonitorScreen::StopProcessMonitorSreen() 
{
    if (!activeMonitorSreen) 
        return;
    
    activeMonitorSreen = false;
    if (threadMonitorSreen.joinable()) 
    {
        threadMonitorSreen.join();
    }
}
//------------------------------------------------------------------------------
/**
 * @brief Захватывает изображение с виртуального экрана (всех мониторов) в цикле
 * 
 * Метод выполняет следующие действия:
 * 1. Считывает изображение с экрана с переодичностью 100 мс
 * 2. Создает матрицу ScreenMat для хранения изображения (формат CV_8UC3 - 24bit BGR)
 * 
 */
void cMonitorScreen::processMonitorSreen()
{
    DWORD PixelDataSize;
	LPBYTE PixelData = nullptr;
	HDC hDCDesctop;
	HDC hDC;
	HGDIOBJ old_obj;
	HBITMAP hBitmap;

	auto StartReadScreen =  std::chrono::steady_clock::time_point();
	auto StopReadScreen = std::chrono::steady_clock::time_point();
	std::chrono::duration<double, std::milli> PauseReadScreen;

	// Получаем координаты виртуального экрана (учитывает все мониторы)
	int left = GetSystemMetrics(SM_XVIRTUALSCREEN);
	int top = GetSystemMetrics(SM_YVIRTUALSCREEN);
	int width = GetSystemMetrics(SM_CXVIRTUALSCREEN);
	int height = GetSystemMetrics(SM_CYVIRTUALSCREEN);

    //Создаем MAT
	ScreenMat.create(height, width, CV_8UC3);

    while (activeMonitorSreen) 
    {
        //**************************************************************************
        //Запоминем врема начала работы с экраном
        StartReadScreen = std::chrono::steady_clock::now();

        //**************************************************************************
        // Очищаем PixelData
        if (PixelData) 
        {
            GlobalFree((HGLOBAL)PixelData);
            PixelData = nullptr;
        }

        //**************************************************************************
        // Получаем hDC рабочего стола
        hDCDesktop = GetDC(nullptr);
        if (!hDCDesktop) 
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            continue;
        }

        //**************************************************************************
        // Получаем совместимый с рабочим столом hDC
        hDC = CreateCompatibleDC(hDCDesktop);
        if (!hDC) 
        {
            ReleaseDC(nullptr, hDCDesktop);
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            continue;
        }

        //**************************************************************************
		// Создаем совместимый Bitmap
        hBitmap = CreateCompatibleBitmap(hDCDesktop, width, height);
        if (!hBitmap) 
        {
            DeleteDC(hDC);
            ReleaseDC(nullptr, hDCDesktop);
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            continue;
        }

        //**************************************************************************
        // Подключаем Bitmap для работы с hDC
        old_obj = SelectObject(hDC, hBitmap);
        if (!old_obj) 
        {
            DeleteObject(hBitmap);
            DeleteDC(hDC);
            ReleaseDC(nullptr, hDCDesktop);
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            continue;
        }
        
        //**************************************************************************
		// Копируем виртуальный экран в Bitmap
        if (!BitBlt(hDC, 0, 0, width, height, hDCDesktop, left, top, SRCCOPY | CAPTUREBLT)) 
        {
            SelectObject(hDC, old_obj);
            DeleteObject(hBitmap);
            DeleteDC(hDC);
            ReleaseDC(nullptr, hDCDesktop);
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            continue;
        }

        //**************************************************************************
		// Выделяем память под данные пикселей
		int stride = ((width * 3 + 3) & ~3); // выравнивание по 4 байта
		PixelDataSize = stride * height;
		PixelData = (LPBYTE)GlobalAlloc(GMEM_FIXED, PixelDataSize);
        if (!PixelData) 
        {
            SelectObject(hDC, old_obj);
            DeleteObject(hBitmap);
            DeleteDC(hDC);
            ReleaseDC(nullptr, hDCDesktop);
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            continue;
        }

        //**************************************************************************
		// Настраиваем структуру для получения данных
		BITMAPINFOHEADER bi = { 0 };
		bi.biSize = sizeof(BITMAPINFOHEADER);
		bi.biWidth = width;
		bi.biHeight = -height; // отрицательный -> top-down
		bi.biPlanes = 1;
		bi.biBitCount = 24; // BGR по 1 байту
		bi.biCompression = BI_RGB;

        //**************************************************************************
		// Копируем Bitmap в буфер
        if (!GetDIBits(hDC, hBitmap, 0, height, PixelData, (BITMAPINFO*)&bi, DIB_RGB_COLORS)) 
        {
            GlobalFree((HGLOBAL)PixelData);
            PixelData = nullptr;
            SelectObject(hDC, old_obj);
            DeleteObject(hBitmap);
            DeleteDC(hDC);
            ReleaseDC(nullptr, hDCDesktop);
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            continue;
        }

        //**************************************************************************
        //Попируем поле
		{
            std::lock_guard<std::mutex> lock(mutexMatrixScreen);
            for (int y = 0; y < height; ++y)
                memcpy(ScreenMat.ptr(y), PixelData + y * stride, width * 3);
        }

        //**************************************************************************
        //Освобождаем ресурсы
		SelectObject(hDC, old_obj);
		DeleteObject(hBitmap);
		DeleteDC(hDC);
		ReleaseDC(nullptr, hDCDesctop);

        //**************************************************************************
        //Пауза
		StopReadScreen = std::chrono::steady_clock::now(); 	
		semaphoreMatrixScreen.release();

		PauseReadScreen = StopReadScreen - StartReadScreen;
		if (PauseReadScreen.count() < SCREEN_SLEEP_MS)
			std::this_thread::sleep_for(std::chrono::milliseconds(SCREEN_SLEEP_MS - PauseReadScreen.count()));
		else
			std::this_thread::sleep_for(std::chrono::milliseconds(1));        
    }

    if (PixelData) 
        GlobalFree((HGLOBAL)PixelData);
}
//------------------------------------------------------------------------------,
/**
 * @brief Ожидает доступности нового кадра экрана * 
 * Блокирует выполнение потока до тех пор, пока:
 * - Не будет захвачен и обработан новый кадр экрана
 * 
 */
void cMonitorScreen::WaitScreen(void)
{
	semaphoreMatrixScreen.acquire(); 
}
//------------------------------------------------------------------------------
ScreenStatus GetColorPixel(std::pair<uint16_t, uint16_t>& pos, std::tuple color<uint8_t, uint8_t, uint8_t>)
{
	if (!activeMonitorSreen)
		return NO_SCREEN_DATA;

    cv::Vec3b pixel(0, 0, 0);

    {
        std::lock_guard<std::mutex> lock(mutexMatrixScreen);
        if (ScreenMat.empty())
            return NO_SCREEN_DATA;

        if (pos.first >= static_cast<uint16_t>(ScreenMat.cols) || 
            pos.second >= static_cast<uint16_t>(ScreenMat.rows))
            return INVALID_WINDOW;

        pixel = ScreenMat.at<cv::Vec3b>(pos.second, pos.first);
    }
    color = std::make_tuple(pixel[2], pixel[1], pixel[0]);
	return FOUND;
}
//------------------------------------------------------------------------------
ScreenStatus FindTargetPixelOnScreen(std::string& target_img_name, RECT RectTargetWindow, std::pair<int, int>& pos)
{
    //**************************************************************************
    if (!activeMonitorSreen)
		return NO_SCREEN_DATA;
    //**************************************************************************
	// --- Загрузка шаблона ---
	cv::Mat targetTemplate = cv::imread(target_img_name, cv::IMREAD_COLOR);
	if (targetTemplate.empty())
	{		
		return NO_INPUT_DATA;
	}

    //**************************************************************************
	// --- Захват экрана ---
	cv::Mat screenCopy;
    {
        std::lock_guard<std::mutex> lock(mutexMatrixScreen);
        if (ScreenMat.empty())
            return NO_SCREEN_DATA;
        screenCopy = ScreenMat.clone();
    }
        
    //**************************************************************************
	// --- Проверка границ окна ---
	// Расчёт ширины и высоты окна
	int winWidth = RectTargetWindow.right - RectTargetWindow.left;
	int winHeight = RectTargetWindow.bottom - RectTargetWindow.top;

    if (winWidth <= 0 || winHeight <= 0) 
    {
        return INVALID_WINDOW;
    }
	
    //**************************************************************************
	// --- Вычисление ROI ---
	// Берём видимую часть окна
    int roiLeft = std::max(RectTargetWindow.left, 0);
	int roiTop = std::max(RectTargetWindow.top, 0);
	int roiRight = std::min(RectTargetWindow.right, screenCopy.cols);
	int roiBottom = std::min(RectTargetWindow.bottom, screenCopy.rows);

    if (roiRight <= roiLeft || roiBottom <= roiTop) 
    {
        return INVALID_WINDOW;
    }
	
    //**************************************************************************
	// Создаём ROI для поиска
	cv::Rect searchROI(roiLeft, roiTop, roiRight - roiLeft, roiBottom - roiTop);
	cv::Mat searchArea = screenCopy(searchROI);

    //**************************************************************************
    // --- Проверка размера шаблона ---
	if (targetTemplate.cols > searchArea.cols || targetTemplate.rows > searchArea.rows) 
    {
        return TEMPLATE_TOO_LARGE;
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
		return NOT_FOUND;

    //**************************************************************************
	// --- Расчёт координат центра ---
    int foundX = roiLeft + maxLoc.x + targetTemplate.cols / 2;
    int foundY = roiTop + maxLoc.y + targetTemplate.rows / 2;

    if (foundX < 0 || foundY < 0 || foundX >= screenCopy.cols || foundY >= screenCopy.rows) {
        return OUT_OF_BOUNDS;
    }

    pos = {foundX, foundY};
    return FOUND;
}
//------------------------------------------------------------------------------