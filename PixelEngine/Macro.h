#pragma once

//######################## DEBUG ########################//

#ifdef PE_DEBUG
#include <iostream>

#define LOG(x) std::cout << x << std::endl


#endif

//######################## DEBUG ########################//

#ifdef PE_RELEASE

#define LOG(x) 

#endif