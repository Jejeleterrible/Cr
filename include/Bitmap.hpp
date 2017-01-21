#pragma once
#include "Core.hpp"
#include "Utility.hpp"


namespace Cr
{

	class Bitmap
	{
	public:
		void LoadFromFile(const std::string &filename, ID2D1DCRenderTarget *pRenderTarget);


	//private:
		ID2D1Bitmap *m_bmp;
	};


	using BitmapHandle = std::shared_ptr<Bitmap>;

};
