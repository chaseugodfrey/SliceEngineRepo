#ifdef SLICESCRIPTAPI_EXPORTS
#define SLICESCRIPTAPI_API __declspec(dllexport)
#else
#define SLICESCRIPTAPI_API __declspec(dllimport)
#endif