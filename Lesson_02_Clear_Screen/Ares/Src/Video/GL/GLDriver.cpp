#include <Video/GL/GLDriver.h>

namespace Ares {
	void	 GLDriver::InitDriver() {
		GLenum err = glewInit();
		if (GLEW_OK != err) {
			printf("Error: %s\n", glewGetErrorString(err));
		}
		SDL_Surface *sur = SDL_GetVideoSurface();
		BBWidth = sur->w;
		BBHeight = sur->h;
	}

	void	 GLDriver::CreateSurfaces() {

	}

	void	 GLDriver::DestroySurfaces() {

	}

	void	 GLDriver::Update() {

	}

	void	 GLDriver::DestroyDriver() {
		
	}

	void	 GLDriver::SetWindow(void *window) {

	}

	void	 GLDriver::SetDimensions(int, int) {

	}

	void	 GLDriver::Clear() {
		glClearColor(1.0, 0.0, 0.5, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void	 GLDriver::SwapBuffers() {
		SDL_GL_SwapBuffers();
	}
}