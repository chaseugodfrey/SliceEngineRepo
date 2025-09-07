#pragma once

#ifdef SLICESCRIPTAPI_EXPORTS
#define SLICESCRIPTAPI_API __declspec(dllexport)
#else
#define SLICESCRIPTAPI_API __declspec(dllimport)
#endif

using namespace System;

namespace ScriptAPI {
    public ref class Bridge {
    public:
        static void Hello() {
            Console::WriteLine("Hello from C++/CLI!");
        }
    };
}
