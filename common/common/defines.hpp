#ifndef LWE__SECURITY_INCLUDES_HPP__
#define LWE__SECURITY_INCLUDES_HPP__

#include "cstdint"
#include "stdexcept"

// Check OS
#if _WIN32 || _WIN64
#    if _WIN64
#        define X64
#    else
#        define X86
#    endif
#elif __GNUC__
#    if __x86_64__ || __ppc64__
#        define X64
#    else
#        define X86
#    endif
#else
#    error Unknown OS
#endif

#ifndef IN
#    define IN
#endif

#ifndef OUT
#    define OUT
#endif

#ifndef OPT
#    define OPT
#endif

#ifndef _SSIZE_T_DEFINED_
#    define _SSIZE_T_DEFINED_
#    ifdef X64
using ssize_t = int64_t;
#    else
using ssize_t = int32_t;
#    endif
#endif

#endif