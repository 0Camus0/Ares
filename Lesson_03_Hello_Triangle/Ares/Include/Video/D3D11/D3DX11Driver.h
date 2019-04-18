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
		void*	GetAPIObject() const;
		void**	GetAPIObjectReference();
		void    DestroyResources();

		~D3DX11Device() {}

		ComPtr<ID3D11Device>            pD3D11Device;
	};

	class D3DX11DeviceContext : public DeviceContext {
	public:		
		void*	GetAPIObject() const;
		void**	GetAPIObjectReference();
		void    DestroyResources();

		void SetTopology(MeshTopology::E);
		void DrawIndexed(unsigned int VertexCount, unsigned int StartIndex, unsigned int StartVertex);

		~D3DX11DeviceContext() {}

		ComPtr<ID3D11DeviceContext>		pD3D11DeviceContext;
	};

	class D3DX11VertexBuffer : public VertexBuffer {
	public:
		void*	GetAPIObject() const;
		void**	GetAPIObjectReference();
		void    DestroyResources();
		void Create(Device*, BufferDesc, const void* pB = 0);
		void Reset(DeviceContext*, const void*, unsigned int size);
		void SetCurrent(DeviceContext*);
		void SetCurrent(DeviceContext*, const unsigned int stride, const unsigned int offset);

		~D3DX11VertexBuffer() {}

		ComPtr<ID3D11Buffer> pD3D11Buffer;
		D3D11_BUFFER_DESC	 API_Desc;
	};

	class D3DX11IndexBuffer : public IndexBuffer {
	public:
		void*	GetAPIObject() const;
		void**	GetAPIObjectReference();
		void    DestroyResources();
		void Create(Device*, BufferDesc, const void* pB = 0);
		void Reset(DeviceContext*, const void*, unsigned int size);
		void SetCurrent(DeviceContext*);
		void SetCurrent(DeviceContext*, const unsigned int offset);

		~D3DX11IndexBuffer() {}

		ComPtr<ID3D11Buffer> pD3D11Buffer;
		D3D11_BUFFER_DESC	 API_Desc;
		DXGI_FORMAT			 API_Format;
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