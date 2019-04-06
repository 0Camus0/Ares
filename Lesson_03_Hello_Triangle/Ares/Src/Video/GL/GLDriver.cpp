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

	void*	GLDeviceContext::GetAPIObject() const {
		return 0;
	}

	void**	GLDeviceContext::GetAPIObjectReference() {
		return 0;
	}

	void    GLDeviceContext::DestroyResources() {

	}

	void	 GLDriver::InitDriver() {
		GLenum err = glewInit();
		if (GLEW_OK != err) {
			LogPrintError("Error when calling glewInit: %s", glewGetErrorString(err));
		}
		else {
			LogPrintRelease("GL Initialization Successful!");
		}

		SDL_Surface *sur = SDL_GetVideoSurface();
		BBWidth = sur->w;
		BBHeight = sur->h;

		pDevice = new GLDevice();
		pDeviceContext = new GLDeviceContext();
	}

	void	 GLDriver::Update() {

	}

	void	 GLDriver::DestroyDriver() {
		delete pDevice;
		pDevice = NULL;
		delete pDeviceContext;
		pDeviceContext = NULL;
	}

	void	 GLDriver::SetWindow(void *window) {

	}

	void	 GLDriver::Clear() {
		glClearColor(1.0, 0.0, 0.5, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void	 GLDriver::SwapBuffers() {
		SDL_GL_SwapBuffers();
	}
}