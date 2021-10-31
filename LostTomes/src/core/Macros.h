#pragma once


#ifdef LTOMES_PLATFORM_WINDOWS

#endif


#ifdef LTOMES_DEBUG

#endif

#ifdef LTOMES_RELEASE

#endif


#define C_RED "\033[91m"
#define C_GREEN "\033[92m"
#define C_YELLOW "\033[93m"
#define C_BLUE "\033[94m"
#define C_CYAN "\033[96m"

#define C_RESET "\033[0m"


#define LOG_ERROR(message) std::cout << C_RED << "--------------------\nERROR: " << message << "\n--------------------" << std::endl << C_RESET