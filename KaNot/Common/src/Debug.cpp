#include <Debug.h>
#include <stdarg.h>

#ifdef _WIN32
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
#endif

void checkGlError(const char* ErrorPlaceName) {
    for (GLint error = glGetError(); error; error = glGetError()) 
	{
        LOGI("At error check %s() glError (0x%x)\n", ErrorPlaceName, error);
    }
}

void printGLString(const char *name, GLenum s) {
    const char *v = (const char *) glGetString(s);
    LOGI("GL %s = %s\n", name, v);
}