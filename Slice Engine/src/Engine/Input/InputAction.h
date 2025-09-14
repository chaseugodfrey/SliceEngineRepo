// InputActions.h
#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <functional>
#include <optional>
#include "InputTypes.h"
#include "InputSystem.h"

namespace SliceEngine
{
    enum class ActionState : uint8_t { None, Started, Performed, Canceled };
    enum class BindingType : uint8_t { Key, MouseButton };

    struct Binding
    {
        BindingType type{ BindingType::Key };
        int code{ 0 };            // GLFW key or GLFW mouse button index
        Modifiers mods{};       // required modifiers (exact match)

        static Binding Key(int key, Modifiers m = {}) { return { BindingType::Key, key, m }; }
        static Binding Mouse(int button, Modifiers m = {}) { return { BindingType::MouseButton, button, m }; }
    };

    struct Action
    {
        std::string name;
        std::vector<Binding> bindings;
        // polling cache
        bool wasDownLastFrame{ false };
    };

    class ActionMap
    {
    public:
        explicit ActionMap(std::string mapName) : name(std::move(mapName)) {}
        const std::string& GetName() const { return name; }

        void AddAction(const std::string& actionName);
        void AddBinding(const std::string& actionName, const Binding& binding);

        // polling api (unity-style)
        bool GetActionPressed(const std::string& actionName) const;
        bool GetActionDown(const std::string& actionName) const;
        bool GetActionReleased(const std::string& actionName) const;

        // internal update (called each frame)
        void Update();

    private:
        std::string name;
        std::unordered_map<std::string, Action> actions;

        static bool IsBindingDown(const Binding& b);
        static bool IsBindingPressed(const Binding& b);
        static bool IsBindingReleased(const Binding& b);
    };

    // manager: handle multiple maps and an active one
    class InputActions
    {
    public:
        static InputActions& Get()
        {
            static InputActions g;
            return g;
        }

        ActionMap& CreateMap(const std::string& mapName);
        bool HasMap(const std::string& mapName) const;
        ActionMap* GetMap(const std::string& mapName);
        void SetActiveMap(const std::string& mapName);
        ActionMap* GetActiveMap();

        // convenience wrappers for scripting/imgui
        bool GetActionPressed(const std::string& name);
        bool GetActionDown(const std::string& name);
        bool GetActionReleased(const std::string& name);

        // call each frame
        void Update();

        // coroutine/timer hook (optional; wire to your engine scheduler)
        using WaitSecondsFn = std::function<void(double seconds)>;
        void SetWaitFunction(WaitSecondsFn fn) { waitFn = std::move(fn); }
        void WaitForSeconds(double seconds) { if (waitFn) waitFn(seconds); }

    private:
        std::unordered_map<std::string, ActionMap> maps;
        std::string active;

        WaitSecondsFn waitFn{};
    };
}
