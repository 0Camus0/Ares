#ifndef ARES_DRIVER_BASE_H
#define ARES_DRIVER_BASE_H

#include <Core/Config.h>
#include <Core/Defs.h>

namespace Ares {

	class IBaseDriverObject {
	public:
		virtual void*	GetAPIObject() const = 0;
		virtual void**	GetAPIObjectReference() = 0;
		virtual ~IBaseDriverObject() {}
	};

	class Device : public IBaseDriverObject {
	public:
		~Device() {}
	};


	class DeviceContext : public IBaseDriverObject {
	public:
		~DeviceContext(){}
	};
	
	class BaseDriver {
	public:
		BaseDriver(ApplicationDesc* pDesc) : pAppDesc(pDesc) {  }
		virtual	void	 InitDriver() = 0;
		virtual void	 Update() = 0;
		virtual void	 DestroyDriver() = 0;
		virtual void	 SetWindow(void *window) = 0;
		virtual void	 Clear() = 0;
		virtual void	 SwapBuffers() = 0;
		virtual ~BaseDriver() {}

		
		ApplicationDesc  *pAppDesc;
		Device			 *pDevice;
		DeviceContext	 *pDeviceContext;
		GraphicsApi_::E  CurrentAPI;
		int	BBWidth, BBHeight;
	};
}

#endif