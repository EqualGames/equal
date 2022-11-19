#pragma once

#ifdef EQ_DLL_EXPORT
#define EQ_EXPORT __declspec(dllexport)
#else
#define EQ_EXPORT
#endif
