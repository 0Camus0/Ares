#include <Video/D3D11/D3D11Driver.h>

namespace Ares {
	
	ComPtr<ID3D11Device>            D3D11Device;	
	ComPtr<ID3D11DeviceContext>		D3D11DeviceContext; 
	ComPtr<IDXGISwapChain>			DXGISwapchain;	
	ComPtr<ID3D11RenderTargetView>  D3D11RenderTargetView;
	ComPtr<ID3D11DepthStencilView>  D3D11DepthStencilTargetView;
	ComPtr<ID3D11Texture2D>			D3D11DepthTex;	

	void	 D3D11Driver::InitDriver() {

		DXGI_MODE_DESC BackBufferDesc;
		ZeroMemory(&BackBufferDesc, sizeof(DXGI_MODE_DESC));
		BackBufferDesc.Width = pAppDesc->WindowWidth;
		BackBufferDesc.Height = pAppDesc->WindowHeight;
		BackBufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; 
		BackBufferDesc.RefreshRate.Numerator = 0;
		BackBufferDesc.RefreshRate.Denominator = 1;
		BackBufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		BackBufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

		//	Descriptor of the Swap Chain
		DXGI_SWAP_CHAIN_DESC SwapChainDesc;
		ZeroMemory(&SwapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
		SwapChainDesc.BufferDesc = BackBufferDesc;
		SwapChainDesc.BufferCount = 1;
		SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		SwapChainDesc.SampleDesc.Count = 1;
		SwapChainDesc.SampleDesc.Quality = 0;
		SwapChainDesc.OutputWindow = GetActiveWindow();
		SwapChainDesc.Windowed = (pAppDesc->VideoMode != Ares::VideoMode_::FullScreen);
		SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		HRESULT hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL,
#if DEBUG_DRIVER
			D3D11_CREATE_DEVICE_DEBUG,	
#else
			0,
#endif
			NULL, NULL, D3D11_SDK_VERSION, &SwapChainDesc, &DXGISwapchain, &D3D11Device, NULL, &D3D11DeviceContext);

		ComPtr<ID3D11Texture2D> BackBuffer;
		hr = DXGISwapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), &BackBuffer);

		D3D11_TEXTURE2D_DESC descDepth;
		descDepth.Width = pAppDesc->WindowWidth;
		descDepth.Height = pAppDesc->WindowHeight;
		descDepth.MipLevels = 1;
		descDepth.ArraySize = 1;
		descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;	
		descDepth.SampleDesc.Count = 1;
		descDepth.SampleDesc.Quality = 0;
		descDepth.Usage = D3D11_USAGE_DEFAULT;
		descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL; 
		descDepth.CPUAccessFlags = 0;
		descDepth.MiscFlags = 0;
		hr = D3D11Device->CreateTexture2D(&descDepth, NULL, &D3D11DepthTex);	

		D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
		ZeroMemory(&dsvd, sizeof(dsvd));

		dsvd.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;

		hr = D3D11Device->CreateDepthStencilView(D3D11DepthTex.Get(), &dsvd, &D3D11DepthStencilTargetView);

		hr = D3D11Device->CreateRenderTargetView(BackBuffer.Get(), NULL, &D3D11RenderTargetView);

		D3D11DeviceContext->OMSetRenderTargets(1, D3D11RenderTargetView.GetAddressOf(), D3D11DepthStencilTargetView.Get());


		Viewport.TopLeftX = 0;
		Viewport.TopLeftY = 0;
		Viewport.Width = static_cast<float>(pAppDesc->WindowWidth);
		Viewport.Height = static_cast<float>(pAppDesc->WindowHeight);
		Viewport.MinDepth = 0;
		Viewport.MaxDepth = 1;

		D3D11DeviceContext->RSSetViewports(1, &Viewport);
	}

	void	 D3D11Driver::CreateSurfaces() {

	}

	void	 D3D11Driver::DestroySurfaces() {

	}

	void	 D3D11Driver::Update() {

	}

	void	 D3D11Driver::DestroyDriver() {
		D3D11DeviceContext->OMSetRenderTargets(0, 0, 0);
		D3D11DeviceContext->Flush();

		D3D11RenderTargetView.Reset();
		D3D11DepthStencilTargetView.Reset();
	}

	void	 D3D11Driver::SetWindow(void *window) {

	}

	void	 D3D11Driver::SetDimensions(int, int) {

	}

	void	 D3D11Driver::Clear() {
		float rgba[4];
		rgba[0] = 0.5f;
		rgba[1] = 0.5f;
		rgba[2] = 1.0f;
		rgba[3] = 1.0f;


		D3D11DeviceContext->ClearRenderTargetView(D3D11RenderTargetView.Get(), rgba);

		D3D11DeviceContext->ClearDepthStencilView(D3D11DepthStencilTargetView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);
	}

	void	 D3D11Driver::SwapBuffers() {
		DXGISwapchain->Present(0, 0);
	}
}