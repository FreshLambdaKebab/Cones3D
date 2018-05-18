#include "Window.h"

#include <iostream>
#include <GL\glew.h>

Window::Window(int width, int height, const std::string& title):
	m_window(nullptr),
	m_glContext(nullptr),
	m_isClosed(false)
{
	//initializ sdl
	SDL_Init(SDL_INIT_EVERYTHING);

	//set opengl attributes
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	//create sdl window & glcontext
	m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | 
	SDL_WINDOW_RESIZABLE);
	if (m_window == nullptr) {
		printf("could not create sdl window %s\n", SDL_GetError());
	}

	m_glContext = SDL_GL_CreateContext(m_window);
	if (m_glContext == nullptr) {
		printf("could not create sdl gl context %s\n", SDL_GetError());
	}

	//initialize glew
	GLenum status = glewInit();
	if (status != GLEW_OK) {
		std::cerr << "glew failed to be initialized\n";
	}

	//check and print ogl version
	printf("**** OpenGL Version: %s ****\n", glGetString(GL_VERSION));
}

Window::~Window()
{
	//delete and release sdl/opengl shit
	SDL_GL_DeleteContext(m_glContext);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void Window::Render(float red, float green, float blue, float alpha)
{
	//clear window display color
	glClearColor(red, green, blue, alpha);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Window::Update()
{
	SwapBuffers();

	SDL_Event windowEvent;

	while (SDL_PollEvent(&windowEvent)) 
	{
		switch (windowEvent.type)
		{
		case SDL_QUIT:
			m_isClosed = true;
		}

		//check if user has pressed escaped to exit window
		if (windowEvent.type == SDL_KEYDOWN && windowEvent.key.keysym.sym == SDLK_ESCAPE)
		{
			m_isClosed = true;
		}
	}
}

bool Window::Shutdown()
{
	return m_isClosed;
}

void Window::SwapBuffers()
{
	SDL_GL_SwapWindow(m_window);
}
