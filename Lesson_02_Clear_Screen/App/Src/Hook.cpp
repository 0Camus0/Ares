#if defined(_WIN32) || defined(_WIN64)
#include <Windows.h>

#define DELAYIMP_INSECURE_WRITABLE_HOOKS 

#include <DelayImp.h>
#pragma comment(lib, "delayimp")

extern "C" FARPROC WINAPI RenameSDLHook(unsigned dliNotify, PDelayLoadInfo pdli)
{
	if (dliNotify == dliNotePreLoadLibrary) {
		if (pdli && pdli->szDll && !_stricmp(pdli->szDll, "SDL.dll")) {
#ifdef _WIN64
			return (FARPROC)LoadLibrary(TEXT("SDLx64.dll"));				
#else
			return (FARPROC)LoadLibrary(TEXT("SDLx86.dll"));
#endif
		}
	}
	return NULL;	
}

extern "C"  PfnDliHook __pfnDliNotifyHook2 = RenameSDLHook;
extern "C"  PfnDliHook __pfnDliFailureHook2 = RenameSDLHook;
#endif