#include <Core/WinFramework.h>

#include <SDL/SDL.h>
#include <Video/D3D11/D3D11Driver.h>
#include <Video/GL/GLDriver.h>

namespace Ares {

	void WinFramework::InitGlobalVars() {
		pBaseApp->InitVars();
	}

	void WinFramework::OnCreateApplication() {

		if (SDL_Init(SDL_INIT_VIDEO) < 0) {
			printf("Video initialization failed: %s\n", SDL_GetError());
			exit(1);
		}

		SDL_WM_SetCaption("Ares", 0);

		int flags = SDL_HWSURFACE;

		if (AplicationDescriptor.GraphicsApi == Ares::GraphicsApi_::OPENGL) {
			flags = flags | SDL_OPENGL;
			SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
		}

		flags = flags | SDL_OPENGL;
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

		if (SDL_SetVideoMode(AplicationDescriptor.WindowWidth, AplicationDescriptor.WindowHeight, 32, flags) == 0) {
			printf("Video mode set failed: %s\n", SDL_GetError());
			exit(1);
		}


		if (AplicationDescriptor.GraphicsApi == Ares::GraphicsApi_::OPENGL)
			pBaseDriver = new GLDriver(&AplicationDescriptor);
		else
			pBaseDriver = new D3D11Driver(&AplicationDescriptor);

		pBaseDriver->InitDriver();
		pBaseApp->CreateAssets();
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
		while (SDL_PollEvent(&evento)) {
			if (evento.key.keysym.sym == SDLK_q) {
				m_alive = false;
			}

			if (evento.key.keysym.sym == SDLK_o) {	
				SwitchAPI(Ares::GraphicsApi_::E::OPENGL);
			}

			if (evento.key.keysym.sym == SDLK_d) {
				SwitchAPI(Ares::GraphicsApi_::E::D3D11);
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