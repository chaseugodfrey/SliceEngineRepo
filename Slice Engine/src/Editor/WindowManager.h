#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include "WindowTypes.h"

namespace SliceEngine
{

	class WindowManager
	{

	public:
		
		std::vector<std::unique_ptr<EditorWindow>> list;
		void Init();
		void Render();

		template <typename T>
		void AddWindow();

	};

	template <typename T>
	void WindowManager::AddWindow()
	{
		list.push_back(std::make_unique<T>());
	}

}



#endif