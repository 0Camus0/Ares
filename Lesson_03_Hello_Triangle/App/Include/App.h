#ifndef APP_H
#define APP_H

#include <Core/Core.h>

class App : public Ares::AppBase {
public:
	App() : AppBase() {}
	void InitVars();
	void LoadAssets();
	void CreateAssets();
	void DestroyAssets();

	void OnUpdate();
	void OnDraw();
	void OnInput();

	void OnPause();
	void OnResume();
	void OnReset();
};

#endif