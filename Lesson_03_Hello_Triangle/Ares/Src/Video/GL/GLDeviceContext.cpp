#include <Video/GL/GLDriver.h>
#include <Util/Log.h>

namespace Ares {
	void*	GLDeviceContext::GetAPIObject() const {
		return 0;
	}

	void**	GLDeviceContext::GetAPIObjectReference() {
		return 0;
	}

	void GLDeviceContext::SetTopology(MeshTopology::E Topology) {
		switch (Topology){
		case Ares::MeshTopology::E::POINT_LIST:
			API_Topology = GL_POINTS;
			break;
		case Ares::MeshTopology::E::LINE_LIST:
			API_Topology = GL_LINES;
			break;
		case Ares::MeshTopology::E::LINE_STRIP:
			API_Topology = GL_LINE_STRIP;
			break;
		case Ares::MeshTopology::E::TRIANGLE_LIST:
			API_Topology = GL_TRIANGLES;
			break;
		case Ares::MeshTopology::E::TRIANGLE_STRIP:
			API_Topology = GL_TRIANGLE_STRIP;
			break;
		default:
			API_Topology = GL_TRIANGLES;
			break;
		}
	}

	void GLDeviceContext::DrawIndexed(unsigned int VertexCount, unsigned int StartIndex, unsigned int StartVertex) {
		glDrawElements(API_Topology, VertexCount, API_IBFormat, 0);
	}

	void GLDeviceContext::DestroyResources() {

	}
}