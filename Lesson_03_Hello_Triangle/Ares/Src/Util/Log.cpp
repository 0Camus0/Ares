#include <Util/Log.h>

#include <iostream>
#include <sstream>
#include <stdarg.h> 
#include <iosfwd>
#include <string>

#include <windows.h>
#include <Psapi.h>

static char Log_Buffer[LOG_BUFFER_SIZE];	// 1 Kb should be enough

int	CurrentMemoryUssage() {
	PROCESS_MEMORY_COUNTERS_EX pmc;
	GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
	SIZE_T virtualMemUsedByMe = pmc.PrivateUsage;
	return (int)virtualMemUsedByMe;
}

void	LogPrint(int color, const char* format, ...) {
#if USE_COLORED_CONSOLE
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	WORD wOldColorAttrs;
	GetConsoleScreenBufferInfo(h, &csbiInfo);
	wOldColorAttrs = csbiInfo.wAttributes;
#endif
	va_list arg;
	va_start(arg, format);
	vsprintf_s(Log_Buffer, format, arg);
	va_end(arg);
#if USE_COLORED_CONSOLE
	SetConsoleTextAttribute(h, color | FOREGROUND_INTENSITY);
#endif

	std::stringstream extra_info_debug;
#if USE_SHOW_THREADS_IDS
	extra_info_debug << "TID[" << (int)GetCurrentThreadId() << "] ";
#endif

#if USE_SHOW_MEM_USAGE
	int bytes = CurrentMemoryUssage();
	int mbytes = bytes / 1048576;
	extra_info_debug << "RAM[" << mbytes << " MB] ";
#endif

	std::cout << extra_info_debug.str() << Log_Buffer << std::endl;

#if USE_COLORED_CONSOLE
	SetConsoleTextAttribute(h, wOldColorAttrs);
#endif
}
