#pragma once
#include "Core.hpp"


namespace Cr
{

	struct Color
		/// \brief A structure that represents a RGBA color
	{
		Uint8 r;
		Uint8 g;
		Uint8 b;
		Uint8 a;
	};

	const Color White{ 255, 255, 255, 255 };
	const Color Black{ 0, 0, 0, 255 };
	const Color Red{ 255, 0, 0, 255 };
	const Color Green{ 0, 255, 0, 255 };
	const Color Blue{ 0, 0, 255, 255 };

	struct Point
		/// \brief A structure that represents a point with 2D coordinates
	{
		Coord x;
		Coord y;
	};

	template <class T>
	struct Vector2
		/// \brief A structure with 2 fields of the templated type
	{
		T x;
		T y;
	};

	/// \brief Convert strings to wide strings
	/// \param const std::string &s : the string
	/// \return std::wstring : the wide string
	inline std::wstring s2ws(const std::string& s)
	{
		int len;
		int slength = (int)s.length() + 1;
		len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
		wchar_t* buf = new wchar_t[len];
		MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
		std::wstring r(buf);
		delete[] buf;
		return r;
	}

};