#include <Renderer.hpp>
#include <Keyboard.hpp>
#include <Core.hpp>


int main()
{
	
	Cr::Window win = Cr::Window("test", 1024, 768);
	Cr::RendererHandle ren = Cr::Renderer::New(win);

	Cr::RectangleShape rect(Cr::Point{ 10, 10 }, Cr::Point{ 1000, 100 }, Cr::Color{ 255, 0, 0, 255 }, win.GetRenderTarget(), win.GetFactory());	
	Cr::RectangleShape rect2(Cr::Vector2<Cr::Point>{Cr::Point{10, 110}, Cr::Point{100, 200}}, Cr::Color{ 0, 255, 0, 255 }, win.GetRenderTarget(), win.GetFactory());

	while (win.Display())
	{
		ren->Draw(rect);
		ren->Draw(rect2);
	}

	return 0;
}
