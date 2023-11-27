#include <iostream>
#include "Renderer.h"

int main(int argc, char**)
{
	std::cout << "hello world";

	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("Window", 1980, 1080);

	bool quit = false;
	while (!quit)
	{
		SDL_Event event;
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		}
	}

	renderer.Shutdown();

	return 0;
}