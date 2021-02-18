#pragma once
#include <cassert>

#define RETURN(expression) {if (expression) {return;}}
#define RETURN_FALSE(expression) {if (!(expression)) {return false;}}

#define NULLPTR_RETURN(p) {if ((p) == nullptr) {return;}}

#ifndef ALIGN
#define ALIGN(x, a) (((x) + ((a) - 1)) & ~((a) - 1))
#endif

#if defined(_DEBUG) || defined(DEBUG)
#ifndef ENGINE_DEBUG
#define ENGINE_DEBUG
#endif
#endif