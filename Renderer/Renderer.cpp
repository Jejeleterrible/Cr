#include "Renderer.hpp"



using namespace Cr;

Cr::Renderer::Renderer()
{
	m_window_handle = (HWND*)GetConsoleWindow();

	m_factory = nullptr;
	m_render_target = nullptr;

	Init(*m_window_handle);

}

Cr::Renderer::~Renderer()
{
	if (m_render_target)
		m_render_target->Release();

	if (m_factory)
		m_factory->Release();
}


Renderer::Renderer(Window &window)
{
	m_window_handle = window.GetHandle();

	m_factory = window.GetFactory();
	m_render_target = window.GetRenderTarget();

}


std::shared_ptr<Cr::Renderer> Cr::Renderer::New()
{
	Renderer *ren = new Renderer();
	std::shared_ptr<Renderer> sh;
	sh.reset(ren);

	return sh;
}


std::shared_ptr<Cr::Renderer> Cr::Renderer::New(Window &window)
{
	Renderer *ren = new Renderer(window);
	std::shared_ptr<Renderer> sh;
	sh.reset(ren);

	return sh;
}


void Renderer::DrawLine(Point & p1, Point & p2, const Color & color)
{
	BeginDraw();

	ID2D1SolidColorBrush *brush;
	m_render_target->CreateSolidColorBrush(D2D1::ColorF(color.r, color.g, color.b, color.a), &brush);
	m_render_target->DrawLine(D2D1::Point2F((float)p1.x, (float)p1.y), D2D1::Point2F((float)p2.x, (float)p2.y), brush);

	brush->Release();

	EndDraw();
}


void Renderer::DrawRect(Point & p1, Point & p2, const Color & color, bool filled)
{
	BeginDraw();

	ID2D1SolidColorBrush *brush;
	m_render_target->CreateSolidColorBrush(D2D1::ColorF(color.r, color.g, color.b, color.a), &brush);
	
	if (!filled)
		m_render_target->DrawRectangle(D2D1::RectF((float)p1.x, (float)p1.y, (float)p2.x, (float)p2.y), brush);
	else
		m_render_target->FillRectangle(D2D1::RectF((float)p1.x, (float)p1.y, (float)p2.x, (float)p2.y), brush);

	brush->Release();

	EndDraw();
}


void Renderer::DrawRect(Point & tlc, Uint32 width, Uint32 height, const Color & color, bool filled)
{
	BeginDraw();

	ID2D1SolidColorBrush *brush;
	m_render_target->CreateSolidColorBrush(D2D1::ColorF(color.r, color.g, color.b, color.a), &brush);

	if (!filled)
		m_render_target->DrawRectangle(D2D1::RectF((float)tlc.x, (float)tlc.y, (float)tlc.x + width, (float)tlc.y + height), brush);
	else
		m_render_target->FillRectangle(D2D1::RectF((float)tlc.x, (float)tlc.y, (float)tlc.x + width, (float)tlc.y + height), brush);

	brush->Release();

	EndDraw();
}


void Renderer::DrawEllipsis(Point & p1, Point & p2, const Color & color, bool filled)
{
	
	Point center{p1.x+p2.x/2, p1.y+p2.y/2};
	float radiusX = p2.x / 2;
	float radiusY = p2.y / 2; 
	
	BeginDraw();

	ID2D1SolidColorBrush *brush;
	m_render_target->CreateSolidColorBrush(D2D1::ColorF(color.r, color.g, color.b, color.a), &brush);

	if (!filled)
		m_render_target->DrawEllipse(D2D1::Ellipse(D2D1::Point2F((float)center.x, (float)center.y), radiusX, radiusY), brush);
	else
		m_render_target->FillEllipse(D2D1::Ellipse(D2D1::Point2F((float)center.x, (float)center.y), radiusX, radiusY), brush);

	brush->Release();

	EndDraw();
}

void Cr::Renderer::DrawBitmap(Bitmap & bmp, Point & pos)
{
	if (bmp.m_bmp == nullptr)
		return;

	BeginDraw();

	D2D1_SIZE_F size = bmp.m_bmp->GetSize();
	D2D1_POINT_2F upperLeftCorner = D2D1::Point2F(100.f, 10.f);
	// Draw a bitmap.
	m_render_target->DrawBitmap(
		bmp.m_bmp,
		D2D1::RectF(
			pos.x,
			pos.y,
			pos.x + size.width,
			pos.y + size.height)
	);

	EndDraw();
}


void Cr::Renderer::Clear(const Color & color)
{
	BeginDraw();
	m_render_target->Clear(D2D1::ColorF(color.r, color.g, color.b, color.a));
	EndDraw();
}


void Cr::Renderer::Init(HWND handleWindow)
{
	HRESULT result = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_factory);

	if(result != S_OK)
	{
		std::cerr << "Error while creating the factory" << std::endl;
	}

	RECT rect;
	GetClientRect(*m_window_handle, &rect);

	result = m_factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(*m_window_handle, D2D1::SizeU(rect.right, rect.bottom)), &m_render_target);

	if (result != S_OK)
	{
		std::cerr << "Error while creating the render target" << std::endl;
	}
}

void Cr::Renderer::Draw(Shape & shape)
{
	BeginDraw();
	m_render_target->DrawGeometry(shape.GetGeometry(), shape.GetBrush());
	EndDraw();
}

