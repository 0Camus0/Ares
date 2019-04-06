#include <Video/D3D11/D3DX11Driver.h>
#include <Util/Log.h>

namespace Ares {
	
	void*	D3DX11Device::GetAPIObject() const {
		return (void*)D3D11Device.Get();
	}

	void**	D3DX11Device::GetAPIObjectReference(){
		return (void**)D3D11Device.GetAddressOf();
	}

	void*	D3DX11DeviceContext::GetAPIObject() const {
		return (void*)D3D11DeviceContext.Get();
	}

	void**	D3DX11DeviceContext::GetAPIObjectReference() {
		return (void**)D3D11DeviceContext.GetAddressOf();
	}

	void	 D3DX11Driver::InitDriver() {	
		D3D11_DEPTH_STENCIL_VIEW_DESC DescStencilView;
		ComPtr<ID3D11Texture2D>		  pBackBuffer;
		DXGI_MODE_DESC			      DescBackBuffer;
		DXGI_SWAP_CHAIN_DESC          DescSwapChain;
		D3D11_TEXTURE2D_DESC          DescDepthTexture;		
		ID3D11Device                 *pD3D11Device = NULL;
		ID3D11DeviceContext          *pD3D11DeviceContext = NULL;
		HRESULT						  hr;

		pDevice = new D3DX11Device();
		pDeviceContext = new D3DX11DeviceContext();
		
		ZeroMemory(&DescBackBuffer, sizeof(DXGI_MODE_DESC));
		DescBackBuffer.Width = pAppDesc->WindowWidth;
		DescBackBuffer.Height = pAppDesc->WindowHeight;
		DescBackBuffer.Format = DXGI_FORMAT_R8G8B8A8_UNORM; 
		DescBackBuffer.RefreshRate.Numerator = 0;
		DescBackBuffer.RefreshRate.Denominator = 1;
		DescBackBuffer.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		DescBackBuffer.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		
		ZeroMemory(&DescSwapChain, sizeof(DXGI_SWAP_CHAIN_DESC));
		DescSwapChain.BufferDesc = DescBackBuffer;
		DescSwapChain.BufferCount = 1;
		DescSwapChain.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		DescSwapChain.SampleDesc.Count = 1;
		DescSwapChain.SampleDesc.Quality = 0;
		DescSwapChain.OutputWindow = GetActiveWindow();
		DescSwapChain.Windowed = (pAppDesc->VideoMode != Ares::VideoMode_::FullScreen);
		DescSwapChain.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL,
#if DEBUG_DRIVER
			D3D11_CREATE_DEVICE_DEBUG,	
#else
			0,
#endif
			NULL, NULL, D3D11_SDK_VERSION, &DescSwapChain, &DXGISwapchain, reinterpret_cast<ID3D11Device**>(pDevice->GetAPIObjectReference()), NULL, reinterpret_cast<ID3D11DeviceContext**>(pDeviceContext->GetAPIObjectReference()));

		 if (!SUCCEEDED(hr)) {
			 LogPrintError("Error creating the Device, Swap Chain and Context %d", (int)hr);
			 goto _end;
		 }

		 pD3D11Device = reinterpret_cast<ID3D11Device*>(pDevice->GetAPIObject());
		 pD3D11DeviceContext = reinterpret_cast<ID3D11DeviceContext*>(pDeviceContext->GetAPIObject());
		
		hr = DXGISwapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), &pBackBuffer);

		if (!SUCCEEDED(hr)) {
			LogPrintError("Error getting the Back Buffer %d", (int)hr);
			goto _end;
		}

		DescDepthTexture.Width = pAppDesc->WindowWidth;
		DescDepthTexture.Height = pAppDesc->WindowHeight;
		DescDepthTexture.MipLevels = 1;
		DescDepthTexture.ArraySize = 1;
		DescDepthTexture.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;	
		DescDepthTexture.SampleDesc.Count = 1;
		DescDepthTexture.SampleDesc.Quality = 0;
		DescDepthTexture.Usage = D3D11_USAGE_DEFAULT;
		DescDepthTexture.BindFlags = D3D11_BIND_DEPTH_STENCIL; 
		DescDepthTexture.CPUAccessFlags = 0;
		DescDepthTexture.MiscFlags = 0;
		hr = pD3D11Device->CreateTexture2D(&DescDepthTexture, NULL, &D3D11DepthTex);

		if (!SUCCEEDED(hr)) {
			LogPrintError("Error creating the Depth Texture %d", (int)hr);
			goto _end;
		}
		
		ZeroMemory(&DescStencilView, sizeof(DescStencilView));

		DescStencilView.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		DescStencilView.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;

		hr = pD3D11Device->CreateDepthStencilView(D3D11DepthTex.Get(), &DescStencilView, &D3D11DepthStencilTargetView);

		if (!SUCCEEDED(hr)) {
			LogPrintError("Error creating the Depth Stencil View %d", (int)hr);
			goto _end;
		}

		hr = pD3D11Device->CreateRenderTargetView(pBackBuffer.Get(), NULL, &D3D11RenderTargetView);

		if (!SUCCEEDED(hr)) {
			LogPrintError("Error creating the Render Target View %d", (int)hr);
			goto _end;
		}

		pD3D11DeviceContext->OMSetRenderTargets(1, D3D11RenderTargetView.GetAddressOf(), D3D11DepthStencilTargetView.Get());

		Viewport.TopLeftX = 0;
		Viewport.TopLeftY = 0;
		Viewport.Width = static_cast<float>(pAppDesc->WindowWidth);
		Viewport.Height = static_cast<float>(pAppDesc->WindowHeight);
		Viewport.MinDepth = 0;
		Viewport.MaxDepth = 1;

		pD3D11DeviceContext->RSSetViewports(1, &Viewport);

	_end:
		if (!SUCCEEDED(hr)) {
			LogPrintError("Fatal exiting program!");
			exit(1);
		}
		else {
			LogPrintRelease("D3D11 Initialization Successful!");
		}		
	}

	void	 D3DX11Driver::Update() {

	}

	void	 D3DX11Driver::DestroyDriver() {
		ID3D11DeviceContext          *pD3D11DeviceContext = reinterpret_cast<ID3D11DeviceContext*>(pDeviceContext->GetAPIObject());

		pD3D11DeviceContext->OMSetRenderTargets(0, 0, 0);
		pD3D11DeviceContext->Flush();
		pD3D11DeviceContext = NULL;

		D3D11RenderTargetView.Reset();
		D3D11DepthStencilTargetView.Reset();

		delete pDevice;
		pDevice = NULL;
		delete pDeviceContext;
		pDeviceContext = NULL;
	}

	void	 D3DX11Driver::SetWindow(void *window) {

	}

	void	 D3DX11Driver::Clear() {
		float rgba[4];
		ID3D11Device                 *pD3D11Device = reinterpret_cast<ID3D11Device*>(pDevice->GetAPIObject());
		ID3D11DeviceContext          *pD3D11DeviceContext = reinterpret_cast<ID3D11DeviceContext*>(pDeviceContext->GetAPIObject());

		rgba[0] = 0.5f;
		rgba[1] = 0.5f;
		rgba[2] = 1.0f;
		rgba[3] = 1.0f;


		pD3D11DeviceContext->ClearRenderTargetView(D3D11RenderTargetView.Get(), rgba);

		pD3D11DeviceContext->ClearDepthStencilView(D3D11DepthStencilTargetView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);
	}

	void	 D3DX11Driver::SwapBuffers() {
		DXGISwapchain->Present(0, 0);
	}
}