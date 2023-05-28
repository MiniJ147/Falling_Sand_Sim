#pragma once
#include <iostream>
#include <vector>

typedef uint8_t U8;
typedef uint16_t U16;
typedef uint32_t U32;
typedef uint64_t U64;

#define DEBUG_MODE 1

#if DEBUG_MODE == 1
#define LOG(x) std::cout << x << std::endl
#else
#define LOG(x)
#endif

struct Vec2f
{
	float x;
	float y;
};

inline void debug_error_print(const char* file, const char* func, const char* msg)
{
	if (DEBUG_MODE == 0)
		return;

	printf("=====ERROR=====\n");
	printf("FILE: %s\nFUNCTION: %s\nMSG: %s\n===============\n", file, func, msg);
}

inline void bubble_sort(std::vector<U32>& ids)
{
	if (ids.size() == 1 || ids.size() == 0)
	{
		debug_error_print("utils.h", "bubble_sort", "Cannot sort a size of 1 or 0 array");
		return;
	}

	bool sorted = false;
	while (!sorted)
	{
		sorted = true;
		for (int i = 0; i < ids.size()-1; ++i)
		{
			if (ids[i] > ids[i + 1])
			{
				int temp = ids[i + 1];
				ids[i + 1] = ids[i];
				ids[i] = temp;
				sorted = false;
			}
		}
	}
}

//U32 version
inline U32 binary_search(std::vector<U32> ids, U32 id, U32 lower, U32 upper)
{
	int i_mid = (lower + upper) / 2;

	if (lower > upper)
		return -1;

	if (ids[i_mid] > id)
	{
		return binary_search(ids, id, lower, i_mid - 1);
	}
	if (ids[i_mid] < id)
	{
		return binary_search(ids, id, i_mid + 1, upper);
	}

	return i_mid;
}