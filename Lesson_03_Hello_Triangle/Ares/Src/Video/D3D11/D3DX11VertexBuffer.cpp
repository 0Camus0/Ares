#include <Video/D3D11/D3DX11Driver.h>
#include <Util/Log.h>

#include <stdio.h>
#include <string.h>

namespace Ares {
	void*	D3DX11VertexBuffer::GetAPIObject() const {
		return (void*)pD3D11Buffer.Get();
	}
	
	void**	D3DX11VertexBuffer::GetAPIObjectReference() {
		return (void**)pD3D11Buffer.GetAddressOf();
	}

	void D3DX11VertexBuffer::DestroyResources() {

	}

	void D3DX11VertexBuffer::Create(Device* pDevice, BufferDesc desc, const void* pB) {

	}

	void D3DX11VertexBuffer::Reset(DeviceContext* pDeviceContext, const void* pB, unsigned int size) {

	}

	void D3DX11VertexBuffer::SetCurrent(DeviceContext* pDeviceContext) {

	}

	void D3DX11VertexBuffer::SetCurrent(DeviceContext* pDeviceContext, const unsigned int stride, const unsigned int offset) {

	}
}