#pragma once

#include <string>
#include <SDL\SDL.h>

class Window
{
public:
	Window(int width,int height,const std::string& title);
	~Window();

	void Render(float red,float green,float blue,float alpha);
	void Update();
	bool Shutdown();

	//getters
	SDL_Window* GetWindow()const { return m_window; }
	const SDL_GLContext& GetGLContext()const { return m_glContext; }

private:
	void SwapBuffers();

	Window(const Window& other){}
	Window& operator=(const Window& other){}

	SDL_Window* m_window;
	SDL_GLContext m_glContext;
	bool m_isClosed;
};

