#pragma once
#include "Core.hpp"
#include "Utility.hpp"

//TODO: Add other shapes
//TODO: Comments

namespace Cr {

	class Shape
	{
	public:

		/// \brief Create a new shape (ctor)
		/// \param Point position : the position of the shape on the screen
		/// \param Point size : the size of the shape
		/// \param Color color : the color of the shape
		/// \param ID2D1HwndRenderTarget *renderTarget : the render target of the window
		Shape(Point position, Point size, Color color, ID2D1HwndRenderTarget *renderTarget);

		/// \brief Destructor of the class
		~Shape();

		/// \brief Get the position of the shape
		/// \return Point : the position
		Point GetPosition();

		/// \brief Get the color of the shape
		/// \return Color : the color
		Color GetColor();

		/// \brief Get the geometry of the shape
		/// \return ID2D1Geometry* : the geometry
		ID2D1Geometry *GetGeometry();

		/// \brief Get the brush of the shape
		/// \return ID2D1SolidColorBrush* : the brush
		ID2D1SolidColorBrush *GetBrush();

		/// \brief Set the position of the shape
		/// \param Point position : the position
		virtual void SetPosition(Point position);

		/// \brief Set the color of the shape
		/// \param Color color : the color
		virtual void SetColor(Color color);

	protected:

		/// \brief position of the shape
		Point m_position;

		/// \brief size of the shape
		Point m_size;

		/// \brief color of the shape
		Color m_color;

		/// \brief geometry of the shape
		ID2D1Geometry *m_geometry;

		/// \brief brush of the shape
		ID2D1SolidColorBrush *m_brush;

		/// \brief factory
		ID2D1Factory *m_factory;

		/// \brief render target
		ID2D1HwndRenderTarget *m_renderTarget;

	};


	class RectangleShape : public Shape
	{
	//TODO: Add fill fonctionnality
	public:
		RectangleShape(Point position, Point size, Color color, ID2D1HwndRenderTarget *renderTarget, ID2D1Factory *factory);
		RectangleShape(Vector2<Point> pt, Color color, ID2D1HwndRenderTarget *renderTarget, ID2D1Factory *factory);
		void SetPosition(Point position) override;
		void SetColor(Color color) override;
		
	private:

	};

}