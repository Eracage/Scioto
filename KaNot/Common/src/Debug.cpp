#include <Debug.h>


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

void checkGlError(const char* op) {
    for (GLint error = glGetError(); error; error = glGetError()) 
	{
        LOGI("after %s() glError (0x%x)\n", op, error);
    }
}