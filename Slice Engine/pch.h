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
#include "src/Engine/Logger.h"

// Common Types
#include "src/Engine/Vectors/Vector2.h"
#include "src/Engine/Vectors/Vector3.h"


// glfw
#include <glew.h>
#include <glfw3.h>

// fmod
#include <fmod/include/fmod.hpp>
#include <fmod/include/fmod_common.h>
#include <fmod/include/fmod_studio.hpp>
#include <fmod/include/fmod_studio_common.h>

// imgui
#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

// jolt
#include <JoltLib/Jolt/RegisterTypes.h>
#include <JoltLib/Jolt/Core/Factory.h>
#include <JoltLib/Jolt/Core/TempAllocator.h>
#include <JoltLib/Jolt/Core/JobSystemThreadPool.h>
#include <JoltLib/Jolt/Physics/PhysicsSettings.h>
#include <JoltLib/Jolt/Physics/PhysicsSystem.h>
#include <JoltLib/Jolt/Physics/Collision/Shape/BoxShape.h>
#include <JoltLib/Jolt/Physics/Collision/Shape/SphereShape.h>
#include <JoltLib/Jolt/Physics/Body/BodyCreationSettings.h>
#include <JoltLib/Jolt/Physics/Body/BodyActivationListener.h>

#endif 