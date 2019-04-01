#ifndef ARES_D3D11_DRIVER_H
#define ARES_D3D11_DRIVER_H

#include <Core/BaseDriver.h>

#include <d3d11.h>
#include <dxgi.h>
#include <D3Dcompiler.h>

#include <wrl.h>
#include <wrl/client.h>
using namespace Microsoft::WRL;

#include <stdio.h>

namespace Ares {
	class D3D11Driver : public BaseDriver {
	public:
		D3D11Driver(ApplicationDesc *pDesc) : BaseDriver(pDesc) {}
		~D3D11Driver()
		{
			
		}
		void	 InitDriver();
		void	 Update();
		void	 DestroyDriver();
		void	 SetWindow(void *window);
		void	 Clear();
		void	 SwapBuffers();

		D3D11_VIEWPORT Viewport;

		ComPtr<ID3D11Device>            D3D11Device;
		ComPtr<ID3D11DeviceContext>		D3D11DeviceContext;
		ComPtr<IDXGISwapChain>			DXGISwapchain;
		ComPtr<ID3D11RenderTargetView>  D3D11RenderTargetView;
		ComPtr<ID3D11DepthStencilView>  D3D11DepthStencilTargetView;
		ComPtr<ID3D11Texture2D>			D3D11DepthTex;
	};
}

#endif