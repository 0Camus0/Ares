#include <Video/GL/GLDriver.h>
#include <Util/Log.h>

#include <stdio.h>
#include <string.h>

namespace Ares {
	void*	GLIndexBuffer::GetAPIObject() const {
		return 0;
	}

	void**	GLIndexBuffer::GetAPIObjectReference() {
		return 0;
	}
	
	void GLIndexBuffer::DestroyResources() {
		if (Desc.State == BufferState_::E::BUFFER_ALLOCATED) {
			delete[] pBuffer;
			pBuffer = 0;
		}
		glDeleteBuffers(1, &API_Id);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void GLIndexBuffer::Create(Device* pDevice, BufferDesc desc, const void* pB) {
		Desc.ByteWidth = desc.ByteWidth;
		Desc.Usage = desc.Usage;
		switch (Desc.Usage) {
		case BufferUsage_::E::DEFAULT:
			API_Usage = GL_STATIC_DRAW;
			break;
		case BufferUsage_::E::STATIC:
			API_Usage = GL_STATIC_DRAW;
			break;
		case BufferUsage_::E::DYNAMIC:
			API_Usage = GL_DYNAMIC_DRAW;
			break;
		default:
			API_Usage = GL_STATIC_DRAW;
			break;
		}
		if (pB && Desc.ByteWidth) {
			pBuffer = new unsigned char[Desc.ByteWidth + 1];
			memcpy(pBuffer, pB, Desc.ByteWidth);
			pBuffer[Desc.ByteWidth] = '\0';
			Desc.State = BufferState_::E::BUFFER_ALLOCATED;
		}
		glGenBuffers(1, &API_Id);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, API_Id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, Desc.ByteWidth, &pBuffer[0], API_Usage);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void GLIndexBuffer::Reset(DeviceContext* pDeviceContext, const void* pB, unsigned int size) {
		Desc.ByteWidth = size;
		if (Desc.State == BufferState_::E::BUFFER_ALLOCATED) {
			delete[] pBuffer;
		}
		pBuffer = new unsigned char[Desc.ByteWidth + 1];
		memcpy(pBuffer, pB, Desc.ByteWidth);
		pBuffer[Desc.ByteWidth] = '\0';
		if (API_Usage == GL_STATIC_DRAW) {
			glDeleteBuffers(1, &API_Id);
			glGenBuffers(1, &API_Id);
		}
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, API_Id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, Desc.ByteWidth, &pBuffer[0], API_Usage);
	}

	void GLIndexBuffer::SetCurrent(DeviceContext* pDeviceContext) {
		pDeviceContext->pIB = (IndexBuffer *)this;
	}

	void GLIndexBuffer::SetCurrent(DeviceContext* pDeviceContext, const unsigned int offset, BufferFormat_::E format) {
		pDeviceContext->pIB = (IndexBuffer *)this;
		GetGLDeviceContext(pDeviceContext)->IBOffset = offset;
		GetGLDeviceContext(pDeviceContext)->API_IBFormat = format;
	}
}