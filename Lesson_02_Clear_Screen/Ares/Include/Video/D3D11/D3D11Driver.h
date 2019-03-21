#ifndef ARES_D3D11_DRIVER_H
#define ARES_D3D11_DRIVER_H

#include <Core/BaseDriver.h>

#include <d3d11.h>
#include <dxgi.h>
#include <D3Dcompiler.h>

#include <wrl.h>
#include <wrl/client.h>
using namespace Microsoft::WRL;

namespace Ares {
	class D3D11Driver : public BaseDriver {
	public:
		D3D11Driver(ApplicationDesc *pDesc) : BaseDriver(pDesc) {}
		void	 InitDriver();
		void	 CreateSurfaces();
		void	 DestroySurfaces();
		void	 Update();
		void	 DestroyDriver();
		void	 SetWindow(void *window);
		void	 SetDimensions(int, int);
		void	 Clear();
		void	 SwapBuffers();

		D3D11_VIEWPORT Viewport;
	};
}

#endif