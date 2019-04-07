#ifndef ARES_GL_DRIVER_H
#define ARES_GL_DRIVER_H

#include <Core/BaseDriver.h>

#include <GL/glew.h>
#include <SDL/SDL.h>

namespace Ares {

	class GLDevice : public Device {
	public:		
		void*	GetAPIObject() const;
		void**	GetAPIObjectReference();
		void    DestroyResources();
		~GLDevice() {}
	};

	class GLDeviceContext : public DeviceContext {
	public:		
		void*	GetAPIObject() const;
		void**	GetAPIObjectReference();
		void    DestroyResources();

		void SetTopology(MeshTopology::E);
		void DrawIndexed(unsigned int VertexCount, unsigned int StartIndex, unsigned int StartVertex);

		~GLDeviceContext() {}

		unsigned int API_IBFormat;
		unsigned int API_Topology;
		unsigned int Stride;
		unsigned int Offset;
	};

	class GLVertexBuffer : public VertexBuffer {
	public:
		void*	GetAPIObject() const;
		void**	GetAPIObjectReference();
		void    DestroyResources();
		void Create(Device*, BufferDesc, const void* pB = 0);
		void Reset(DeviceContext*, const void*, unsigned int size);
		void SetCurrent(DeviceContext*);
		void SetCurrent(DeviceContext*, const unsigned int stride, const unsigned int offset);
		~GLVertexBuffer(){}

		unsigned int API_Id;
		unsigned int API_Usage;
	};

	class GLDriver : public BaseDriver {
	public:
		GLDriver(ApplicationDesc *pDesc) : BaseDriver(pDesc) {}
		void	 InitDriver();
		void	 Update();
		void	 DestroyDriver();
		void	 SetWindow(void *window);
		void	 Clear();
		void	 SwapBuffers();
		~GLDriver() {}
	};
}

#define GetGLDeviceContext(a) reinterpret_cast<Ares::GLDeviceContext*>(a)

#endif