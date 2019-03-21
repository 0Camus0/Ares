#include <Core\WinFramework.h>
#include <App.h>
#include "Hook.cpp"

Ares::AppBase		  *pApp = 0;
Ares::RootFramework   *pFrameWork = 0;

int main(int arg, char ** args) {
	Ares::ApplicationDesc desc;
	desc.WindowWidth = 1280;
	desc.WindowHeight = 720;
	desc.VideoMode = Ares::VideoMode_::Windowed;
	desc.GraphicsApi = Ares::GraphicsApi_::OPENGL;

	pApp = new App;
	pFrameWork = new Ares::WinFramework((App::AppBase*)pApp, desc);
	pFrameWork->Run();

	delete pFrameWork;
	delete pApp;
	
	return 0;
}

