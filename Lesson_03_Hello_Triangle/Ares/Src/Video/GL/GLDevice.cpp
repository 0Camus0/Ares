#include <Video/GL/GLDriver.h>
#include <Util/Log.h>

namespace Ares {
	void*	GLDevice::GetAPIObject() const {
		return 0;
	}

	void**	GLDevice::GetAPIObjectReference() {
		return 0;
	}

	void    GLDevice::DestroyResources() {

	}
}