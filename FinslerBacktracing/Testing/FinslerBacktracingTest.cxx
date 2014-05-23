#include <iostream>
#include "itkTestMain.h"

void RegisterTests()
{
  REGISTER_TEST(FinslerBacktracingTest);
}

#undef main
#define main FinslerBacktracingTest
#include "../FinslerBacktracing.cxx"
