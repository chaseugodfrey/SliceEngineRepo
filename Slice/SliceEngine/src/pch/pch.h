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
#include "Logger.h"

// Common Types
#include "Vectors/Vector2.h"
#include "Vectors/Vector3.h"

// external libs

// glfw
#include <glew.h>
#include <glfw3.h>

// fmod
#include <fmod.hpp>
#include <fmod_common.h>
#include <fmod_studio.hpp>
#include <fmod_studio_common.h>

//// imgui
//#include <imgui.h>
//#include <imgui_internal.h>
//#include <imgui_impl_glfw.h>
//#include <imgui_impl_opengl3.h>
//#include <ImGuizmo.h>

// jolt
#include <Jolt.h>
#include <RegisterTypes.h>
#include <Core/Factory.h>
#include <Core/TempAllocator.h>
#include <Core/JobSystemThreadPool.h>
#include <Physics/PhysicsSettings.h>
#include <Physics/PhysicsSystem.h>
#include <Physics/Collision/Shape/BoxShape.h>
#include <Physics/Collision/Shape/SphereShape.h>
#include <Physics/Body/BodyCreationSettings.h>
#include <Physics/Body/BodyActivationListener.h>

#endif 