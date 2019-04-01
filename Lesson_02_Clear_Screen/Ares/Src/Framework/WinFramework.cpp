#include <Core/WinFramework.h>

#include <SDL/SDL.h>
#include <Video/D3D11/D3D11Driver.h>
#include <Video/GL/GLDriver.h>

#include <Util/Log.h>
#include <string>

namespace Ares {

	void WinFramework::InitGlobalVars() {
		pBaseApp->InitVars();
	}

	void WinFramework::OnCreateApplication() {

		if (SDL_Init(SDL_INIT_VIDEO) < 0) {
			LogPrintError("Video initialization failed: %s", SDL_GetError());
			exit(1);
		}
		else {
			LogPrintRelease("SDL Init Completed with Success!");
		}

		std::string  Title = "Ares [";
		Title += (AplicationDescriptor.GraphicsApi == Ares::GraphicsApi_::OPENGL) ? "GL" : "D3D11";
		Title += "]";

		SDL_WM_SetCaption(Title.c_str(), 0);

		int flags = SDL_HWSURFACE;

		if (AplicationDescriptor.GraphicsApi == Ares::GraphicsApi_::OPENGL) {
			flags = flags | SDL_OPENGL;
			SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
		}

		if (AplicationDescriptor.VideoMode == Ares::VideoMode_::FullScreen) {
			flags = flags | SDL_FULLSCREEN;
		}

		flags = flags | SDL_OPENGL;
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

		if (SDL_SetVideoMode(AplicationDescriptor.WindowWidth, AplicationDescriptor.WindowHeight, 32, flags) == 0) {
			LogPrintError("Video mode set failed: %s", SDL_GetError());
			exit(1);
		}

		if (AplicationDescriptor.GraphicsApi == Ares::GraphicsApi_::OPENGL)
			pBaseDriver = new GLDriver(&AplicationDescriptor);
		else
			pBaseDriver = new D3D11Driver(&AplicationDescriptor);

		pBaseDriver->InitDriver();
		pBaseApp->CreateAssets();

		if(IsDebuggerPresent()){
			LogPrintRelease("Hi Debbugger!");
		}
	}

	void WinFramework::SwitchAPI(GraphicsApi_::E api) {
		if (AplicationDescriptor.GraphicsApi == api)
			return;

		OnDestroyApplication();

		AplicationDescriptor.GraphicsApi = api;
		
		OnCreateApplication();
	}

	void WinFramework::OnDestroyApplication() {
		pBaseApp->DestroyAssets();
		pBaseDriver->DestroyDriver();
		delete pBaseDriver;
		pBaseDriver = NULL;
		SDL_Quit();
	}

	void WinFramework::OnInterruptApplication() {

	}

	void WinFramework::OnResumeApplication() {

	}

	void WinFramework::UpdateApplication() {
		pBaseApp->OnUpdate();

		pBaseDriver->Clear();

		pBaseApp->OnDraw();

		pBaseDriver->SwapBuffers();
	}

	void WinFramework::ProcessInput() {
		SDL_Event       evento;
		static int		api = (int)AplicationDescriptor.GraphicsApi;

		while (SDL_PollEvent(&evento)) {
			if (evento.key.keysym.sym == SDLK_q) {
				m_alive = false;
				LogPrintInfo("About to close the Program");
			}

			if (evento.key.keysym.sym == SDLK_a) {
				api++;
				if (api >= Ares::GraphicsApi_::E::MAX_GRAPHICS_API) {
					api = Ares::GraphicsApi_::E::OPENGL;
				}
				SwitchAPI((Ares::GraphicsApi_::E)api);
			}
		}
	}

	void WinFramework::ResetApplication() {

	}

	void WinFramework::Run() {
		OnCreateApplication();
		while (m_alive) {
			ProcessInput();
			UpdateApplication();
		}
		OnDestroyApplication();
	}
}