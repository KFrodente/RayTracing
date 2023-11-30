#include <iostream>
#include "Renderer.h"
#include "Random.h"
#include "Canvas.h"
#include "Camera.h"
#include "Scene.h"
#include "Material.h"
#include "Sphere.h"

int main(int argc, char**)
{
	seedRandom((unsigned int)time(nullptr));

	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("Window", 1920, 1080);

	Canvas canvas(1920, 1080, renderer);

	float aspectRatio = canvas.GetSize().x / (float)canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 0, 1 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, 70.0f, aspectRatio);

	Scene scene; // sky color could be set with the top and bottom color
	scene.SetCamera(camera);

	// create material
	auto material = std::make_shared<Lambertian>(color3_t{ 0, 0, 1 });

	for (int i = 0; i < 15; i++)
	{
		// create objects -> add to scene
		auto sphere = std::make_unique<Sphere>(random({-5, -5, -15}, {5, 5, -5}), random01() * 3, material);
		scene.AddObject(std::move(sphere));

	}
		

	bool quit = false;
	while (!quit)
	{
		/*canvas.Clear({ 0, 0, 0, 1 });
		for (int i = 0; i < 100000; i++)
		{
			canvas.DrawPoint({ random(0, canvas.GetSize().x), random(0, canvas.GetSize().y) }, { random(0.0f, 1.0f), random(0.0f, 1.0f), random(0.0f, 1.0f), 1 });
		}*/
		canvas.Clear({ 0, 0, 0, 1 });
		scene.Render(canvas);
		canvas.Update();

		renderer.PresentCanvas(canvas);
		SDL_Event event;
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				quit = true;
				break;
			}
			break;
		}
	}

	renderer.Shutdown();

	return 0;
}