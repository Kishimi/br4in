#pragma once

#include <cassert>

using i8 = char;
using i32 = int;
using i64 = long long int;

using u8 = unsigned char;
using u32 = unsigned int;
using u64 = unsigned long long int;

using s8 = signed char;
using s32 = signed int;

using Byte = i8;
using uByte = u8;

#if defined DEBUG
#define BR4IN_ASSERT(x) assert(x)
#else
#define BR4IN_ASSERT(x)
#endif
