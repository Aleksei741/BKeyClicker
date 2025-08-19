#pragma once
#include <stdio>
#include <thread>
#include <atomic>
#include <mutex>
#include <semaphore>
#include <chrono>
#include <string>
#include <string>
#include <utility>

#include "IncludeOpenCV.h"
#include "IncludeWindpws.h"

class cMonitorScreen
{
private:
	std::thread threadMonitorSreen;
	std::atomic<bool> activeMonitorSreen;
	std::mutex mutexMatrixScreen;
	std::binary_semaphore semaphoreMatrixScreen;
	cv::Mat ScreenMat;

	void StartProcessMonitorSreen(void);
	void StopProcessMonitorSreen(void);
	void processMonitorSreen(void);
public:
	enum class Status 
	{
    SUCCESS,            // Успешный захват и обработка
	NOT_FOUND,          // Успешный захват и обработка
	SCREEN_EMPTY,       // Экран не считался.
    IMAGE_EMPTY,         // Изображение пустое (не считалось)
    PROCESSING_ERROR,    // Ошибка обработки
    INVALIG_REGION,      // Некорректная область захвата
	INVALIG_TARGET,      // Некорректный входной файл
	};

	cMonitorScreen();
    ~cMonitorScreen();
	cMonitorScreen::Status GetColorPixel(const cv::Point& pos, cv::Vec3b& color)
	cMonitorScreen::Status GetMat(cv::Mat& screenCopy);
	
	void WiatScreen(void);
    
protected:

};

