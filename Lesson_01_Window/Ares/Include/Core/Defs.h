#ifndef ARES_DEFS_H
#define ARES_DEFS_H

namespace Ares {

	namespace VideoMode {
		enum E {
			FullScreen,
			Windowed
		};
	}

	struct ApplicationDesc {
		unsigned int WindowWidth;
		unsigned int WindowHeight;
		VideoMode::E videoMode;
		ApplicationDesc() {
			WindowWidth = 1280;
			WindowHeight = 720;
			videoMode = VideoMode::Windowed;
		}
	};
}

#endif