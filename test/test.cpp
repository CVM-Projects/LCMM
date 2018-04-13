#include "lcmm.h"
#include <cstdio>
#include <cstdlib>

void* test_alloc(int n)
{
	std::printf("Alloc %d\n", n);
	return new int(n);
}

void test_free(void *ptr)
{
	std::printf("Free %d\n", *(int*)ptr);
	std::free(ptr);
}

struct DynamicObject
{
	LCMM::Info *lcmm_info = nullptr;
	void *data = nullptr;
};

int main()
{
	DynamicObject do1;
	do1.data = test_alloc(1);
}
