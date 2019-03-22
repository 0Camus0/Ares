#ifndef ARES_DEFS_H
#define ARES_DEFS_H

namespace Ares {

	namespace VideoMode_ {
		enum E {
			FullScreen,
			Windowed
		};
	}

	namespace GraphicsApi_ {
		enum E {
			OPENGL = 0,
			D3D11,
			MAX_GRAPHICS_API
		};
	}

	struct ApplicationDesc {
		unsigned int	WindowWidth;
		unsigned int	WindowHeight;
		VideoMode_::E	VideoMode;
		GraphicsApi_::E	GraphicsApi;
		ApplicationDesc() {
			WindowWidth		= 1280;
			WindowHeight	= 720;
			VideoMode		= VideoMode_::Windowed;
			GraphicsApi		= GraphicsApi_::D3D11;
		}
	};
}

#endif