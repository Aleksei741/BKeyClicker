#pragma once
//******************************************************************************
// Секция определения констант OpenCV
//******************************************************************************
#ifndef CV_STATIC
#define CV_STATIC
#endif

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

//******************************************************************************
//include
//******************************************************************************
#include <opencv2/opencv.hpp>

//******************************************************************************
//include lib
//******************************************************************************
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

//******************************************************************************
// ENF OF FILE
//******************************************************************************