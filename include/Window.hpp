#pragma once
#include "Core.hpp"
#include "Utility.hpp"

namespace Cr
{

	class Window
	/// \brief Class that represents a Window
	/// \author Jeremy BOURDILLAT
	/// \version 0.2
	{
	public:

		/// \brief Constructor of the Window class
		/// \param const std::string &title : the title of the window
		/// \param int width : the width of the window
		/// \param int height : the height of the window
		Window(const std::string &title, int width = 800, int height = 600);

		/// \brief Display the window
		/// \return a boolean to say if the window has to be displayed or not
		/// \warning May be used in a while loop, as the condition
		bool Display();

		/// \brief Get the handle of the window, as a HWND from winAPI
		/// \return HWND* : the handle
		HWND *GetHandle();

		/// \brief Get the factory of the window, to draw on it
		/// \return ID2D1Factory * : the factory
		ID2D1Factory *GetFactory();

		/// \brief Get the Render Target of the window, to draw on it
		/// \return ID2D1HwndRenderTarget * : the Render Target
		ID2D1HwndRenderTarget *GetRenderTarget();

		/// \brief Get the position of the mouse on the window
		/// \return Point : the mouse position on the window
		Point GetMousePosition();

		/// \brief Set the callback for the LEFT mouse button
		/// \param void (*func)(Window *, Point, void *) : the function
		/// \param void *data : a generic pointer to get another object
		void OnLMouseButtonDown(void (*func)(Window *, Point, void *), void *data = nullptr);

		/// \brief Set the callback for the RIGHT mouse button
		/// \param void (*func)(Window *, Point, void *) : the function
		/// \param void *data : a generic pointer to get another object
		void OnRMouseButtonDown(void(*func)(Window *, Point, void *), void *data = nullptr);

		/// \brief Set the callback for the MIDDLE mouse button
		/// \param void (*func)(Window *, Point, void *) : the function
		/// \param void *data : a generic pointer to get another object
		void OnMMouseButtonDown(void(*func)(Window *, Point, void *), void *data = nullptr);

		/// \brief Close the window, and more often, close the application
		void Close();

		/// \brief Destructor of the class
		~Window();


	private:
		/// \brief the callback of the window
		/// \param HWND window : the current window
		/// \param UINT msg : the current message
		/// \param WPARAM wParam : the wparam
		/// \param LPARAM lParam : the lparam
		/// \return LRESULT : the result
		static LRESULT CALLBACK callback(HWND window, UINT msg, WPARAM wParam, LPARAM lParam);

		/// \brief Handle to the window
		HWND m_window;

		/// \brief Message of the window
		MSG m_message;

		/// \brief Class of the window
		WNDCLASSEX m_window_class;

		/// \brief A pointer to a Direct2D factory
		ID2D1Factory *m_factory;

		/// \brief A pointer to a Direct2D RenderTarget
		ID2D1HwndRenderTarget *m_render_target;

		/// \brief Structure wich contains the callback for the LEFT mouse button
		struct
		{
			void(*function)(Window *, Point, void *);
			void *data;
		}m_LBCallback;

		/// \brief Structure wich contains the callback for the RIGHT mouse button
		struct
		{
			void(*function)(Window *, Point, void *);
			void *data;
		}m_RBCallback;

		/// \brief Structure wich contains the callback for the MIDDLE mouse button
		struct
		{
			void(*function)(Window *, Point, void *);
			void *data;
		}m_MBCallback;

	};

};