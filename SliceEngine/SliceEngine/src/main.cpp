// ===== SLICE ENGINE =====
// -- Created 8 Feb 2025
// -- Chase Rodrigues

#include "Application.h"

int main()
{
	SliceEngine::Core app;
	app.Init();
	app.Run();
	app.Destroy();

	return 0;
}