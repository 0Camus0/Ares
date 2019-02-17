#include <Core\WinFramework.h>
#include <App.h>

Ares::AppBase		  *pApp = 0;
Ares::RootFramework   *pFrameWork = 0;

int main(int arg, char ** args) {

	Ares::ApplicationDesc desc;
	desc.WindowWidth = 1280;
	desc.WindowHeight = 720;
	desc.videoMode = Ares::VideoMode::Windowed;
	
	pApp = new App;
	pFrameWork = new Ares::WinFramework((App::AppBase*)pApp);
	pFrameWork->Run();

	delete pFrameWork;
	delete pApp;
	
	
	return 0;
}