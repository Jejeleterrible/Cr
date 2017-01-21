#include "Shape.hpp"

using namespace Cr;


Cr::Shape::Shape(Point position, Point size, Color color, ID2D1HwndRenderTarget *renderTarget)
{
	m_position = position;
	m_size = size;
	m_color = color;
	m_renderTarget = renderTarget;

	renderTarget->CreateSolidColorBrush(D2D1::ColorF(color.r, color.g, color.b, color.a), &m_brush);
}

Shape::~Shape()
{
}

Point Cr::Shape::GetPosition()
{
	return m_position;
}

Color Cr::Shape::GetColor()
{
	return m_color;
}

ID2D1Geometry * Cr::Shape::GetGeometry()
{
	return m_geometry;
}

ID2D1SolidColorBrush * Cr::Shape::GetBrush()
{
	return m_brush;
}

void Cr::Shape::SetPosition(Point position)
{
	m_position = position;
}

void Cr::Shape::SetColor(Color color)
{
	m_color = color;
}

Cr::RectangleShape::RectangleShape(Point position, Point size, Color color, ID2D1HwndRenderTarget * renderTarget, ID2D1Factory *factory) : Shape(position, size, color, renderTarget)
{	
	factory->CreateRectangleGeometry(D2D1::RectF(position.x, position.y, position.x + size.x, position.y + size.y), (ID2D1RectangleGeometry**)&m_geometry);
	m_factory = factory;
}

void Cr::RectangleShape::SetPosition(Point position)
{
	SetPosition(position);
	m_factory->CreateRectangleGeometry(D2D1::RectF(position.x, position.y, position.x + m_size.x, position.y + m_size.y), (ID2D1RectangleGeometry**)&m_geometry);
}

void Cr::RectangleShape::SetColor(Color color)
{
	SetColor(color);
	m_renderTarget->CreateSolidColorBrush(D2D1::ColorF(color.r, color.g, color.b, color.a), &m_brush);
}

Cr::RectangleShape::RectangleShape(Vector2<Point> pt, Color color, ID2D1HwndRenderTarget * renderTarget, ID2D1Factory *factory) : Shape(pt.x, Point{ pt.x.x + pt.y.x, pt.x.y + pt.y.y }, color, renderTarget)
{
	factory->CreateRectangleGeometry(D2D1::RectF(pt.x.x, pt.x.y, pt.y.x, pt.y.y), (ID2D1RectangleGeometry**)&m_geometry);
	m_factory = factory;
}