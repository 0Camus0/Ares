#include <Video/D3D11/D3DX11Driver.h>
#include <Util/Log.h>

#include <stdio.h>
#include <string.h>

namespace Ares {
	void*	D3DX11IndexBuffer::GetAPIObject() const {
		return (void*)pD3D11Buffer.Get();
	}

	void**	D3DX11IndexBuffer::GetAPIObjectReference() {
		return (void**)pD3D11Buffer.GetAddressOf();
	}

	void D3DX11IndexBuffer::DestroyResources() {
		if (Desc.State == BufferState_::E::BUFFER_ALLOCATED) {
			delete[] pBuffer;
			pBuffer = 0;
			Desc.State = BufferState_::E::BUFFER_NOT_ALLOCATED;
		}
		pD3D11Buffer.Get()->Release();
	}

	void D3DX11IndexBuffer::Create(Device* pDevice, BufferDesc desc, const void* pB) {
		Desc = desc;
		ID3D11Device *pD3D11Device = reinterpret_cast<ID3D11Device*>(pDevice->GetAPIObject());
		switch (Desc.Usage) {
		case BufferUsage_::E::DEFAULT:
			API_Desc.Usage = D3D11_USAGE_DEFAULT;
			break;
		case BufferUsage_::E::DYNAMIC:
			API_Desc.Usage = D3D11_USAGE_DYNAMIC;
			API_Desc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
			break;
		case BufferUsage_::E::STATIC:
			API_Desc.Usage = D3D11_USAGE_IMMUTABLE;
			break;
		default:
			API_Desc.Usage = D3D11_USAGE_DEFAULT;
			break;
		}

		switch (Desc.Format){
		case BufferFormat_::E::BYTE16:
			API_Format = DXGI_FORMAT::DXGI_FORMAT_R16_UINT;
			break;
		case BufferFormat_::E::BYTE32:
			API_Format = DXGI_FORMAT::DXGI_FORMAT_R32_UINT;
			break;
		default:
			API_Format = DXGI_FORMAT::DXGI_FORMAT_R32_UINT;
			break;
		}

		API_Desc.ByteWidth = Desc.ByteWidth;
		API_Desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

		if (pB && Desc.ByteWidth) {
			pBuffer = new unsigned char[Desc.ByteWidth + 1];
			memcpy(pBuffer, pB, Desc.ByteWidth);
			pBuffer[Desc.ByteWidth] = '\0';
			Desc.State = BufferState_::E::BUFFER_ALLOCATED;
			D3D11_SUBRESOURCE_DATA ApiData = { pBuffer, 0, 0 };
			pD3D11Device->CreateBuffer(&API_Desc, &ApiData, pD3D11Buffer.GetAddressOf());
		}
		else {
			pD3D11Device->CreateBuffer(&API_Desc, 0, pD3D11Buffer.GetAddressOf());
		}
	}

	void D3DX11IndexBuffer::Reset(DeviceContext* pDeviceContext, const void* pB, unsigned int size) {
		ID3D11DeviceContext *pD3D11DeviceContext = reinterpret_cast<ID3D11DeviceContext*>(pDeviceContext->GetAPIObject());
		Desc.ByteWidth = size;
		if (Desc.State == BufferState_::E::BUFFER_ALLOCATED) {
			delete[] pBuffer;
		}
		pBuffer = new unsigned char[Desc.ByteWidth + 1];
		memcpy(pBuffer, pB, Desc.ByteWidth);
		pBuffer[Desc.ByteWidth] = '\0';
		pD3D11DeviceContext->UpdateSubresource(pD3D11Buffer.Get(), 0, 0, &pBuffer[0], 0, 0);
	}

	void D3DX11IndexBuffer::SetCurrent(DeviceContext* pDeviceContext) {
		pDeviceContext->pIB = (IndexBuffer *)this;
		ID3D11DeviceContext *pD3D11DeviceContext = reinterpret_cast<ID3D11DeviceContext*>(pDeviceContext->GetAPIObject());
		pD3D11DeviceContext->IASetIndexBuffer(pD3D11Buffer.Get(), API_Format, 0);
	}

	void D3DX11IndexBuffer::SetCurrent(DeviceContext* pDeviceContext, const unsigned int offset) {
		pDeviceContext->pIB = (IndexBuffer *)this;
		ID3D11DeviceContext *pD3D11DeviceContext = reinterpret_cast<ID3D11DeviceContext*>(pDeviceContext->GetAPIObject());
		pD3D11DeviceContext->IASetIndexBuffer(pD3D11Buffer.Get(), API_Format, offset);
	}
}