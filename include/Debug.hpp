#ifndef DEBUG_HPP
#define DEBUG_HPP

#include "core/Common.hpp"

#if defined(_MSC_VER)
#define BREAK __debugbreak();
#else
#include <signal.h>
#define BREAK raise(SIGINT)
#endif

#define ASSERT(x)                                                              \
	if (!(x))                                                                  \
		BREAK;
#define GLCall(x)                                                              \
	GLClearError();                                                            \
	x;                                                                         \
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

#define DEBUG_LOG(category, level, message, ...)                               \
	fprintf(stderr, "[%s] ", category);                                        \
	fprintf(stderr, "[%s] (%s, %d): ", level, __FILE__, __LINE__);             \
	fprintf(stderr, message, ##__VA_ARGS__);                                   \
	fprintf(stderr, "\n")

void GLClearError();
bool GLLogCall(const char *function, const char *file, int32 line);

#endif // DEBUG_HPP
