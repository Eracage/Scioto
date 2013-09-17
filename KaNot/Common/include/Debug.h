#ifdef _WIN32
#include <Windows.h>
#define  LOGI(...)  PrintToOutput(false,__VA_ARGS__)
#define  LOGE(...)  PrintToOutput(true,__VA_ARGS__)
void PrintToOutput(bool error, const char* message)
{
	if (error)
		OutputDebugStringA(" --(ERROR)-- ");
	OutputDebugStringA(message);
	OutputDebugStringA("\n");
}
#else
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#endif




//#include <stdarg.h>
//#include <iostream>
//
//namespace Scioto
//{
//	void Debugline(std::string Text, ...)
//	{
//		va_list 
//#ifdef _WIN32
//#else
//#endif
//
//	}
//}