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
	enun ScreenStatus
	{
		FOUND,
		NOT_FOUND,
		INVALID_WINDOW,
		NO_INPUT_DATA,
		NO_SCREEN_DATA,
	};

	cMonitorScreen();
    ~cMonitorScreen();
	ScreenStatus GetColorPixel(std::pair<uint16_t, uint16_t>& pos, std::tuple color<uint8_t, uint8_t, uint8_t>);
	ScreenStatus FindTargetPixelOnScreen(std::string& target_img_name, RECT RectTargetWindow, std::pair<int, int>& pos);
	
	void WiatScreen(void);
    
protected:

};

