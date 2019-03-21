#ifndef ARES_CORE_H
#define ARES_CORE_H

#include <Core/Defs.h>
#include <Core/BaseDriver.h>

namespace Ares {
	class RootFramework;
	class AppBase {
	public:
		AppBase() : bInitialized(false), bPaused(false), pFramework(0) {}
		virtual void InitVars() = 0;
		virtual void CreateAssets() = 0;
		virtual void LoadAssets() = 0;
		virtual void DestroyAssets() = 0;
		virtual void OnUpdate() = 0;
		virtual void OnDraw() = 0;
		virtual void OnInput() = 0;
		virtual void OnPause() = 0;
		virtual void OnResume() = 0;
		virtual void OnReset() = 0;

		void	SetParentFramework(RootFramework* pParentFramework) {
			pFramework = pParentFramework;
		}
		bool			bInitialized;
		bool			bPaused;
		RootFramework	*pFramework;
	};

	class RootFramework {
	public:
		RootFramework(AppBase *pApp, ApplicationDesc Desc) : pBaseApp(pApp), pBaseDriver(0), AplicationDescriptor(Desc) {}
		virtual void InitGlobalVars() = 0;
		virtual void OnCreateApplication() = 0;
		virtual void OnDestroyApplication() = 0;
		virtual void OnInterruptApplication() = 0;
		virtual void OnResumeApplication() = 0;
		virtual void UpdateApplication() = 0;
		virtual void ProcessInput() = 0;
		virtual void ResetApplication() = 0;
		virtual void Run() = 0;

		AppBase			*pBaseApp;
		BaseDriver		*pBaseDriver;
		bool			bInitialized;
		ApplicationDesc AplicationDescriptor;
	};
}

#endif
