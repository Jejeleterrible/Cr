#pragma once
#include "Core.hpp"
#include "Window.hpp"
#include "Bitmap.hpp"
#include "Shape.hpp"



namespace Cr 
{

	
	class Renderer
		/// \brief This class is very important. It is used to display shapes and images. It's the center of the lib
		/// \author Jeremy BOURDILLAT
		/// \version 0.2
	{
	public:
		/// \brief The default constructor
		Renderer();

		/// \brief The default destructor
		~Renderer();

		/// \brief A constructor that takes the window to display in
		/// \param HWND window : a handle to a winapi window
		Renderer(Window &window);

		/// \brief Default constructor for Handles
		/// \return a shared pointer to a renderer
		static std::shared_ptr<Renderer> New();

		/// \brief Constructor for handles with the window to display in
		/// \param HWND window : a handle to a winapi window
		/// \return a shared pointer to a renderer
		static std::shared_ptr<Renderer> New(Window &window);

		/// \brief Draw a line on the surface
		/// \param Point &p1 : the first point, the beginning of the line
		/// \param Point &p2 : the second point, the end of the line
		/// \param Color &color : the color of the line
		void DrawLine(Point &p1, Point &p2, const Color &color);

		/// \brief Draw a rectangle on the surface
		/// \param Point &p1 : the first point, the top left corner
		/// \param Point &p2 : the second point, the bottom right corner
		/// \param Color &color : the color of the rectangle
		/// \param bool filled : choose if the rect will be filled or not
		void DrawRect(Point &p1, Point &p2, const Color &color, bool filled = false);

		/// \brief Draw a rectangle on the surface
		/// \param Point &tlc : the top left corner
		/// \param Uint32 width : the width of the rectangle
		/// \param Uint32 height : the height of the rectangle
		/// \param Color &color : the color of the rectangle
		/// \param bool filled : choose if the rect will be filled or not
		void DrawRect(Point &tlc, Uint32 width, Uint32 height, const Color &color, bool filled = false);

		/// \brief Draw an ellipsis on the surface
		/// \param Point &p1 : the first point, the top left corner
		/// \param Point &p2 : the second point, the bottom right corner
		/// \param Color &color : the color of the ellipsis
		/// \param bool filled : choose if the ellipsis will be filled or not
		void DrawEllipsis(Point &p1, Point &p2, const Color &color, bool filled = false);

		/// \brief Draw a bitmap image
		/// \param Bitmap &bmp : the bitmap
		/// \param Point &pos : position of the bitmap on the screen
		void DrawBitmap(Bitmap &bmp, Point &pos);

		/// \brief Clear the screen with the given color
		/// \param const Color &color : the color to clear with
		void Clear(const Color &color = Black);

		/// \brief Signal to Direct2D we are getting to draw
		void BeginDraw() { m_render_target->BeginDraw(); }

		/// \brief Signal to Direct2D that we have finished to draw
		void EndDraw() { m_render_target->EndDraw(); }

		/// \brief Initialize Direct2D
		/// \param HWND handleWindow : the window to display in
		/// \warning Used by the class itself, don't use it yourself !
		void Init(HWND handleWindow);

		/// \brief Draw a Shape
		/// \param Shape &shape : the shape to render
		void Draw(Shape &shape);


	private:

		/// \brief a pointer to a Window Handle from winapi
		HWND *m_window_handle;

		/// \brief A pointer to a Direct2D factory
		ID2D1Factory *m_factory;

		/// \brief A pointer to a Direct2D RenderTarget
		ID2D1HwndRenderTarget *m_render_target;

	};

	/// \brief A using to a shared pointer of a renderer
	using RendererHandle = std::shared_ptr<Renderer>;

};