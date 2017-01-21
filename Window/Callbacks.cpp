#include "Window.hpp"

using namespace Cr;


LRESULT CALLBACK Window::callback(HWND window, UINT msg, WPARAM wParam, LPARAM lParam)
{

	static Window* win = nullptr;

	if (msg == WM_NCCREATE || msg == WM_CREATE)
	{
		SetWindowLong(window, GWL_USERDATA, (long)(LPCREATESTRUCT(lParam))->lpCreateParams);
		win = (Window*)GetWindowLong(window, GWL_USERDATA);
	}


	switch (msg)
	{

	case WM_CREATE:
		return 0;

	case WM_MOUSEMOVE:
		if (win != nullptr)
		{
			win->m_render_target->BeginDraw();
			win->m_render_target->Clear(D2D1::ColorF(0, 0, 0));
			win->m_render_target->EndDraw();
		}
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return DefWindowProc(window, msg, wParam, lParam);

	case WM_PAINT:

		/*if(win != nullptr)
		{
		win->m_render_target->BeginDraw();
		win->m_render_target->Clear(D2D1::ColorF(0, 0, 0));
		win->m_render_target->EndDraw();
		}*/
		return 0;

	case WM_LBUTTONDOWN:

		if (win->m_LBCallback.function)
			win->m_LBCallback.function(win, win->GetMousePosition(), win->m_LBCallback.data);
		return 0;

	case WM_RBUTTONDOWN:

		if (win->m_RBCallback.function)
			win->m_RBCallback.function(win, win->GetMousePosition(), win->m_RBCallback.data);
		return 0;

	case WM_MBUTTONDOWN:

		if (win->m_MBCallback.function)
			win->m_MBCallback.function(win, win->GetMousePosition(), win->m_MBCallback.data);
		return 0;


	default:
		return DefWindowProc(window, msg, wParam, lParam);

	}
}

void Cr::Window::OnLMouseButtonDown(void(*func)(Window *, Point, void *), void *data)
{
	m_LBCallback.function = func;
	m_LBCallback.data = data;
}

void Cr::Window::OnRMouseButtonDown(void(*func)(Window *, Point, void *), void *data)
{
	m_RBCallback.function = func;
	m_RBCallback.data = data;
}

void Cr::Window::OnMMouseButtonDown(void(*func)(Window *, Point, void *), void *data)
{
	m_MBCallback.function = func;
	m_MBCallback.data = data;
}