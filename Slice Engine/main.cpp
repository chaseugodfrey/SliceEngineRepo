#include "src/Engine/Engine.h"

int main()
{
	SliceEngine::Engine engine{};
	

	engine.Init();
	
	engine.Update();

	engine.Exit();



	return 0;
}
