#pragma once

#ifdef DEBUG
#define LOG(x) std::cout<< x <<std::endl;
#else
#define LOG(x)
#endif
