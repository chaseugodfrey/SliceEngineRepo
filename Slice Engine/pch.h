#ifndef PCH_H
#define PCH_H

#include <iostream>
#include <filesystem>
#include <sstream>
#include <iomanip>

#include <chrono>
#include <memory>

#include <string>
#include <vector>
#include <array>
#include <deque>
#include <queue>
#include <map>

#include <algorithm>
#include <functional>
#include <algorithm>
#include <type_traits>

#include <thread>

#include <math.h>

// Logger
#include "src/Logger.h"

// Common Types
#include "src/Vectors/Vector2.h"
#include "src/Vectors/Vector3.h"


// glfw
#include "ThirdParty/glew/GL/glew.h"
#include "ThirdParty/glfw/include/glfw3.h"

#ifdef EDITOR

#include <include/imgui.h>
#include <include/imgui_internal.h>
#include <include/imgui_impl_glfw.h>
#include <include/imgui_impl_opengl3.h>

#endif



#endif 