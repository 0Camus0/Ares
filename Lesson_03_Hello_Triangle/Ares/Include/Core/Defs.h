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

	namespace BufferType_ {
		enum E {
			VERTEX,
			INDEX,
			CONSTANT,
			GENERIC
		};
	}

	namespace BufferUsage_ {
		enum E {
			DEFAULT,
			DYNAMIC,
			STATIC
		};
	}

	namespace BufferFormat_ {
		enum E {
			BYTE8,
			BYTE16,
			BYTE32,
			NOT_APPLICABLE
		};
	}

	namespace BufferState_ {
		enum E {
			BUFFER_ALLOCATED,
			BUFFER_NOT_ALLOCATED
		};
	}

	namespace MeshTopology {
		enum E {
			POINT_LIST,
			LINE_LIST,
			LINE_STRIP,
			TRIANGLE_LIST,
			TRIANGLE_STRIP
		};
	}

	struct BufferDesc {
		BufferDesc() :	ByteWidth(0), 
						Stride(0),
						Offset(0), 
						Type(BufferType_::E::GENERIC),
						Usage(BufferUsage_::E::DEFAULT),
						Format(BufferFormat_::E::NOT_APPLICABLE),
						State(BufferState_::E::BUFFER_NOT_ALLOCATED)
						{}
		unsigned int	 ByteWidth;
		unsigned int	 Stride;
		unsigned int	 Offset;
		BufferType_::E   Type;
		BufferUsage_::E  Usage;	
		BufferFormat_::E Format;
		BufferState_::E  State;
	};

	struct ApplicationDesc {
		ApplicationDesc() : WindowWidth(1280),
							WindowHeight(720),
							VideoMode(VideoMode_::E::Windowed),
							GraphicsApi(GraphicsApi_::E::D3D11)
						{}
		unsigned int	WindowWidth;
		unsigned int	WindowHeight;
		VideoMode_::E	VideoMode;
		GraphicsApi_::E	GraphicsApi;		
	};
}

#endif