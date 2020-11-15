#pragma once

#define RETURN(expression) {if (expression) {return;}}
#define RETURN_FALSE(expression) {if (!(expression)) {return false;}}

#define NULLPTR_RETURN(p) {if ((p) == nullptr) {return;}}

#undef ASSERT
#define ASSERT(expression) {assert(expression);};

#ifndef ALIGN
#define ALIGN(x, a) (((x) + ((a) - 1)) & ~((a) - 1))
#endif