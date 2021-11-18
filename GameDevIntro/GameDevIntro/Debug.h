#pragma once


#define _W(x)  __W(x)
#define __W(x)  L##x

#define VA_PRINTS(s) {				\
		va_list argp;				\
		va_start(argp, fmt);		\
		vswprintf_s(s, fmt, argp);	\
		va_end(argp);				\
}	

class Debug
{
private:
    Debug() {}

public:

    static void DebugOutTitle(const wchar_t* fmt, ...);
    static void DebugOut(const wchar_t* fmt, ...);

};

