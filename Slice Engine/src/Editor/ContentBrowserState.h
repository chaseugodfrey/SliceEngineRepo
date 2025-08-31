#ifndef EDITOR_CONTENT_BROWSER_STATE_H
#define EDITOR_CONTENT_BROWSER_STATE_H

#include <filesystem>

namespace SliceEngine
{
	struct ContentBrowserState
	{
		std::filesystem::path path;
	};
}

#endif