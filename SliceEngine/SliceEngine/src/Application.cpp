#include "../src/pch.h"
#include "Application.h"
#include "AppModules/Logger.h"

namespace SliceEngine
{
	void Application::Init()
	{
		isRunning = true;

		m_mainWindow = std::make_unique<sf::Window>(sf::VideoMode({ 800, 600 }), "Slice Engine", sf::Style::Default);
	}

	void Application::Run()
	{
		while (isRunning)
		{
			while (const std::optional event = m_mainWindow->pollEvent())
			{
				if (event->is<sf::Event::Closed>())
				{
					isRunning = false;
				}
			}

			int i = 10;
			Logger::Log(i);
		}
	}

	void Application::Destroy()
	{
		m_mainWindow->close();
	}
}


