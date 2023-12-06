#include <iostream>
#include "Renderer.h"
#include "Random.h"
#include "Canvas.h"
#include "Camera.h"
#include "Scene.h"
#include "Material.h"
#include "Sphere.h"
#include "Plane.h"
#include "Triangle.h"
#include <glm/gtx/color_space.hpp>

int main(int argc, char**)
{
	seedRandom((unsigned int)time(nullptr));

	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("Window", 800, 800);

	Canvas canvas(800, 800, renderer);

	float aspectRatio = canvas.GetSize().x / (float)canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 1, 10 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, 20.0f, aspectRatio);

	Scene scene(/*glm::vec3{1.0f}, glm::vec3{ 0.5f, 0.7f, 1.0f}, */8); // sky color could be set with the top and bottom color
	scene.SetCamera(camera);

		

	// create material
	auto material = std::make_shared<Lambertian>(color3_t{ 0, 0, 1 });

	// create material
	auto metal = std::make_shared<Metal>(color3_t{ 1, 1, 1 }, 0.0f);

	// create objects -> add to scene
	/*for (int i = 0; i < 35; i++)
	{
		auto lambertian = std::make_shared<Lambertian>(color3_t{ random(.5f, 1.0f), random(.5f, 1.0f), random(.5f, 1.0f) });
		std::shared_ptr<Material> material = (int(random(0, 100)) >= 25) ? std::dynamic_pointer_cast<Material>(lambertian) : std::dynamic_pointer_cast<Material>(metal);
		auto sphere = std::make_unique<Sphere>(random({ -10, -5, -15 }, { 10, 5, -5 }), random01() * 3, material);
		scene.AddObject(std::move(sphere));
	}*/

	//auto lambertian = std::make_shared<Lambertian>(color3_t{ random(.5f, 1.0f), random(.5f, 1.0f), random(.5f, 1.0f) });
	//auto triangle = std::make_unique<Triangle>(glm::vec3{ -1, 1, 1 }, glm::vec3{ 1, 1, 1 }, glm::vec3{ 1.5f, 2, 1 }, lambertian);
	//scene.AddObject(std::move(triangle));
	
	for (int x = -10; x < 10; x++)
	{
		for (int z = -10; z < 10; z++)
		{

			std::shared_ptr<Material> material;

			// create random material
			float r = random01();
			if (r < 0.3f)		material = std::make_shared<Lambertian>(glm::rgbColor(glm::vec3{ random(0, 360), 1.0f, 1.0f }));
			else if (r < 0.6f)	material = std::make_shared<Metal>(color3_t{ random(0.5f, 1.0f) }, random(0, 0.5f));
			else if (r < 0.9f)	material = std::make_shared<Dielectric>(color3_t{ 1.0f }, random(1.1f, 2));
			else				material = std::make_shared<Emissive>(glm::rgbColor(glm::vec3{ random(0, 360), 1.0f, 1.0f }), 5.0f);

			// set random sphere radius
			float radius = random(0.2f, 0.3f);
			// create sphere using random radius and material
			auto sphere = std::make_unique<Sphere>(glm::vec3{ x + random(-0.5f, 0.5f), radius, z + random(-0.5f, 0.5f) }, radius, material);
			// add sphere to the scene
			scene.AddObject(std::move(sphere));
		}
	}

	material = std::make_shared<Lambertian>(color3_t{ 0.2f });
	auto plane = std::make_unique<Plane>(glm::vec3{ 0, -3, 0 }, glm::vec3{ 0, 1, 0 }, material);
	scene.AddObject(std::move(plane));
		
	canvas.Clear({ 0, 0, 0, 1 });
	scene.Render(canvas, 10);
	canvas.Update();

	bool quit = false;
	while (!quit)
	{
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