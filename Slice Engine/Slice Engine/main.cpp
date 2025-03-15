#include "src/App.h"

int main()
{
	SliceEngine::App app{};
	app.Init();
	app.Update();
	app.Exit();
	return 0;
}
