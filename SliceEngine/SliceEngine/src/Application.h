#ifndef SLICE_APP_H
#define SLICE_APP_H

#include <SFML/Window.hpp>

namespace SliceEngine
{
	class Application
	{
		bool isRunning;

		std::unique_ptr<sf::Window> m_mainWindow;

	public:

		void Init();
		void Run();
		void Destroy();
	};
}


#endif