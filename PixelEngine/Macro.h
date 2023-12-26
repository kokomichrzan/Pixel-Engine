#pragma once

//######################## DEBUG ########################//

#ifdef PE_DEBUG
#include <iostream>

#define LOGMacro(x) std::cout << x << std::endl


#endif

//######################## DEBUG ########################//

#ifdef PE_RELEASE

#define LOGMacro(x) 

#endif