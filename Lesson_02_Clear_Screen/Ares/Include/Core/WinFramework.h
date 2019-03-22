#ifndef ARES_WINFRAMEWORK_H
#define ARES_WINFRAMEWORK_H

#include <Core\Core.h>

namespace Ares {
	class WinFramework : public RootFramework {
	public:
		WinFramework(AppBase *pBaseApp, ApplicationDesc Desc) : RootFramework(pBaseApp, Desc), m_alive(true) {
			pBaseApp->SetParentFramework(this);
			bInitialized = false;
		}
		void InitGlobalVars();
		void OnCreateApplication();
		void OnDestroyApplication();
		void OnInterruptApplication();
		void OnResumeApplication();
		void UpdateApplication();
		void ProcessInput();
		void ResetApplication();
		void Run();
		void SwitchAPI(GraphicsApi_::E api);

		~WinFramework() {	}

		bool	m_alive;
	private:
	};
}

#endif