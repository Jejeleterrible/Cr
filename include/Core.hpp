#pragma once
#include <iostream>
#include <memory>
#include <windows.h>
#include <iomanip>
#include <vector>
#include <conio.h>
#include <d2d1.h>
#include <wincodec.h>

using Uint32 = uint32_t;
using Uint16 = uint16_t;
using Uint8 = uint8_t;
using Coord = float;


template <class T> void SafeRelease(T **ppT)
{
	if (*ppT)
	{
		(*ppT)->Release();
		*ppT = NULL;
	}
}

