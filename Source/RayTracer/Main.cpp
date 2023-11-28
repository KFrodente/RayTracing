#include <iostream>
#include "Renderer.h"
#include "Random.h"
#include "Canvas.h"

int main(int argc, char**)
{
	seedRandom((unsigned int)time(nullptr));

	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("Window", 1980, 1080);

	Canvas canvas(1980, 1080, renderer);


	bool quit = false;
	while (!quit)
	{
		canvas.Clear({ 0, 0, 0, 1 });
		for (int i = 0; i < 100000; i++)
		{
			canvas.DrawPoint({ random(0, 1980), random(0, 1080) }, { random(0.0f, 1.0f), random(0.0f, 1.0f), random(0.0f, 1.0f), 1 });
		}
		canvas.Update();
		renderer.PresentCanvas(canvas);
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