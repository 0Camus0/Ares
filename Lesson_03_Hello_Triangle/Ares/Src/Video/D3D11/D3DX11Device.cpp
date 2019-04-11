#include <Video/D3D11/D3DX11Driver.h>
#include <Util/Log.h>

namespace Ares {
	void*	D3DX11Device::GetAPIObject() const {
		return (void*)pD3D11Device.Get();
	}

	void**	D3DX11Device::GetAPIObjectReference() {
		return (void**)pD3D11Device.GetAddressOf();
	}

	void    D3DX11Device::DestroyResources() {

	}
}