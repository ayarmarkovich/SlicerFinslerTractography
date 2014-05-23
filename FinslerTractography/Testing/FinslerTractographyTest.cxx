#include <iostream>
#include "itkTestMain.h"

void RegisterTests()
{
  REGISTER_TEST(FinslerTractographyTest);
}

#undef main
#define main FinslerTractographyTest
#include "../FinslerTractography.cxx"
