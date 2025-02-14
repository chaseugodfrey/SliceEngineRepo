#include "../src/pch.h"
#include "Application.h"


// might need to relocate logger
#include "AppModules/Logger.h"


namespace SliceEngine
{
	void Application::Init()
	{
		TimePoint now = std::chrono::high_resolution_clock::now();
		isRunning = true;

		m_mainWindow = std::make_unique<sf::Window>(sf::VideoMode({ 800, 600 }), "Slice Engine", sf::Style::Default);
		m_sessionManager = std::make_unique<SessionManager>(now);

#ifdef GLFW
		GLFWwindow* window;
		glfwCreateWindow(1920, 1080, "Slice Engine", nullptr, nullptr);
#endif
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

			for (auto& module : m_Modules)
			{
				module.Update();
			}

			TestCode();

		}
	}

	void Application::Destroy()
	{
		m_mainWindow->close();
	}

	// TEST CODE AREA

	void Application::TestCode()
	{
		Logger::Log(m_sessionManager->GetDurationInMilliseconds());
	}
}


