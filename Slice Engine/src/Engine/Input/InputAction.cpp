// InputActions.cpp
#include "InputAction.h"

namespace SliceEngine
{
    // ActionMap
    void ActionMap::AddAction(const std::string& actionName)
    {
        if (!actions.count(actionName))
            actions.emplace(actionName, Action{ actionName });
    }

    void ActionMap::AddBinding(const std::string& actionName, const Binding& binding)
    {
        AddAction(actionName);
        actions[actionName].bindings.push_back(binding);
    }

    bool ActionMap::GetActionDown(const std::string& actionName) const
    {
        auto it = actions.find(actionName);
        if (it == actions.end()) return false;
        // any binding down == action down
        for (const auto& b : it->second.bindings)
            if (IsBindingDown(b)) return true;
        return false;
    }

    bool ActionMap::GetActionPressed(const std::string& actionName) const
    {
        auto it = actions.find(actionName);
        if (it == actions.end()) return false;
        for (const auto& b : it->second.bindings)
            if (IsBindingPressed(b)) return true;
        return false;
    }

    bool ActionMap::GetActionReleased(const std::string& actionName) const
    {
        auto it = actions.find(actionName);
        if (it == actions.end()) return false;
        for (const auto& b : it->second.bindings)
            if (IsBindingReleased(b)) return true;
        return false;
    }

    void ActionMap::Update()
    {
        // optional future: maintain edge detection per-action if you want internal caches.
        // current impl queries InputSystem directly for edges each call.
        (void)0;
    }

    // binding helpers
    static inline bool mods_match(const Modifiers& req, int glfwMods)
    {
        const bool hasShift = (glfwMods & GLFW_MOD_SHIFT) != 0;
        const bool hasCtrl = (glfwMods & GLFW_MOD_CONTROL) != 0;
        const bool hasAlt = (glfwMods & GLFW_MOD_ALT) != 0;
        return req.shift == hasShift && req.ctrl == hasCtrl && req.alt == hasAlt;
    }

    bool ActionMap::IsBindingDown(const Binding& b)
    {
        auto& in = InputSystem::Get();
        if (!in.IsEnabled() || in.GetMode() != InputMode::Game) return false;

        switch (b.type)
        {
        case BindingType::Key:         return in.IsKeyDown(b.code);
        case BindingType::MouseButton: return in.IsMouseDown(static_cast<MouseButtons>(b.code));
        default: return false;
        }
    }

    bool ActionMap::IsBindingPressed(const Binding& b)
    {
        auto& in = InputSystem::Get();
        if (!in.IsEnabled() || in.GetMode() != InputMode::Game) return false;

        switch (b.type)
        {
        case BindingType::Key:         return in.IsKeyPressed(b.code);
        case BindingType::MouseButton: return in.IsMousePressed(static_cast<MouseButtons>(b.code));
        default: return false;
        }
    }

    bool ActionMap::IsBindingReleased(const Binding& b)
    {
        auto& in = InputSystem::Get();
        if (!in.IsEnabled() || in.GetMode() != InputMode::Game) return false;

        switch (b.type)
        {
        case BindingType::Key:         return in.IsKeyReleased(b.code);
        case BindingType::MouseButton: return in.IsMouseReleased(static_cast<MouseButtons>(b.code));
        default: return false;
        }
    }

    // InputActions
    ActionMap& InputActions::CreateMap(const std::string& mapName)
    {
        auto it = maps.find(mapName);
        if (it == maps.end())
            it = maps.emplace(mapName, ActionMap(mapName)).first;
        if (active.empty()) active = mapName;
        return it->second;
    }

    bool InputActions::HasMap(const std::string& mapName) const
    {
        return maps.find(mapName) != maps.end();
    }

    ActionMap* InputActions::GetMap(const std::string& mapName)
    {
        auto it = maps.find(mapName);
        return (it == maps.end()) ? nullptr : &it->second;
    }

    void InputActions::SetActiveMap(const std::string& mapName)
    {
        if (maps.find(mapName) != maps.end())
            active = mapName;
    }

    ActionMap* InputActions::GetActiveMap()
    {
        if (active.empty()) return nullptr;
        auto it = maps.find(active);
        return (it == maps.end()) ? nullptr : &it->second;
    }

    bool InputActions::GetActionPressed(const std::string& name)
    {
        auto* m = GetActiveMap(); if (!m) return false;
        return m->GetActionPressed(name);
    }
    bool InputActions::GetActionDown(const std::string& name)
    {
        auto* m = GetActiveMap(); if (!m) return false;
        return m->GetActionDown(name);
    }
    bool InputActions::GetActionReleased(const std::string& name)
    {
        auto* m = GetActiveMap(); if (!m) return false;
        return m->GetActionReleased(name);
    }

    void InputActions::Update()
    {
        auto* m = GetActiveMap();
        if (m) m->Update();
    }
}
