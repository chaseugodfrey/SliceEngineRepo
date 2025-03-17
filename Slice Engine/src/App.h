#ifndef SLICE_APP_H
#define SLICE_APP_H

#include "AppWindow.h"
#include "../Engine/SliceEngine.h"

#ifdef EDITOR
#include "../Editor/SliceEditor.h"
#endif 

namespace SliceEngine
{
	class App
	{
		bool isRunning{};
		AppWindow appWindow;
		
#ifdef EDITOR
		Editor editor;
#endif
		std::unique_ptr<Engine> engine;

	public:
		void Init();
		void Update();
		void Exit();
	};
}

#endif 