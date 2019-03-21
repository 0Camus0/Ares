#ifndef ARES_DRIVER_BASE_H
#define ARES_DRIVER_BASE_H

#include <Core/Config.h>
#include <Core/Defs.h>

namespace Ares {
	class BaseDriver {
	public:
		BaseDriver(ApplicationDesc* pDesc) : pAppDesc(pDesc) {  }
		virtual	void	 InitDriver() = 0;
		virtual void	 CreateSurfaces() = 0;
		virtual void	 DestroySurfaces() = 0;
		virtual void	 Update() = 0;
		virtual void	 DestroyDriver() = 0;
		virtual void	 SetWindow(void *window) = 0;
		virtual void	 SetDimensions(int, int) = 0;
		virtual void	 Clear() = 0;
		virtual void	 SwapBuffers() = 0;

		
		ApplicationDesc  *pAppDesc;
		GraphicsApi_::E  CurrentAPI;
		int	BBWidth, BBHeight;
	};
}

#endif