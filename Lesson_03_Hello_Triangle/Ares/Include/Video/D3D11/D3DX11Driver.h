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

	class D3DX11Device : public Device {
	public:
		~D3DX11Device(){}
		void*	GetAPIObject() const;
		void**	GetAPIObjectReference();
	private:
		ComPtr<ID3D11Device>            D3D11Device;
	};

	class D3DX11DeviceContext : public DeviceContext {
	public:
		~D3DX11DeviceContext() {}
		void*	GetAPIObject() const;
		void**	GetAPIObjectReference();
	private:
		ComPtr<ID3D11DeviceContext>		D3D11DeviceContext;
	};

	class D3DX11Driver : public BaseDriver {
	public:
		D3DX11Driver(ApplicationDesc *pDesc) : BaseDriver(pDesc) {}
		~D3DX11Driver()
		{
			
		}
		void	 InitDriver();
		void	 Update();
		void	 DestroyDriver();
		void	 SetWindow(void *window);
		void	 Clear();
		void	 SwapBuffers();

		D3D11_VIEWPORT Viewport;				
		ComPtr<IDXGISwapChain>			DXGISwapchain;
		ComPtr<ID3D11RenderTargetView>  D3D11RenderTargetView;
		ComPtr<ID3D11DepthStencilView>  D3D11DepthStencilTargetView;
		ComPtr<ID3D11Texture2D>			D3D11DepthTex;
	};
}

#endif