#include "Color_RGBA.h"

inline void Color_RGBA::SetRGB(byte r, byte g, byte b)
{
	rgba[0] = r;
	rgba[1] = g;
	rgba[2] = b;
}

inline void Color_RGBA::SetA(byte a)
{
	rgba[3] = a;
}

inline byte & Color_RGBA::operator[](int i)
{
	if (i > 3) throw(1);
	return rgba[i];
}
