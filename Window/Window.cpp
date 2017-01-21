#include "Window.hpp"

using namespace Cr;

Window::Window(const std::string &title, int width, int height)
{

	ZeroMemory(&m_window_class, sizeof(WNDCLASSEX));

	m_window_class.cbSize = sizeof(WNDCLASSEX);
	m_window_class.lpfnWndProc = callback;
	m_window_class.cbClsExtra = 0;
	m_window_class.cbWndExtra = 0;
	m_window_class.hInstance = nullptr;
	m_window_class.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	m_window_class.hCursor = LoadCursor(nullptr, IDC_ARROW);
	m_window_class.hbrBackground = (HBRUSH)(1 + COLOR_BTNFACE);
	m_window_class.lpszMenuName = nullptr;
	m_window_class.lpszClassName = TEXT(title.c_str());
	m_window_class.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassEx(&m_window_class);

	RECT rect{ 0, 0, width, height };
	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, false, WS_EX_OVERLAPPEDWINDOW);

	m_window = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, TEXT(title.c_str()), TEXT(title.c_str()), WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, rect.right - rect.left, rect.bottom - rect.top,
		nullptr, nullptr, GetModuleHandle(nullptr), (void*)this);

	if (!m_window)
		std::cerr << "Error while trying to create the window" << std::endl;

	/*Creating factory and render target*/

	HRESULT result = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_factory);

	if (result != S_OK)
	{
		std::cerr << "Error while creating the factory" << std::endl;
	}

	RECT rect2;
	GetClientRect(m_window, &rect2);

	result = m_factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(m_window, D2D1::SizeU(rect2.right, rect2.bottom)), &m_render_target);

	if (result != S_OK)
	{
		std::cerr << "Error while creating the render target" << std::endl;
	}

	ShowWindow(m_window, SW_SHOW);
	UpdateWindow(m_window);

}


bool Window::Display()
{
	if (PeekMessage(&m_message, m_window, 0, 0, PM_REMOVE))
	{
		if (m_message.message == WM_QUIT || m_message.message == WM_DESTROY)
			return false;

		TranslateMessage(&m_message);
		DispatchMessage(&m_message);

		return true;
	}
	else
	{
		return false;
	}
}


HWND *Window::GetHandle()
{
	return  &m_window;
}

ID2D1Factory * Cr::Window::GetFactory()
{
	return m_factory;
}

ID2D1HwndRenderTarget * Cr::Window::GetRenderTarget()
{
	return m_render_target;
}

Point Cr::Window::GetMousePosition()
{
	POINT point;
	
	GetCursorPos(&point);
	ScreenToClient(m_window, &point);
	
	return Point{ (Coord)point.x, (Coord)point.y };
}

Window::~Window() 
{
	;
}

void Cr::Window::Close()
{
	DestroyWindow(m_window);
}
