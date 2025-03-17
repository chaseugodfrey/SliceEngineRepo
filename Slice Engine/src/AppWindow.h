#ifndef SLICE_APP_WINDOW_H
#define SLICE_APP_WINDOW_H

struct GLFWwindow;

namespace SliceEngine
{

	struct WindowData
	{
		float width, height;
		float pos_x, pos_y;
	};

	class AppWindow
	{
		GLFWwindow* m_appWindow;

	public:
		void CreateDefaultWindow();
		void ResizeWindow();
		void SetFullscreen(bool mode);
		bool isWindowClosed();
		GLFWwindow* GetWindow();
	};
}

#endif