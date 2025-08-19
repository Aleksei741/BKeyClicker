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
 * Не будет захвачен и обработан новый кадр экрана
 * 
 */
void cMonitorScreen::WaitScreen(void)
{
	semaphoreMatrixScreen.acquire(); 
}
//------------------------------------------------------------------------------
cMonitorScreen::Status GetColorPixel(const cv::Point& pos, cv::Vec3b& color)
{
	if (!activeMonitorSreen)
		return Status::PROCESSING_ERROR;

    color = cv::Vec3b(0, 0, 0);

    {
        std::lock_guard<std::mutex> lock(mutexMatrixScreen);
        if (ScreenMat.empty())
            return Status::SCREEN_EMPTY;

         if (pos.x < 0 || 
            pos.y < 0 || 
            pos.x >= ScreenMat.cols || 
            pos.y >= ScreenMat.rows)
            return Status::INVALIG_REGION;

        color = ScreenMat.at<cv::Vec3b>(pos);
    }

	return Status::SUCCESS;
}
//------------------------------------------------------------------------------
cMonitorScreen::Status GetMat(cv::Mat& screenCopy)
{
	if (!activeMonitorSreen)
		return Status::PROCESSING_ERROR;

    {
        std::lock_guard<std::mutex> lock(mutexMatrixScreen);
        if (ScreenMat.empty())
        {
            screenCopy.release();
            return Status::SCREEN_EMPTY;
        }
        screenCopy = ScreenMat.clone();
    }

	return Status::SUCCESS;
}
//------------------------------------------------------------------------------