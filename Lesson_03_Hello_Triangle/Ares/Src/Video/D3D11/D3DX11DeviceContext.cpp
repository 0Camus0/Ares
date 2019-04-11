#include <Video/D3D11/D3DX11Driver.h>
#include <Util/Log.h>

namespace Ares {
	void*	D3DX11DeviceContext::GetAPIObject() const {
		return (void*)pD3D11DeviceContext.Get();
	}

	void**	D3DX11DeviceContext::GetAPIObjectReference() {
		return (void**)pD3D11DeviceContext.GetAddressOf();
	}

	void    D3DX11DeviceContext::DestroyResources() {

	}

	void D3DX11DeviceContext::SetTopology(MeshTopology::E Topology) {
		D3D11_PRIMITIVE_TOPOLOGY API_Topology;
		switch (Topology){
		case MeshTopology::POINT_LIST:
			API_Topology = D3D11_PRIMITIVE_TOPOLOGY_POINTLIST;
			break;
		case MeshTopology::LINE_LIST:
			API_Topology = D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
			break;
		case MeshTopology::LINE_STRIP:
			API_Topology = D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP;
			break;
		case MeshTopology::TRIANGLE_LIST:
			API_Topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
			break;
		case MeshTopology::TRIANGLE_STRIP:
			API_Topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
			break;
		default:
			API_Topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
			break;
		}
		pD3D11DeviceContext->IASetPrimitiveTopology(API_Topology);
	}

	void D3DX11DeviceContext::DrawIndexed(unsigned int VertexCount, unsigned int StartIndex, unsigned int StartVertex) {
		pD3D11DeviceContext->DrawIndexed(VertexCount, StartIndex, StartVertex);
	}
}