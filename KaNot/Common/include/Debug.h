#ifdef _WIN32
#include <Windows.h>
#include <iostream>
#define  LOGI(...)  PrintToOutput(false,__VA_ARGS__)
//Use tostring()
#define  LOGE(...)  PrintToOutput(true,__VA_ARGS__)
void PrintToOutput(bool error, const char* format, ...)
{
	va_list args;

	char message[10240];
	va_start(args,format);
	vsprintf(message,format,args);
	va_end(args);

		
	OutputDebugStringA("\n");
	if (error)
		OutputDebugStringA(" --(ERROR)-- ");
	OutputDebugStringA(message);
}
#else
#include <android/log.h>
#define  LOG_TAG    "libKaNot"
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