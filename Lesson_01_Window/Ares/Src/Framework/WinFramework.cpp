#include <Core/WinFramework.h>

#include <SDL/SDL.h>

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

		if (AplicationDescriptor.videoMode == Ares::VideoMode::FullScreen) {
			flags |= SDL_FULLSCREEN;
		}

		if (SDL_SetVideoMode(AplicationDescriptor.WindowWidth, AplicationDescriptor.WindowHeight, 32, flags) == 0) {
			printf("Video mode set failed: %s\n", SDL_GetError());
			exit(1);
		}

		pBaseApp->CreateAssets();
	}

	void WinFramework::OnDestroyApplication() {
		pBaseApp->DestroyAssets();
	}

	void WinFramework::OnInterruptApplication() {

	}

	void WinFramework::OnResumeApplication() {

	}

	void WinFramework::UpdateApplication() {
		pBaseApp->OnUpdate();
		pBaseApp->OnDraw();
	}

	void WinFramework::ProcessInput() {
		SDL_Event       evento;
		while (SDL_PollEvent(&evento)) {
			if (evento.key.keysym.sym == SDLK_q) {
				m_alive = false;
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