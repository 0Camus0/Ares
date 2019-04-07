#ifndef ARES_DRIVER_BASE_H
#define ARES_DRIVER_BASE_H

#include <Core/Config.h>
#include <Core/Defs.h>

namespace Ares {

	class VertexBuffer;
	class IndexBuffer;
	class ConstantBuffer;

	class IBaseDriverObject {
	public:
		virtual void*	GetAPIObject() const = 0;
		virtual void**	GetAPIObjectReference() = 0;
		virtual void	DestroyResources() = 0;
		virtual ~IBaseDriverObject() {}
	};

	class Device : public IBaseDriverObject {
	public:
		~Device() {}
	};

	class DeviceContext : public IBaseDriverObject {
	public:		
		virtual void SetTopology(MeshTopology::E) = 0;
		virtual void DrawIndexed(unsigned int VertexCount, unsigned int StartIndex, unsigned int StartVertex) = 0;
		~DeviceContext() {}

		VertexBuffer	*pVB;
		IndexBuffer		*pIB;
		ConstantBuffer	*pCB;
	};
	
	class IBuffer : public IBaseDriverObject {
	public:
		virtual void Create(Device&, BufferDesc, const void* pB = 0) = 0;
		virtual void Reset(DeviceContext*, const void*, unsigned int size) = 0;
		virtual void SetCurrent(DeviceContext*) = 0;
		virtual ~IBuffer() {}
		
		unsigned char *pBuffer;
		BufferDesc	   Desc;
	};

	class VertexBuffer : public IBuffer {
	public:
		virtual void SetCurrent(DeviceContext*, const unsigned int stride, const unsigned int offset) = 0;
		~VertexBuffer() {}
	};

	class IndexBuffer : public IBuffer {
	public:
		virtual void SetCurrent(DeviceContext*, const unsigned int offset, BufferFormat_::E format = BufferFormat_::BYTE32) = 0;
		~IndexBuffer() {}
	};

	class ConstantBuffer : public IBuffer {
	public:
		~ConstantBuffer() {}
	};

	class BaseDriver {
	public:
		BaseDriver(ApplicationDesc* pDesc) : pAppDesc(pDesc) {  }
		virtual	void	 InitDriver() = 0;
		virtual void	 Update() = 0;
		virtual void	 DestroyDriver() = 0;
		virtual void	 SetWindow(void *window) = 0;
		virtual void	 Clear() = 0;
		virtual void	 SwapBuffers() = 0;
		virtual ~BaseDriver() {}

		
		ApplicationDesc  *pAppDesc;
		Device			 *pDevice;
		DeviceContext	 *pDeviceContext;
		GraphicsApi_::E  CurrentAPI;
		int	BBWidth, BBHeight;
	};
}

#endif