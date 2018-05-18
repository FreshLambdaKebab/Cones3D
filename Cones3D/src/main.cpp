#include "Window.h"
#include <GL\glew.h>

int main()
{
	Window window(800, 600, "Tittle");

	//main loop
	while (!window.Shutdown())
	{
		//update and render the window
		window.Render(1.0f, 0.0f, 0.2f, 1.0f);
		window.Update();
	}

	return 0;
}
