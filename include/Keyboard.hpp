#pragma once
#include "Core.hpp"


namespace Cr 
{
	class Keyboard
	{
	public:

		enum Keys
		{
			A = 'a',B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z, /*Letters*/
			N1 = '1', N2, N3, N4, N5, N6, N7, N8, N9, N0,			   /*Numbers*/
			Escape=0x1b
		};

		static inline Uint8 GetKey()
		{
			return _getch();
		};
	};
};