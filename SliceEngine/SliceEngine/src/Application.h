#ifndef SLICE_APP_H
#define SLICE_APP_H

#include <SFML/Window.hpp>
#include "AppModules/AppModuleList.h"

namespace SliceEngine
{
	class Application
	{
		bool isRunning;

		std::unique_ptr<sf::Window> m_mainWindow;
		std::unique_ptr<SessionManager> m_sessionManager;
		std::vector<IModule> m_Modules;

	public:

		void Init();
		void Run();
		void Destroy();

		void TestCode();
	};
}


#endif