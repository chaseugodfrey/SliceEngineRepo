#ifndef SLICE_APP_H
#define SLICE_APP_H

#include "AppWindow.h"

namespace SliceEngine
{
	class App
	{
		bool isRunning{};
		AppWindow appWindow;

	public:
		void Init();
		void Update();
		void Exit();
	};
}

#endif 