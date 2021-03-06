#ifndef ARES_GL_DRIVER_H
#define ARES_GL_DRIVER_H

#include <Core/BaseDriver.h>

#include <GL/glew.h>
#include <SDL/SDL.h>

namespace Ares {
	class GLDriver : public BaseDriver {
	public:
		GLDriver(ApplicationDesc *pDesc) : BaseDriver(pDesc) {}
		~GLDriver() {

		}
		void	 InitDriver();
		void	 Update();
		void	 DestroyDriver();
		void	 SetWindow(void *window);
		void	 Clear();
		void	 SwapBuffers();
	};
}

#endif