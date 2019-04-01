#ifndef ARES_LOG_H
#define ARES_LOG_H

#include <Core/Config.h>

#define USE_SHOW_MEM_USAGE		1
#define USE_SHOW_THREADS_IDS	1
#define USE_COLORED_CONSOLE		1
#define LOG_BUFFER_SIZE			1024*1024


#define COLOR_DEBUG		2
#define COLOR_ERROR		4
#define COLOR_INFO		8
#define COLOR_WARNING	14

void	LogPrint(int color, const char* format, ...);

#ifdef DEBUG_LOGS
#define	LogPrintInfo(s,...) LogPrint(COLOR_INFO,s, __VA_ARGS__);
#define	LogPrintDebug(s,...) LogPrint(COLOR_DEBUG,s, __VA_ARGS__);
#define	LogPrintWarning(s,...) LogPrint(COLOR_WARNING,s, __VA_ARGS__);
#else
#define  LogPrintInfo(...) ((void)0)
#define  LogPrintDebug(...) ((void)0)
#define  LogPrintWarning(...) ((void)0)
#endif

#define	LogPrintError(s,...) LogPrint(COLOR_ERROR,s, __VA_ARGS__);
#define	LogPrintRelease(s,...) LogPrint(COLOR_DEBUG,s, __VA_ARGS__);

#endif